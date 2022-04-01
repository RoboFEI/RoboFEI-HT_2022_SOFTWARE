// Open terminal #2 
// $ ros2 run control control
#include <chrono>
#include <memory>
#include <thread>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/set_position.hpp"
#include "custom_interfaces/msg/decision.hpp"
#include "GaitMove.hpp"

#define INI_FILE_PATH       "../../Action/src/control_framework/config.ini"

using namespace std::chrono_literals;
using std::placeholders::_1;
int movement = 1;
int i=0; 
bool stop_gait = true;

class Control : public rclcpp::Node
{
public:
  Control()
  : Node("control"), count_(0)
  {
    RCLCPP_INFO(this->get_logger(), "Running action node");
    GaitMove gaitMove(ini);
    subscription_ = this->create_subscription<custom_interfaces::msg::Decision>(
      "/decision", 10, std::bind(&Control::topic_callback, this, _1));
    publisher_ = this->create_publisher<custom_interfaces::msg::SetPosition>("set_position", 10); 
    movement = 2;   
    if(movement==1){
      timer_ = this->create_wall_timer(
      500ms, std::bind(&Control::timer_callback_goodbye, this));
    }
    else if(movement == 2){
      
      gaitMove.walk_foward_fast(stop_gait, false);
    }
    else{
      timer_ = this->create_wall_timer(
      500ms, std::bind(&Control::timer_callback_stop, this));
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
    message.id = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};          
    message.position = {1024, 1024, 2593, 1024, 1024, 2593, 1024, 1024, 2593, 1024, 1024, 2593, 1024, 1024, 2593, 1024, 1024, 2593};   
    // for (int i=0; i<=18; i++){
    //   printf("ID: %d", message.id[i]);
    //   printf("ID: %d", message.position[i]);
    // }
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(1));

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
  minIni* ini;
  ini = new minIni((char *)INI_FILE_PATH);
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Control>());
  rclcpp::shutdown();
  return 0;
}