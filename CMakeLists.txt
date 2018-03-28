cmake_minimum_required(VERSION 2.8.3)
project(obstacle_detector)

find_package(catkin REQUIRED COMPONENTS
  nodelet
  pcl_ros
  roscpp
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS pcl_ros roscpp nodelet
  LIBRARIES ${PROJECT_NAME}_lib
)

###########
## Build ##
###########
include_directories(
  include
  ${${PROJECT_NAME}_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(${PROJECT_NAME}_lib
  src/outliers_remover.cpp
)

## Declare a C++ executable
add_executable(remove_outliers_node src/outliers_remover.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(remove_outliers_node
  ${catkin_LIBRARIES}
  ${PROJECT_NAME}_lib
)

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(remove_outliers_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

#############
## Install ##
#############
## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)
