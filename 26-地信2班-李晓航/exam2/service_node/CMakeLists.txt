cmake_minimum_required(VERSION 3.8)
project(service_node)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(add_two_ints_srv REQUIRED)

add_executable(server src/server.cpp)
ament_target_dependencies(server rclcpp add_two_ints_srv)

add_executable(client src/client.cpp)
ament_target_dependencies(client rclcpp add_two_ints_srv)

install(TARGETS server client DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch params DESTINATION share/${PROJECT_NAME})

ament_package()