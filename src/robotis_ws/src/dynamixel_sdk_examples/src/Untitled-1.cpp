// Open terminal #2 
// $ ros2 run dynamixel_sdk_examples minimal_pub
// $ ros2 launch dynamixel_sdk_examples dynamixel_sdk_examples.launch.py

#include <chrono>
#include <memory>
#include <thread>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/set_position.hpp"
#include "custom_interfaces/msg/set_position_original.hpp"
using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher")
  {
    RCLCPP_INFO(this->get_logger(), "Run read minimal publisher");
    publisher_ = this->create_publisher<custom_interfaces::msg::SetPosition>("set_position", 10); 
    publisher_single = this->create_publisher<custom_interfaces::msg::SetPositionOriginal>("set_position_single", 10);
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = custom_interfaces::msg::SetPosition();   
    auto message_single = custom_interfaces::msg::SetPositionOriginal(); 
    RCLCPP_INFO(this->get_logger(), "Stand Up Back");
            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 40;
            publisher_single->publish(message_single);


            // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            // //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
            // message.position = {2048,2048,2096,2000,2048,2048,2048,2103,2048,2060,2048,2048,2048,2048,2048,2048,2048,2048,2048};   
            // publisher_->publish(message);
            // usleep(7000000);

          
            RCLCPP_INFO(this->get_logger(), "Step 1");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1    2    3    4   5   6    7    8    9   10   11   12   13   14   15   16   17   18   19    20
            message.position = {944,3203,2096,2000,804,3292,2048,2048,2048,2060,1315,2781,3665,442,2000,2096,2048,2048,2048,2048};   
            publisher_->publish(message);
            usleep(3000000);


            RCLCPP_INFO(this->get_logger(), "Step 2");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14   15   16   17   18   19  20
            message.position = {882,3214,2096,2000,1178,2918,2048,2048,2048,2060,952,3144,3665,442,1978,2118,2048,2048,2048,2048};   
            publisher_->publish(message);
            usleep(3000000);

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 70;
            publisher_single->publish(message_single);
            
            RCLCPP_INFO(this->get_logger(), "Step 3");
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19  20
            message.position = {1769,2294,2096,2000,2048,2048,2048,2048,2048,2060,1146,2950,3621,475,2296,1720,2048,2048,2048,2048};   
            publisher_->publish(message);
            usleep(3000000);

            RCLCPP_INFO(this->get_logger(), "Step 4");
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

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 30;
            publisher_single->publish(message_single);
            
            //Step7:
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
            message.position = {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1670,2406,2791,1306,2495,1634,2048,2081,2047,2047};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(5)); //1

  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<custom_interfaces::msg::SetPosition>::SharedPtr publisher_;     
  rclcpp::Publisher<custom_interfaces::msg::SetPositionOriginal>::SharedPtr publisher_single; 
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}