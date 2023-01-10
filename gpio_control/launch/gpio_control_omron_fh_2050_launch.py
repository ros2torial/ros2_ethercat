
from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import Command, FindExecutable


def generate_launch_description():

    gpio_controller_path = PathJoinSubstitution([FindPackageShare('gpio_control'), 'config', 'camera_controller_fh_2050.yaml'])
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name='xacro')]),
            ' ',
            PathJoinSubstitution(
                [FindPackageShare('gpio_control'), 'urdf', 'camera_ros2_control_omron_fh_2050.xacro']
            ),
        ]
    )
    robot_description = {"robot_description": robot_description_content}

    ros2_control_node = Node(
        package='controller_manager',
        executable='ros2_control_node',
        parameters=[robot_description, gpio_controller_path],
        output='screen',
    )

    gpio_controller_node = Node(
        package='controller_manager',
        executable='spawner',
        arguments=['gpio_command_controller', "--controller-manager", "/controller_manager"],
        output='screen',
    )
  
    # Create the launch description and populate
    ld = LaunchDescription()

    # declared_arguments

    # nodes_to_start
    ld.add_action(ros2_control_node)
    ld.add_action(gpio_controller_node)

    return ld