# obstacle_detector

# Start ROS core
$ roscore

# Open Realsense SR300 Camera
$ roslaunch realsense_camera sr300_nodelet_rgbd.launch 

# Start outliers_remover without nodelet
$ rosrun obstacle_detector outlier_remover

# Start outliers_remover with nodelet 
$ roslaunch obstacle_detector outlier_remover_nodelet.launch 

# Convert Point Cloud to 3D laser scan
$ roslaunch obstacle_detector pointcloud2scan.launch 

