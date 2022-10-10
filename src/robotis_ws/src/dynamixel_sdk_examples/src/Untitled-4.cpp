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
     RCLCPP_INFO(this->get_logger(), "Parado");                            
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
            message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,2048,2048};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(4)); //1
    RCLCPP_INFO(this->get_logger(), "Right kick");                            
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
            std::this_thread::sleep_for(std::chrono::seconds(4)); //1
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


