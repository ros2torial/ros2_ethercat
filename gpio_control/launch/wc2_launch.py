
from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import Command, FindExecutable, LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from nav2_common.launch import RewrittenYaml


def generate_launch_description():

    namespace_arg = DeclareLaunchArgument(name='namespace', default_value='/hardware', description='namespace for different robot')
    gpio_controller_path = PathJoinSubstitution([FindPackageShare('gpio_control'), 'config', 'gpio_controller_omron_nxecc201_nxid5442_nxod5256.yaml'])
    gpio_controller_arg = DeclareLaunchArgument(name='gpio_controller', default_value=gpio_controller_path, description='Absolute path to controller file')
    param_substitutions = {}
    configured_params = RewrittenYaml(
        source_file=LaunchConfiguration('gpio_controller'),
        root_key=LaunchConfiguration('namespace'),
        param_rewrites=param_substitutions,
        convert_types=True)
    gpio_controller_namespace_arg = DeclareLaunchArgument(name='gpio_controller_namespace', default_value=configured_params, description='Absolute path to controller file')
    controller_manager_arg = DeclareLaunchArgument(name='controller_manager', default_value=[LaunchConfiguration('namespace'), '/controller_manager'], description='Absolute path to palpicker controller file')

    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name='xacro')]),
            ' ',
            PathJoinSubstitution(
                [FindPackageShare('gpio_control'), 'urdf', 'gpio_ros2_control_omron_nxecc201_nxid5442_nxod5256.xacro']
            ),
        ]
    )
    robot_description = {"robot_description": robot_description_content}

    ros2_control_node = Node(
        namespace=LaunchConfiguration('namespace'),
        package='controller_manager',
        executable='ros2_control_node',
        parameters=[robot_description, LaunchConfiguration('gpio_controller_namespace')],
        output='screen',
    )

    gpio_controller_node = Node(
        package='controller_manager',
        executable='spawner',
        arguments=['gpio_command_controller', "--controller-manager", LaunchConfiguration('controller_manager')],
        output='screen',
    )

    output_control_node = Node(
        package='gpio_control',
        executable='output_control_service_server',
        output='screen',
    )

    output_reset_node = Node(
        package='gpio_control',
        executable='output_reset_service_server',
        output='screen',
    )
  
    # Create the launch description and populate
    ld = LaunchDescription()

    # declared_arguments
    ld.add_action(namespace_arg)
    ld.add_action(gpio_controller_arg)
    ld.add_action(gpio_controller_namespace_arg)
    ld.add_action(controller_manager_arg)

    # nodes_to_start
    ld.add_action(ros2_control_node)
    ld.add_action(gpio_controller_node)
    ld.add_action(output_control_node)
    ld.add_action(output_reset_node)

    return ld