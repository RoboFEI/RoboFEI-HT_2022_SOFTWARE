// Copyright 2021 ROBOTIS CO., LTD.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*******************************************************************************
// This example is written for DYNAMIXEL X(excluding XL-320) and MX(2.0) series with U2D2.
// For other series, please refer to the product eManual and modify the Control Table addresses and other definitions.
// To test this example, please follow the commands below.
//
// Open terminal #1
// $ ros2 run dynamixel_sdk_examples read_write_node
// ros2 topic pub -1 decision custom_interfaces/Decision "{decision: 1}"
//
// Open terminal #2 (run one of below commands at a time)
// $ ros2 topic pub -1 /set_position_single custom_interfaces/SetPositionOriginal "{id: 30, address: 116, position: 1000}"
// $ ros2 topic pub -1 /set_position custom_interfaces/SetPosition "{id: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, position: {2048, 2031, 2032, 2033, 2034, 2035, 2036, 2037, 2039, 2038, 2049, 2040, 2041, 2042, 2043, 2044, 2045, 2046, 2047, 2050}}"
// $ ros2 topic pub -1 /set_position custom_interfaces/SetPosition "{id: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, position: {2500, 1900, 2100, 2048, 2047, 2046, 2049, 2050, 2051, 2052, 2045, 2044}}"
// $ ros2 topic pub -1 /set_position custom_interfaces/SetPosition "{id: {1, 2, 5, 6}, position: {2500, 1900, 2048, 2048}}"
// $ ros2 service call /get_position custom_interfaces/srv/GetPosition "id: 1"
//
// Author: Will Son
*******************************************************************************/

#include <cstdio>
#include <memory>
#include <string>
#include <unistd.h>
#include <list>
#include <chrono>
#include <functional>

#include "dynamixel_sdk/dynamixel_sdk.h"
#include "custom_interfaces/msg/set_position.hpp"
#include "custom_interfaces/msg/set_position_original.hpp"
#include "custom_interfaces/srv/get_position.hpp"
#include "custom_interfaces/msg/neck_position.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"

#include "read_write_node.hpp"

// Control table address for X series (except XL-320)
#define ADDR_OPERATING_MODE 11
#define ADDR_TORQUE_ENABLE 64
#define ADDR_GOAL_POSITION 116
#define ADDR_PRESENT_POSITION 132

// Protocol version
#define PROTOCOL_VERSION 2.0  // Default Protocol version of DYNAMIXEL X series.

// Default setting
#define BAUDRATE 1000000  // Default Baudrate of DYNAMIXEL X series
#define DEVICE_NAME "/dev/ttyUSB0"  // [Linux]: "/dev/ttyUSB*", [Windows]: "COM*"

using namespace dynamixel;

using namespace std::chrono_literals;


PortHandler * portHandler = PortHandler::getPortHandler(DEVICE_NAME);
PacketHandler * packetHandler = PacketHandler::getPacketHandler(PROTOCOL_VERSION);
GroupSyncWrite groupSyncWrite(portHandler, packetHandler, ADDR_GOAL_POSITION, 4);

uint8_t dxl_error = 0;
uint32_t goal_position[19] = {0};
int dxl_comm_result = COMM_TX_FAIL;
int dxl_addparam_result = false;

