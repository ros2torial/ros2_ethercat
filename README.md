# ros2_ethercat
contains packages to communicate with omron ethercat devices

## Start IgH EtherCAT Master

to start IgH EtherCAT Master run

```shell
sudo /etc/init.d/ethercat start
sudo chmod 777 /dev/EtherCAT0
ethercat slaves
```

or directly run the *ethercat_start.sh* file in the gpio_control which automatically run the above three commands

## Start EtherCAT ROS2 Control

start gpio controller, communication with hardware and the additional services depending on workcell
```shell
ros2 launch gpio_control wc2_launch.py
```
or 
```shell
ros2 launch gpio_control wc3_launch.py
```
If this launch terminal is killed by the user then the outputs which were **HIGH** will automatically become **LOW**.

### To Control Output

to set a particuler output keeping other output values same ->

```shell
ros2 service call /output_control custom_interfaces/srv/OutputControl "output_number: 15
value: true
"
```
```shell
ros2 service call /output_control custom_interfaces/srv/OutputControl "output_number: 15
value: false
"
```

### To Reset Output

to reset all the output to zero value ->

```shell
ros2 service call /output_reset std_srvs/srv/Trigger {}
```

### To provide a High Pulse to Output

to set a particuler output HIGH for certain duration(ms) ->

```shell
ros2 run gpio_control test_output_publisher 15 1000
```

### Additional Information

to check the io states run

```shell
ros2 topic echo /hardware/gpio_command_controller/gpio_states
```
```shell
publish on /hardware/gpio_command_controller/commands topic to set output
```
```shell
ros2 topic pub -r1 /hardware/gpio_command_controller/commands std_msgs/msg/Float64MultiArray "layout:
  dim: [{"label": "gpio_num","size": 2,"stride": 32}, {"label": "io_num","size": 16,"stride": 16}]
  data_offset: 0
data: [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]
"
```
