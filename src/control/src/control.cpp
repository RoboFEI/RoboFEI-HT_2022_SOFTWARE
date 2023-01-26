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
#include "custom_interfaces/msg/vision.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "custom_interfaces/msg/neck_position.hpp"
#include "GaitMove.hpp"
#include "custom_interfaces/msg/set_position_original.hpp"
#include "custom_interfaces/srv/reset.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
int movement = 1;
int last_movement = 1;
int contador = 0;
int cont_vision = 2047;
int cont_vision_up = 1300;
int cont_fall_side = 0;
bool stop_gait = true;
bool fallen = false;
bool fallenFront = false;
bool fallen_side = false;
double X_amplitude = 4;
double Y_amplitude = 4;
double A_amplitude = 4;
bool same_moviment = false;
uint32_t valor = 246;
uint32_t valor_up = 250;
int neck_sides = 2048;
int neck_up = 2048;


int contador_gait = 0;

int cont = 0;
int limit[2][3] = {{1826, 1528, 1230}, {2270, 1972, 2866}};

using namespace Robot;

class Control : public rclcpp::Node
{
public:
  Control()
  : Node("control")
  {
    RCLCPP_INFO(this->get_logger(), "Running action node");
    subscription_ = this->create_subscription<custom_interfaces::msg::Decision>(
      "/decision", 10, std::bind(&Control::topic_callback_decision, this, _1));
    subscription_neck = this->create_subscription<custom_interfaces::msg::NeckPosition>(
      "/neck_position", 10, std::bind(&Control::topic_callback_neck, this, _1));
    subscription_imu = this->create_subscription<sensor_msgs::msg::Imu>(
    "imu/data", 10, std::bind(&Control::topic_callback_imu, this, _1));
    publisher_ = this->create_publisher<custom_interfaces::msg::SetPosition>("set_position", 10); 
    publisher_single = this->create_publisher<custom_interfaces::msg::SetPositionOriginal>("set_position_single", 10);
    publisher_walk = this->create_publisher<custom_interfaces::msg::Walk>("walking", 10); 
    // client = this->create_client<custom_interfaces::srv::Reset>("imu/reset");
    // auto req = std::make_shared<custom_interfaces::srv::Reset::Request>();
    // req->reset_ekf = true;
    // if (!client->wait_for_service(1s)) {
    //   if (!rclcpp::ok()) {
    //     RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
    //   }
    //   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    // }
    // auto result = client->async_send_request(req);
    // // Wait for the result.
    // if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) ==
    //   rclcpp::FutureReturnCode::SUCCESS)
    //   {
    //     RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Reset successful");
    //   } 
    //   else {
    //     RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to reset");
    //   }
    }

