#include <obstacle_detector/outliers_remover.h>
//#include "../include/obstacle_detector/outliers_remover.h"
using namespace obstacle_detector;

void Outliers_Remover::cloudCB(const sensor_msgs::PointCloud2ConstPtr& input)
{
  // Transfer from ROS type to PCL type
  pcl::fromROSMsg (*input, *scene_cloud);

  // Downsampling
  pcl::VoxelGrid<PT> sor;
  sor.setInputCloud(scene_cloud);
  sor.setLeafSize (0.01f, 0.01f, 0.01f);
  sor.filter (*downsample_cloud);

  // Create the filtering object
  pcl::StatisticalOutlierRemoval<PT> filter;
  filter.setInputCloud (downsample_cloud);
  filter.setMeanK (100);
  filter.setStddevMulThresh (0.1);
  // To show remove point
  //filter.setNegative (true);
  filter.filter (*remove_outlier_cloud);

  // Transfer PCL type to ROS type
  pcl::toROSMsg(*remove_outlier_cloud, downsample_cloud_msg);
  downsample_cloud_msg.header.frame_id = "camera_rgb_optical_frame";
  cloud_pub.publish(downsample_cloud_msg);
}

int main(int argc, char** argv)
{
  ros::init (argc, argv, "Outliers_Remover_node");
  ros::NodeHandle nh;
  ros::NodeHandle nh_local("~");
  Outliers_Remover outliers_remover(nh,nh_local);
  //ros::Publisher pub = nh.advertise<PointCloud> ("points2", 1);

  // PointCloud::Ptr msg (new PointCloud);
  // msg->header.frame_id = "some_tf_frame";
  // msg->height = msg->width = 1;
  // msg->points.push_back (pcl::PointXYZ(1.0, 2.0, 3.0));

  ros::Rate loop_rate(100);
  while (ros::ok())
  {
    ros::spinOnce ();
    loop_rate.sleep ();
  }
}
