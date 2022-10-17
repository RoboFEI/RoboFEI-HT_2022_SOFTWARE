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


    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {2048,2048,2096,2000,2048,2048,2048,2103,2048,2060,2048,2048,2048,2048,2048,2048,2048,2048,2048};   
    publisher_->publish(message);
    usleep(3000000);

    // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    // //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    // message.position = {2048,2048,2096,2000,2048,2048,2048,2048,2048,2060,1348,2748,3500,596,1748,2348,2048,2048,2048};   
    // publisher_->publish(message);
    // usleep(3000000);

    // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    // //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    // message.position = {2048,2048,2096,2000,1024,3072,2048,2048,2048,2060,1227,2869,3621,475,2596,1500,2048,2048,2048};   
    // publisher_->publish(message);
    // usleep(3000000);

    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    //                    1    2    3    4   5   6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {944,3203,2096,2000,804,3292,2048,2048,2048,2060,1315,2781,3665,442,2000,2096,2048,2048,2048};   
    publisher_->publish(message);
    usleep(3000000);


    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    //                    1   2     3    4   5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {882,3214,2096,2000,1178,2918,2048,2048,2048,2060,952,3144,3665,442,1978,2118,2048,2048,2048};   
    publisher_->publish(message);
    usleep(3000000);

    message_single.id = 254;
    message_single.address = 112;
    message_single.position = 70;
    publisher_single->publish(message_single);

    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {1769,2294,2096,2000,2048,2048,2048,2048,2048,2060,1146,2950,3621,475,2596,1500,2048,2048,2048};   
    publisher_->publish(message);
    usleep(3000000);

    // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    // //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    // message.position = {2011,2122,2096,2000,2048,2048,2048,2103,2048,2060,853,3243,3621,475,2211,1885,2048,2048,2048};   
    // publisher_->publish(message);
    // usleep(3000000);

    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {2121,1975,2096,2000,2048,2048,2048,2048,2048,2060,589,3507,3621,475,2296,1800,2048,2048,2048};   
    publisher_->publish(message);
    usleep(4000000);

    // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    // //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    // message.position = {2011,2122,2096,2000,2048,2048,2048,2048,2048,2060,636,3474,3665,442,2145,1951,2048,2048,2048};   
    // publisher_->publish(message);
    // usleep(2000000);

    // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    // //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    // message.position = {1952,2192,2096,2000,2048,2048,2048,2048,2048,2060,1029,3067,3665,442,2442,1654,2048,2048,2048};   
    // publisher_->publish(message);
    // usleep(4000000);


    // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    // //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    // message.position = {2121,1975,2096,2000,2048,2048,2048,2048,2048,2060,1070,3020,3621,475,2714,1382,2048,2048,2048};   
    // publisher_->publish(message);
    // usleep(3000000);


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



    // 15 = 2048 + 800 // 16 = 2048 - 800 //
    // 11 = 2048 - 800 // 12 = 2048 + 800 //
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
    message.position = {2048,2048,2148,1948,2048,2048,2048,2048,2047,2047,1248,2848,3644,452,2848,1248,2047,2047,2047};   
    publisher_->publish(message);
    usleep(1600000);


    // 11 += 224 // 12 -= 224
    // 15 -= 224 // 16 += 224
    // 13 -= 448 // 14 += 448
    // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    //  //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
    //  message.position = {2048,2048,2148,1948,1024,3072,1917,2067,2047,2047,1472,2624,3196,900,2624,1472,2047,2047,2047};   
    // publisher_->publish(message);
    // std::this_thread::sleep_for(std::chrono::seconds(2)); // Seg_1

    // message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    //  //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
    //  message.position = {2048,2048,2148,1948,1024,3072,1917,2067,2047,2047,1696,2400,2748,1348,2400,1696,2047,2047,2047};   
    // publisher_->publish(message);
    // std::this_thread::sleep_for(std::chrono::seconds(1)); // Seg_2

    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
    message.position = {2048,2048,2148,1948,1024,3072,2048,2048,2047,2047,1920,2176,2300,1748,2176,1920,2047,2047,2047};   
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