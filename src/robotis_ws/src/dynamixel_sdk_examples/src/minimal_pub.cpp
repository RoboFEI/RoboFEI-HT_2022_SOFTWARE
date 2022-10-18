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
    message_single.id = 254;
          message_single.address = 112;
          message_single.position = 80;
          publisher_single->publish(message_single);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
          message.position = {2047,2047,2183,1896,417,3679,2048,2067,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047};   
          publisher_->publish(message);
          usleep(3000000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
          message.position = {2152,1942,2183,1896,766,3328,2048,2067,2047,2047,837,3259,3028,1066,2919,1175,2047,2047,2047};   
          publisher_->publish(message);
          usleep(1500000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2755,1339,2183,1896,2048,2048,2048,2067,2047,2047,837,3259,3275,819,2657,1494,2047,2047,2047};   
          publisher_->publish(message);

          message_single.id = 254;
          message_single.address = 112;
          message_single.position = 128;
          publisher_single->publish(message_single);

          usleep(1500000);



          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2612,1484,2183,1896,2048,2048,2048,2067,2047,2047,837,3259,3574,522,2705,1391,2047,2047,2047};   
          publisher_->publish(message);

          message_single.id = 254;
          message_single.address = 112;
          message_single.position = 10;
          publisher_single->publish(message_single);
          usleep(1500000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2755,1339,2183,1896,2048,2048,2048,2067,2047,2047,841,3259,3644,452,2551,1545,2047,2047,2047};   
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

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1248,2848,3644,452,2848,1248,2047,2047,2047};   
          publisher_->publish(message);
          usleep(3000000);

          message_single.id = 254;
          message_single.address = 112;
          message_single.position = 10;
          publisher_single->publish(message_single);

          usleep(1000000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
          //                    1   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 
          message.position = {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1248,2848,3181,909,2533,1555,2047,2047,2047};   
          publisher_->publish(message);
          usleep(3000000);

          message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
          //                    1   2     3    4    5    6    7    8   9   10   11   12   13   14   15   16   17   18      19       20
          message.position = {1724,2372,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,   2048,    1300};
          publisher_->publish(message);

          message_single.id = 254;
          message_single.address = 112;
          message_single.position = 60;
          publisher_single->publish(message_single);   
          usleep(2000000);








    usleep(10000000);


               

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