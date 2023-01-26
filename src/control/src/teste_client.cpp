#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
 
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "custom_interfaces/action/control.hpp"

using Control_action = custom_interfaces::action::Control;
using GoalHandleAction = rclcpp_action::ClientGoalHandle<Control_action>;

int i = 1;
int cont = 0;

class FibonacciActionClient : public rclcpp::Node
{
public:
    FibonacciActionClient()
  : Node("client_server")
  {
    
    this->client_ptr_ = rclcpp_action::create_client<Control_action>(
      this,
      "control_action");

    this->timer_ = this->create_wall_timer(
      std::chrono::milliseconds(500),
      std::bind(&FibonacciActionClient::send_goal, this));

  }

  void send_goal()
  {
    using namespace std::placeholders;


    if (!this->client_ptr_->wait_for_action_server()) {
      RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
      rclcpp::shutdown();
    }

    auto goal_msg = Control_action::Goal();
    goal_msg.action_number = i;
    cont++;
    if(cont==16){
      client_ptr_->async_cancel_all_goals();
      RCLCPP_ERROR(this->get_logger(), "Cancellation was requested.");
      i=16;
    }

    RCLCPP_INFO(this->get_logger(), "Sending goal %d", i);

    auto send_goal_options = rclcpp_action::Client<Control_action>::SendGoalOptions();
    send_goal_options.goal_response_callback =
      std::bind(&FibonacciActionClient::goal_response_callback, this, _1);
    send_goal_options.feedback_callback =
      std::bind(&FibonacciActionClient::feedback_callback, this, _1, _2);
    send_goal_options.result_callback =
      std::bind(&FibonacciActionClient::result_callback, this, _1);
    this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
    
  }


private:
  rclcpp_action::Client<Control_action>::SharedPtr client_ptr_;
  rclcpp::TimerBase::SharedPtr timer_;

   void goal_response_callback(GoalHandleAction::SharedPtr goal_handle)
  {
    if (!goal_handle) {
      RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
    } else {
      RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
    }
  }

  void feedback_callback(
    GoalHandleAction::SharedPtr,
    const std::shared_ptr<const Control_action::Feedback> feedback)
  {
    std::stringstream ss;
    ss << "Movements remaining: ";
    auto number = feedback->movements_remaining;
    ss << number << " ";
    RCLCPP_INFO(this->get_logger(), ss.str().c_str());
  }

  void result_callback(const GoalHandleAction::WrappedResult & result)
  {
    switch (result.code) {
      case rclcpp_action::ResultCode::SUCCEEDED:
        break;
      case rclcpp_action::ResultCode::ABORTED:
        RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
        return;
      case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
        return;
      default:
        RCLCPP_ERROR(this->get_logger(), "Unknown result code");
        return;
    }
    std::stringstream ss;
    ss << "Result received: ";
    auto finished = result.result->finished;
    ss << finished << " ";
    RCLCPP_INFO(this->get_logger(), ss.str().c_str());
  }
};  // class FibonacciActionClient

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FibonacciActionClient>());
  rclcpp::shutdown();
  return 0;
}