cmake_minimum_required(VERSION 2.8.3)
project(obstacle_detector)

set(CMAKE_CXX_FLAGS "-std=c++11 -fpermissive ${CMAKE_CXX_FLAGS} -Wfatal-errors\ ")

find_package(catkin REQUIRED COMPONENTS
  nodelet
  pcl_ros
  roscpp
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS pcl_ros roscpp nodelet
  LIBRARIES outliers_remover_lib
)

###########
## Build ##
###########
include_directories(
  include
  ${${PROJECT_NAME}_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS}
)

## Declare outliers_remover library
add_library(outliers_remover_lib
  src/outliers_remover.cpp
)
target_link_libraries(outliers_remover_lib 
  ${catkin_LIBRARIES}
)
add_dependencies(outliers_remover_lib 
  ${catkin_EXPORTED_TARGETS}
)

## Declare a C++ executable
add_executable(outliers_remover_node 
  src/outliers_remover.cpp
)
target_link_libraries(outliers_remover_node
 outliers_remover_lib
)

## Declare a Nodelet library
## And specify libraries to link a library or executable target against
add_library(${PROJECT_NAME}_nodelet
  nodelet/outliers_remover_nodelet.cpp
  )

target_link_libraries(${PROJECT_NAME}_nodelet 
  outliers_remover_lib
)
if(catkin_EXPORTED_LIBRARIES)
  add_dependencies(${PROJECT_NAME}_nodelet ${catkin_EXPORTED_LIBRARIES})
endif()

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(outliers_remover_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

#############
## Install ##
#############
## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)
