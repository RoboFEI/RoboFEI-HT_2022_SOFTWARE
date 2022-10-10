// Open terminal #2 
// $ ros2 run control control
// $ ros2 run um7 um7_node
// $ ros2 launch control action.launch.py


// ros2 topic pub -1 /decision custom_interfaces/Decision "{decision: 1}"

#include <chrono>
#include <memory>
#include <thread>
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <libgen.h> //dirname

#include "MotionManager.h"
#include "Walking.h"
#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/set_position.hpp"
#include "custom_interfaces/msg/decision.hpp"
#include "custom_interfaces/msg/walk.hpp"
#include "custom_interfaces/msg/param_walk.hpp"
#include "custom_interfaces/msg/vision.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "custom_interfaces/msg/neck_position.hpp"
#include "GaitMove.hpp"
#include "custom_interfaces/msg/set_position_original.hpp"
#include "custom_interfaces/srv/reset.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
int movement = 1;
int contador = 0;
int cont_vision = 2047;
int cont_vision_up = 1751;
int cont_fall_side = 0;
bool stop_gait = true;
bool fallen = false;
bool fallenFront = false;
bool fallen_side = false;
double X_amplitude = 4;
double Y_amplitude = 4;
double A_amplitude = 4;
bool same_moviment = false;
uint32_t valor = 256;
uint32_t valor_up = 256;
int neck_sides = 2048;
int neck_up = 2048;

using namespace Robot;

class Control : public rclcpp::Node
{
public:
  Control()
  : Node("control")
  {
    RCLCPP_INFO(this->get_logger(), "Running action node");
    subscription_ = this->create_subscription<custom_interfaces::msg::Decision>(
      "/decision", 10, std::bind(&Control::topic_callback, this, _1));
    subscription_neck = this->create_subscription<custom_interfaces::msg::NeckPosition>(
      "/neck_position", 10, std::bind(&Control::topic_callback_neck, this, _1));
    subscription_imu = this->create_subscription<sensor_msgs::msg::Imu>(
    "imu/data", 10, std::bind(&Control::topic_callback_imu, this, _1));
    publisher_ = this->create_publisher<custom_interfaces::msg::SetPosition>("set_position", 10); 
    publisher_single = this->create_publisher<custom_interfaces::msg::SetPositionOriginal>("set_position_single", 10);
    publisher_walk = this->create_publisher<custom_interfaces::msg::Walk>("walking", 10); 
    timer_ = this->create_wall_timer(8ms, std::bind(&Control::Process, this));
    }

  private:
    void topic_callback_imu(const std::shared_ptr<sensor_msgs::msg::Imu> imu_msg_) const
    {
      float IMU_ACCEL_Z = imu_msg_->linear_acceleration.z/10;
      float IMU_ACCEL_X = imu_msg_->linear_acceleration.x/10;
      RCLCPP_INFO(this->get_logger(),"ACEL Z %f\n", IMU_ACCEL_Z);
      if(IMU_ACCEL_Z > 0.7 || IMU_ACCEL_Z < -0.7)
        contador++;
      else
        contador = 0;
      RCLCPP_INFO(this->get_logger(),"Contador %d \n", contador);
      
      if(contador>=5)
      {
        RCLCPP_INFO(this->get_logger(),"Caido");
        fallen = true; // Robô caido
        if(IMU_ACCEL_Z < 0){  // Robô caido de frente
          fallenFront = true;
        }
        else{  // Robô caido de costas
          fallenFront = false;
        }
      }
      
      if(IMU_ACCEL_X > 0.7 || IMU_ACCEL_X < -0.7)
        cont_fall_side++;
      else
        cont_fall_side = 0;
      RCLCPP_INFO(this->get_logger(),"Contador fall side %d \n", cont_fall_side);
      
      if(cont_fall_side>=3)
      {
        RCLCPP_INFO(this->get_logger(),"Caido");
        fallen_side = true; // Robô caido
      }
    }

    void topic_callback_neck(const std::shared_ptr<custom_interfaces::msg::NeckPosition> neck_msg) const
    {
      neck_sides = neck_msg->position19;
      neck_up = neck_msg->position20;
    }

