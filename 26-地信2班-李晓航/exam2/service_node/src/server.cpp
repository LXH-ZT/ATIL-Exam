#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "add_two_ints_srv/srv/add_two_ints.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class ServerNode : public rclcpp::Node {
public:
    ServerNode() : Node("add_two_ints_server") {
        // 读取服务名
        this->declare_parameter("service_name", "/add_two_ints");
        std::string srv_name = this->get_parameter("service_name").as_string();

        service_ = this->create_service<add_two_ints_srv::srv::AddTwoInts>(
            srv_name, std::bind(&ServerNode::handle_service, this, _1, _2));
    }
private:
    void handle_service(const std::shared_ptr<add_two_ints_srv::srv::AddTwoInts::Request> request,
                        std::shared_ptr<add_two_ints_srv::srv::AddTwoInts::Response> response) {
        response->sum = request->a + request->b;
        RCLCPP_INFO(this->get_logger(), "收到请求: a=%ld, b=%ld", request->a, request->b);
    }
    rclcpp::Service<add_two_ints_srv::srv::AddTwoInts>::SharedPtr service_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ServerNode>());
    rclcpp::shutdown();
    return 0;
}