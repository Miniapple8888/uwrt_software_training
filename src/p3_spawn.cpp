#include "../include/software_training/p3_spawn.hpp"

namespace composition {

p3_spawn::p3_spawn(const rclcpp::NodeOptions &options)
    : Node{"p3_spawn", options} {
    // initialize client
    this->client = this->create_client<turtlesim::srv::Spawn>("/spawn");
    // spawn the turtles
    this->spawn_turtle();
} 
    
p3_spawn::spawn_turtle() {
    // Check if the service is available
    if (!client_->wait_for_service(std::chrono::seconds(2))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting");
            return;
        }
        RCLCPP_ERROR(this->get_logger(), "Service not available");
        return;
    }

    for (auto turtle : in this->turtles) {
        auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
        request->name = turtle->name;
        request->x = turtle->x;
        request->x = turtle->y;
        request->theta = turtle->rad;


        // create callback lambda
        auto callback = [this](rclcpp::Client<turtlesim::srv::Spawn>::SharedFuture response) -> void {
            RCLCPP_INFO(this->get_logger(), "Turtle Info: name:%s x:%.2f y:%.2f, theta:%.2f", 
            response->name.c_str(), response->x, response->y, response->theta);
            rclcpp::shutdown(); // kill this node
        };

        // send async request with request msg and callback as params
        auto future = client_->async_send_request(request, callback);
    }
}

} // namespace composition

#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(composition::p3_spawn)
