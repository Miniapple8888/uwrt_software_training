#include "../include/software_training/p2_circle.hpp"

using namespace std::chrono_literals;
namespace composition {

p2_circle::p2_circle(const rclcpp::NodeOptions& options) 
    : Node{"p2_circle", options} {
    const std::string turtle1_vel_pub = "/turtle1/cmd_vel";
    this->publisher = this->create_publisher<geometry_msgs::msg::Twist>(turtle1_vel_pub);

    // create a timer to run the callback every n milliseconds
    this->timer_ = this->create_wall_timer(
        std::chrono::seconds(1),
        [this]() { this->publish_callback(); }
    );
}

void p2_circle::publish_callback() {
    auto twist_msg = geometry_msgs::msg::Twist();

    twist_msg.linear = this->linear;
    twist_msg.angular = this->angular;

    this->publisher->publish(twist_msg);

    // Log the message for debugging
    RCLCPP_INFO(this->get_logger(), "Publishing Twist: linear(x: %f, y: %f, z: %f), angular(x: %f, y: %f, z: %f)",
                twist_msg.linear.x, twist_msg.linear.y, twist_msg.linear.z,
                twist_msg.angular.x, twist_msg.angular.y, twist_msg.angular.z);
}

} // namespace composition

#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(composition::p2_circle)
