/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DetectorCascada.h
 * Author: fabricio
 *
 * Created on 10 de marzo de 2016, 18:03
 */

#ifndef DETECTORCASCADA_H
#define DETECTORCASCADA_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <string>
#include <vector>
#include <iostream>


#define DISTANCIA_FOCAL		570
#define ALTURA_MAXIMA_M		2.6 // Está entrenado con un poco de background, entonces las personas detectadas son más altas..
#define ALTURA_MINIMA_M		1.3

class DetectorCascada {
public:
    DetectorCascada();
    DetectorCascada(const DetectorCascada& orig);
    DetectorCascada(cv::Mat imagen,cv::Mat profundidad){this->imagen = imagen; this->profundidad = profundidad;}
    std::vector<cv::Rect> DetectarAndDibujar(const float& escala_inicial);
    void SetImagen(const cv::Mat imagen){this->imagen = imagen;}
    void SetProfundidad(const cv::Mat profundidad){this->profundidad =imagen;}
    cv::Mat GetImagen(){return this->imagen;}
    cv::Mat GetProfundidad(){return this->profundidad;}
    virtual ~DetectorCascada();
    
private:
    
    
    //Vector de rectangulos donde se encuentran las personas
    std::vector<cv::Rect> personas;
    // Detector de opencv
    cv::CascadeClassifier *cascada;
    
    // PARÁMETROS y SUS VALORES POR DEFECTO
    
    // Dirección del classificador en cascada, entrenado con features LBP o HAAR, en formato XML apto para OpenCV
    std::string direccion_a_cascada;
    // Tamaño mínimo de las personas a buscar, en pixeles. (Columnas,filas)
    cv::Size tamanio_minimo{40,120};
    // Tamaño máximo de las personas a buscar, en pixeles.
    cv::Size tamanio_maximo{400,1200};
    // scaleFactor – Parameter specifying how much the image size is reduced at each image scale. > 1
    float scaleFactor = 1.1;
    // minNeighbors – Parameter specifying how many neighbors each candidate rectangle should have to retain it.
    int minNeighbors = 4;
    // Usar la información de profundidad para filtrar según altura estimada
    bool usar_profundidad_altura = false;
    
    cv::Mat imagen;
    cv::Mat profundidad;
    

};

#endif /* DETECTORCASCADA_H */

