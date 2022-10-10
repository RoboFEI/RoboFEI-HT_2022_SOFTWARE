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
    message.position = {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1512,2582,2791,1306,2536,1560,2048,2081,2047,2047};
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
    message.position = {2047,2047,2118,1978,2048,2048,2047,2047,1930,2054,1743,2384,2440,1696,2212,1863,2120,1975,2047,2047};

    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(3)); //1



    // Dobrar joelhos
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {2047,2047,2137,1446,496,2854,2047,2047,1950,2054,1746,2368,2622,1696,2271,1856,2120,1942,2047,2047};   
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1


    // Equilibrar em uma perna
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,2356,2478,3151,1586,2543,1813,2179,1953,2047,1301};   
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1
    

        // Perna pra trás
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,2356,2478,3151,1586,2296,1813,2048,1953,2047,1301};   
    publisher_->publish(message);

    message_single.id = 11;
    message_single.address = 112;
    message_single.position = 8400;
    publisher_single->publish(message_single);
      std::this_thread::sleep_for(std::chrono::seconds(1)); //1

    message_single.id = 13;
    message_single.address = 112;
    message_single.position = 4200;
    publisher_single->publish(message_single);
      std::this_thread::sleep_for(std::chrono::seconds(1)); //1

    message_single.id = 15;
    message_single.address = 112;
    message_single.position = 4200;
    publisher_single->publish(message_single);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1

        // Quase chute
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,2356,2478,3217,1586,2191,1813,2048,1953,2047,1301};   
    publisher_->publish(message);
    usleep(200000);

    message_single.id = 11;
    message_single.address = 112;
    message_single.position = 15000;
    publisher_single->publish(message_single);

    message_single.id = 13;
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
    message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,879,2478,2560,1586,2296,1878,2103,1942,2047,1301};   
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(2)); //1

    message_single.id = 254;
    message_single.address = 112;
    message_single.position = 10;
    publisher_single->publish(message_single);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1

       // Quase chute
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,2356,2478,3217,1586,2191,1889,2048,1953,2047,1301};   
    publisher_->publish(message);
    usleep(200000);


        // Perna pra trás
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,2356,2478,3151,1586,2296,1889,2048,1953,2047,1301};   
    publisher_->publish(message);
    usleep(2000000);

        // Equilibrar em uma perna
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {2047,2047,2137,1515,507,2854,2047,2047,1950,2054,2356,2478,3151,1586,2543,1889,2179,1953,2047,1301};   
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //1

    message_single.id = 254;
    message_single.address = 112;
    message_single.position = 4000;
    publisher_single->publish(message_single);
    
    message_single.id = 18;
    message_single.address = 112;
    message_single.position = 20;
    publisher_single->publish(message_single);

        // Dobrar joelhos
    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
    message.position = {2047,2047,2137,1446,496,2854,2047,2047,1950,2054,1746,2368,2622,1696,2271,1856,2120,1942,2047,2047};   
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(2)); //1

    message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19, 20};
    //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18  19 
    message.position = {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1743,2384,2791,1306,2536,1560,2048,2081,2047,2047};
    publisher_->publish(message);
    std::this_thread::sleep_for(std::chrono::seconds(5)); //1


    // message_single.id = 254;
    // message_single.address = 112;
    // message_single.position = 50;
    // publisher_single->publish(message_single);

  // // Volta da perna
  //   message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
  //   //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
  //   message.position = {2047,2047,2137,1515,507,2854,2047,2047,2032,2106,1712,2384,2251,1262,2100,1560,1823,2048,2047};   
  //   publisher_->publish(message);
  //   std::this_thread::sleep_for(std::chrono::seconds(2)); //1

  //   message_single.id = 18;
  //   message_single.address = 112;
  //   message_single.position = 128;
  //   publisher_single->publish(message_single);

  //     // Volta total
  //   message.id = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
  //   //                    1   2     3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19
  //   message.position = {1724,2367,2591,1812,968,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,2047};   
  //   publisher_->publish(message);
  //   std::this_thread::sleep_for(std::chrono::seconds(3)); //1

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