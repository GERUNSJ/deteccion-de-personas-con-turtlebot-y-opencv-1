/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DetectorHog.cpp
 * Author: fabricio
 * 
 * Created on 29 de marzo de 2016, 08:49
 */

#include "DetectorHog.h"


static float a_tamanio_real(unsigned int i_longitud_px, float i_distancia_al_objeto){
	return (float) i_longitud_px * i_distancia_al_objeto / DISTANCIA_FOCAL;
}

static bool es_altura_creible(const cv::Rect & i_rect, const cv::Mat & i_img_profundidad16){

    cv::Mat auxmat = i_img_profundidad16.clone();


    int altura_px = i_rect.height;
    int centro_x = i_rect.x + ((i_rect.width-1)/2);
    int centro_y = i_rect.y + ((i_rect.height-1)*1/3); // 1/3 para centro de torso
    ushort valor;

    auxmat.at<ushort>(centro_y,centro_x) = 65535;

    rectangle(auxmat, i_rect, cv::Scalar(65535));

    valor = i_img_profundidad16.at<ushort>(centro_y,centro_x);

    float distancia_al_objeto = (float) valor / 1000; // Viene en mm, la pasamos a metros.

    float altura_m = a_tamanio_real(altura_px, distancia_al_objeto);

    std::cout << "\naltura_m " << altura_m;

    if( altura_m < ALTURA_MINIMA_M || altura_m > ALTURA_MAXIMA_M )
        return false;
    else
        return true;
}


DetectorHog::DetectorHog() {
    // Se crea el detector de opencv
    hog = new cv::HOGDescriptor(winSize, blockSize, blockStride, cellSize, nbins, derivAperture, winSigma,
                    histogramNormType, L2HysThreshold, gammaCorrection, nlevels);
    hog->setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}

DetectorHog::DetectorHog(const DetectorHog& orig) {
}

std::vector<cv::Rect> DetectorHog::DetectarAndDibujar(const float& escala_inicial)
{
    // Más o menos lo mismo del ejemplo samples/cpp/peopledetect.cpp

    //	 C++: void gpu::HOGDescriptor::detectMultiScale(const GpuMat& img, vector<Rect>& found_locations, double hit_threshold=0, Size win_stride=Size(), Size padding=Size(), double scale0=1.05, int group_threshold=2)
    //	    Parameters:
    //
    //	        img – Source image. See gpu::HOGDescriptor::detect() for type limitations.
    //	        found_locations – Detected objects boundaries.
    //	        hit_threshold – Threshold for the distance between features and SVM classifying plane. See gpu::HOGDescriptor::detect() for details.
    //	        win_stride – Window stride. It must be a multiple of block stride.
    //	        padding – Mock parameter to keep the CPU interface compatibility. It must be (0,0).
    //	        scale0 – Coefficient of the detection window increase.
    //	        group_threshold – Coefficient to regulate the similarity threshold. When detected, some objects can be covered by many rectangles. 0 means not to perform grouping. See groupRectangles() .

    //    virtual void detectMultiScale(const Mat& img, CV_OUT vector<Rect>& foundLocations,
    //                                  double hitThreshold=0, Size winStride=Size(),
    //                                  Size padding=Size(), double scale=1.05,
    //                                  double finalThreshold=2.0, bool useMeanshiftGrouping = false) const;

    
    // Verificamos entrada de 8 bits
    if(imagen.depth() != CV_8U){
        std::cout << "\nERROR IMAGEN COLOR: Solo soporta 8 bits\n"; //
        /// TODO: Error
        std::vector<cv::Rect> vacio;
        return vacio;
        std::exit(EXIT_FAILURE);
    }

    // Limpiamos los vectores
    personas.clear();
    personas_filtered.clear();

    // Ejecutar el detector con los parámetros por defecto. para obtener un índice de respuesta más 
    // alta (y más falsas positivos, respectivamente), y disminuir la hitThreshold 
    // groupThreshold ( setear el groupThreshold en 0 para desactivar la agrupación).
    
    //hog->detectMultiScale(imagen, personas, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 3);
    hog->detectMultiScale(imagen, personas, hit_threshold, cv::Size(8,8), cv::Size(32,32), pasoEscala , umbralAgrupamiento);


    //filtramos los rectangulos iguales
    size_t i, j;
    for( i = 0; i < personas.size(); i++ ){
        cv::Rect r = personas[i];
        for( j = 0; j < personas.size(); j++ ) // Para todos los rects encontrados
            if( j != i && (r & personas[j]) == r) // si hay dos iguales
                break;
        if( j == personas.size() ) // Si no hubieron dos iguales, lo guarda
            personas_filtered.push_back(r);
    }

    
    // Para cada detección
    for( i = 0; i < personas_filtered.size(); i++ ){
    	// Achicamos los rectangulos detectados
        cv::Rect r = personas_filtered[i];

        // the HOG detector returns slightly larger rectangles than the real objects.
        // so we slightly shrink the rectangles to get a nicer output.
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);

        // Des-escalamos
        r.x = floor(r.x * escala_inicial);
        r.y = floor(r.y * escala_inicial);
        r.height = floor(r.height * escala_inicial);
        r.width = floor(r.width * escala_inicial);
        
        
        // Filtramos según la altura real estimada
        if( !(profundidad.empty())){
            if( !es_altura_creible(r, profundidad) )
                continue; // Termina con esta predetección y continúa el for
        }
        //Actualizamos  el vector personas con el valor de la imagen real
        personas[i] = r;
    }
    return personas;
}

DetectorHog::~DetectorHog() {
}

