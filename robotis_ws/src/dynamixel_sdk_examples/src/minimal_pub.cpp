// Open terminal #2 
// $ ros2 run dynamixel_sdk_examples minimal_pub
#include <chrono>
#include <memory>
#include <thread>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/set_position.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher")
  {
    RCLCPP_INFO(this->get_logger(), "Run read minimal publisher");
    publisher_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 10); 
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();   
      message.id = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};          
      message.position = {1024, 1024, 2593, 1024, 1024, 2593, 1024, 1024, 2593, 1024, 1024, 2593, 1024, 1024, 2593, 1024, 1024, 2593};   
      // for (int i=0; i<=18; i++){
      //   printf("ID: %d", message.id[i]);
      //   printf("ID: %d", message.position[i]);
      // }
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>::SharedPtr publisher_;     
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}