    void Process(){
      auto message_walk = custom_interfaces::msg::Walk();  
      auto message = custom_interfaces::msg::SetPosition();  
      auto message_param = custom_interfaces::msg::ParamWalk();  
      auto message_single = custom_interfaces::msg::SetPositionOriginal();  
      if(fallen == true){ // Robô caido, tem que levantar antes de qualquer movimento
        message_walk.walk = 0; 
        publisher_walk->publish(message_walk);
        if (fallenFront == true){ // Caido de frente      
          RCLCPP_INFO(this->get_logger(), "Stand Up Front");                     
          message_single.id = 254;
          message_single.address = 112;
          message_single.position = 80;
          publisher_single->publish(message_single);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
          message.position = {2047,2047,2048,2048,417,3679,2048,2067,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047};   
          publisher_->publish(message);
          usleep(3000000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
          message.position = {2152,1942,2096,2000,766,3328,2048,2067,2047,2047,837,3259,3028,1066,2919,1175,2047,2047,2047};   
          publisher_->publish(message);
          usleep(1500000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2755,1339,2096,2000,2048,2048,2048,2067,2047,2047,837,3259,3275,819,2657,1494,2047,2047,2047};   
          publisher_->publish(message);
          usleep(1500000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,841,3259,3644,452,2657,1494,2047,2047,2047};   
          publisher_->publish(message);
          usleep(1500000);

          message_single.id = 254;
          message_single.address = 112;
          message_single.position = 30;
          publisher_single->publish(message_single);

          message_single.id = 13;
          message_single.address = 112;
          message_single.position = 60;
          publisher_single->publish(message_single);

          message_single.id = 14;
          message_single.address = 112;
          message_single.position = 60;
          publisher_single->publish(message_single);

          // 15 = 2048 + 800 // 16 = 2048 - 800 //
          // 11 = 2048 - 800 // 12 = 2048 + 800 //
          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1248,2848,3644,452,2848,1248,2047,2047,2047};   
          publisher_->publish(message);
          usleep(1600000);

          // 11 += 224 // 12 -= 224
          // 15 -= 224 // 16 += 224
          // 13 -= 448 // 14 += 448
          // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //  //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          //  message.position = {2048,2048,2148,1948,1024,3072,1917,2067,2047,2047,1472,2624,3196,900,2624,1472,2047,2047,2047};   
          // publisher_->publish(message);
          // std::this_thread::sleep_for(std::chrono::seconds(2)); // Seg_1

          // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //  //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          //  message.position = {2048,2048,2148,1948,1024,3072,1917,2067,2047,2047,1696,2400,2748,1348,2400,1696,2047,2047,2047};   
          // publisher_->publish(message);
          // std::this_thread::sleep_for(std::chrono::seconds(1)); // Seg_2

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1920,2176,2300,1748,2176,1920,2047,2047,2047};   
          publisher_->publish(message);
          usleep(20000000);

          message_single.id = 254;
          message_single.address = 112;
          message_single.position = 60;
          publisher_single->publish(message_single);
          fallen = false;
        }
        else{ // Robô caido de costas
          RCLCPP_INFO(this->get_logger(), "Stand Up Back");
            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 40;
            publisher_single->publish(message_single);


            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2048,2048,2096,2000,2048,2048,2048,2103,2048,2060,2048,2048,2048,2048,2048,2048,2048,2048,2048};   
            publisher_->publish(message);
            usleep(3000000);

            // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            // //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            // message.position = {2048,2048,2096,2000,2048,2048,2048,2048,2048,2060,1348,2748,3500,596,1748,2348,2048,2048,2048};   
            // publisher_->publish(message);
            // usleep(3000000);

            // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            // //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            // message.position = {2048,2048,2096,2000,1024,3072,2048,2048,2048,2060,1227,2869,3621,475,2596,1500,2048,2048,2048};   
            // publisher_->publish(message);
            // usleep(3000000);

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1    2    3    4   5   6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {944,3203,2096,2000,804,3292,2048,2048,2048,2060,1315,2781,3665,442,2000,2096,2048,2048,2048};   
            publisher_->publish(message);
            usleep(3000000);


            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {882,3214,2096,2000,1178,2918,2048,2048,2048,2060,952,3144,3665,442,1978,2118,2048,2048,2048};   
            publisher_->publish(message);
            usleep(3000000);

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 70;
            publisher_single->publish(message_single);

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {1769,2294,2096,2000,2048,2048,2048,2048,2048,2060,1146,2950,3621,475,2596,1500,2048,2048,2048};   
            publisher_->publish(message);
            usleep(3000000);

            // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            // //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            // message.position = {2011,2122,2096,2000,2048,2048,2048,2103,2048,2060,853,3243,3621,475,2211,1885,2048,2048,2048};   
            // publisher_->publish(message);
            // usleep(3000000);

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2121,1975,2096,2000,2048,2048,2048,2048,2048,2060,589,3507,3621,475,2296,1800,2048,2048,2048};   
            publisher_->publish(message);
            usleep(4000000);



            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 30;
            publisher_single->publish(message_single);

