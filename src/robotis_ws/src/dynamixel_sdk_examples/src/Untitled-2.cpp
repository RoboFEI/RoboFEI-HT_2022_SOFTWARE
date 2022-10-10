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
    RCLCPP_INFO(this->get_logger(), "Stand Up Front");               
    // std::this_thread::sleep_for(std::chrono::seconds(1));       
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