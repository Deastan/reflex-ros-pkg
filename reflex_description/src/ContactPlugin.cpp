/*
 * Jonathan Burkhard, SMS-Lab, ETH Zurich, Switzerland
 * Jonathan Burkhard, CSEM S.A., Alpnach Dorf, Switzerland
 *
 * Contact plugin
 * Input :    Contact from Gazebo
 * Output :   publish message with the name of the sensors
 *            True if there is a contact
 *            False if there is not a contact 
 */

#include "ContactPlugin.h"

using namespace gazebo;

GZ_REGISTER_SENSOR_PLUGIN(ContactPlugin)

/////////////////////////////////////////////////
ContactPlugin::ContactPlugin() : SensorPlugin()
{
}

/////////////////////////////////////////////////
ContactPlugin::~ContactPlugin()
{
  // Disconnect sensor, see if this deletes sensor from world properly when
  //   hand is removed from world using remove_model
  // API https://osrf-distributions.s3.amazonaws.com/gazebo/api/dev/classgazebo_1_1sensors_1_1ContactSensor.html
  if (this -> parentSensor)
  {
    ROS_INFO ("Disconnecting contact sensor %s", this -> GetHandle ().c_str ());
    this -> parentSensor -> DisconnectUpdated (this -> updateConnection);
  }
}

/////////////////////////////////////////////////
void ContactPlugin::Load(sensors::SensorPtr _sensor, sdf::ElementPtr /*_sdf*/)
{
  // Make sure the ROS node for Gazebo has already been initialized
  if (!ros::isInitialized())
  {
    ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load plugin. "
      << "Load the Gazebo system plugin 'libgazebo_ros_api_plugin.so' in the gazebo_ros package)");
    return;
  }

  // Changing std to boost
  // boost::dynamic_pointer_cast<sensors::ContactSensor>(_sensor);
  // std::dynamic_pointer_cast<sensors::ContactSensor>(_sensor);
  // Get the parent sensor
  this->parentSensor = 
    boost::dynamic_pointer_cast<sensors::ContactSensor>(_sensor);

  // Make sure the parent sensor is valid.
  if (!this->parentSensor)
  {
    gzerr << "ContactPlugin requires a ContactSensor.\n";
    return;
  }

  // Connect to the sensor update event.
  this->updateConnection = this->parentSensor->ConnectUpdated(
      std::bind(&ContactPlugin::OnUpdate, this));

  // Make sure the parent sensor is active.
  this->parentSensor->SetActive(true);

  name_sensor = "/iiwa/" + _sensor->GetName();
  std::cerr << name_sensor << std::endl;
  contact_publisher = nh.advertise <std_msgs::Bool>(name_sensor, 30);
}

/////////////////////////////////////////////////

// For Gazebo 7+, it should be Contacts() with upper case, instead of lower case.
// contacts = this->parentSensor->Contacts();
// For previous versions (here 2.2):
// contacts = this->parentSensor->GetContacts();
// Be sure to check the Gazebo version on the tutorial's top-right corner.
void ContactPlugin::OnUpdate()
{   
  // Get all the contacts.
  msgs::Contacts contacts;
  contacts = this->parentSensor->GetContacts();

  if(contacts.contact_size () > 0)
  {
    ROS_INFO ("There is a contact ! ");
    // contact_message.header.stamp = ros::Time::now ();
    contact_message.data = true;
    contact_publisher.publish (contact_message);
  }else
  {
    // contact_message.header.stamp = ros::Time::now ();
    contact_message.data = false;
    contact_publisher.publish (contact_message);
  }
}