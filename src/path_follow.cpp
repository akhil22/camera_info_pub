#include <cmath>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <nav_msgs/Path.h>
#include <ros/ros.h>
class PathFollower {
public:
  ros::NodeHandle *nh;
  ros::Subscriber path_sub;
  ros::Publisher vel_pub;
  void PathCallback(const nav_msgs::Path::ConstPtr msg) {
    if (msg->poses.size() <= 0) {
      return;
    }
    double x = msg->poses[0].pose.position.x;
    double y = msg->poses[0].pose.position.y;
    ROS_INFO("thete %f y = %f", x, y);
    if (x > 30 || y > 10) {
      return;
    }
    double theta = atan2(y, x);
    ROS_INFO("thete %f", theta);
    geometry_msgs::Twist twist;
    twist.linear.x = 0.4 - theta * 0.4;
    twist.angular.z = theta * 1.5;
    vel_pub.publish(twist);
  }
  PathFollower() {
    nh = new ros::NodeHandle;
    path_sub =
        nh->subscribe("/target_path", 20, &PathFollower::PathCallback, this);
    vel_pub = nh->advertise<geometry_msgs::Twist>("/cmd_vel", 20);
  }
};
int main(int argc, char **argv) {
  ros::init(argc, argv, "path_follower");
  PathFollower path_follwer;
  ros::spin();
}