ReadWriteNode::ReadWriteNode()
: Node("read_write_node")
{
  RCLCPP_INFO(this->get_logger(), "Run read write node");

  this->declare_parameter("qos_depth", 10);
  int8_t qos_depth = 0;
  this->get_parameter("qos_depth", qos_depth);

  const auto QOS_RKL10V =
    rclcpp::QoS(rclcpp::KeepLast(qos_depth)).reliable().durability_volatile();
  
  //Create a publisher to send the neck position for vision.py
  neck_position_publisher = this->create_publisher<custom_interfaces::msg::NeckPosition>("neck_position", 10);
  timer_ = this->create_wall_timer(
  8ms, std::bind(&ReadWriteNode::timer_callback, this));

  set_position_subscriber_ =
    this->create_subscription<SetPosition>(
    "set_position",
    QOS_RKL10V,
    [this](const std::shared_ptr<SetPosition> msg) -> void 
    {

      RCLCPP_INFO(this->get_logger(), "Entrou na funcao");
      
      uint8_t dxl_error = 0;

      uint8_t motors [20][4];

      for (int i=0; i<20; i++){
        uint32_t position = (unsigned int)msg->position[i]; // Convert int32 -> uint32
                
        motors[i][0] = DXL_LOBYTE(DXL_LOWORD(position));
        motors[i][1] = DXL_HIBYTE(DXL_LOWORD(position));
        motors[i][2] = DXL_LOBYTE(DXL_HIWORD(position));
        motors[i][3] = DXL_HIBYTE(DXL_HIWORD(position));  
      }
      
      RCLCPP_INFO(this->get_logger(), "Fez os parametros");

      for(int i=0; i<20; i++)
      {
        dxl_addparam_result = groupSyncWrite.addParam((uint8_t)msg->id[i], motors[i]);
        if (dxl_addparam_result != true) {
          RCLCPP_INFO(this->get_logger(), "Failed to addparam to groupSyncWrite for Dynamixel ID %d", msg->id[i]);
        }
      }

      dxl_comm_result = groupSyncWrite.txPacket();

      if (dxl_comm_result != COMM_SUCCESS) {
        RCLCPP_INFO(this->get_logger(), "%s", packetHandler->getTxRxResult(dxl_comm_result));
      } 
      else if (dxl_error != 0) {
        RCLCPP_INFO(this->get_logger(), "%s", packetHandler->getRxPacketError(dxl_error));
      } 
      else {
        RCLCPP_INFO(this->get_logger(), "Set [ID: {%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,%d,%d,%d}] [Goal Position: {%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,%d, %d,%d}]", 
        msg->id[0], msg->id[1], msg->id[2], msg->id[3], msg->id[4], msg->id[5], msg->id[6], msg->id[7], msg->id[8], msg->id[9], msg->id[10], msg->id[11], msg->id[12], msg->id[13], msg->id[14], msg->id[15], msg->id[16], msg->id[17], msg->id[18], msg->id[19],
        msg->position[0], msg->position[1], msg->position[2], msg->position[3], msg->position[4], msg->position[5], msg->position[6], msg->position[7], msg->position[8], msg->position[9], msg->position[10], msg->position[11], msg->position[12], msg->position[13], msg->position[14], msg->position[15], msg->position[16], msg->position[17],msg->position[18], msg->position[19]);
      }

      RCLCPP_INFO(this->get_logger(), "Terminou");

      groupSyncWrite.clearParam();
    }
    );


    set_position_subscriber_single =
    this->create_subscription<SetPositionOriginal>(
    "set_position_single",
    QOS_RKL10V,
    [this](const SetPositionOriginal::SharedPtr msg) -> void
    {
      uint8_t dxl_error = 0;

      // Position Value of X series is 4 byte data.
      // For AX & MX(1.0) use 2 byte data(uint16_t) for the Position Value.
      uint32_t goal_position = (unsigned int)msg->position;  // Convert int32 -> uint32
      uint32_t ADDR_GOAL = (unsigned int)msg->address;

      if(ADDR_GOAL == 102){
        // Write Goal Position (length : 4 bytes)
        // When writing 2 byte data to AX / MX(1.0), use write2ByteTxRx() instead.
        dxl_comm_result =
        packetHandler->write2ByteTxRx(
          portHandler,
          (uint8_t) msg->id,
          ADDR_GOAL,
          goal_position,
          &dxl_error
        );

        if (dxl_comm_result != COMM_SUCCESS) {
          RCLCPP_INFO(this->get_logger(), "%s", packetHandler->getTxRxResult(dxl_comm_result));
        } else if (dxl_error != 0) {
          RCLCPP_INFO(this->get_logger(), "%s", packetHandler->getRxPacketError(dxl_error));
        } else {
          RCLCPP_INFO(this->get_logger(), "Set [ID: %d] [Goal Position: %d] [Address: %d]", msg->id, msg->position, msg->address);
        }
      }

      else{
        // Write Goal Position (length : 4 bytes)
        // When writing 2 byte data to AX / MX(1.0), use write2ByteTxRx() instead.
        dxl_comm_result =
        packetHandler->write4ByteTxRx(
          portHandler,
          (uint8_t) msg->id,
          ADDR_GOAL,
          goal_position,
          &dxl_error
        );

        if (dxl_comm_result != COMM_SUCCESS) {
          RCLCPP_INFO(this->get_logger(), "%s", packetHandler->getTxRxResult(dxl_comm_result));
        } else if (dxl_error != 0) {
          RCLCPP_INFO(this->get_logger(), "%s", packetHandler->getRxPacketError(dxl_error));
        } else {
          RCLCPP_INFO(this->get_logger(), "Set [ID: %d] [Goal Position: %d] [Address: %d]", msg->id, msg->position, msg->address);
        }
      }
    }
    );

    auto get_present_position =
    [this](
    const std::shared_ptr<GetPosition::Request> request,
    std::shared_ptr<GetPosition::Response> response) -> void
    {
      // Read Present Position (length : 4 bytes) and Convert uint32 -> int32
      // When reading 2 byte data from AX / MX(1.0), use read2ByteTxRx() instead.
      dxl_comm_result = packetHandler->read4ByteTxRx(
        portHandler,
        (uint8_t) request->id,
        ADDR_PRESENT_POSITION,
        reinterpret_cast<uint32_t *>(&present_position),
        &dxl_error
      );

      RCLCPP_INFO(
        this->get_logger(),
        "Get [ID: %d] [Present Position: %d]",
        request->id,
        present_position
      );

      response->position = present_position;
    };
  get_position_server_ = create_service<GetPosition>("get_position", get_present_position);

}

