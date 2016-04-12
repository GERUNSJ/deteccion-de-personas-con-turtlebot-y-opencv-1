/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    //cv::Mat src;
    //cv_bridge::CvImagePtr cv_ptr;
    std::cout << "6666" << std::endl;
  /*try
  {
      std::cout << "7777***2" << std::endl;
      //cv::imshow("vista", cv_bridge::toCvShare(msg, "bgr8")->image);
      //src = cv_bridge::CvImage(msg, "bgr8")->image;
      //src = cv_bridge::toCvShare(msg, "bgr8")->image;
      //src = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
      
    //cv::imshow("Este es el B", cv_bridge::toCvShare(msg, "bgr8")->image);
      //cv::imshow("vista", src);
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }*/
    
    
        try{
        //cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_8UC3);
        cv::imshow("vista", cv_bridge::toCvShare(msg, "bgr8")->image);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception:  %s", e.what());
        return;
    }
    
    
    //cv::imshow("vista", *cv_ptr->image);
    
    // Output modified video stream
    //image_pub_.publish(cv_ptr->toImageMsg());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  std::cout << "11111" << std::endl;
  ros::NodeHandle nh;
  std::cout << "22222" << std::endl;
  cv::namedWindow("vista");
  std::cout << "33333" << std::endl;
  cv::startWindowThread();
  std::cout << "44444444" << std::endl;
  image_transport::ImageTransport it(nh);
  std::cout << "5555****" << std::endl;
  image_transport::Subscriber sub = it.subscribe("camera/image", 1, imageCallback);
  std::cout << "8888" << std::endl;
  
  ros::spin();
  cv::destroyWindow("vista");
}