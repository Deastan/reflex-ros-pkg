cmake_minimum_required(VERSION 2.8.3)
project(reflex_control)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  reflex
  reflex_msgs2
  roscpp
  sensor_msgs
  urdf
  visualization_msgs
  gazebo_ros
  std_msgs 
  geometry_msgs
)

# Depend on system install of Gazebo
find_package(gazebo REQUIRED)

# Because GPU cluster says this package requires c++11 to build, not sure why.
#   Builds fine without this on my laptop.
set(CMAKE_CXX_FLAGS "-std=c++0x")

###################################
## catkin specific configuration ##
###################################
catkin_package(
  #  INCLUDE_DIRS include
  #  LIBRARIES reflex_gazebo
  CATKIN_DEPENDS roscpp  
#  DEPENDS Boost
)

#include_directories(
#  ${catkin_INCLUDE_DIRS}
#)

###########
## Build ##
###########
## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(${Boost_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

add_executable(transmissionProximalToDistal_node src/transmissionProximalToDistal_node.cpp)
target_link_libraries(transmissionProximalToDistal_node ${catkin_LIBRARIES})
#add_dependencies(transmissionProximalToDistal_node beginner_tutorials_generate_messages_cpp)

## Specify libraries to link a library or executable target against
#target_link_libraries(contact ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})


## Declare a cpp executable
#add_executable(hand_visualizer2 src/hand_visualizer.cpp)
#add_executable(reflex imu.py)

## Specify libraries to link a library or executable target against
#target_link_libraries(hand_visualizer2 ${catkin_LIBRARIES})
#add_dependencies(hand_visualizer2 reflex_msgs2_gencpp)
