#!/usr/bin/env python
# Adapt from:
# https://github.com/bgromov/thymio_gazebo/blob/master/thymio_description/scripts/gazebo_link_pose

import rospy
from gazebo_msgs.msg import LinkStates
from geometry_msgs.msg import Pose

class GazeboLinkPose:
  link_name = 'object_to_push::link'
  link_pose = Pose()
  def __init__(self, link_name):
    self.link_name = link_name
    self.link_name_rectified = link_name.replace("::", "_")

    if not self.link_name:
      raise ValueError("'link_name' is an empty string")

    self.states_sub = rospy.Subscriber("/gazebo/link_states", LinkStates, self.callback)
    self.pose_pub = rospy.Publisher("/gazebo/" + self.link_name_rectified, Pose, queue_size = 10)

  def callback(self, data):
    try:
      ind = data.name.index(self.link_name)
      self.link_pose = data.pose[ind]
    except ValueError:
      pass

if __name__ == '__main__':
  try:
    rospy.init_node('Gazebo_object_pose', anonymous=False)
    # Shortcut the code...
    # gp = GazeboLinkPose(rospy.get_param('~link_name'))
    gp = GazeboLinkPose('object_to_push::link')
    publish_rate = 30#rospy.get_param('~publish_rate', 10)

    rate = rospy.Rate(publish_rate)
    while not rospy.is_shutdown():
      gp.pose_pub.publish(gp.link_pose)
      rate.sleep()

  except rospy.ROSInterruptException:
    pass