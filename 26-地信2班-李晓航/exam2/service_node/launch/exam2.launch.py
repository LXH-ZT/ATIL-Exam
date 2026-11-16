import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    config = os.path.join(
        get_package_share_directory('service_node'),
        'params',
        'params.yaml'
    )

    return LaunchDescription([
        Node(
            package='robot_status_node_cpp',
            executable='publisher',
            name='atil_1',
            namespace='robot1',
            output='screen',
            parameters=[config]
        ),
        Node(
            package='robot_status_node_cpp',
            executable='subscriber',
            name='robot_status_subscriber',
            namespace='robot1',
            output='screen',
            parameters=[config]
        ),
        Node(
            package='service_node',
            executable='server',
            name='add_two_ints_server',
            namespace='robot1',
            output='screen',
            parameters=[config]
        ),
        Node(
            package='service_node',
            executable='client',
            name='add_two_ints_client',
            namespace='robot1',
            output='screen',
            parameters=[config]
        )
    ])