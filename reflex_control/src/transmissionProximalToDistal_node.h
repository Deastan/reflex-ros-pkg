/*
 * Jonathan Burkhard, SMS-Lab, ETH Zurich, Switzerland
 * Jonathan Burkhard, CSEM S.A., Alpnach Dorf, Switzerland
 *
 */
#include <string>
#include <std_msgs/Bool.h>

#include <std_msgs/Float64.h>
// std_msgs/Float64.msg

// ROS
// #include <ros/ros.h>
  
#include "ros/ros.h"
#include "std_msgs/String.h"




// ROS part 
// Initialization
// std::string name_sensor; // Name of the sensors for the topic
// ros::NodeHandle nh; /// node
// ros::Publisher contact_publisher; // publisher for ros
// std_msgs::Bool contact_message;

ros::Publisher publisher_proximal_1;
ros::Publisher publisher_proximal_2;
ros::Publisher publisher_proximal_3;

std_msgs::Float64 contact_message_proximal_1;
std_msgs::Float64 contact_message_proximal_2;
std_msgs::Float64 contact_message_proximal_3;

// void callback(const std_msgs::StringConstPtr& str);
void callback_proximal_1(const std_msgs::Float64& msg);
void callback_proximal_2(const std_msgs::Float64& msg);
void callback_proximal_3(const std_msgs::Float64& msg);