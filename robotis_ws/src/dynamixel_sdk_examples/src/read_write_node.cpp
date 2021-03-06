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
// $ ros2 topic pub -1 /set_position dynamixel_sdk_custom_interfaces/SetPosition "{id: {6, 2}, position: {300, 500}}"
// $ ros2 topic pub -1 /set_position dynamixel_sdk_custom_interfaces/SetPosition "{id: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}, position: {300, 500, 400, 300, 500, 400, 300, 500, 400, 300, 500, 400, 300, 500, 400, 300, 500, 400, 300}}"
// $ ros2 topic pub -1 /set_position dynamixel_sdk_custom_interfaces/SetPosition "{id: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, position: {2500, 1900, 2100, 2048, 2047, 2046, 2049, 2050, 2051, 2052, 2045, 2044}}"
// $ ros2 topic pub -1 /set_position dynamixel_sdk_custom_interfaces/SetPosition "{id: {1, 2, 5, 6}, position: {2500, 1900, 2048, 2048}}"
//
// Author: Will Son
*******************************************************************************/

#include <cstdio>
#include <memory>
#include <string>

#include "dynamixel_sdk/dynamixel_sdk.h"
#include "dynamixel_sdk_custom_interfaces/msg/set_position.hpp"
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
#define DEVICE_NAME "/dev/ttyACM0"  // [Linux]: "/dev/ttyUSB*", [Windows]: "COM*"

using namespace dynamixel;

PortHandler * portHandler = PortHandler::getPortHandler(DEVICE_NAME);
PacketHandler * packetHandler = PacketHandler::getPacketHandler(PROTOCOL_VERSION);
GroupSyncWrite groupSyncWrite(portHandler, packetHandler, ADDR_GOAL_POSITION, 4);

uint8_t dxl_error = 0;
uint32_t goal_position[3] = {0};
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
  
  set_position_subscriber_ =
    this->create_subscription<SetPosition>(
    "set_position",
    QOS_RKL10V,
    [this](const std::shared_ptr<SetPosition> msg) -> void 
    {

      RCLCPP_INFO(this->get_logger(), "Entrou na funcao");
      
      uint8_t dxl_error = 0;

      uint8_t param_goal_position0[4]; 
      uint8_t param_goal_position1[4];
      uint8_t param_goal_position2[4]; 

      //for(int i=0; i<=2; i++){
        // Write Goal Position (length : 4 bytes)
        // When writing 2 byte data to AX / MX(1.0), use write2ByteTxRx() instead.
      uint32_t position0 = (unsigned int)msg->position[0]; // Convert int32 -> uint32
      param_goal_position0[0] = DXL_LOBYTE(DXL_LOWORD(position0));
      param_goal_position0[1] = DXL_HIBYTE(DXL_LOWORD(position0));
      param_goal_position0[2] = DXL_LOBYTE(DXL_HIWORD(position0));
      param_goal_position0[3] = DXL_HIBYTE(DXL_HIWORD(position0));
      uint32_t position1 = (unsigned int)msg->position[1]; // Convert int32 -> uint32
      param_goal_position1[0] = DXL_LOBYTE(DXL_LOWORD(position1));
      param_goal_position1[1] = DXL_HIBYTE(DXL_LOWORD(position1));
      param_goal_position1[2] = DXL_LOBYTE(DXL_HIWORD(position1));
      param_goal_position1[3] = DXL_HIBYTE(DXL_HIWORD(position1));
      uint32_t position2 = (unsigned int)msg->position[2]; // Convert int32 -> uint32
      param_goal_position2[0] = DXL_LOBYTE(DXL_LOWORD(position2));
      param_goal_position2[1] = DXL_HIBYTE(DXL_LOWORD(position2));
      param_goal_position2[2] = DXL_LOBYTE(DXL_HIWORD(position2));
      param_goal_position2[3] = DXL_HIBYTE(DXL_HIWORD(position2));

      RCLCPP_INFO(this->get_logger(), "Fez os parametros");

      dxl_addparam_result = groupSyncWrite.addParam((uint8_t)msg->id[0], param_goal_position0);
      if (dxl_addparam_result != true) {
        RCLCPP_INFO(this->get_logger(), "Failed to addparam to groupSyncWrite for Dynamixel ID %d", msg->id[0]);
      }

      dxl_addparam_result = groupSyncWrite.addParam((uint8_t)msg->id[1], param_goal_position1);
      if (dxl_addparam_result != true) {
        RCLCPP_INFO(this->get_logger(), "Failed to addparam to groupSyncWrite for Dynamixel ID %d", msg->id[1]);
      }

      dxl_addparam_result = groupSyncWrite.addParam((uint8_t)msg->id[2], param_goal_position2);
      if (dxl_addparam_result != true) {
        RCLCPP_INFO(this->get_logger(), "Failed to addparam to groupSyncWrite for Dynamixel ID %d", msg->id[2]);
      }

      dxl_comm_result = groupSyncWrite.txPacket();

      if (dxl_comm_result != COMM_SUCCESS) {
        RCLCPP_INFO(this->get_logger(), "%s", packetHandler->getTxRxResult(dxl_comm_result));
      } 
      else if (dxl_error != 0) {
        RCLCPP_INFO(this->get_logger(), "%s", packetHandler->getRxPacketError(dxl_error));
      } 
      else {
        RCLCPP_INFO(this->get_logger(), "Set [ID: {%d, %d, %d}] [Goal Position: {%d, %d, %d}]", 
        msg->id[0], msg->id[1], msg->id[2], msg->position[0], msg->position[1], msg->position[2]);
      }

      RCLCPP_INFO(this->get_logger(), "Terminou");

      groupSyncWrite.clearParam();
    }
    );

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
}

int main(int argc, char * argv[])
{

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