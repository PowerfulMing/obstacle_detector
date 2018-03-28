/***********************************************************************
 *  Object Pose Estimation
 *
 *  Author: Chien-Ming Lin (2018/03/23)
 * 
 *  To remove the noise of point cloud and republish it!
 * 
 *  Input:  sensor_msgs/pointcloud2
 *  Output: sensor_msgs/pointcloud2
 * 
 *  2018/03/27 Porting nodes to nodelets
 ***********************************************************************/
#include <iostream>

// ROS
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

// PCL
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/voxel_grid.h>

typedef pcl::PointXYZRGB PT;                   // Point Type with XYZ and color
typedef pcl::PointCloud<PT> PCT;                // Point Cloud Type


namespace obstacle_detector
{
class Outliers_Remover
{
    public:
        Outliers_Remover(ros::NodeHandle& nh, ros::NodeHandle& nh_local):
        scene_cloud(new PCT),
        downsample_cloud(new PCT),
        remove_outlier_cloud(new PCT)
        {
            cloud_sub = nh_.subscribe("/camera/depth_registered/points", 1, &Outliers_Remover::cloudCB,this);
            cloud_pub = nh_.advertise<sensor_msgs::PointCloud2>("/camera/depth_registered/points_without_noise", 1);
        }
        ~Outliers_Remover(){}

    private:

        // Callback Function for Subscribe Point Cloud
        void cloudCB(const sensor_msgs::PointCloud2ConstPtr& input);
        
        // ---------------- //
        // ---- Variable ---//
        // ---------------- //
        
        //ROS
        ros::NodeHandle nh_;
        ros::Subscriber cloud_sub;
        ros::Publisher cloud_pub;
        sensor_msgs::PointCloud2 downsample_cloud_msg;

        // PCL Point Cloud
        PCT::Ptr scene_cloud;
        PCT::Ptr downsample_cloud;
        PCT::Ptr remove_outlier_cloud;
};
}
