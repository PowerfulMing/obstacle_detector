/*
 * outliers_remover_nodelet_class.h
 *
 *  Created on: 2018/03/28
 *      Author: Chien-Ming Lin
 */
#ifndef OUTLIERS_REMOVER_NODELET_CLASS_H_
#define OUTLIERS_REMOVER_NODELET_CLASS_H_
#include <memory>
#include <iostream>
#include <std_srvs/Empty.h>
#include <nodelet/nodelet.h>
#include <obstacle_detector/outliers_remover.h>
#include <pluginlib/class_list_macros.h>

namespace obstacle_detector
{
class OutliersRemoverNodeletClass : public nodelet::Nodelet
{
public:
    OutliersRemoverNodeletClass()
    {
	    ROS_INFO("OutliersRemoverNodeletClass Constructor");
    }
    ~OutliersRemoverNodeletClass()
    {
	    ROS_INFO("OutliersRemoverNodeletClass Destructor");
    }

    virtual void onInit()
    {
	    NODELET_INFO("OutliersRemoverNodeletClass - %s", __FUNCTION__);
        ros::NodeHandle nh = getNodeHandle();
        ros::NodeHandle nh_local = getPrivateNodeHandle();
        outliers_remover_ = std::shared_ptr<Outliers_Remover>(new Outliers_Remover(nh, nh_local));
    }
private:
    std::shared_ptr<Outliers_Remover> outliers_remover_;
};
}

#endif /* OUTLIERS_REMOVER_NODELET_CLASS_H_ */

PLUGINLIB_EXPORT_CLASS(obstacle_detector::OutliersRemoverNodeletClass, nodelet::Nodelet)
