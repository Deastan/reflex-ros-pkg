/*
 * Jonathan Burkhard, SMS-Lab, ETH Zurich, Switzerland
 * Jonathan Burkhard, CSEM S.A., Alpnach Dorf, Switzerland
 *
 * Node Transmission link the proximal joint with the distal
 *
 */

 // Includes
#include <string>

// Function
#include <std_msgs/Float64.h>
#include "std_msgs/String.h"

// ROS
#include "ros/ros.h"


// Variables initialization

//Publishers
ros::Publisher publisher_proximal_1;
ros::Publisher publisher_proximal_2;
ros::Publisher publisher_proximal_3;

// Messages
std_msgs::Float64 contact_message_proximal_1;
std_msgs::Float64 contact_message_proximal_2;
std_msgs::Float64 contact_message_proximal_3;

// Callback function
void callback_proximal_1(const std_msgs::Float64& msg);
void callback_proximal_2(const std_msgs::Float64& msg);
void callback_proximal_3(const std_msgs::Float64& msg);