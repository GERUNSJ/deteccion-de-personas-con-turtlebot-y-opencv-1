/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DetectorCascada.cpp
 * Author: fabricio
 * 
 * Created on 10 de marzo de 2016, 18:03
 */


#include "DetectorCascada.h"



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


DetectorCascada::DetectorCascada() {
    cascada = new cv::CascadeClassifier;
    
   // Cargamos el modelo o cascada
    if( !cascada->load("/home/fabricio/visionary.net_pedestrian_cascade_web_LBP.xml" ) )    {
        std::cerr << "ERROR: Could not load classifier cascade" << std::endl;
        return;
    }
}

DetectorCascada::DetectorCascada(const DetectorCascada& orig) {
    
    cascada = new cv::CascadeClassifier;
    
   // Cargamos el modelo o cascada
    if( !cascada->load( direccion_a_cascada )){
        std::cerr << "ERROR: Could not load classifier cascade" << std::endl;
        return;
    }
}

std::vector<cv::Rect> DetectorCascada::DetectarAndDibujar(const float& escala_inicial){
    
    // Verificamos entrada de 8 bits
    if(imagen.depth() != CV_8U)    {
        std::cout << "\nERROR IMAGEN COLOR: Solo soporta 8 bits\n"; //
        /// TODO: Error
        std::vector<cv::Rect> vacio;
        return vacio;
        std::exit(EXIT_FAILURE);
    }
    
    // Limpiamos el vector de personas
    personas.clear();
    
    cascada->detectMultiScale( imagen,
        personas,
        scaleFactor,
        minNeighbors,
        0 /*| cv::CASCADE_SCALE_IMAGE*/, /*flags*/
        tamanio_minimo,
        tamanio_maximo );
           
    // Para cada detección
    for( unsigned int i = 0; i < personas.size(); i++){
        cv::Rect r = personas[i];
        
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

DetectorCascada::~DetectorCascada() {
}