  private:
    void topic_callback_imu(const std::shared_ptr<sensor_msgs::msg::Imu> imu_msg_) const
    {
      float IMU_ACCEL_Z = imu_msg_->linear_acceleration.z/10;
      float IMU_ACCEL_X = imu_msg_->linear_acceleration.x/10;
      //RCLCPP_INFO(this->get_logger(),"ACEL Z %f\n", IMU_ACCEL_Z);
      if(IMU_ACCEL_Z > 0.7 || IMU_ACCEL_Z < -0.7)
        contador++;
      else
        contador = 0;
      //RCLCPP_INFO(this->get_logger(),"Contador %d \n", contador);
      
      if(contador>=30)
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
      //RCLCPP_INFO(this->get_logger(),"Contador fall side %d \n", cont_fall_side);
      
      if(cont_fall_side>=30)
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

    void topic_callback_decision(const std::shared_ptr<custom_interfaces::msg::Decision> msg) const{
      RCLCPP_INFO(this->get_logger(), "Decision Callback " );   
      movement = (int)msg->decision;
      auto message_walk = custom_interfaces::msg::Walk();  
      auto message = custom_interfaces::msg::SetPosition();   
      auto message_single = custom_interfaces::msg::SetPositionOriginal();  
      RCLCPP_INFO(this->get_logger(), "decision: %d", movement); 
      
      //printf("decision: %d", movement);

      if(fallen == true){ // Robô caido, tem que levantar antes de qualquer movimento
        message_walk.walk = 0; 
        publisher_walk->publish(message_walk);
        if (fallenFront == true){ // Caido de frente OK     
          RCLCPP_INFO(this->get_logger(), "Stand Up Front");                     
          message_single.id = 254;
          message_single.address = 112;
          message_single.position = 80;
          publisher_single->publish(message_single);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
          message.position = {2047,2047,2183,1896,417,3679,2048,2067,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047};   
          publisher_->publish(message);
          usleep(3000000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
          message.position = {2152,1942,2183,1896,766,3328,2048,2067,2047,2047,837,3259,3028,1066,2919,1175,2047,2047,2047};   
          publisher_->publish(message);
          usleep(1500000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2755,1339,2183,1896,2048,2048,2048,2067,2047,2047,837,3259,3275,819,2657,1494,2047,2047,2047};   
          publisher_->publish(message);

          message_single.id = 254;
          message_single.address = 112;
          message_single.position = 128;
          publisher_single->publish(message_single);

          usleep(1500000);



          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2612,1484,2183,1896,2048,2048,2048,2067,2047,2047,837,3259,3574,522,2705,1391,2047,2047,2047};   
          publisher_->publish(message);

          message_single.id = 254;
          message_single.address = 112;
          message_single.position = 10;
          publisher_single->publish(message_single);
          usleep(1500000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2755,1339,2183,1896,2048,2048,2048,2067,2047,2047,841,3259,3644,452,2551,1545,2047,2047,2047};   
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

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1248,2848,3644,452,2848,1248,2047,2047,2047};   
          publisher_->publish(message);
          usleep(3000000);

          message_single.id = 254;
          message_single.address = 112;
          message_single.position = 10;
          publisher_single->publish(message_single);

          usleep(1000000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1248,2848,3181,909,2533,1555,2047,2047,2047};   
          publisher_->publish(message);
          usleep(3000000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
          //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
          message.position = {1724,2372,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,   2048,    1300};
          publisher_->publish(message);

          message_single.id = 254;
          message_single.address = 112;
          message_single.position = 60;
          publisher_single->publish(message_single);   
          usleep(2000000);
          fallen = false;
        }
        else{ // Robô caido de costas OK
          RCLCPP_INFO(this->get_logger(), "Stand Up Back");
          message_single.id = 254;
            message_single.address = 112;
            message_single.position = 40;
            publisher_single->publish(message_single);
          
            RCLCPP_INFO(this->get_logger(), "Step 1");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1    2    3    4   5   6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {944,3203,2152,1943,804,3292,2048,2048,2048,2060,1315,2781,3665,442,2000,2096,2048,2048,2048,2048};   
            publisher_->publish(message);
            usleep(2400000);


            RCLCPP_INFO(this->get_logger(), "Step 2");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14   15   16   17   18   19  20
            message.position = {882,3214,2152,1943,1178,2918,2048,2048,2048,2060,952,3144,3665,442,1978,2118,2048,2048,2048,2048};   
            publisher_->publish(message);
            usleep(2000000);
            
            RCLCPP_INFO(this->get_logger(), "Step 3");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19  20
            message.position = {1769,2294,2152,1943,2048,2048,2048,2048,2048,2060,1146,2950,3621,475,2296,1801,2048,2048,2048,2048};   
            publisher_->publish(message);
            usleep(1800000);

            RCLCPP_INFO(this->get_logger(), "Step 4");
            //Parar 3.5 e colocar os msms só que melhorados para o 3.9
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            message.position = {1753,2359,2152,1943,2048,2048,2048,2048,2048,2060,1248,2848,3644,452,2848,1248,2047,2048,2048};   
            publisher_->publish(message);
            usleep(2000000);

            RCLCPP_INFO(this->get_logger(), "Step 5");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4    5    6    7    8    9   10   11  12   13   14  15   16   17   18   19
            message.position = {1732,2397,2214,1882,2012,2033,2105,2106,2034,2071,1814,2254,3658,440,3151,924,2045,2047,2048};   
            publisher_->publish(message);
            usleep(2000000);

              message_single.id = 254;
            message_single.address = 112;
            message_single.position = 20;
            publisher_single->publish(message_single);

            RCLCPP_INFO(this->get_logger(), "Step 6");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4    5    6    7    8    9   10   11  12   13   14  15   16   17   18   19
            message.position = {1724,2367,2294,1812,627,3468,2105,2106,2034,2071,1429,2694,3658,440,3151,924,2045,2047,2048};   
            publisher_->publish(message);


            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 45;
            publisher_single->publish(message_single);

            message_single.id = 11;
            message_single.address = 112;
            message_single.position = 30;
            publisher_single->publish(message_single);

            message_single.id = 15;
            message_single.address = 112;
            message_single.position = 30;
            publisher_single->publish(message_single);

            message_single.id = 16;
            message_single.address = 112;
            message_single.position = 35;
            publisher_single->publish(message_single);

            message_single.id = 12;
            message_single.address = 112;
            message_single.position = 35;
            publisher_single->publish(message_single);

            usleep(2000000);
            RCLCPP_INFO(this->get_logger(), "Step 9");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
            message.position = {1724,2367,2217,1878,627,3468,2052,2044,2048,2048,1712,2384,2791,1305,2536,1560,2048,2048,2048,2345};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(5)); //1

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 90;
            publisher_single->publish(message_single);

          fallen = false;
        }
      }
      else if (fallen_side == true){
        message_walk.walk = 0; 
        publisher_walk->publish(message_walk);

        message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
        message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,2048,2048};
        publisher_->publish(message);
        std::this_thread::sleep_for(std::chrono::seconds(2)); //1

        message_single.id = 254;
        message_single.address = 112;
        message_single.position = 10000;
        publisher_single->publish(message_single);
        std::this_thread::sleep_for(std::chrono::seconds(1)); //1


        message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
        message.position = {3154,2367,2294,1812,1463,3468,2052,2044,2032,2106,611,1178,2791,1306,2536,1560,2048,2081,2047,2047};
        publisher_->publish(message);
        std::this_thread::sleep_for(std::chrono::seconds(2)); //1 

        message_single.id = 254;
        message_single.address = 112;
        message_single.position = 10000;
        publisher_single->publish(message_single);
        std::this_thread::sleep_for(std::chrono::seconds(2)); //1

        message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
        message.position = {3154,2367,2294,998,1463,3468,2052,2044,2032,2106,1168,1178,3244,2483,2536,1560,2048,2081,2047,2047};
        publisher_->publish(message);
        std::this_thread::sleep_for(std::chrono::seconds(1)); //1 

        message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
        message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,2048,2048};
        publisher_->publish(message);
        std::this_thread::sleep_for(std::chrono::seconds(2)); //1

