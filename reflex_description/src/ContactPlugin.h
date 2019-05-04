/*
 * Jonathan Burkhard, SMS-Lab, ETH Zurich, Switzerland
 * Jonathan Burkhard, CSEM S.A., Alpnach Dorf, Switzerland
 *
 */

#ifndef _GAZEBO_CONTACT_PLUGIN_HH_
#define _GAZEBO_CONTACT_PLUGIN_HH_

#include <string>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>

// ROS
#include <ros/ros.h>


// My packages
#include <reflex_msgs2/FingerPressure.h>

#include <gazebo/gazebo.hh>
#include <gazebo/sensors/sensors.hh>

namespace gazebo
{
  /// \brief An example plugin for a contact sensor.
  class ContactPlugin : public SensorPlugin
  {
    /// \brief Constructor.
    public: ContactPlugin();

    /// \brief Destructor.
    public: virtual ~ContactPlugin();

    /// \brief Load the sensor plugin.
    /// \param[in] _sensor Pointer to the sensor that loaded this plugin.
    /// \param[in] _sdf SDF element that describes the plugin.
    public: virtual void Load(sensors::SensorPtr _sensor, sdf::ElementPtr _sdf);

    /// \brief Callback that receives the contact sensor's update signal.
    private: virtual void OnUpdate();

    /// \brief Pointer to the contact sensor
    private: sensors::ContactSensorPtr parentSensor;

    /// \brief Connection that maintains a link between the contact sensor's
    /// updated signal and the OnUpdate callback.
    private: event::ConnectionPtr updateConnection;

    /// Ros part 
    /// Initialization
    private: std::string name_sensor; // Name of the sensors for the topic
    private: ros::NodeHandle nh; /// node
    private: ros::Publisher contact_publisher; // publisher for ros
    private: std_msgs::Bool contact_message;
  };
}
#endif