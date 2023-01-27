// Open terminal #2 
// $ ros2 run control control
// $ ros2 run um7 um7_node
// $ ros2 launch control action.launch.py


// ros2 topic pub -1 /decision custom_interfaces/Decision "{decision: 1}"
// ros2 action send_goal  /control_action custom_interfaces/action/Control "{action_number: 1}"

#include <chrono>
#include <memory>
#include <thread>
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <libgen.h> //dirname
#include <vector>
#include <cstdio>
#include <string.h>

#include "MotionManager.h"
#include "Walking.h"
#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/set_position.hpp"
#include "custom_interfaces/msg/decision.hpp"
#include "custom_interfaces/msg/walk.hpp"
#include "custom_interfaces/msg/vision.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "custom_interfaces/msg/neck_position.hpp"
#include "GaitMove.hpp"
#include "custom_interfaces/msg/set_position_original.hpp"
#include "custom_interfaces/srv/reset.hpp"
#include "custom_interfaces/action/control.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

using namespace std;
using namespace Robot;
using Control_action = custom_interfaces::action::Control;
using GoalHandleAction = rclcpp_action::ServerGoalHandle<Control_action>;
using namespace std::chrono_literals;
using std::placeholders::_1;

int movement = 1;
int contador = 0;
int cont_vision = 2047;
int cont_vision_up = 1300;
int cont_fall_side = 0;
bool stop_gait = true;
uint32_t valor = 246;
uint32_t valor_up = 250;
int neck_sides = 2048;
int neck_up = 2048;
int sleep_sec = 0;
int parameters = false;
int parameter_number = 0;
int walk = 0;
int sidle = 0;
int turn = 0;

class Control : public rclcpp::Node
{
public:
  Control()
  : Node("control")
  {
    RCLCPP_INFO(this->get_logger(), "Running action node");
    subscription_neck = this->create_subscription<custom_interfaces::msg::NeckPosition>(
      "/neck_position", 10, std::bind(&Control::topic_callback_neck, this, _1));
    // subscription_imu = this->create_subscription<sensor_msgs::msg::Imu>(
    // "imu/data", 10, std::bind(&Control::topic_callback_imu, this, _1));
    publisher_ = this->create_publisher<custom_interfaces::msg::SetPosition>("set_position", 10); 
    publisher_single = this->create_publisher<custom_interfaces::msg::SetPositionOriginal>("set_position_single", 10);
    publisher_walk = this->create_publisher<custom_interfaces::msg::Walk>("walking", 10); 
    
    using namespace std::placeholders;

    this->action_server_ = rclcpp_action::create_server<Control_action>(
    this,
    "control_action",
    std::bind(&Control::handle_goal, this, _1, _2), // Callbacks
    std::bind(&Control::handle_cancel, this, _1),
    std::bind(&Control::handle_accepted, this, _1));
    }

private:

    void topic_callback_neck(const std::shared_ptr<custom_interfaces::msg::NeckPosition> neck_msg) const
    {
      neck_sides = neck_msg->position19;
      neck_up = neck_msg->position20;
    }