        fallen_side = false;
      }
      else{

        // if (movement != last_movement && (movement == 5 || movement == 6 || movement == 9 || movement == 10  || movement ==14 || movement == 15 || movement == 18 || movement == 19) ){
          
        //   if(fallen == true || fallen_side == true || contador_gait >= 500){
        //     printf("CAIU Durante Gait\n");
        //     contador_gait = 0;
        //     last_movement = movement;
        //   } 
        //   else if (contador_gait < 500){
        //     RCLCPP_INFO(this->get_logger(), "Gait"); 
        //     message_single.id = 254;
        //     message_single.address = 112;
        //     message_single.position = 128;
        //     publisher_single->publish(message_single);
        //     message_walk.walk = 0;   
        //     message_walk.sidle = 0;  
        //     message_walk.turn = 0;   
        //     message_walk.walk_number = 2; 
        //     publisher_walk->publish(message_walk);
        //     contador_gait += 1; 
        //   }
          
        //   //sleep(5);

        // }
          switch (movement){
            case 1: // Parado
              message_walk.walk_number = 0; 
              publisher_walk->publish(message_walk);
              RCLCPP_INFO(this->get_logger(), "Parado");                            
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
              message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2136,   2048,    1586};
              publisher_->publish(message);
              break;
            case 2: // Greeting
              message_walk.walk_number = 0; 
              publisher_walk->publish(message_walk);
              RCLCPP_INFO(this->get_logger(), "Greeting");                            
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
              message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2136,   2048,    1586};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(1));
              break;
              
              
            case 3: // Right kick
              message_walk.walk_number = 0;
              publisher_walk->publish(message_walk);
              RCLCPP_INFO(this->get_logger(), "Right kick");

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 128;
              publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1 

              //apoiando no pe
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
              message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2057,1712,2384,2799,1306,2536,1560,2298,1993,2047,cont_vision_up};
              publisher_->publish(message);

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 3;
              publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1 

              message_single.id = 6;
              message_single.address = 112;
              message_single.position = 15;
              publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1 



              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
              message.position = {1724,2147,2217,1757,627,2467,2052,2044,2032,2057,1483,2384,3056,1306,2536,1560,2298,1993,2047,cont_vision_up};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1


              //Levantando perna para tras
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
              message.position = {1724,2147,2217,1757,627,2467,2052,2044,2032,2057,2236,2384,2976,1306,2775,1560,2058,1993,2047,cont_vision_up};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 10;
              publisher_single->publish(message_single);
              message_single.id = 13;
              message_single.address = 112;
              message_single.position = 5;
              publisher_single->publish(message_single);
              message_single.id = 15;
              message_single.address = 112;
              message_single.position = 10;
              publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1 

              
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
              message.position = {1724,2147,2217,1500,627,2467,2052,2044,1928,2057,1291,2345,3360,1306,2278,1560,1956,1993,2047,cont_vision_up};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1

              message_single.id = 13;
              message_single.address = 112;
              message_single.position = 256;
              publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1 

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
              message.position = {1724,2147,2217,1500,627,2467,2052,2044,1928,2057,1291,2312,2283,1306,1997,1560,1956,1993,2047,cont_vision_up};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
              message.position = {1724,2147,2217,1500,627,2467,2052,2044,1928,2134,1291,2312,3297,1306,2572,1560,1956,1993,2047,cont_vision_up};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1 

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 128;
              publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1 

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
              message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1787,2384,2735,1306,2564,1560,2048,2136,   2048,    1300};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1 

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 128;
              publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1
                  
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
              message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2136,   2048,    1300};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1 


              break;
            case 4: // Left kick OK
              message_walk.walk_number = 0;
              publisher_walk->publish(message_walk);
              RCLCPP_INFO(this->get_logger(), "Left kick");                            
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
              message.position = {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1767,2329,2791,1306,2536,1560,2048,2048,2047,cont_vision_up};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 15;
              publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1

              // 3 = 2048 + 70 // 4 = 248 - 70
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19    20
              message.position = {2047,2047,2116,1976,2046,2046,2047,2047,2040,2164,1744,2324,2398,1654,2231,1882,2119,2191,2047,cont_vision_up};

              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(3)); //1


              // Dobrar joelhos
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20
              message.position = {2047,2047,2648,1957,1240,3598,2047,2047,2040,2144,1726,2348,2398,1472,2238,1823,2152,1974,2047,cont_vision_up};   
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1


              // Equilibrar em uma perna
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14  15   16   17   18   19
              message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2281,1551,2152,1915,2793,cont_vision_up};   
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1
              
              
              // // Equilibrar em uma perna
              // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              // //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14  15   16   17   18   19
              // message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2281,1551,2152,1915,2793,cont_vision_up};   
              // publisher_->publish(message);
              // std::this_thread::sleep_for(std::chrono::seconds(1)); //1
              
              
                  // Perna pra trás
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13  14   15   16   17   18   19
              message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2281,1798,2152,2046,2793,cont_vision_up};   
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
              message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,877,2281,1903,2152,2046,2793,cont_vision_up};   
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
              message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,3215,2508,1534,2216,1798,2152,1991,2793,cont_vision_up};   
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
              message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,877,2205,1903,2152,2046,2793,cont_vision_up};   
              publisher_->publish(message);
              usleep(2000000);


                  // Perna pra trás
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13  14   15   16   17   18   19
              message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2205,1798,2152,2046,2793,cont_vision_up};   
              publisher_->publish(message);


                  // Equilibrar em uma perna
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14  15   16   17   18   19
              message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2205,1551,2152,1915,2793,cont_vision_up};   
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
              message.position = {2047,2047,2648,1957,1240,3598,2047,2047,2040,2164,1726,2348,2508,1472,2238,1796,2152,2140,2047,cont_vision_up};   
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
              message.position = {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1767,2329,2791,1306,2536,1560,2048,2048,2047,cont_vision_up};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 128;
              publisher_single->publish(message_single);
              movement = 1;
              
              break;

            case 5: // Turn right
              RCLCPP_INFO(this->get_logger(), "Turn Right");  
              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 128;
              publisher_single->publish(message_single);                      
              message_walk.walk = 0;   
              message_walk.sidle = 0;  
              message_walk.turn = -27;   
              message_walk.walk_number = 11; 
              publisher_walk->publish(message_walk);
              break;
            case 6: // Turn left
              RCLCPP_INFO(this->get_logger(), "Turn Left");      
              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 128;
              publisher_single->publish(message_single);                      
              message_walk.walk = 0;   
              message_walk.sidle = 0;  
              message_walk.turn = 30;   
              message_walk.walk_number = 12; 
              publisher_walk->publish(message_walk);
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
            case 8: // Search ball OK
              message_walk.walk_number = 0; 
              publisher_walk->publish(message_walk);        
              RCLCPP_INFO(this->get_logger(), "Moving head");

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 128;
              publisher_single->publish(message_single);


              //Thiago (errado )
              // cont_vision += valor;
              // if(cont_vision < limit[0][cont] || cont_vision > limit[1][cont])
              // {
              //   if(cont < 1)
              //   {
              //     cont++;
              //   }
              //   else cont = 0;
              //   valor *= -1;
            
              //   cont_vision_up += valor_up;
            
              //   if(cont_vision_up > 1850)
              //   {
              //     cont_vision_up = 1300;
              //   }
              // }

            
              // if(yyy == 0){
              //   cont_vision_up = 1350;
              //   if(xxx == 0){
              //     cont_vision = 2171;
              //     xxx++;
                  
              //   } else if(xxx == 1){
              //     cont_vision = 1925;
              //     xxx++;
              //   } else{
              //     xxx = 0;
              //     yyy++;
              //   }
              // } else if(yyy == 1){
              //   cont_vision_up = 1600;
              //   if(xxx == 0){
              //     cont_vision = 1467;
              //     xxx++;
              //   } else if(xxx == 1){
              //     cont_vision = 2048;
              //     xxx++;
              //   } else if(xxx == 2){
              //     cont_vision = 2629;
              //     xxx++;
              //   } else{
              //     xxx = 0;
              //     yyy++;
              //   }
              // } else if(yyy == 2){
              //   cont_vision_up = 1850;
              //   if(xxx == 0){
              //     cont_vision = 3073;
              //     xxx++;
              //   } else if(xxx == 1){
              //     cont_vision = 2560;
              //     xxx++;
              //   } else if(xxx == 2){
              //     cont_vision = 2048;
              //     xxx++;
              //   } else if(xxx == 3){
              //     cont_vision = 1535;
              //     xxx++;
              //   } else if(xxx == 4){
              //     cont_vision = 1023;
              //     xxx++;
              //   } else{
              //     xxx = 0;
              //     yyy = 0;
              //   }
              // }

              
              // printf("%d" , cont_vision_up);
              if (cont_vision_up + valor_up >= 1850){

                cont_vision_up = 1300;
              }
              else{
                cont_vision_up += valor_up;
              }

              // if (cont_vision_up + valor < 1850){
              //   cont_vision_up = 1300;
              // }
              // else if (cont_vision_up + valor > 1850){
              //   cont_vision_up = 1300;
              //   cont_vision = 2270;
              // }



              // cont_vision += valor;
              // if(cont_vision>=3071 || cont_vision<1024){
              //   valor *= -1;
              //   cont_vision_up += valor_up;
              //   RCLCPP_INFO(this->get_logger(), "Entrou no 1 if, cont_vision_up: %d",cont_vision); 
              //   if (cont_vision_up > 1850){
              //   //  RCLCPP_INFO(this->get_logger(), "Entrou no 2 if"); 
              //     cont_vision_up = 1300;
              //   }
              // }

              // Thiago
              // if(cont_vision>=3071 || cont_vision<1024)
              // { 
              //   valor *= -1;
              //   if(cont_vision_up > 1800 && !teste)
              //   {
              //     RCLCPP_INFO(this->get_logger(), "1");
              //     cont_vision_up = 1850;
              //     teste = true;
              //   }
              //   else
              //   {
              //     cont_vision_up += valor_up;
              //     RCLCPP_INFO(this->get_logger(), "2");
              //   }
              //   if(teste)
              //   {
              //     cont_vision_up = 1300;
              //     teste = false;
              //     RCLCPP_INFO(this->get_logger(), "3");
              //   }
              //   RCLCPP_INFO(this->get_logger(), "%d", teste);
              // }
              
              
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19           20
              message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2136,cont_vision, cont_vision_up};

              publisher_->publish(message);

              // std::this_thread::sleep_for(std::chrono::seconds(2));   
              
              break;
            case 9: // Turn ball clockwise
              RCLCPP_INFO(this->get_logger(), "Turn around ball clockwise");    
              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 128;
              publisher_single->publish(message_single);                       
              message_walk.walk = 0;     //Andar para frente  (-) ou para (+)tras
              message_walk.sidle = -60;  //Andar para lateral (-)esquerda (+)direita
              message_walk.turn = -12;   //Angulo de rotacao  (-)esquerda (+)direita
              message_walk.walk_number = 5; 
              publisher_walk->publish(message_walk);
              break;        
              
            case 10: // Turn ball anticlockwise
              RCLCPP_INFO(this->get_logger(), "Turn around ball anticlockwise");    
              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 128;
              publisher_single->publish(message_single);                        
              message_walk.walk = 0;   
              message_walk.sidle = 60;  
              message_walk.turn = 12;  
              message_walk.walk_number = 6; 
              publisher_walk->publish(message_walk);
              break;
            case 11: // Fall left OK
              message_walk.walk_number = 0; 
              publisher_walk->publish(message_walk);
              RCLCPP_INFO(this->get_logger(), "Fall left");   

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 2000;
              publisher_single->publish(message_single); 
                  

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
              message.position = {1724,2367,2217,1878,627,3468,2052,2044,2048,2048,1712,2384,2791,1305,2536,1560,2048,2048,   cont_vision, cont_vision_up};
              publisher_->publish(message);
              usleep(100000);

              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19  20 
              message.position = {2047,2047,2047,2047,2048,2048,2052,2044,2048,2048,1712,2384,2791,1305,2536,1560,2048,2048,   cont_vision, cont_vision_up};
              publisher_->publish(message);
              usleep(100000);

              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19  20 
              message.position = {2047,2047,4034,40,2048,2048,2052,2044,2048,2048,1712,2384,2791,1305,2536,1560,2048,2048,   cont_vision, cont_vision_up};
              publisher_->publish(message);
              usleep(100000);

              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19  20 
              message.position = {2047,2047,4034,40,2048,2048,2052,2044,2048,2048,1712,2998,2791,469,2536,1560,1794,1763,   cont_vision, cont_vision_up};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(20));
              break;
            case 12: // Fall right OK
              message_walk.walk_number = 0; 
              publisher_walk->publish(message_walk);
              RCLCPP_INFO(this->get_logger(), "Fall right");

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 2000;
              publisher_single->publish(message_single);
                  

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
              message.position = {1724,2367,2217,1878,627,3468,2052,2044,2048,2048,1712,2384,2791,1305,2536,1560,2048,2048,   cont_vision, cont_vision_up};
              publisher_->publish(message);
              usleep(200000);

              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19  20 
              message.position = {2047,2047,2047,2047,2048,2048,2052,2044,2048,2048,1712,2384,2791,1305,2536,1560,2048,2048,   cont_vision, cont_vision_up};
              publisher_->publish(message);
              usleep(200000);

              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19  20 
              message.position = {2047,2047,4034,40,2048,2048,2052,2044,2048,2048,1712,2384,2791,1305,2536,1560,2048,2048,   cont_vision, cont_vision_up};
              publisher_->publish(message); // 892 3662
              usleep(200000);

              //                    1   2     3   4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19  20 
              message.position = {2047,2047,4034,40,2048,2048,2052,2044,2048,2048,892,2384,3662,1305,2536,1560,2302,2333,   cont_vision, cont_vision_up};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(20)); 
          
              break;
            case 13: // Agachando OK
              message_walk.walk_number = 0;
              publisher_walk->publish(message_walk);
              RCLCPP_INFO(this->get_logger(), "Agachando"); 
              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 80;
              publisher_single->publish(message_single);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
              message.position = {2047,2047,2048,2048,417,3679,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047, 2047};   
              publisher_->publish(message);
              usleep(3000000);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2     3    4    5    6    7    8   9   10   11  12   13  14  15   16   17   18   19   20
              message.position = {2803,1293,2096,2000,852,3244,2047,2047,2047,2047,606,3259,3440,665,2657,1296,2047,2047,2047, 2047};  
              publisher_->publish(message);
              usleep(1500000);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
              message.position = {2755,1339,2096,2000,2048,2048,2047,2047,2047,2047,573,3523,3451,632,2690,1406,2047,2047,2047, 2047};  
              publisher_->publish(message);
              usleep(2000000);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
              message.position = {2755,1339,2096,2000,2048,2048,2047,2047,2047,2047,573,3523,3638,434,2690,1406,2047,2047,2047, 2047};   
              publisher_->publish(message);
              usleep(3000000);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
              //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
              message.position = {2048,2048,2148,1948,1024,3072,2047,2047,2047,2047,841,3259,3644,452,2657,1494,2047,2047,2047, 2047};  
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
              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 128;
              publisher_single->publish(message_single);
              message_walk.walk = 20;   
              message_walk.sidle = 0;  
              message_walk.turn = 0; 
              message_walk.walk_number = 1;  
              publisher_walk->publish(message_walk);
              break;
            case 15: // Gait OK
              RCLCPP_INFO(this->get_logger(), "Gait"); 
              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 128;
              publisher_single->publish(message_single);
              message_walk.walk = 0;   
              message_walk.sidle = 0;  
              message_walk.turn = 0;   
              message_walk.walk_number = 2; 
              publisher_walk->publish(message_walk);
              break;
            case 16: // Stand up back OK
              message_walk.walk_number = 0;
              publisher_walk->publish(message_walk);
              RCLCPP_INFO(this->get_logger(), "Stand up back");
              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 40;
              publisher_single->publish(message_single);
            
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1    2    3    4   5   6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
              message.position = {944,3203,2096,2000,804,3292,2048,2048,2048,2060,1315,2781,3665,442,2000,2096,2048,2048,2048,2048};   
              publisher_->publish(message);
              usleep(2400000);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
              //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14   15   16   17   18   19  20
              message.position = {882,3214,2096,2000,1178,2918,2048,2048,2048,2060,952,3144,3665,442,1978,2118,2048,2048,2048,2048};   
              publisher_->publish(message);
              usleep(2000000);

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 70;
              publisher_single->publish(message_single);
              
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19  20
              message.position = {1769,2294,2096,2000,2048,2048,2048,2048,2048,2060,1146,2950,3621,475,2296,1801,2048,2048,2048,2048};   
              publisher_->publish(message);
              usleep(1800000);

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


              // 15 = 2048 + 800 // 16 = 2048 - 800 //
              // 11 = 2048 - 800 // 12 = 2048 + 800 //
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
              //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
              message.position = {2400,1696,2148,1948,1024,3072,2048,2048,2047,2047,1248,2848,3644,452,2848,1248,2047,2047,2047};   
              publisher_->publish(message);
              usleep(1600000);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
              //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
              message.position = {2048,2048,2148,1948,1024,3072,2048,2048,2047,2047,1920,2176,2300,1748,2176,1843,2047,2047,2047};   
              publisher_->publish(message);
              usleep(2000000);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
              //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
              message.position = {2048,2048,2148,1948,1024,3072,2048,2048,2047,2047,1711,2385,2601,1495,2341,1753,2047,2047,2047};   
              publisher_->publish(message);
              usleep(2000000);

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 30;
              publisher_single->publish(message_single);
              
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
              message.position = {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1670,2406,2791,1306,2495,1634,2048,2081,2047,2047};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(5)); //1
              break;
            case 17: // Stand up front OK
                message_walk.walk_number = 0;
                publisher_walk->publish(message_walk);
                RCLCPP_INFO(this->get_logger(), "Stand up front"); 
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

                message_single.id = 254;
                message_single.address = 112;
                message_single.position = 10;
                publisher_single->publish(message_single);

                message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
                //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
                message.position = {2755,1339,2096,2000,2048,2048,2048,2067,2047,2047,837,3259,3574,522,2705,1391,2047,2047,2047};   
                publisher_->publish(message);
                usleep(1500000);

                message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
                //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
                message.position = {2755,1339,2096,2000,2048,2048,2048,2067,2047,2047,841,3259,3644,452,2551,1545,2047,2047,2047};   
                publisher_->publish(message);
                usleep(1500000);

                usleep(5000000);

                message_single.id = 254;
                message_single.address = 112;
                message_single.position = 1;
                publisher_single->publish(message_single);

                message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
                //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18    19  
                message.position = {1724,2367,2217,1878,627,3468,2052,2048,2032,2106,1712,2384,2791,1306,2536,1560,2048,2136, 2048};
                publisher_->publish(message);
                usleep(20000000);


                message_single.id = 254;
                message_single.address = 112;
                message_single.position = 60;
                publisher_single->publish(message_single); 

                message_single.id = 13;
                message_single.address = 112;
                message_single.position = 60;
                publisher_single->publish(message_single);

                message_single.id = 14;
                message_single.address = 112;
                message_single.position = 60;
                publisher_single->publish(message_single);

                message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
                //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
                message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1248,2848,3644,452,2848,1248,2047,2047,2047};   
                publisher_->publish(message);
                usleep(3000000);

                message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
                //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
                message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1920,2176,2300,1748,2176,1920,2047,2047,2047};   
                publisher_->publish(message);
                usleep(5000000);

                message_single.id = 254;
                message_single.address = 112;
                message_single.position = 1;
                publisher_single->publish(message_single);

                message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
                //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18    19  
                message.position = {1724,2367,2217,1878,627,3468,2052,2048,2032,2106,1712,2384,2791,1306,2536,1560,2048,2136, 2048};
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
              break;
            case 19: // Andar direita
              RCLCPP_INFO(this->get_logger(), "Andar direita"); 
              message_walk.walk = 0;   
              message_walk.sidle = 20;  
              message_walk.turn = 0;   
              message_walk.walk_number = 7; 
              publisher_walk->publish(message_walk);
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
              usleep(200000);
              break;
            case 21: // Centralizar bola à direita
              RCLCPP_INFO(this->get_logger(), "Centralizando bola à direita"); 
              message_walk.walk_number = 0; 
              publisher_walk->publish(message_walk);  
              cont_vision-=15;
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19           20
              message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,cont_vision, cont_vision_up};
              publisher_->publish(message);
              usleep(200000);
              break;
            case 22: // Centralizar bola no pé

              RCLCPP_INFO(this->get_logger(), "Centralizando bola no pé"); 
              message_walk.walk_number = 0; 
              publisher_walk->publish(message_walk);  
              cont_vision_up-=15;
              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19           20
              message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,cont_vision, cont_vision_up};
              publisher_->publish(message);
              usleep(200000);
              break;
            case 23: // Levantando de lado
              message_walk.walk_number = 0; 
              RCLCPP_INFO(this->get_logger(), "Levantando de lado"); 
              publisher_walk->publish(message_walk);

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
              message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,2048,2048};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 10000;
              publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1


              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
              message.position = {3154,2367,2294,1812,1463,3468,2052,2044,2032,2106,611,1178,2791,1306,2536,1560,2048,2081,2047,2047};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1 

              message_single.id = 254;
              message_single.address = 112;
              message_single.position = 10000;
              publisher_single->publish(message_single);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
              message.position = {3154,2367,2294,998,1463,3468,2052,2044,2032,2106,1168,1178,3244,2483,2536,1560,2048,2081,2047,2047};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(1)); //1 

              message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
              //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
              message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,2048,2048};
              publisher_->publish(message);
              std::this_thread::sleep_for(std::chrono::seconds(2)); //1

              fallen_side = false;
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