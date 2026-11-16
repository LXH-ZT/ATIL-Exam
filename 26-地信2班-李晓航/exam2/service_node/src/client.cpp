 #include <chrono>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "add_two_ints_srv/srv/add_two_ints.hpp"

using namespace std::chrono_literals;

class ClientNode : public rclcpp::Node {
public:
    ClientNode() : Node("add_two_ints_client") {
        
        this->declare_parameter("service_name", "/add_two_ints");
        std::string srv_name = this->get_parameter("service_name").as_string();

        client_ = this->create_client<add_two_ints_srv::srv::AddTwoInts>(srv_name);
    }
    void send_request() {
        while (!client_->wait_for_service(1s)) {
            RCLCPP_INFO(this->get_logger(), "等待服务端...");
        }
        auto request = std::make_shared<add_two_ints_srv::srv::AddTwoInts::Request>();
        request->a = 3;
        request->b = 5;
        auto future = client_->async_send_request(request,
            [this](rclcpp::Client<add_two_ints_srv::srv::AddTwoInts>::SharedFuture future) {
                RCLCPP_INFO(this->get_logger(), "收到结果: %ld", future.get()->sum);
            });
    }
private:
    rclcpp::Client<add_two_ints_srv::srv::AddTwoInts>::SharedPtr client_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ClientNode>();
    node->send_request();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
