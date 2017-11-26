cmake_minimum_required(VERSION 2.8.3)
project(robo_rot)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
##  geometry_msgs
##  nav_msgs
  roscpp
##  rospy
##  sensor_msgs
##  tf
  std_msgs 
  pcl_ros 
##  laser_assembler 
##  message_filters 
## laser_geometry 
  
##cv_bridge
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenGL_INCLUDE_DIRS}
)
add_executable(robo_rot_node 
   src/ros_main.cpp
)

add_dependencies(robo_rot_node  ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(robo_rot_node
  ${catkin_LIBRARIES}
  ${OpenGL_LIBRARIES}
  ${GLUT_LIBRARY}
 )
