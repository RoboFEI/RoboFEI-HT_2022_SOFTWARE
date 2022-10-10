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
    RCLCPP_INFO(this->get_logger(), "Right kick");                            
    message_single.id = 254;
    message_single.address = 112;
    message_single.position = 630;
    publisher_single->publish(message_single);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1


    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
    message.position = {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2081,2047,2047};
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(5)); //1

    message_single.id = 254;
    message_single.address = 112;
    message_single.position = 15;
    publisher_single->publish(message_single);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1

    // 3 = 2048 + 70 // 4 = 248 - 70
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19    20
    message.position = {2047,2047,2116,1976,2046,2046,2047,2047,2040,2164,1744,2324,2398,1654,2231,1882,2119,2191,2047,2047};

    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(3)); //1


    // Dobrar joelhos
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20
    message.position = {2047,2047,2648,1957,1240,3598,2047,2047,2040,2164,1726,2348,2398,1472,2238,1796,2152,2140,2047,2047};   
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1


    // Equilibrar em uma perna
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14  15   16   17   18   19
    message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2164,1616,1738,2508,943,2281,1551,2152,2046,2793,2047};   
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1
    
    
        // Perna pra trás
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13  14   15   16   17   18   19
    message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2244,1616,1738,2508,943,2281,1798,2152,2046,2793,2047};   
    publisher_->publish(message);

    message_single.id = 12;
    message_single.address = 112;
    message_single.position = 8400;
    publisher_single->publish(message_single);
      std::this_thread::sleep_for(std::chrono::seconds(1)); //1

    message_single.id = 14;
    message_single.address = 112;
    message_single.position = 4200;
    publisher_single->publish(message_single);
      std::this_thread::sleep_for(std::chrono::seconds(1)); //1

    message_single.id = 16;
    message_single.address = 112;
    message_single.position = 4200;
    publisher_single->publish(message_single);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1

        // Quase chute
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13  14   15   16   17   18   19
    message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2244,1616,1738,2508,877,2281,1903,2152,2046,2793,2047};   
    publisher_->publish(message);
    usleep(2000000);

    message_single.id = 12;
    message_single.address = 112;
    message_single.position = 15000;
    publisher_single->publish(message_single);

    message_single.id = 14;
    message_single.address = 112;
    message_single.position = 15000;
    publisher_single->publish(message_single);

    message_single.id = 15;
    message_single.address = 112;
    message_single.position = 750;
    publisher_single->publish(message_single);


        // Chute
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                   1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2244,1616,3215,2508,1534,2216,1798,2152,1991,2793,2047};   
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(2)); //1

    message_single.id = 254;
    message_single.address = 112;
    message_single.position = 10;
    publisher_single->publish(message_single);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1

       // Quase chute
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13  14   15   16   17   18   19
    message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2244,1616,1738,2530,943,2260,2046,2145,2046,2047,2047};   
    publisher_->publish(message);
    usleep(2000000);


        // Perna pra trás
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13  14   15   16   17   18   19
    message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2244,1616,1738,2530,943,2260,1798,2145,2046,2047,2047};   
    publisher_->publish(message);


        // Equilibrar em uma perna
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14  15   16   17   18   19
    message.position = {2047,2047,2579,1957,1240,3587,2047,2047,2040,2164,1616,1738,2530,943,2260,1798,2145,2046,2047,2047};   
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1

    message_single.id = 254;
    message_single.address = 112;
    message_single.position = 4000;
    publisher_single->publish(message_single);
    
    message_single.id = 17;
    message_single.address = 112;
    message_single.position = 10;
    publisher_single->publish(message_single);

        // Dobrar joelhos
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {2047,2047,2648,1957,1240,3598,2047,2047,2040,2164,1726,2348,2398,1472,2200,1796,2152,2140,2047,2047};   
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1

    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
    message.position = {1727,2370,2282,1800,626,3467,2050,1987,1988,2062,1765,2327,2788,1303,2534,1558,2046,2046,2047,2047};
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(5)); //1

    message_single.id = 254;
    message_single.address = 112;
    message_single.position = 128;
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