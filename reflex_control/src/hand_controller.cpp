/*
 * Jonathan Burkhard, SMS-Lab, ETH Zurich, Switzerland
 * Jonathan Burkhard, CSEM S.A., Alpnach Dorf, Switzerland
 *
 * Node Transmission link the proximal joint with the distal
 */

//Include
#include "hand_controller.h"

int main(int argc, char **argv)
{
  // Init ROS
  ros::init(argc, argv, "hand_controller");

  ros::NodeHandle nh;

  publisher_proximal_1 = nh.advertise <std_msgs::Float64>("/reflex_takktile_2/proximal_joint_1_position_controller/command", 30);
  publisher_proximal_2 = nh.advertise <std_msgs::Float64>("/reflex_takktile_2/proximal_joint_2_position_controller/command", 30);
  publisher_proximal_3 = nh.advertise <std_msgs::Float64>("/reflex_takktile_2/proximal_joint_3_position_controller/command", 30);

  ros::Subscriber sub_close_hand = nh.subscribe("/reflex_takktile_2/close_hand", 30, callback_close_hand);

  ros::AsyncSpinner spinner(6);  // Use 4 threads
  spinner.start();

  ros::waitForShutdown();

  return 0;
} // end main function

void callback_close_hand(const std_msgs::Bool& msg)
{ 
  if(msg.data == true)
  {
    float proximal_angle = 1.57;

    message_proximal_1.data = proximal_angle;
    message_proximal_2.data = proximal_angle;
    message_proximal_3.data = proximal_angle;

    publisher_proximal_1.publish(message_proximal_1);
    publisher_proximal_2.publish(message_proximal_2);
    publisher_proximal_3.publish(message_proximal_3);

  }else
  {
    float proximal_angle = 0.0;

    message_proximal_1.data = proximal_angle;
    message_proximal_2.data = proximal_angle;
    message_proximal_3.data = proximal_angle;

    publisher_proximal_1.publish (message_proximal_1);
    publisher_proximal_2.publish (message_proximal_2);
    publisher_proximal_3.publish (message_proximal_3);    
  }
} // end callback_close_hand function 
