#pragma once

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include <rclcpp/rclcpp.hpp>

#include <turtlesim/srv/kill.hpp>

namespace composition {
class p1_clear : public rclcpp::Node {
    public:
        p1_clear(const rclcpp::NodeOptions &options);
    private:
        void kill(); // function that sends kill requests
        
        // the client to send requests with
        rclcpp::Client<turtlesim::srv::Kill>::SharedPtr client;
        
        // all the turtles
        std::vector<std::string> turtle_names = {"moving_turtle", "stationary turtle"};
        
};

} // namespace composition
