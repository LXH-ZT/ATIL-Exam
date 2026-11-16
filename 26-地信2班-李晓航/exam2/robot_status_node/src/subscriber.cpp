#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "robot_status_msg/msg/robot_status.hpp"

using std::placeholders::_1;

class RobotStatusSubscriber : public rclcpp::Node {
public:
    RobotStatusSubscriber() : Node("robot_status_subscriber") {
        // 读取话题名
        this->declare_parameter("topic_name", "/robot_status");
        std::string topic = this->get_parameter("topic_name").as_string();

        subscription_ = this->create_subscription<robot_status_msg::msg::RobotStatus>(
            topic, 10, std::bind(&RobotStatusSubscriber::topic_callback, this, _1));
    }
private:
    void topic_callback(const robot_status_msg::msg::RobotStatus::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "收到: 名称=%s, 速度=%.2f, 坐标=(%.2f, %.2f)", 
                    msg->robot_name.c_str(), msg->speed, msg->position_x, msg->position_y);
    }
    rclcpp::Subscription<robot_status_msg::msg::RobotStatus>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RobotStatusSubscriber>());
    rclcpp::shutdown();
    return 0;
}