#pragma once

#include <chrono>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

namespace composition {

class p2_circle : public rclcpp::Node {
    public:
        p2_circle(const rclcpp::NodeOptions& options);
    private:
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;
        void publish_callback();
        // callback timer
        rclcpp::TimerBase::SharedPtr timer_;

        Vector3 linear{1.0,0.0,0.0};
        Vector3 angular{0.0,0.0,1.0};
};


} // namespace composition