            message_single.id = 13;
            message_single.address = 112;
            message_single.position = 60;
            publisher_single->publish(message_single);

            message_single.id = 14;
            message_single.address = 112;
            message_single.position = 60;
            publisher_single->publish(message_single);



            // 15 = 2048 + 800 // 16 = 2048 - 800 //
            // 11 = 2048 - 800 // 12 = 2048 + 800 //
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
            message.position = {2048,2048,2148,1948,1024,3072,2048,2048,2047,2047,1248,2848,3644,452,2848,1248,2047,2047,2047};   
            publisher_->publish(message);
            usleep(1600000);


            // 11 += 224 // 12 -= 224
            // 15 -= 224 // 16 += 224
            // 13 -= 448 // 14 += 448
            // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //  //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
            //  message.position = {2048,2048,2148,1948,1024,3072,1917,2067,2047,2047,1472,2624,3196,900,2624,1472,2047,2047,2047};   
            // publisher_->publish(message);
            // std::this_thread::sleep_for(std::chrono::seconds(2)); // Seg_1

            // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //  //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
            //  message.position = {2048,2048,2148,1948,1024,3072,1917,2067,2047,2047,1696,2400,2748,1348,2400,1696,2047,2047,2047};   
            // publisher_->publish(message);
            // std::this_thread::sleep_for(std::chrono::seconds(1)); // Seg_2

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
            message.position = {2048,2048,2148,1948,1024,3072,2048,2048,2047,2047,1920,2176,2300,1748,2176,1920,2047,2047,2047};   
            publisher_->publish(message);
            usleep(20000000);

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 60;
            publisher_single->publish(message_single);
    
