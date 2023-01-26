// Open terminal #2 
// $ ros2 run dynamixel_sdk_examples minimal_pub
#include <chrono>
#include <memory>
#include <thread>
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <libgen.h> //dirname

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/set_position.hpp"
#include "custom_interfaces/msg/decision.hpp"
#include "custom_interfaces/msg/vision.hpp"
#include "custom_interfaces/msg/walk.hpp"
#include "custom_interfaces/msg/humanoid_league_msgs.hpp"
#include "custom_interfaces/msg/set_position_original.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

bool gc = true;
int cont_vision = 2048;
int cont_vision_up = 1586;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher")
  {
    RCLCPP_INFO(this->get_logger(), "Run read minimal publisher");
    publisher_ = this->create_publisher<custom_interfaces::msg::SetPosition>("set_position", 10); 
    publisher_single = this->create_publisher<custom_interfaces::msg::SetPositionOriginal>("set_position_single", 10);
    publisher_walk = this->create_publisher<custom_interfaces::msg::Walk>("walking", 10); 
    subscription_vision = this->create_subscription<custom_interfaces::msg::Vision>(
      "ball_position", 10, std::bind(&MinimalPublisher::topic_callback_vision, this, _1));
  }

private:

  void topic_callback_vision(const std::shared_ptr<custom_interfaces::msg::Vision> vision_msg) const
      {
        auto ball_left = vision_msg->ball_left;
        auto ball_center_left = vision_msg->ball_center_left;
        auto ball_detect = vision_msg->ball_detected;
        auto ball_med = vision_msg->ball_med;
        auto ball_close = vision_msg->ball_close;
 
      auto message = custom_interfaces::msg::SetPosition();   
      auto message_single = custom_interfaces::msg::SetPositionOriginal(); 
      if (ball_detect){
        if (ball_med || ball_close){
          if (ball_left || ball_center_left){
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
          }
          else{
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
          }
        }
      }
      else{
        RCLCPP_INFO(this->get_logger(), "Parado");                            
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
            message.position = {1724,2367,2217,1878,627,3468,2052,2044,2048,2048,1712,2384,2791,1305,2536,1560,2048,2048,   cont_vision, cont_vision_up};
            publisher_->publish(message);
      }
    }
      
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<custom_interfaces::msg::SetPosition>::SharedPtr publisher_; 
    rclcpp::Publisher<custom_interfaces::msg::SetPositionOriginal>::SharedPtr publisher_single; 
    rclcpp::Publisher<custom_interfaces::msg::Walk>::SharedPtr publisher_walk;   
  rclcpp::Subscription<custom_interfaces::msg::Vision>::SharedPtr subscription_vision;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}