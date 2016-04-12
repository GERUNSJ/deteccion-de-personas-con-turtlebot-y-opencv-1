/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DetectorHog.h
 * Author: fabricio
 *
 * Created on 29 de marzo de 2016, 08:49
 */

#ifndef DETECTORHOG_H
#define DETECTORHOG_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <vector>
#include <iostream>


#define DISTANCIA_FOCAL		570
#define ALTURA_MAXIMA_M		2.6 // Está entrenado con un poco de background, entonces las personas detectadas son más altas..
#define ALTURA_MINIMA_M		1.3


class DetectorHog {
public:
    DetectorHog();
    DetectorHog(const DetectorHog& orig);
    DetectorHog(cv::Mat imagen,cv::Mat profundidad){this->imagen = imagen; this->profundidad = profundidad;}
    std::vector<cv::Rect> DetectarAndDibujar(const float& escala_inicial);
    void SetImagen(const cv::Mat imagen){this->imagen = imagen;}
    void SetProfundidad(const cv::Mat profundidad){this->profundidad =imagen;}
    cv::Mat GetImagen(){return this->imagen;}
    cv::Mat GetProfundidad(){return this->profundidad;}
    virtual ~DetectorHog();
private:
    	// Detector de opencv
	cv::HOGDescriptor *hog;

	// PARÁMETROS y SUS VALORES POR DEFECTO
        
	// Coefficient of the detection window increase.
	const double pasoEscala = 1.05;
	// Minimum possible number of rectangles minus 1. The threshold is used in a group of rectangles to retain it.
	// Coefficient to regulate the similarity threshold. When detected, some objects can be covered by many rectangles.
	// 0 means not to perform grouping.
	const unsigned int umbralAgrupamiento = 4;
	// Threshold for the distance between features and SVM classifying plane. Usually it is 0 and
	// should be specfied in the detector coefficients (as the last free coefficient).
	// But if the free coefficient is omitted (which is allowed), you can specify it manually here.
	const float hit_threshold = 0;
	// Modelo a usar. Puede ser getDefaultPeopleDetector o getDaimlerPeopleDetector. No sabemos cómo usar uno externo
	std::string setSVMDetector;
        
       // Depende del modelo entrenado
	const cv::Size winSize=cv::Size(64, 128);
       // Solo 16*16 soportado
	const cv::Size blockSize = cv::Size(16,16);
        // Múltiplo de cellSize
	const cv::Size blockStride = cv::Size(8,8);	
        // Solo 8*8 soportado
	const cv::Size cellSize = cv::Size(8,8);	
        // Solo 9 soportado
	const int nbins = 9;	
        // ?
	const int derivAperture = 1;	
        // Gaussian smoothing window parameter. (-1 por defecto)
	const double winSigma =-1;
	
	const int histogramNormType = cv::HOGDescriptor::L2Hys;
	const double L2HysThreshold = 0.2;
	const bool gammaCorrection = true;
	const int nlevels = cv::HOGDescriptor::DEFAULT_NLEVELS;
        
        cv::Mat imagen;
        cv::Mat profundidad;
        
        //Vector de rectangulos donde se encuentran las personas
        std::vector<cv::Rect> personas, personas_filtered;

};

#endif /* DETECTORHOG_H */

