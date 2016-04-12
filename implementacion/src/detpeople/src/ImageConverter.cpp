/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ImageConverter.cpp
 * Author: fabricio
 * 
 * Created on 22 de marzo de 2016, 10:07
 */

#include "ImageConverter.h"


void ImageConverter::ProcesamientoImagen(){
    imagen_prefiltrada->SetImagen(imagen_recibida);
    //imagen_prefiltrada->BackgroundSubtractorMOG2();

    //Implementacion de filtros de acondicionamientos de las imagenes
    
    //imagen_prefiltrada->Filtro2D(desenfoque);
    //imagen_prefiltrada->Filtro2D(repujado);
    imagen_prefiltrada->FiltroEstandard();
    
    // Achicamos la imagen, muy util para disminuir el tiempo de procesamiento en imagenes grandes
    imagen_prefiltrada->Achicar(escala_inicial);
    
    
    imagen_recibida = imagen_prefiltrada->GetImagen();
    
    //Deteccion de Histograma de Gradientes Orientados
    HOG->SetImagen(imagen_recibida);
    if(!imagen_recibida_depth.empty())
        HOG->SetProfundidad(imagen_recibida_depth);
    personas = HOG->DetectarAndDibujar(escala_inicial);
    
    
}



  
ImageConverter::ImageConverter(): it_(nh_) {
    
    // Suscriptor para MICROSOFT KINECT
    //image_sub_ = it_.subscribe("/camera/rgb/image_rect_color", 1, &ImageConverter::imageCb, this);//
    
    // Suscriptor para la Raspberry PI y la webcam
    image_sub_ = it_.subscribe("/camera/image", 1, &ImageConverter::imageCb, this);
    
    // Suscriptor a la imagen de profundidad
    image_sub_depth_ = it_.subscribe("/camera/depth_registered/hw_registered/image_rect_raw", 1, &ImageConverter::imageDepth, this);//
    
    // Publicador
    image_pub_ = it_.advertise("/image_converter/output_video", 1);
        
    //crea los objetos utilizados para procesar la imagen
    imagen_prefiltrada = new PreFiltro();
    //deteccion = new DetectorCascada();
    HOG = new DetectorHog();

    // Declaracion de las ventanas
    cv::namedWindow(OPENCV_WINDOW);
    //cv::namedWindow(OPENCV_WINDOW2);
}


void ImageConverter::imageCb(const sensor_msgs::ImageConstPtr& msg)
{
    
    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }    
    catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    
    imagen_recibida = cv_ptr->image;
    imagen_mostrada = imagen_recibida.clone();

 
    ProcesamientoImagen();
    //cv::imshow(OPENCV_WINDOW2, imagen_recibida); 
    
     // Creamos un rectángulo en una copia de la imagen original. tl es top-left, br es bottom-right
    for( unsigned int i = 0; i < personas.size(); i++ ) 
        rectangle(imagen_mostrada, personas[i].tl(), personas[i].br(), cv::Scalar(0,255,0), 3);
 
    // Update GUI Window
    cv::imshow(OPENCV_WINDOW, imagen_mostrada);
    cv::waitKey(3);
    
    //Actualizamos la informacion del mensaje de ROS con la nueva imagen procesada
    cv_ptr->header   = cv_ptr->header;                      
    cv_ptr->encoding = sensor_msgs::image_encodings::BGR8; 
    cv_ptr->image    = imagen_mostrada;                     

    // Salida del video modificada
    image_pub_.publish(cv_ptr->toImageMsg());
}


void ImageConverter::imageDepth(const sensor_msgs::ImageConstPtr& msg1){
    
    try {
        cv_ptr_depth = cv_bridge::toCvCopy(msg1, sensor_msgs::image_encodings::TYPE_16UC1);
    }    
    catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    
    imagen_recibida_depth = cv_ptr_depth->image;
    imagen_mostrada_depth = imagen_recibida_depth.clone();

 
    
}


ImageConverter::~ImageConverter() {
    cv::destroyWindow(OPENCV_WINDOW);
    //cv::destroyWindow(OPENCV_WINDOW2);
}

