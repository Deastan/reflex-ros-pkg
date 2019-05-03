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

  ROS_INFO ("********** I am in ContactPlugin::Load(sensors::SensorPtr _sensor, sdf::ElementPtr /*_sdf*/)");
  std::cout << "BIM BIM BIM : ContactPlugin::Load(sensors::SensorPtr _sensor, sdf::ElementPtr /*_sdf*/)" << std::endl;
  // Changing std to boost
  // boost::dynamic_pointer_cast<sensors::ContactSensor>(_sensor);
  // std::dynamic_pointer_cast<sensors::ContactSensor>(_sensor);
  // Get the parent sensor.
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
}

/////////////////////////////////////////////////

// For Gazebo 7+, it should be Contacts() with upper case, instead of lower case.
// contacts = this->parentSensor->Contacts();
// For previous versions (here 2.2):
// contacts = this->parentSensor->GetContacts();
// Be sure to check the Gazebo version on the tutorial's top-right corner.
void ContactPlugin::OnUpdate()
{   
  ROS_INFO ("********** I am in ContactPlugin::OnUpdate()");
  std::cout << "BIM BIM BIM : ContactPlugin::OnUpdate()" << std::endl;
  // Get all the contacts.
  msgs::Contacts contacts;
  contacts = this->parentSensor->GetContacts();

  for (unsigned int i = 0; i < contacts.contact_size(); ++i)
  {
    std::cout << "Collision between[" << contacts.contact(i).collision1()
              << "] and [" << contacts.contact(i).collision2() << "]\n";

    for (unsigned int j = 0; j < contacts.contact(i).position_size(); ++j)
    {
      std::cout << j << "  Position:"
                << contacts.contact(i).position(j).x() << " "
                << contacts.contact(i).position(j).y() << " "
                << contacts.contact(i).position(j).z() << "\n";
      std::cout << "   Normal:"
                << contacts.contact(i).normal(j).x() << " "
                << contacts.contact(i).normal(j).y() << " "
                << contacts.contact(i).normal(j).z() << "\n";
      std::cout << "   Depth:" << contacts.contact(i).depth(j) << "\n";
    }
  }
}