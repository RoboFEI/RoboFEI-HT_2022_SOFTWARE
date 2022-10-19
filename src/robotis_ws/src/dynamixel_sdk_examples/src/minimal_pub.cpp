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

int cont_vision_up = 1300;
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
         RCLCPP_INFO(this->get_logger(), "Right kick");

            RCLCPP_INFO(this->get_logger(), "Right kick");

             //parado                    
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
            message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2136,   2048,    1300};
            publisher_->publish(message);

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 128;
            publisher_single->publish(message_single);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1 

            //apoiando no pe
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
            message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2057,1712,2384,2799,1306,2536,1560,2298,1965,2047,cont_vision_up};
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
            message_single.position = 10;
            publisher_single->publish(message_single);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1 

            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
            message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1787,2384,2735,1306,2564,1560,2048,2136,   2048,    1300};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(2)); //1 

            message_single.id = 254;
            message_single.address = 112;
            message_single.position = 80;
            publisher_single->publish(message_single);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1
                 
            message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
            //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
            message.position = {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2136,   2048,    1300};
            publisher_->publish(message);
            std::this_thread::sleep_for(std::chrono::seconds(1)); //1 







    


               

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