#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
#include <math.h>

// Pose of turtle1
turtlesim::Pose _pose1;

// Pose of turtle2
turtlesim::Pose _pose2;

void poseCallback1(const turtlesim::Pose::ConstPtr& msg)
{
    _pose1 = *msg;
}

void poseCallback2(const turtlesim::Pose::ConstPtr& msg)
{
    _pose2 = *msg;
}
 
int main (int argc, char* argv[])
{
    ros::init (argc, argv, "turtle_control_node");

    ros::NodeHandle n;

    ros::Subscriber sub1 = n.subscribe("turtle1/pose", 1, poseCallback1);

    ros::Subscriber sub2 = n.subscribe("turtle2/pose", 1, poseCallback2);

    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 1);

    ros::Rate loop_rate (1);

    int count = 0;

    while (ros::ok ())
    {
    double dx = _pose1.x - _pose2.x;     

    double dy = _pose1.y - _pose2.y;

    double dabs = sqrt(dx * dx + dy * dy);

    ROS_INFO("deltaAbs: %lf", dabs); 

    double theta = atan2(dy, dx);

    double deltaTheta = theta - _pose2.theta;

    ROS_INFO("deltaTheta: %lf", deltaTheta); 

        geometry_msgs::Twist msg;

    msg.linear.x = 0.1 * dabs;

    msg.linear.y = 0.0;

    msg.linear.z = 0.0;

    msg.angular.x = 0.0;

    msg.angular.y = 0.0;

    msg.angular.z = 0.5 * deltaTheta;

    //Stop Schwelle

    if(dabs < 0.8)

    {

        msg.linear.x = 0.0;

    }    

        pub.publish (msg);

    ros::spinOnce();

    loop_rate.sleep();
    }
    return 0;
}

 