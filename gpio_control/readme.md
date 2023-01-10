to start 

first run

sudo chmod 777 /dev/EtherCAT0

-------------------

then run(for beckoff)

ros2 launch gpio_control gpio_control_launch.py

after that publish on /gpio_command_controller/commands topic to set output

#in 1 input module(8 output pin) + 1 output module(8 output pin) of beckhoff
ros2 topic pub -r1 /gpio_command_controller/commands std_msgs/msg/Float64MultiArray "layout:
  dim: [{"label": "gpio_num","size": 2,"stride": 16}, {"label": "io_num","size": 8,"stride": 8}]
  data_offset: 0
data: [1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0]
"
#in 1 output module(16 output pin) of omron
ros2 topic pub -r1 /gpio_command_controller/commands std_msgs/msg/Float64MultiArray "layout:
  dim: [{"label": "gpio_num","size": 1,"stride": 16}, {"label": "io_num","size": 16,"stride": 16}]
  data_offset: 0
data: [1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0]
"

for info http://docs.ros.org/en/api/std_msgs/html/msg/MultiArrayLayout.html

to check the io states run

ros2 topic echo /gpio_command_controller/gpio_states

------------------------------------------

ros2 launch gpio_control gpio_control_omron_nxecc201_nxid5442_nxod5256_wc2_launch.py

to check the io states run

ros2 topic echo /gpio_command_controller/gpio_states

publish on /gpio_command_controller/commands topic to set output

ros2 topic pub -r1 /gpio_command_controller/commands std_msgs/msg/Float64MultiArray "layout:
  dim: [{"label": "gpio_num","size": 2,"stride": 32}, {"label": "io_num","size": 16,"stride": 16}]
  data_offset: 0
data: [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]
"

-------------------------------------

to set a particuler output keeping other output values same ->

ros2 run gpio_control output_control_service_server

ros2 service call /output_control custom_interfaces/srv/OutputControl "output_number: 15
value: true
"

ros2 service call /output_control custom_interfaces/srv/OutputControl "output_number: 15
value: false
"

------------------------------------------

to reset all the output to zero value ->

ros2 run gpio_control output_reset_service_server

ros2 service call /output_reset std_srvs/srv/Trigger {}

--------------------------

to set a particuler output HIGH for certain duration(ms) ->

ros2 run gpio_control test_output_publisher 15 1000

----------------------------
