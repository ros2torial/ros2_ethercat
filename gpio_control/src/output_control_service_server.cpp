#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/srv/output_control.hpp"
#include "std_msgs/msg/multi_array_dimension.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "std_msgs/msg/multi_array_dimension.hpp"
#include "control_msgs/msg/dynamic_joint_state.hpp"

#include <memory>
#include <chrono>

class OutputControl : public rclcpp::Node
{
  public:
    OutputControl()
    : Node("output_control")
    {
      using namespace std::placeholders;
      callback_group_subscriber = this->create_callback_group(
        rclcpp::CallbackGroupType::MutuallyExclusive, true);
      callback_group_service_server = this->create_callback_group(
        rclcpp::CallbackGroupType::MutuallyExclusive, true);
      auto sub_opt = rclcpp::SubscriptionOptions();
      sub_opt.callback_group = callback_group_subscriber;

      initialise_multi_array();
      subscription_ = this->create_subscription<control_msgs::msg::DynamicJointState>(
      "/hardware/gpio_command_controller/gpio_states", 1, std::bind(&OutputControl::io_status_cb, this, _1), sub_opt);

      publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
      "/hardware/gpio_command_controller/commands", 1);

      service_server_ = this->create_service<custom_interfaces::srv::OutputControl>(
      "output_control", std::bind(&OutputControl::output_control_cb, this, _1, _2), rmw_qos_profile_services_default, callback_group_service_server);

    }

  private:

    rclcpp::Subscription<control_msgs::msg::DynamicJointState>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_;
    rclcpp::Service<custom_interfaces::srv::OutputControl>::SharedPtr service_server_;

    rclcpp::CallbackGroup::SharedPtr callback_group_subscriber;
    rclcpp::CallbackGroup::SharedPtr callback_group_service_server;

    double output_status[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    std_msgs::msg::Float64MultiArray output_msg;
    std_msgs::msg::MultiArrayDimension dim1;
    std_msgs::msg::MultiArrayDimension dim2;

    void initialise_multi_array()
    {
      output_msg.layout.dim.clear();
      dim1.label = "gpio_num";
      dim1.size = 2;
      dim1.stride = 32;
      output_msg.layout.dim.push_back(dim1);
      dim2.label = "io_num";
      dim2.size = 16;
      dim2.stride = 16;
      output_msg.layout.dim.push_back(dim2);
      output_msg.layout.data_offset = 0;
    }

    void io_status_cb(const control_msgs::msg::DynamicJointState::SharedPtr msg)
    {
      for(int i = 0; i < 16; i++)
        output_status[i] = msg->interface_values[1].values[i];
    }

    void output_control_cb(const std::shared_ptr<custom_interfaces::srv::OutputControl::Request> request,
                                 std::shared_ptr<custom_interfaces::srv::OutputControl::Response> response)
    {
      int max_attempt = 10;
      while(max_attempt)
      {
        if(request->value == output_status[request->output_number])
        {break;}
        output_msg.data.clear();
        for(int i = 0;  i < 32; i++)
        { 
          if(i < 16)
          {output_msg.data.push_back(0);}
          else
          {
            if(i == (request->output_number + 16))
            {output_msg.data.push_back(request->value);}
            else
            {output_msg.data.push_back(output_status[i - 16]);}
          }
        }
        publisher_->publish(output_msg);
        --max_attempt;
        std::this_thread::sleep_for(std::chrono::microseconds(10*1000));
      }
      if(max_attempt)
        response->success = true;
      else
        response->success = false; 
    }

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::executors::MultiThreadedExecutor executor;
  auto output_control_node = std::make_shared<OutputControl>();  
  executor.add_node(output_control_node);
  executor.spin();
  rclcpp::shutdown();
  return 0;
}