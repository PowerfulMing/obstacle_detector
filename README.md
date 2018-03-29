# obstacle_detector

## Start Detect Obstacle
### Start ROS core
'''
$ roscore
'''
### Open Realsense SR300 Camera
'''
$ roslaunch realsense_camera sr300_nodelet_rgbd.launch 
'''
### Start outliers_remover without nodelet
'''
$ rosrun obstacle_detector outlier_remover
'''
### Start outliers_remover with nodelet 
'''
$ roslaunch obstacle_detector outlier_remover_nodelet.launch 
'''
### Convert Point Cloud to 3D laser scan
'''
$ roslaunch obstacle_detector pointcloud2scan.launch 
'''
## Running Some Test
### Run with rtabmap
'''
$ roslaunch rtabmap_ros rtabmap.launch rtabmap_args:="--delete_db_on_start" depth_topic:=/camera/depth_registered/sw_registered/image_rect_raw
'''

### Run with FIRA_GAZEBO and MOVE_BASE 
To test whether move_base will generate the local cost map with noise or not.
Gazebo and robot_state_publisher will publish a fake robot link
'''
// FIRA in Gazebo
$ roslaunch fira6_gazebo UEC_research.launch 
// Open SR300 camera
$ roslaunch realsense_camera sr300_nodelet_rgbd.launch 
// Remove the noise point cloud from SR300 and downsample
$ roslaunch obstacle_detector outlier_remover_nodelet.launch 
// Convert point cloud to 2D laser scan
$ roslaunch obstacle_detector pointcloud2scan.launch 
// 
$ rosrun tf static_transform_publisher 0 0 0 0 0 0 scaer_base camera_link 100

'''


