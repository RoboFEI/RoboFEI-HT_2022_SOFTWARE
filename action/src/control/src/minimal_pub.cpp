// Open terminal #2 
// $ ros2 run dynamixel_sdk_examples minimal_pub
#include <chrono>
#include <memory>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/set_position.hpp"
#include "custom_interfaces/msg/decision.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
int movement = 1;
int i=0; 

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    RCLCPP_INFO(this->get_logger(), "Running action node");
    subscription_ = this->create_subscription<custom_interfaces::msg::Decision>(
      "/decision", 10, std::bind(&MinimalPublisher::topic_callback, this, _1));
    publisher_ = this->create_publisher<custom_interfaces::msg::SetPosition>("set_position", 10);    
    if(movement==1){
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback_goodbye, this));
    }
    else{
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback_stop, this));
    }
  }

  void topic_callback(const std::shared_ptr<custom_interfaces::msg::Decision> msg) const
  {
    auto message_dec = custom_interfaces::msg::Decision();
    message_dec.decision = msg->decision;
    movement = (int)message_dec.decision;
    RCLCPP_INFO(this->get_logger(), "I heard %d", (int)msg->decision);
  }

  void timer_callback_goodbye() 
  {
    RCLCPP_INFO(this->get_logger(), "Goodbye");
    auto message = custom_interfaces::msg::SetPosition();                              
    while (i<=1){
      RCLCPP_INFO(this->get_logger(), "%d", i);
      message.id = {2, 4, 6};          
      message.position = {1024, 1024, 2593};   
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));
      message.id = {2, 4, 6};          
      message.position = {1024, 1024, 3553};   
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));
      i++;
      // RCLCPP_INFO(this->get_logger(), "%d", i);
      if (i==1){
        break;
      }
    }
    rclcpp::TimerBase::SharedPtr timer_;     
    rclcpp::Subscription<custom_interfaces::msg::Decision>::SharedPtr subscription_;
    rclcpp::Publisher<custom_interfaces::msg::SetPosition>::SharedPtr publisher_;    
    size_t count_;
  }

  void timer_callback_stop() 
  {
    RCLCPP_INFO(this->get_logger(), "Stopping");
    auto message = custom_interfaces::msg::SetPosition();                               
    for (int i=1; i<=8; i=i*2){
      RCLCPP_INFO(this->get_logger(), "%d", i);
      message.id = {2, 4, 6};          
      message.position = {1024, 1024, 2593};   
      publisher_->publish(message);
      std::this_thread::sleep_for(std::chrono::seconds(1));
      // RCLCPP_INFO(this->get_logger(), "%d", i);
    }
  }

  rclcpp::TimerBase::SharedPtr timer_;     
  rclcpp::Subscription<custom_interfaces::msg::Decision>::SharedPtr subscription_;
  rclcpp::Publisher<custom_interfaces::msg::SetPosition>::SharedPtr publisher_;    
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}