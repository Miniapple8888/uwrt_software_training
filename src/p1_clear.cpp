#include "../include/software_training/p1_clear.hpp"

namespace composition {

p1_clear::p1_clear(const rclcpp::NodeOptions &options) 
    : Node("p1_clear", options){
    // initialize the client
    this->client = this->create_client<turtlesim::srv::Kill>("/kill");
    // run the kill command
    this->kill();
}

void p1_clear::kill() {
    // Check if the service is available
    if (!client_->wait_for_service(std::chrono::seconds(2))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting");
            return;
        }
        RCLCPP_ERROR(this->get_logger(), "Service not available");
        return;
    }

    for (auto name : this->turtle_names) {
        // create a msg holds kill request
        auto request = std::make_shared<turtlesim::srv::Kill::Request>();
        // set name field of msg
        request->name = name;
        // create callback lambda
        auto callback = [this](rclcpp::Client<turtlesim::srv::Kill>::SharedFuture response) -> void {
            (void)response; // void the response since we don't need one
            RCLCPP_INFO(this->get_logger(), "Turtle  Killed");
            rclcpp::shutdown(); // kill this node
        };

        // send async request with request msg and callback as params
        auto future = client_->async_send_request(request, callback);
    }
}

#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(composition::p1_clear)
