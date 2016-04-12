/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: fabricio
 *
 * Created on 8 de marzo de 2016, 17:50
 */

#include <cstdlib>
#include "ImageConverter.h"
#include <ros/ros.h>

using namespace std;

int main(int argc, char** argv)
{
  cout<<"estamos ver 1.0.11"<< endl;
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  ros::spin();
  return 0;
}
