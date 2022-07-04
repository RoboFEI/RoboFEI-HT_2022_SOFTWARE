// Open terminal #2 
// $ ros2 run dynamixel_sdk_examples minimal_pub
#include <chrono>
#include <memory>
#include <thread>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/decision.hpp"

using namespace std::chrono_literals;

class DecisionNode : public rclcpp::Node
{
public:
  DecisionNode()
  : Node("decision")
  {
    RCLCPP_INFO(this->get_logger(), "Run read decision publisher");
    publisher_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::Decision>("/decision", 10); 
    timer_ = this->create_wall_timer(
      500ms, std::bind(&DecisionNode::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = dynamixel_sdk_custom_interfaces::msg::Decision();   
      message.decision = 14;          
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));   
      message.decision = 14;          
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));   
      message.decision = 14;          
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));   

      message.decision = 14;          
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));   
      message.decision = 14;          
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));   
      message.decision = 14;          
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));   
      message.decision = 14;          
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));   
      message.decision = 14;          
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));   
      message.decision = 14;          
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));   
      message.decision = 14;          
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));   

      message.decision = 15;          
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));

  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::Decision>::SharedPtr publisher_;     
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DecisionNode>());
  rclcpp::shutdown();
  return 0;
}