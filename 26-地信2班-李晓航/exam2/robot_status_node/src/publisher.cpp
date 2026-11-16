#include <chrono>//算秒工具
#include <memory>//内存管理工具
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "robot_status_msg/msg/robot_status.hpp"

using namespace std::chrono_literals;

class RobotStatusPublisher : public rclcpp::Node {
public:
    RobotStatusPublisher() : Node("robot_status_publisher") {
        // 读取 YAML 参数：频率和话题名
        this->declare_parameter("publish_rate", 1.0);
        this->declare_parameter("topic_name", "/robot_status");
        
        double rate = this->get_parameter("publish_rate").as_double();
        std::string topic = this->get_parameter("topic_name").as_string();

        publisher_ = this->create_publisher<robot_status_msg::msg::RobotStatus>(topic, 10);
        timer_ = this->create_wall_timer(
            std::chrono::duration<double>(1.0 / rate), 
            std::bind(&RobotStatusPublisher::timer_callback, this));
    }

private:
    void timer_callback() {
        auto message = robot_status_msg::msg::RobotStatus();
        message.robot_name = "ATIL_Bot";
        message.speed = 1.5;
        message.position_x = 10.0;
        message.position_y = 20.0;
        publisher_->publish(message);
        RCLCPP_INFO(this->get_logger(), "发布: 名字=%s, 速度=%.1f", message.robot_name.c_str(), message.speed);
    }
    rclcpp::Publisher<robot_status_msg::msg::RobotStatus>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RobotStatusPublisher>());
    rclcpp::shutdown();
    return 0;
}