          fallen = false;
        }
      }
      else{
        switch (movement){
          case 1: // Parado
            message_walk.walk_number = 0; 
            publisher_walk->publish(message_walk);
            RCLCPP_INFO(this->get_logger(), "Parado");                            
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
            message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,   2048,    1345};
            publisher_->publish(message);
            break;
          case 2: // Greeting
            message_walk.walk_number = 0; 
            publisher_walk->publish(message_walk);
            RCLCPP_INFO(this->get_logger(), "Greeting");                            
            message.id = {4, 5, 6};          
            message.position = {2024, 2048, 2093};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
          case 3: // Right kick OK
            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 630;
            publisher_single->publish(message_single);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1


            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
            message.position = {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2081,2047,2047};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(5)); //1

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 15;
            publisher_single->publish(message_single);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1


            // 3 = 2048 + 70 // 4 = 248 - 70
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19    20
            message.position = {2047,2047,2118,1978,2048,2048,2047,2047,1930,2054,1770,2350,2440,1696,2212,1863,2120,1975,2047,2047};

            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(3)); //1



            // Dobrar joelhos
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2047,2047,2137,1446,496,2854,2047,2047,1950,2054,1746,2368,2622,1696,2271,1856,2120,1942,2047,2047};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1


            // Equilibrar em uma perna
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,2356,2478,3151,1586,2543,1813,2179,1953,2047,1301};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1
            

                // Perna pra trás
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,2356,2478,3151,1586,2296,1813,2048,1953,2047,1301};   
            publisher_->publish(message);

            message_single.id = 11;
            message_single.address = 112;
            message_single.position = 8400;
            publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1

            message_single.id = 13;
            message_single.address = 112;
            message_single.position = 4200;
            publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1

            message_single.id = 15;
            message_single.address = 112;
            message_single.position = 4200;
            publisher_single->publish(message_single);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1

                // Quase chute
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,2356,2478,3217,1586,2191,1813,2048,1953,2047,1301};   
            publisher_->publish(message);
            usleep(200000);

            message_single.id = 11;
            message_single.address = 112;
            message_single.position = 15000;
            publisher_single->publish(message_single);

            message_single.id = 13;
            message_single.address = 112;
            message_single.position = 15000;
            publisher_single->publish(message_single);

            message_single.id = 15;
            message_single.address = 112;
            message_single.position = 750;
            publisher_single->publish(message_single);


                // Chute
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                   1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,879,2478,2560,1586,2296,1878,2103,1942,2047,1301};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(2)); //1

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 10;
            publisher_single->publish(message_single);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1

              // Quase chute
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,2356,2478,3217,1586,2191,1889,2048,1953,2047,1301};   
            publisher_->publish(message);
            usleep(200000);


                // Perna pra trás
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,2356,2478,3151,1586,2296,1889,2048,1953,2047,1301};   
            publisher_->publish(message);
            usleep(2000000);

                // Equilibrar em uma perna
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,2356,2478,3151,1586,2543,1889,2179,1953,2047,1301};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 4000;
            publisher_single->publish(message_single);
            
            message_single.id = 18;
            message_single.address = 112;
            message_single.position = 20;
            publisher_single->publish(message_single);

                // Dobrar joelhos
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2047,2047,2137,1446,496,2854,2047,2047,1950,2054,1746,2368,2622,1696,2271,1856,2120,1942,2047,2047};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(2)); //1

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
            message.position = {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2081,2047,2047};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(5)); //1

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 128;
            publisher_single->publish(message_single);
            movement = 1;
            break;
          case 4: // Left kick OK
            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 630;
            publisher_single->publish(message_single);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1


            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
            message.position = {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2081,2047,2047};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(5)); //1

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 15;
            publisher_single->publish(message_single);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1

            // 3 = 2048 + 70 // 4 = 248 - 70
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19    20
            message.position = {2047,2047,2116,1976,2046,2046,2047,2047,2040,2164,1744,2324,2398,1654,2231,1882,2119,2191,2047,2047};

            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(3)); //1


            // Dobrar joelhos
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20
            message.position = {2047,2047,2648,1957,1240,3598,2047,2047,2040,2144,1726,2348,2398,1472,2238,1823,2152,1974,2047,2047};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1


            // Equilibrar em uma perna
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14  15   16   17   18   19
            message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2281,1551,2163,1915,2793,2047};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1
            
            
                // Perna pra trás
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13  14   15   16   17   18   19
            message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2281,1798,2141,2046,2793,2047};   
            publisher_->publish(message);

            message_single.id = 12;
            message_single.address = 112;
            message_single.position = 8400;
            publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1

            message_single.id = 14;
            message_single.address = 112;
            message_single.position = 4200;
            publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1

            message_single.id = 16;
            message_single.address = 112;
            message_single.position = 4200;
            publisher_single->publish(message_single);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1

                // Quase chute
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13  14   15   16   17   18   19
            message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,877,2281,1903,2141,2046,2793,2047};   
            publisher_->publish(message);
            usleep(2000000);

            message_single.id = 12;
            message_single.address = 112;
            message_single.position = 15000;
            publisher_single->publish(message_single);

            message_single.id = 14;
            message_single.address = 112;
            message_single.position = 15000;
            publisher_single->publish(message_single);

            message_single.id = 15;
            message_single.address = 112;
            message_single.position = 750;
            publisher_single->publish(message_single);


                // Chute
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                   1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,3215,2508,1534,2216,1798,2152,1991,2793,2047};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(2)); //1

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 10;
            publisher_single->publish(message_single);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1

              // Quase chute
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13  14   15   16   17   18   19
            message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,877,2205,1903,2141,2046,2793,2047};   
            publisher_->publish(message);
            usleep(2000000);


                // Perna pra trás
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13  14   15   16   17   18   19
            message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2205,1798,2141,2046,2793,2047};   
            publisher_->publish(message);


                // Equilibrar em uma perna
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14  15   16   17   18   19
            message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2205,1551,2141,1915,2793,2047};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 4000;
            publisher_single->publish(message_single);
            
            message_single.id = 17;
            message_single.address = 112;
            message_single.position = 10;
            publisher_single->publish(message_single);

                // Dobrar joelhos
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2047,2047,2648,1957,1240,3598,2047,2047,2040,2164,1726,2348,2398,1472,2238,1796,2152,2140,2047,2047};   
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
            message.position = {1727,2370,2282,1800,626,3467,2050,1987,1988,2062,1765,2327,2788,1303,2534,1558,2046,2046,2047,2047};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(5)); //1

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 128;
            publisher_single->publish(message_single);
            movement = 1;
            break;

          case 5: // Turn right
            RCLCPP_INFO(this->get_logger(), "Turn Right");                        
            message_walk.walk = 0;   
            message_walk.sidle = 0;  
            message_walk.turn = -27;   
            message_walk.walk_number = 11; 
            publisher_walk->publish(message_walk);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
          case 6: // Turn left
            RCLCPP_INFO(this->get_logger(), "Turn Left");                            
            message_walk.walk = 0;   
            message_walk.sidle = 0;  
            message_walk.turn = 30;   
            message_walk.walk_number = 12; 
            publisher_walk->publish(message_walk);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
          case 7: // Goodbye OK
            RCLCPP_INFO(this->get_logger(), "Goodbye"); 
            message_walk.walk_number = 0; 
            publisher_walk->publish(message_walk);                           
            for (int i=1; i<=4; i++){
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
              message.position = {2047,1024,2048,1024,2048,2593,2047,2047,2047,2047,2000,2094,2400,1696,2292,1800,2047,2048,2048};   
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(1));
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
              message.position = {2047,1024,2048,1024,2048,3553,2047,2047,2047,2047,2000,2094,2400,1696,2292,1800,2047,2048,2048};   
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(1));
              // RCLCPP_INFO(this->get_logger(), "%d", i);
              if (i%4==0){
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
              message.position = {2047,2047,2048,2048,2048,2200,2047,2047,2047,2047,2000,2094,2400,1696,2292,1800,2047,2048,2048};   
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(10));
              }
            }
            break;
          case 8: // Search ball
            message_walk.walk_number = 0; 
            publisher_walk->publish(message_walk);        
            RCLCPP_INFO(this->get_logger(), "Moving head"); 

            if(cont_vision>=3071 || cont_vision<1024)
            { 
              valor *= -1;
              if(cont_vision_up <= 2048)
                cont_vision_up += valor_up;
              else
                cont_vision_up = 1551;
            }

            cont_vision = cont_vision + valor; 
            
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19           20
            message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,cont_vision, cont_vision_up};

            publisher_->publish(message);

            std::this_thread::sleep_for(std::chrono::seconds(1));   
            
            break;
          case 9: // Turn ball clockwise
            RCLCPP_INFO(this->get_logger(), "Turn around ball clockwise");                           
            message_walk.walk = 0;     //Andar para frente  (-) ou para (+)tras
            message_walk.sidle = -60;  //Andar para lateral (-)esquerda (+)direita
            message_walk.turn = -12;   //Angulo de rotacao  (-)esquerda (+)direita
            message_walk.walk_number = 5; 
            publisher_walk->publish(message_walk);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;


            // message_walk.walk = 0;     //Andar para frente  (-) ou para (+)tras
            // message_walk.sidle = -60;  //Andar para lateral (-)esquerda (+)direita
            // message_walk.turn = -12;   //Angulo de rotacao  (-)esquerda (+)direita
            // message_walk.walk_number = 5; 
            // publisher_walk->publish(message_walk);
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            // break;


            //[Turn Ball Right]
            // ;Rotacionar à direita em volta da bola
            // x_offset = 0; (-) desloca CG para frente (+) desloca CG para traz   2
            // y_offset = -110; (-) desloca CG para esquerda (+) desloca CG para direita   0 (-70)
            // z_offset = 40.0; (+) desloca CG para baixo (-) desloca CG para cima *Não deve ser menor que foot_height 40
            // roll_offset = 0.000000;inclinacao lateral do pe
            // pitch_offset = -2.00000;angulo do pe (+) aumenta angulo pe (-) diminui angulo pe -8
            // yaw_offset = -5.00000 ;giro do pe    tava 0
            // hip_pitch_offset = 12.00000;inclinação (+)=>Frente (-)=>Atras  3 (12 ou 7)

            // period_time = 600.000000;velocidade (-)=>Maior (+)=>Menor
            // dsp_ratio = 0.125;relacao de tempo entre chao e ar
            // step_forward_back_ratio = 5;tamanho do passo
            // foot_height = 38.0;altura pe (-)==>Menor (+)==>Maior 55 *Não deve ser maior que z_offset  (grama alta 38)
            // swing_right_left =12;balanço lateral (+)=>Maior (-)=>Menor
            // swing_top_down = 2;balanço do corpo (+)perna + flexionada (-)=>perna +esticada (2 ou 5)
            // pelvis_offset = 0;angulo da pelvis no eixo x(?)
            // arm_swing_gain = 0.1

            // balance_knee_gain = 0
            // balance_ankle_pitch_gain = 0
            // balance_hip_roll_gain = 0
            // balance_ankle_roll_gain = 0
            // balance_angle_smooth_gain = 0
            // balance_angle_gain = 0
            // lean_fb_gain = 0.000000
            // lean_fb_accel_gain = 0.000000
            // lean_turn_gain = 0.000000
            // start_step_factor = 0.000000
            // p_gain = 0
            // i_gain = 0
            // d_gain = 0

            // turn_angle = -6.0     ;Angulo de rotacao (-)esquerda  (+)direita
            // walk_foward = -3.5    ;Andar para frente(-) ou para (+)tras
            // sidle =20      ;Andar para lateral (-)esquerda  (+)direita //            
            
          case 10: // Turn ball anticlockwise
            RCLCPP_INFO(this->get_logger(), "Turn around ball anticlockwise");                            
            message_walk.walk = 0;   
            message_walk.sidle = 60;  
            message_walk.turn = 12;  
            message_walk.walk_number = 6; 
            publisher_walk->publish(message_walk);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
          case 11: // Fall left OK
            message_walk.walk_number = 0; 
            publisher_walk->publish(message_walk);
            RCLCPP_INFO(this->get_logger(), "Fall left");                              
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19  20 
            message.position = {4095,0,2004,2078,2048,2048,2125,2103,2082,2160,1960,2264,2048,1962,2048,2048,2048,2048,2047,2048};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19  20 
            message.position = {4095,0,2004,2078,2048,2048,2125,2103,2082,2160,1960,2264,2048,1962,2048,2048,1751,1817,2047,2048};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(20));
            break;
          case 12: // Fall right OK
            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 100;
            publisher_single->publish(message_single);
            
            //Posição inicial:
            RCLCPP_INFO(this->get_logger(), "Step 1");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
            message.position = {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1670,2406,2791,1306,2495,1634,2048,2081,2047,2047};
            publisher_->publish(message);
            usleep(800000);

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 100;
            publisher_single->publish(message_single);
            message_single.id = 2;

            //Levantando as pernas e afastando os ombros:
            RCLCPP_INFO(this->get_logger(), "Step 2");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1    2    3    4   5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {1724,2367,2405,1691,627,3468,2052,2044,2032,2106,1670,2406,2505,1570,2231,1788,2048,2081,2047,2047};
            publisher_->publish(message);
            usleep(600000); 
            
            //levantar os braços e tentar estender as pernas
            RCLCPP_INFO(this->get_logger(), "Step 3");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1    2    3    4   5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {4017,79,2405,1691,627,3468,2052,2044,2032,2106,1670,2406,2505,1570,2231,1788,2048,2081,2047,2047};
            publisher_->publish(message);
            usleep(600000);          

            //estendendo os braços (preparando para defender)
            RCLCPP_INFO(this->get_logger(), "Step 4");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1    2    3    4   5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {4017,79,1921,2241,2013,2083,2052,2044,2032,2106,1670,2406,2505,1570,2231,1788,2048,2081,2047,2047};
            publisher_->publish(message);
            usleep(600000);    

            //estendendo as pernas (preparando para cair)
            RCLCPP_INFO(this->get_logger(), "Step 5");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1    2    3    4   5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {4017,79,1921,2241,2013,2083,2052,2044,2032,2106,1899,2230,2384,1712,2231,1788,2048,2081,2047,2047};
            publisher_->publish(message);
            usleep(300000);    
            
            //prepando para cair a direita
            RCLCPP_INFO(this->get_logger(), "Step 6");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1    2    3    4   5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {4017,79,1921,2241,2013,2083,2052,2044,2087,2381,1899,2230,2384,1712,2231,1788,2345,2125,2047,2047};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(5)); //1    
            break;
          case 13: // Agachando OK
            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 80;
            publisher_single->publish(message_single);

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {2047,2047,2048,2048,417,3679,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047, 2047};   
            publisher_->publish(message);
            RCLCPP_INFO(this->get_logger(), "Move 1"); 
            usleep(3000000);

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2     3    4    5    6    7    8   9   10   11  12   13  14  15   16   17   18   19   20
            message.position = {2803,1293,2096,2000,852,3244,2047,2047,2047,2047,606,3259,3440,665,2657,1296,2047,2047,2047, 2047};   
            RCLCPP_INFO(this->get_logger(), "Move 2"); 
            publisher_->publish(message);
            usleep(1500000);

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {2755,1339,2096,2000,2048,2048,2047,2047,2047,2047,573,3523,3451,632,2690,1406,2047,2047,2047, 2047};   
            RCLCPP_INFO(this->get_logger(), "Move 3"); 
            publisher_->publish(message);
            usleep(2000000);

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {2755,1339,2096,2000,2048,2048,2047,2047,2047,2047,573,3523,3638,434,2690,1406,2047,2047,2047, 2047};   
            RCLCPP_INFO(this->get_logger(), "Move 3.5"); 
            publisher_->publish(message);
            usleep(3000000);

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {2048,2048,2148,1948,1024,3072,2047,2047,2047,2047,841,3259,3644,452,2657,1494,2047,2047,2047, 2047};   
            RCLCPP_INFO(this->get_logger(), "Move 4"); 
            publisher_->publish(message);
            usleep(1500000);

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 30;
            publisher_single->publish(message_single);

            message_single.id = 13;
            message_single.address = 112;
            message_single.position = 60;
            publisher_single->publish(message_single);

            message_single.id = 14;
            message_single.address = 112;
            message_single.position = 60;
            publisher_single->publish(message_single);

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1248,2848,3644,452,2848,1248,2047,2047,2047, 2047};   
            publisher_->publish(message);
            usleep(2500000);
            
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
            //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17    18   19    20
            message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1920,2176,2300,1748,2176,1920,2047,2047,2047, 2047};   
            publisher_->publish(message);
            usleep(20000000);

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 60;
            publisher_single->publish(message_single);
            break;
          case 14: // Walking OK
            RCLCPP_INFO(this->get_logger(), "Walking"); 
            message_walk.walk = 20;   
            message_walk.sidle = 0;  
            message_walk.turn = 2.5; 
            message_walk.walk_number = 1;  
            publisher_walk->publish(message_walk);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
          case 15: // Gait OK
            RCLCPP_INFO(this->get_logger(), "Gait"); 
            message_walk.walk = 0;   
            message_walk.sidle = 0;  
            message_walk.turn = -20;   
            message_walk.walk_number = 11; 
            publisher_walk->publish(message_walk);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
          case 16: // Stand up back OK
            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 40;
            publisher_single->publish(message_single);
          
            RCLCPP_INFO(this->get_logger(), "Step 1");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1    2    3    4   5   6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {944,3203,2096,2000,804,3292,2048,2048,2048,2060,1315,2781,3665,442,2000,2096,2048,2048,2048,2048};   
            publisher_->publish(message);
            usleep(2400000);


            RCLCPP_INFO(this->get_logger(), "Step 2");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14   15   16   17   18   19  20
            message.position = {882,3214,2096,2000,1178,2918,2048,2048,2048,2060,952,3144,3665,442,1978,2118,2048,2048,2048,2048};   
            publisher_->publish(message);
            usleep(2000000);

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 70;
            publisher_single->publish(message_single);
            
            RCLCPP_INFO(this->get_logger(), "Step 3");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19  20
            message.position = {1769,2294,2096,2000,2048,2048,2048,2048,2048,2060,1146,2950,3621,475,2296,1801,2048,2048,2048,2048};   
            publisher_->publish(message);
            usleep(1800000);

            RCLCPP_INFO(this->get_logger(), "Step 4");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {2121,1975,2096,2000,2048,2048,2048,2048,2048,2060,589,3507,3621,475,2296,1800,2048,2048,2048};   
            publisher_->publish(message);
            usleep(2000000);



            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 30;
            publisher_single->publish(message_single);

            message_single.id = 13;
            message_single.address = 112;
            message_single.position = 60;
            publisher_single->publish(message_single);

            message_single.id = 14;
            message_single.address = 112;
            message_single.position = 60;
            publisher_single->publish(message_single);


             RCLCPP_INFO(this->get_logger(), "Step 5");
            // 15 = 2048 + 800 // 16 = 2048 - 800 //
            // 11 = 2048 - 800 // 12 = 2048 + 800 //
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
            message.position = {2400,1696,2148,1948,1024,3072,2048,2048,2047,2047,1248,2848,3644,452,2848,1248,2047,2047,2047};   
            publisher_->publish(message);
            usleep(1600000);

            RCLCPP_INFO(this->get_logger(), "Step 6");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
            message.position = {2048,2048,2148,1948,1024,3072,2048,2048,2047,2047,1920,2176,2300,1748,2176,1843,2047,2047,2047};   
            publisher_->publish(message);
            usleep(2000000);


            RCLCPP_INFO(this->get_logger(), "Step 7");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
            message.position = {2048,2048,2148,1948,1024,3072,2048,2048,2047,2047,1711,2385,2601,1495,2341,1753,2047,2047,2047};   
            publisher_->publish(message);
            usleep(2000000);


            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 30;
            publisher_single->publish(message_single);
            
            RCLCPP_INFO(this->get_logger(), "Step 8");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
            message.position = {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1670,2406,2791,1306,2495,1634,2048,2081,2047,2047};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(5)); //1
            break;
          case 17: // Stand up front OK
              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 80;
              publisher_single->publish(message_single);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
              message.position = {2047,2047,2048,2048,417,3679,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047, 2047};   
              publisher_->publish(message);
              RCLCPP_INFO(this->get_logger(), "Move 1"); 
              usleep(3000000);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2     3    4    5    6    7    8   9   10   11  12   13  14  15   16   17   18   19   20
              message.position = {2803,1293,2096,2000,852,3244,2047,2047,2047,2047,606,3259,3440,665,2657,1296,2047,2047,2047, 2047};   
              RCLCPP_INFO(this->get_logger(), "Move 2"); 
              publisher_->publish(message);
              usleep(1500000);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
              message.position = {2755,1339,2096,2000,2048,2048,2047,2047,2047,2047,573,3523,3451,632,2690,1406,2047,2047,2047, 2047};   
              RCLCPP_INFO(this->get_logger(), "Move 3"); 
              publisher_->publish(message);
              usleep(2000000);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
              message.position = {2755,1339,2096,2000,2048,2048,2047,2047,2047,2047,573,3523,3638,434,2690,1406,2047,2047,2047, 2047};   
              RCLCPP_INFO(this->get_logger(), "Move 3.5"); 
              publisher_->publish(message);
              usleep(3000000);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
              message.position = {2048,2048,2148,1948,1024,3072,2047,2047,2047,2047,841,3259,3644,452,2657,1494,2047,2047,2047, 2047};   
              RCLCPP_INFO(this->get_logger(), "Move 4"); 
              publisher_->publish(message);
              usleep(1500000);

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 30;
              publisher_single->publish(message_single);

              message_single.id = 13;
              message_single.address = 112;
              message_single.position = 60;
              publisher_single->publish(message_single);

              message_single.id = 14;
              message_single.address = 112;
              message_single.position = 60;
              publisher_single->publish(message_single);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
              message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1248,2848,3644,452,2848,1248,2047,2047,2047, 2047};   
              publisher_->publish(message);
              usleep(2500000);
              
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17    18   19    20
              message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1920,2176,2300,1748,2176,1920,2047,2047,2047, 2047};   
              publisher_->publish(message);
              usleep(20000000);

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 60;
              publisher_single->publish(message_single);
              break;
          case 18: // Andar esquerda
              RCLCPP_INFO(this->get_logger(), "Andar esquerda"); 
              message_walk.walk = 0;   
              message_walk.sidle = 0;  
              message_walk.turn = 0;   
              message_walk.walk_number = 8; 
              publisher_walk->publish(message_walk);
              std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
          case 19: // Andar direita
            RCLCPP_INFO(this->get_logger(), "Andar direita"); 
            message_walk.walk = 0;   
            message_walk.sidle = 20;  
            message_walk.turn = 0;   
            message_walk.walk_number = 7; 
            publisher_walk->publish(message_walk);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
          case 20: // Centralizar bola à esquerda
            RCLCPP_INFO(this->get_logger(), "Centralizando bola à esquerda"); 
            message_walk.walk_number = 0; 
            publisher_walk->publish(message_walk);  
            cont_vision+=15;
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19           20
            message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,cont_vision, cont_vision_up};
            publisher_->publish(message);
            usleep(300000);
            break;
        }
      }
    }

    void topic_callback(const std::shared_ptr<custom_interfaces::msg::Decision> msg) const
    {
      movement = (int)msg->decision;
      RCLCPP_INFO(this->get_logger(), "I heard %d", movement);
    } 

    rclcpp::Subscription<custom_interfaces::msg::Decision>::SharedPtr subscription_;
    rclcpp::Subscription<custom_interfaces::msg::NeckPosition>::SharedPtr subscription_neck;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr subscription_imu;
    rclcpp::Publisher<custom_interfaces::msg::SetPosition>::SharedPtr publisher_; 
    rclcpp::Publisher<custom_interfaces::msg::SetPositionOriginal>::SharedPtr publisher_single; 
    rclcpp::Publisher<custom_interfaces::msg::Walk>::SharedPtr publisher_walk;      
    rclcpp::Client<custom_interfaces::srv::Reset>::SharedPtr client;
    rclcpp::TimerBase::SharedPtr timer_;
};

void change_current_dir()
{
    char exepath[1024] = {0};
    if(readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
        chdir(dirname(exepath));
}

int main(int argc, char * argv[])
{
  change_current_dir();
  //Configurando para prioridade maxima para executar este processo-------
  char string1[50]; //String
  sprintf(string1,"echo 123456| sudo -S renice -20 -p %d", getpid());
  system(string1);//prioridade
  //GaitMove gaitMove(ini);
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