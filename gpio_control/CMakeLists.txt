cmake_minimum_required(VERSION 3.8)
project(gpio_control)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(gpio_controllers REQUIRED)
find_package(urdf REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_srvs REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(custom_interfaces REQUIRED)
find_package(control_msgs REQUIRED)
find_package(pluginlib REQUIRED)
find_package(ethercat_interface REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

install(
  DIRECTORY launch config urdf src srv
  DESTINATION share/${PROJECT_NAME}
)

# rosidl_generate_interfaces(${PROJECT_NAME}
#   "srv/OutputControl.srv"
#   DEPENDENCIES builtin_interfaces std_msgs std_srvs
# )

# ament_export_dependencies(rosidl_default_runtime)

add_executable(test_output_publisher src/test_output_publisher.cpp)
ament_target_dependencies(test_output_publisher rclcpp std_msgs)

install(TARGETS
  test_output_publisher
  DESTINATION lib/${PROJECT_NAME})

add_executable(output_control_service_server src/output_control_service_server.cpp)
ament_target_dependencies(output_control_service_server rclcpp example_interfaces custom_interfaces control_msgs)

install(TARGETS
  output_control_service_server
  DESTINATION lib/${PROJECT_NAME})

add_executable(output_reset_service_server src/output_reset_service_server.cpp)
ament_target_dependencies(output_reset_service_server rclcpp std_srvs control_msgs)

install(TARGETS
  output_reset_service_server
  DESTINATION lib/${PROJECT_NAME})

# add_executable(camera_service_server src/camera_service_server.cpp)
# target_include_directories(camera_service_server PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>)
# target_compile_features(camera_service_server PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
# ament_target_dependencies(
#   camera_service_server
#   "pluginlib"
#   "ethercat_interface"
# )

# install(TARGETS camera_service_server
#   DESTINATION lib/${PROJECT_NAME})

ament_package()
