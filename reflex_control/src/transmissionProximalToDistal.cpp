/*
 * Jonathan Burkhard, SMS-Lab, ETH Zurich, Switzerland
 * Jonathan Burkhard, CSEM S.A., Alpnach Dorf, Switzerland
 *
 * Node Transmission link the proximal joint with the distal
 */

//Include
#include "transmissionProximalToDistal_node.h"


int main(int argc, char **argv)
{
  // Init ROS
  ros::init(argc, argv, "transmission_proximal_to_distal_node");

  ros::NodeHandle nh;

  publisher_proximal_1 = nh.advertise <std_msgs::Float64>("/reflex_takktile_2/distal_joint_1_position_controller/command", 30);
  publisher_proximal_2 = nh.advertise <std_msgs::Float64>("/reflex_takktile_2/distal_joint_2_position_controller/command", 30);
  publisher_proximal_3 = nh.advertise <std_msgs::Float64>("/reflex_takktile_2/distal_joint_3_position_controller/command", 30);

  // ros::MultiThreadedSpinner spinner(3); // Use 3 threads
  // spinner.spin(); // spin() will not return until the node has been shutdown

  ros::Subscriber sub_proximal_1 = nh.subscribe("/reflex_takktile_2/proximal_joint_1_position_controller/command", 30, callback_proximal_1);
  ros::Subscriber sub_proximal_2 = nh.subscribe("/reflex_takktile_2/proximal_joint_2_position_controller/command", 30, callback_proximal_2);
  ros::Subscriber sub_proximal_3 = nh.subscribe("/reflex_takktile_2/proximal_joint_3_position_controller/command", 30, callback_proximal_3);

    // ros::spinOnce();
    ros::spin();

  // End of the main
  // ROS_INFO_STREAM("End of the node : transmissionProximalToDistal");

  return 0;
} //end main function

void callback_proximal_1(const std_msgs::Float64& msg)
{ 
  contact_message_proximal_1.data = msg.data * 0.5;
  publisher_proximal_1.publish (contact_message_proximal_1);
}

void callback_proximal_2(const std_msgs::Float64& msg)
{ 
  contact_message_proximal_2.data = msg.data * 0.5;
  publisher_proximal_2.publish (contact_message_proximal_2);
}

void callback_proximal_3(const std_msgs::Float64& msg)
{ 
  contact_message_proximal_3.data = msg.data * 0.5;
  publisher_proximal_3.publish (contact_message_proximal_3);
}
