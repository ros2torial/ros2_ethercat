#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/multi_array_dimension.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("output_publisher");
  int output_num = atoi(argv[1]);
  RCLCPP_INFO(node->get_logger(), "output_num: '%i'", output_num);
  int duration_ms = atoi(argv[2]);
  RCLCPP_INFO(node->get_logger(), "duration_ms: '%i'", duration_ms);
  if ((output_num < 0)&&(output_num >= 16))
    return 0;
  if ((duration_ms < 10)&&(duration_ms >= 10000))
    return 0;
  auto publisher_ = node->create_publisher<std_msgs::msg::Float64MultiArray>("/hardware/gpio_command_controller/commands", 1);

  auto message = std_msgs::msg::Float64MultiArray();
  message.layout.dim.clear();
  auto dim1 = std_msgs::msg::MultiArrayDimension();
  dim1.label = "gpio_num";
  dim1.size = 2;
  dim1.stride = 32;
  message.layout.dim.push_back(dim1);
  auto dim2 = std_msgs::msg::MultiArrayDimension();
  dim2.label = "io_num";
  dim2.size = 16;
  dim2.stride = 16;
  message.layout.dim.push_back(dim2);
  message.layout.data_offset = 0;
  RCLCPP_INFO(node->get_logger(), "setting output: '%i' high", output_num);
  for(int i = 0;  i < 32; i++)
  { 
    if(i == (output_num + 16))
    {message.data.push_back(1);}
    else
    {message.data.push_back(0);}
  }
  publisher_->publish(message);
  std::this_thread::sleep_for(std::chrono::microseconds(10));
  publisher_->publish(message);
  std::this_thread::sleep_for(std::chrono::microseconds(10));
  publisher_->publish(message);
  std::this_thread::sleep_for(std::chrono::microseconds(duration_ms*1000));
  message.data.clear();
  for(int i = 0;  i < 32; i++)
    message.data.push_back(0);
  publisher_->publish(message);
  std::this_thread::sleep_for(std::chrono::microseconds(10));
  publisher_->publish(message);
  std::this_thread::sleep_for(std::chrono::microseconds(10));
  publisher_->publish(message);
  publisher_->publish(message);
  RCLCPP_INFO(node->get_logger(), "setting output: '%i' low", output_num);

  rclcpp::shutdown();
  return 0;
}