    // handle new goals, accept or rejects them 
    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID & uuid,
        std::shared_ptr<const Control_action::Goal> goal)
    {
        RCLCPP_INFO(this->get_logger(), "Received action %d", goal->action_number);
        (void)uuid;
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    // receives the cancellation and tell the client that it was accepted
    rclcpp_action::CancelResponse handle_cancel(
        const std::shared_ptr<GoalHandleAction> goal_handle)
    {
        RCLCPP_INFO(this->get_logger(), "Received request to cancel action");
        (void)goal_handle;
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    // accepts a new goal and process it
    void handle_accepted(const std::shared_ptr<GoalHandleAction> goal_handle)
    {
        using namespace std::placeholders;
        // this needs to return quickly to avoid blocking the executor, so spin up a new thread
        std::thread{std::bind(&Control::execute, this, _1), goal_handle}.detach();
    }


    void execute(const std::shared_ptr<GoalHandleAction> goal_handle)
    {
        RCLCPP_INFO(this->get_logger(), "Executing goal");

        auto message_walk = custom_interfaces::msg::Walk();  
        auto message = custom_interfaces::msg::SetPosition();   
        auto message_single = custom_interfaces::msg::SetPositionOriginal();  
        

        vector<int> motors { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
        vector<vector<int>> position;
        vector<int> address;
        vector<float> sleep;
        vector<int> id;
        vector<int> position_single;

        const auto goal = goal_handle->get_goal();
        movement = goal->action_number;
        RCLCPP_INFO(this->get_logger(), "Decision: %d", movement);
        auto feedback = std::make_shared<Control_action::Feedback>();
        auto & movements_remaining = feedback->movements_remaining;
        auto result = std::make_shared<Control_action::Result>();

        message_single.id = 254;
        message_single.address = 112;
        message_single.position = 128;
        publisher_single->publish(message_single);

        switch (movement) {
            case 1: // Parado
              parameters = false;
              //             1    2     3   4    5   6    7    8     9   10   11   12   13   14   15   16   17   18   19   20
              position =  { {1724,2367,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2136,2048,1586} };
              sleep = { 2 }; // sleep em SEGUNDOS
              address = { 116 }; // 116 para definir a posição, 112 para modificar a velocidade
              id = {  }; // id dos motores para mudar a velocidade, 254 = todos os motores
              position_single = {  }; // velocidade
              break;
            case 4: // Left kick OK
              RCLCPP_INFO(this->get_logger(), "Left kick");
              parameters = false;
              //             1    2     3   4    5   6    7    8     9   10   11   12   13   14   15   16   17   18   19        20
              position =  { {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1767,2329,2791,1306,2536,1560,2048,2048,2047,cont_vision_up},
                          {2047,2047,2116,1976,2046,2046,2047,2047,2040,2164,1744,2324,2398,1654,2231,1882,2119,2191,2047,cont_vision_up},
                          {2047,2047,2648,1957,1240,3598,2047,2047,2040,2144,1726,2348,2398,1472,2238,1823,2152,1974,2047,cont_vision_up}, 
                          {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2281,1551,2152,1915,2793,cont_vision_up},
                          {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2281,1798,2152,2046,2793,cont_vision_up},
                          {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,877,2281,1903,2152,2046,2793,cont_vision_up},
                          {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,3215,2508,1534,2216,1798,2152,1991,2793,cont_vision_up},
                          {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,877,2205,1903,2152,2046,2793,cont_vision_up},
                          {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2205,1798,2152,2046,2793,cont_vision_up},
                          {2047,2047,2579,1957,1240,3587,2047,2047,2040,2144,1616,1738,2508,943,2205,1551,2152,1915,2793,cont_vision_up},
                          {2047,2047,2648,1957,1240,3598,2047,2047,2040,2164,1726,2348,2508,1472,2238,1796,2152,2140,2047,cont_vision_up},
                          {1724,2367,2294,1812,627,3468,2052,2044,2032,2106,1767,2329,2791,1306,2536,1560,2048,2048,2047,cont_vision_up}
              };
              sleep = { 3, 3, 1, 1, 3, 2, 3, 2, 1, 1, 1, 2 }; // sleep em SEGUNDOS
              address = { 116, 112, 116, 116, 116, 116, 112, 112, 112, 116, 112, 112, 112, 116, 112, 116, 116, 116, 112, 112, 116, 116 }; // 116 para definir a posição, 112 para modificar a velocidade
              id = { 254, 12, 14, 16, 12, 14, 15, 254, 254, 17 }; // id dos motores para mudar a velocidade, 254 = todos os motores
              position_single = { 15, 8400, 4200, 4200, 15000, 15000, 750, 10, 4000, 10 }; // velocidade
              break;
            case 14: // Walking
              parameters = true;
              RCLCPP_INFO(this->get_logger(), "Walking"); 
              walk= 20;   
              sidle = 0;  
              turn = 0; 
              parameter_number = 1;  
              break;
            case 15: // Gait
              parameters = true;
              RCLCPP_INFO(this->get_logger(), "Gait"); 
              walk= 0;   
              sidle = 0;  
              turn = 0; 
              parameter_number = 2;  
              break;
            case 17: // Stand up Front
              RCLCPP_INFO(this->get_logger(), "Stand Up Front");  
              parameters = false;
              //              1    2     3   4    5   6    7    8     9   10   11   12   13   14   15   16   17   18   19   20
              position = {  {2047,2047,2183,1896,417,3679,2048,2067,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,1300},
                            {2152,1942,2183,1896,766,3328,2048,2067,2047,2047,837,3259,3028,1066,2919,1175,2047,2047,2047,1300},
                            {2755,1339,2183,1896,2048,2048,2048,2067,2047,2047,837,3259,3275,819,2657,1494,2047,2047,2047,1300},
                            {2612,1484,2183,1896,2048,2048,2048,2067,2047,2047,837,3259,3574,522,2705,1391,2047,2047,2047,1300},
                            {2755,1339,2183,1896,2048,2048,2048,2067,2047,2047,841,3259,3644,452,2551,1545,2047,2047,2047,1300},
                            {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1248,2848,3644,452,2848,1248,2047,2047,2047,1300},
                            {2048,2048,2148,1948,1024,3072,2048,2067,2047,2047,1248,2848,3181,909,2533,1555,2047,2047,2047,1300},
                            {1724,2372,2217,1878,627,3468,2052,2044,2032,2106,1712,2384,2791,1306,2536,1560,2048,2048,2048,1300}
                           };
              sleep = { 3, 1.5, 1.5, 1.5, 1.5, 4, 3, 2 }; // sleep em SEGUNDOS
              address = { 112, 116, 116, 116, 112, 116, 112, 116, 112, 112, 112, 116, 112, 116, 116}; // 116 para definir a posição, 112 para modificar a velocidade
              id = { 254, 254, 254, 254, 13, 14, 254 }; // id dos motores para mudar a velocidade, 254 = todos os motores
              position_single = { 80, 128, 10, 30, 60, 60, 10 }; // velocidade
              break;
        }

        if (parameters){
          if (goal_handle->is_canceling()) {
              result->finished = false;
              goal_handle->canceled(result);
              RCLCPP_INFO(this->get_logger(), "Goal canceled");
              return;
          }
          message_walk.walk = walk;   
          message_walk.sidle = sidle;  
          message_walk.turn = turn; 
          message_walk.walk_number = parameter_number;  
          publisher_walk->publish(message_walk);
        }
        else{
          message_walk.walk_number = 0; 
          publisher_walk->publish(message_walk);
          message.id = motors;

          for (int i = 0; i < address.size(); i++){
            // Check if there is a cancel request
            if (goal_handle->is_canceling()) {
                result->finished = false;
                goal_handle->canceled(result);
                RCLCPP_INFO(this->get_logger(), "Goal canceled");
                return;
            }
            if (address[i] == 116) { // position
                message.position = position.front();
                publisher_->publish(message);
                position.erase(position.begin() + 0);
                sleep_sec = sleep.front();
                RCLCPP_INFO(this->get_logger(), "Sleep: %d ", sleep_sec);
                usleep(sleep_sec*1000000);
                RCLCPP_INFO(this->get_logger(), "AAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
                sleep.erase(sleep.begin() + 0);
            }
            else { // velocity
                message_single.id = id.front();
                id.erase(id.begin() + 0);
                message_single.address = address[i];
                message_single.position = position_single.front();
                position_single.erase(position_single.begin() + 0);
                publisher_single->publish(message_single);
            }
            movements_remaining = address.size() - i - 1;
            // Publish feedback
            goal_handle->publish_feedback(feedback);
            RCLCPP_INFO(this->get_logger(), "Feedback: %d movements remaining", movements_remaining);
          }
        }
        
        result->finished = true;
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(), "Goal succeeded");
    }
    rclcpp::Subscription<custom_interfaces::msg::NeckPosition>::SharedPtr subscription_neck;
    // rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr subscription_imu;
    rclcpp::Publisher<custom_interfaces::msg::SetPosition>::SharedPtr publisher_; 
    rclcpp::Publisher<custom_interfaces::msg::SetPositionOriginal>::SharedPtr publisher_single; 
    rclcpp::Publisher<custom_interfaces::msg::Walk>::SharedPtr publisher_walk;      
    rclcpp::Client<custom_interfaces::srv::Reset>::SharedPtr client;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp_action::Server<Control_action>::SharedPtr action_server_;
};

void change_current_dir()
{
    char exepath[1024] = {0};
    if(readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
        chdir(dirname(exepath));
}

int main(int argc, char * argv[])
{
  change_current_dir();
  //Configurando para prioridade maxima para executar este processo-------
  char string1[50]; //String
  sprintf(string1,"echo 123456| sudo -S renice -20 -p %d", getpid());
  system(string1);//prioridade
  //GaitMove gaitMove(ini);
  rclcpp::init(argc, argv);
  // if(MotionManager::GetInstance()->Initialize() == false)
  //   {
  //     printf("Fail to initialize Motion Manager!\n");
  //     return 0;
  // }
  rclcpp::spin(std::make_shared<Control>());
  rclcpp::shutdown();
  return 0;
}