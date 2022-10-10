// Open terminal #2 
// $ ros2 run dynamixel_sdk_examples minimal_pub
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
 
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = custom_interfaces::msg::SetPosition();  
  
     for (int i=1; i<=4; i++){
        message.id = {2, 4, 6};          
        message.position = {1024, 1024, 2593};   
        publisher_->publish(message);
        std::this_thread::sleep_for(std::chrono::seconds(5));
        message.id = {2, 4, 6};          
        message.position = {1024, 1024, 3553};   
        publisher_->publish(message);
        std::this_thread::sleep_for(std::chrono::seconds(5));
        // RCLCPP_INFO(this->get_logger(), "%d", i);
        if (i%4==0){
          message.id = {2, 4, 6};          
          message.position = {1900, 1950, 2200};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<custom_interfaces::msg::SetPosition>::SharedPtr publisher_;     
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}






















































/*


// Open terminal #2 
// $ ros2 run dynamixel_sdk_examples minimal_pub
#include <chrono>
#include <memory>
#include <thread>

#include "rclcpp/rclcpp.hpp"
// #include "dynamixel_sdk_custom_interfaces/msg/set_position.hpp"
#include "custom_interfaces/msg/set_position.hpp"


using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 10);    // CHANGE
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = dynamixel_sdk_custom_interfaces::msg::SetPosition();                               
    for (int i=1; i<=4; i++){
        message.id = {2, 4, 6};          
        message.position = {1024, 1024, 2593};   
        publisher_->publish(message);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        message.id = {2, 4, 6};          
        message.position = {1024, 1024, 3553};   
        publisher_->publish(message);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // RCLCPP_INFO(this->get_logger(), "%d", i);
        if (i%4==0){
          message.id = {2, 4, 6};          
          message.position = {1900, 1950, 2200};   
          publisher_->publish(message);
          std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>::SharedPtr publisher_;         // CHANGE
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}

*/
