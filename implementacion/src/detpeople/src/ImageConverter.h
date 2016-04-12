/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ImageConverter.hpp
 * Author: fabricio
 *
 * Created on 22 de marzo de 2016, 10:07
 */
#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H
#include </opt/ros/indigo/include/ros/ros.h>
//#include <ros/ros.h>
//#include <image_transport/image_transport.h>
//#include <cv_bridge/cv_bridge.h>
//#include <sensor_msgs/image_encodings.h>
#include </opt/ros/indigo/include/image_transport/image_transport.h>
#include </opt/ros/indigo/include/cv_bridge/cv_bridge.h>
#include </opt/ros/indigo/include/sensor_msgs/image_encodings.h>

#include "opencv2/opencv.hpp"
#include "DetectorCascada.h"
#include "PreFiltro.h"
#include "DetectorHog.h"

static const std::string OPENCV_WINDOW = "Imagen final";
//static const std::string OPENCV_WINDOW2 = "Image window";

class ImageConverter
{
    ros::NodeHandle nh_;
    
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Subscriber image_sub_depth_;
    image_transport::Publisher image_pub_;
   
    
    PreFiltro* imagen_prefiltrada;
    //DetectorCascada* deteccion;
    DetectorHog* HOG;
    
    // Número por el que se dividirá la imagen inicialmente. Puede servir si es grande.
    const float escala_inicial = 1;
    
    // vector donde se almacena los rectangulos donde se encuentra la persona
    std::vector<cv::Rect> personas;

    cv_bridge::CvImagePtr cv_ptr;
    // Imagen original recibida.
    cv::Mat imagen_recibida;
    // Imagen modificada
    cv::Mat imagen_mostrada;
    
    
    cv_bridge::CvImagePtr cv_ptr_depth;
    // Imagen original recibida.
    cv::Mat imagen_recibida_depth;
    // Imagen modificada
    cv::Mat imagen_mostrada_depth;
    
    /** \fn En esta funcion se encuentran agrupados todos los metodos y funciones 
     *      dedicadas al procesamiento de la imagen.
     * \return  void  */
    void ProcesamientoImagen();

public:
    /** \fn Se suscribe a la entrada de video, al mensaje "/camera/image", y publica 
     * el video prosesado "/image_converter/output_video"
    *    */  
    ImageConverter();
    /** \fn Funcion suscripta al mensaje "/camera/image", cada ves que se encuentra un nuevo mensaje con este topic
     *      llama a esta funcion.
    * \param const sensor_msgs::ImageConstPtr& msg  --> se le pasa un puntero al mensaje
    * \return  void  */
    void imageCb(const sensor_msgs::ImageConstPtr& msg);
    void imageDepth(const sensor_msgs::ImageConstPtr& msg);
  
    ~ImageConverter();
};


#endif /* IMAGECONVERTER_H */

