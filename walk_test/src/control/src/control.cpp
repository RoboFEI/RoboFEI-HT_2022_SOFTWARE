// Open terminal #2 
// $ ros2 run control control
// $ ros2 run um7 um7_node
// $ ros2 launch control action.launch.py


// ros2 topic pub -1 /decision dynamixel_sdk_custom_interfaces/Decision "{decision: 1}"

#include <chrono>
#include <memory>
#include <thread>
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#include "MotionManager.h"
#include "Walking.h"
#include "rclcpp/rclcpp.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/set_position.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/decision.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/walk.hpp"
#include "sensor_msgs/msg/imu.hpp"

#define INI_FILE_PATH       "../../Action/src/control_framework/config.ini"

using namespace std::chrono_literals;
using std::placeholders::_1;
int movement = 0;
int contador = 0;
bool stop_gait = true;
bool fallen = false;
bool fallenFront = false;
double X_amplitude = 4;
double Y_amplitude = 4;
double A_amplitude = 4;
bool same_moviment = false;

using namespace Robot;

class Control : public rclcpp::Node
{
public:
  Control()
  : Node("control")
  {
    RCLCPP_INFO(this->get_logger(), "Running action node");
    subscription_ = this->create_subscription<dynamixel_sdk_custom_interfaces::msg::Decision>(
      "/decision", 10, std::bind(&Control::topic_callback, this, _1));
    subscription_imu = this->create_subscription<sensor_msgs::msg::Imu>(
    "imu/data", 10, std::bind(&Control::topic_callback_imu, this, _1));
    publisher_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 10); 
    publisher_walk = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::Walk>("walking", 10); 
  }

  private:
    void topic_callback_imu(const std::shared_ptr<sensor_msgs::msg::Imu> imu_msg_) const
    {
      float IMU_ACCEL_Z = imu_msg_->linear_acceleration.z/10;
      RCLCPP_INFO(this->get_logger(),"ACEL Z %f\n", IMU_ACCEL_Z);
      if(IMU_ACCEL_Z > 0.7 || IMU_ACCEL_Z < -0.7)
        contador++;
      else
        contador = 0;
      RCLCPP_INFO(this->get_logger(),"Contador %d \n", contador);
      
      if(contador>=3)
      {
        RCLCPP_INFO(this->get_logger(),"Caido");
        fallen = true; // Robô caido
      }
      if (fallen == true){ // Robô esta caido
        if(IMU_ACCEL_Z > 0){  // Robô caido de frente
          fallenFront = true;
        }
        else{  // Robô caido de costas
          fallenFront = false;
        }
      }
    }

    void topic_callback(const std::shared_ptr<dynamixel_sdk_custom_interfaces::msg::Decision> msg) const
    {
      
      auto message_dec = dynamixel_sdk_custom_interfaces::msg::Decision();
      message_dec.decision = msg->decision;
      movement = (int)message_dec.decision;
      RCLCPP_INFO(this->get_logger(), "I heard %d", movement);
      if(fallen == true){ // Robô caido, tem que levantar antes de qualquer movimento
        if (fallenFront == true){ // Caido de frente
          RCLCPP_INFO(this->get_logger(), "Stand Up Front");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {1, 2, 3};          
          message.position = {1024, 1024, 2593};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(5));
          fallen = false;
        }
        else{ // Robô caido de costas
          RCLCPP_INFO(this->get_logger(), "Stand Up Back");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {1, 2, 3};          
          message.position = {1024, 1024, 2593};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(5));
          fallen = false;
        }
      }
      else{
        if(movement!=14){
          auto message_walk = dynamixel_sdk_custom_interfaces::msg::Walk();                              
          message_walk.walk = 0; 
          publisher_walk->publish(message_walk);
        }
        if(movement==1){
          RCLCPP_INFO(this->get_logger(), "Parado");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {1, 2, 3};          
          message.position = {1024, 1024, 2593};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==2){
          RCLCPP_INFO(this->get_logger(), "Walking");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {4, 5, 6};          
          message.position = {2024, 2048, 2093};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==3){
          RCLCPP_INFO(this->get_logger(), "Right kick");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {4, 5, 6};          
          message.position = {2024, 2048, 2093};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==4){
          RCLCPP_INFO(this->get_logger(), "Left kick");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {4, 5, 6};          
          message.position = {2024, 2048, 2093};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==5){
          RCLCPP_INFO(this->get_logger(), "Turn Right");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {4, 5, 6};          
          message.position = {2024, 2048, 2093};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==6){
          RCLCPP_INFO(this->get_logger(), "Turn Left");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {4, 5, 6};          
          message.position = {2024, 2048, 2093};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==7){
          RCLCPP_INFO(this->get_logger(), "Goodbye");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {4, 5, 6};          
          message.position = {2024, 2048, 2093};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==8){
          RCLCPP_INFO(this->get_logger(), "Moving head");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {4, 5, 6};          
          message.position = {2024, 2048, 2093};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==9){
          RCLCPP_INFO(this->get_logger(), "Turn around ball clockwise");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {4, 5, 6};          
          message.position = {2024, 2048, 2093};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==10){
          RCLCPP_INFO(this->get_logger(), "Turn around ball anticlockwise");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {4, 5, 6};          
          message.position = {2024, 2048, 2093};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==11){
          RCLCPP_INFO(this->get_logger(), "Fall left");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {4, 5, 6};          
          message.position = {2024, 2048, 2093};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==12){
          RCLCPP_INFO(this->get_logger(), "Fall right");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {4, 5, 6};          
          message.position = {2024, 2048, 2093};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==13){
          RCLCPP_INFO(this->get_logger(), "Agachando");
          auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                              
          message.id = {4, 5, 6};          
          message.position = {2024, 2048, 2093};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(movement==14){
          RCLCPP_INFO(this->get_logger(), "Andando");
          auto message_walk = dynamixel_sdk_custom_interfaces::msg::Walk();                              
          message_walk.walk = 1; 
          publisher_walk->publish(message_walk);
          // MotionManager::GetInstance()->SetEnable(true);
          // Walking::GetInstance()->m_Joint.SetEnableBody(true);
          // Walking::GetInstance()->X_MOVE_AMPLITUDE = X_amplitude;
          // Walking::GetInstance()->Y_MOVE_AMPLITUDE = Y_amplitude;
          // Walking::GetInstance()->A_MOVE_AMPLITUDE = A_amplitude;
          // Walking::GetInstance()->Start();
          // if(movement!=14){
          //   Walking::GetInstance()->Stop();
          //   Walking::GetInstance()->m_Joint.SetEnableBody(false);
          // }
        }
      }
    } 

    rclcpp::Subscription<dynamixel_sdk_custom_interfaces::msg::Decision>::SharedPtr subscription_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr subscription_imu;
    rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>::SharedPtr publisher_; 
    rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::Walk>::SharedPtr publisher_walk;   
    rclcpp::TimerBase::SharedPtr timer_;
};


int main(int argc, char * argv[])
{
  //Configurando para prioridade maxima para executar este processo-------
  char string1[50]; //String
  sprintf(string1,"echo fei 123456| sudo -S renice -20 -p %d", getpid());
  system(string1);//prioridade
  rclcpp::init(argc, argv);
  // if(MotionManager::GetInstance()->Initialize() == false)
  //   {
  //     printf("Fail to initialize Motion Manager!\n");
  //     return 0;
  // }
  rclcpp::spin(std::make_shared<Control>());
  rclcpp::shutdown();
  return 0;
}