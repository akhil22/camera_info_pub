#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/Image.h>
#include <string>
class ImagePub {
public:
  ImagePub() {
    nh = new ros::NodeHandle();
    nh->param("height", ht, 800);
    nh->param("wt", wt, 800);
    nh->param("frame", camera_frame, std::string("/cam"));
    //    nh->param("camera_sub_topic", camera_sub_topic,
    //              std::string("/image/compressed"));
    //   nh->param("camera_pub_topic", camera_pub_topic,
    //            std::string("/vehicle/front_camera/image_raw"));
    nh->param("camera_info_pub_topic", camera_info_pub_topic,
              std::string("front_camera/camera_info"));
    // image_sub = nh->subscribe(camera_pub_topic, 5, &ImagePub::CameraSub,
    // this);
    image_pub =
        nh->advertise<sensor_msgs::CameraInfo>(camera_info_pub_topic, 1);
    // camera_info_pub =
    //   nh->advertise<sensor_msgs::CameraInfo>(camera_info_pub_topic, 1);
  }
  void CameraSub(const sensor_msgs::CompressedImage::ConstPtr msg) { return; }

  void CameraInfoPub() {
    while (ros::ok()) {
      ros::Rate(10).sleep();
      sensor_msgs::CameraInfo cam_info_msg;
      cam_info_msg.height = ht;
      cam_info_msg.width = wt;
      cam_info_msg.header.frame_id = camera_frame;
      cam_info_msg.header.stamp = ros::Time::now();
      cam_info_msg.distortion_model = std::string("plumb_bob");
      double fx = 480;
      cam_info_msg.D.resize(5);
      cam_info_msg.D[0] = 0;
      cam_info_msg.D[1] = 0;
      cam_info_msg.D[2] = 0;
      cam_info_msg.D[3] = 0;
      cam_info_msg.D[4] = 0;
      cam_info_msg.K[0] = fx;
      cam_info_msg.K[1] = 0;
      cam_info_msg.K[2] = 400;
      cam_info_msg.K[3] = 0;
      cam_info_msg.K[4] = fx;
      cam_info_msg.K[5] = 400;
      cam_info_msg.K[6] = 0;
      cam_info_msg.K[7] = 0;
      cam_info_msg.K[8] = 1;
      cam_info_msg.P[0] = fx;
      cam_info_msg.P[1] = 0;
      cam_info_msg.P[2] = 400;
      cam_info_msg.P[3] = 0;
      cam_info_msg.P[4] = 0;
      cam_info_msg.P[5] = fx;
      cam_info_msg.P[6] = 400;
      cam_info_msg.P[7] = 0;
      cam_info_msg.P[8] = 0;
      cam_info_msg.P[9] = 0;
      cam_info_msg.P[10] = 1;
      cam_info_msg.P[11] = 0;
      cam_info_msg.R[0] = 1;
      cam_info_msg.R[1] = 0;
      cam_info_msg.R[2] = 0;
      cam_info_msg.R[3] = 0;
      cam_info_msg.R[4] = 1;
      cam_info_msg.R[5] = 0;
      cam_info_msg.R[6] = 0;
      cam_info_msg.R[7] = 0;
      cam_info_msg.R[8] = 1;
      cam_info_msg.binning_x = 0;
      cam_info_msg.binning_y = 0;
      cam_info_msg.roi.height = 0;
      cam_info_msg.roi.width = 0;
      cam_info_msg.roi.x_offset = 0;
      cam_info_msg.roi.y_offset = 0;
      cam_info_msg.roi.do_rectify = false;
      image_pub.publish(cam_info_msg);
      ros::spinOnce();
    }
    return;
  }
  ros::NodeHandle *nh;
  int ht;
  int wt;
  std::string camera_sub_topic;
  std::string camera_pub_topic;
  std::string camera_info_pub_topic;
  std::string camera_frame;
  ros::Subscriber image_sub;
  ros::Publisher image_pub;
  ros::Publisher camera_info_pub;
};
int main(int argc, char **argv) {
  ros::init(argc, argv, "image_pub");
  ImagePub image_pub;
  image_pub.CameraInfoPub();
  // ros::NodeHandle nh("~");
  // int ht;
  // int wt;
  // nh.param("height", ht, 240);
  // nh.param("width", wt, 320);
}
