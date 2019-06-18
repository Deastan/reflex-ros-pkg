/*
 * Jonathan Burkhard, SMS-Lab, ETH Zurich, Switzerland
 * Jonathan Burkhard, CSEM S.A., Alpnach Dorf, Switzerland
 *
 * Node Close/Open the robotic hand
 *
 */

 // Includes
#include <string>
#include <boost/thread.hpp>

// Function
#include <std_msgs/Float64.h>
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"

// ROS
#include "ros/ros.h"

// Variables declaration

//Publishers
ros::Publisher publisher_proximal_1;
ros::Publisher publisher_proximal_2;
ros::Publisher publisher_proximal_3;

// Messages
std_msgs::Bool close_hand_msg;
// Messages
std_msgs::Float64 message_proximal_1;
std_msgs::Float64 message_proximal_2;
std_msgs::Float64 message_proximal_3;

// Callback function
void callback_close_hand(const std_msgs::Bool& msg);