void ReadWriteNode::timer_callback(){
    auto message = custom_interfaces::msg::NeckPosition();

    for(int i=0; i<2; i++)
    {
      dxl_comm_result = packetHandler->read4ByteTxRx(
        portHandler,
        (uint8_t) (19+i), //for motor with id 19 and 20
        ADDR_PRESENT_POSITION,
        reinterpret_cast<uint32_t *>(&motor[i]),
        &dxl_error
      );
    }
   
    message.position19 = motor[0];
    message.position20 = motor[1];

    neck_position_publisher->publish(message);

  }

// RCLCPP_INFO(this->get_logger(), "Set [ID: {%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d}] [Goal Position: {%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d}]", 
//          msg->id[0], msg->id[1], msg->id[3], msg->id[4], msg->id[5], msg->id[6], msg->id[7], msg->id[8], msg->id[9], msg->id[10],
//          msg->id[11], msg->id[12], msg->id[13], msg->id[14], msg->id[15], msg->id[16], msg->id[17], msg->id[18],
//          msg->position[0], msg->position[1], msg->position[2], msg->position[3], msg->position[4], msg->position[5], 
//          msg->position[6], msg->position[7], msg->position[8], msg->position[9], msg->position[10], msg->position[11],
//          msg->position[12], msg->position[13], msg->position[14], msg->position[15], msg->position[16], msg->position[17], msg->position[18]);

ReadWriteNode::~ReadWriteNode()
{
}

void setupDynamixel(uint8_t dxl_id)
{
  // Use Position Control Mode
  dxl_comm_result = packetHandler->write1ByteTxRx(
    portHandler,
    dxl_id,
    ADDR_OPERATING_MODE,
    3,
    &dxl_error
  );

  if (dxl_comm_result != COMM_SUCCESS) {
    RCLCPP_ERROR(rclcpp::get_logger("read_write_node"), "Failed to set Position Control Mode.");
  } else {
    RCLCPP_INFO(rclcpp::get_logger("read_write_node"), "Succeeded to set Position Control Mode.");
  }

  // Enable Torque of DYNAMIXEL
  dxl_comm_result = packetHandler->write1ByteTxRx(
    portHandler,
    dxl_id,
    ADDR_TORQUE_ENABLE,
    1,
    &dxl_error
  );

  if (dxl_comm_result != COMM_SUCCESS) {
    RCLCPP_ERROR(rclcpp::get_logger("read_write_node"), "Failed to enable torque.");
  } else {
    RCLCPP_INFO(rclcpp::get_logger("read_write_node"), "Succeeded to enable torque.");
  }

  //Declarando o valor limite da velocidade usado pelo P_PROFILE_VELOCITY.
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, BROADCAST_ID, 44, 1023, &dxl_error);

  if (dxl_comm_result != COMM_SUCCESS) {
    RCLCPP_ERROR(rclcpp::get_logger("read_write_node"), "Failed to define limit velocity.");
  } else {
    RCLCPP_INFO(rclcpp::get_logger("read_write_node"), "Succeeded to define limit velocity.");
  }

  //Declarando o valor limite da aceleração usado pelo P_PROFILE_ACCELERATION.
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, BROADCAST_ID, 40, 32767, &dxl_error);

  if (dxl_comm_result != COMM_SUCCESS) {
    RCLCPP_ERROR(rclcpp::get_logger("read_write_node"), "Failed to define limit acceleration.");
  } else {
    RCLCPP_INFO(rclcpp::get_logger("read_write_node"), "Succeeded to define limit acceleration.");
  }
}

int main(int argc, char * argv[])
{
  char string1[50]; //String
  sprintf(string1,"echo 123456| sudo -S renice -20 -p %d", getpid());
  system(string1);//prioridade

  // Open Serial Port
  dxl_comm_result = portHandler->openPort();
  if (dxl_comm_result == false) {
    RCLCPP_ERROR(rclcpp::get_logger("read_write_node"), "Failed to open the port!");
    return -1;
  } else {
    RCLCPP_INFO(rclcpp::get_logger("read_write_node"), "Succeeded to open the port.");
  }

  // Set the baudrate of the serial port (use DYNAMIXEL Baudrate)
  dxl_comm_result = portHandler->setBaudRate(BAUDRATE);
  if (dxl_comm_result == false) {
    RCLCPP_ERROR(rclcpp::get_logger("read_write_node"), "Failed to set the baudrate!");
    return -1;
  } else {
    RCLCPP_INFO(rclcpp::get_logger("read_write_node"), "Succeeded to set the baudrate.");
  }

  setupDynamixel(BROADCAST_ID);
  
  rclcpp::init(argc, argv);

  auto readwritenode = std::make_shared<ReadWriteNode>();
  rclcpp::spin(readwritenode);
  rclcpp::shutdown();

  // Disable Torque of DYNAMIXEL
  packetHandler->write1ByteTxRx(
    portHandler,
    BROADCAST_ID,
    ADDR_TORQUE_ENABLE,
    0,
    &dxl_error
  );

  return 0;
}