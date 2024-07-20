#pragma once

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include <rclcpp/rclcpp.hpp>

#include <turtlesim/srv/spawn.hpp>

namespace composition {

class p3_spawn : public rclcpp::Node {
    public:
        p3_spawn(const rclcpp::NodeOptions &options);
    private:
        typedef struct Turtle {
            std::string name;
            float x;
            float y;
            float rad;
        } Turtle;
        // the client to send requests with
        rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr client;
        rclcpp::TimerBase::SharedPtr timer;

        Turtle turtles_to_spawn[2] = {
            {"stationary_turtle", 5.0, 5.0, 0.0},
            {"moving_turtle", 25.0, 10.0, 0.0}
        }

        void spawn_turtle();
};

} // namespace composition
