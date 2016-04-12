/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PreFiltro.cpp
 * Author: fabricio
 * 
 * Created on 12 de marzo de 2016, 19:25
 */
#include "PreFiltro.h"


PreFiltro::PreFiltro() {    
    //pMOG2 = new cv::BackgroundSubtractorMOG2(history, varThreshold, bShadowDetection); //MOG2 approach
    //pMOG2 = new cv::BackgroundSubtractorMOG2(); //MOG2 approach
    //pMOG2->setInt("nmixtures", 3);
    //pMOG2->setDouble("fTau", 0.5);
}

PreFiltro::PreFiltro(const PreFiltro& orig) {
}


void PreFiltro::Filtro2D(int KernelType){  
    
    //definicion de los parametros del filtro
    cv::Point anchor;
    double delta;
    int ddepth;
    
    //contruccion del kernel
    const int kernel_size=3;
    float a=0 ,b=0 ,c=0 ,d=0 ,e=0 ,f=0 ,g=0 ,h=0 ,i=0;
    
    //Seleccionamos del Kernel pedido
    switch(KernelType){
        case repujado:
            a=-0.5 ,b=-0.5 ,c=0 ,d=-0.5 ,e=2 ,f=0.5 ,g=0 ,h=0.5 ,i=0.5; //Filreo Repujado
            break;
        case enfoque:
            a=0 ,b=-1 ,c=0 ,d=-1 ,e=5 ,f=-1 ,g=0 ,h=-1 ,i=0; // Enfocar
            break;
        case desenfoque:
            a=1 ,b=1 ,c=1 ,d=1 ,e=1 ,f=1 ,g=1 ,h=1 ,i=1;//desenfoque
        default:
            a=0 ,b=0 ,c=0 ,d=0 ,e=1 ,f=0 ,g=0 ,h=0 ,i=0;// por defecto
            break;        
    }
    
    cv::Mat kernel;
    float m[kernel_size][kernel_size]={
        {a, b, c}, 
        {d, e, f}, 
        {g, h, i}};

    
    /// Inicializamos los argumentos para el Filltro2D
    anchor = cv::Point( -1, -1 );
    delta = 0;
    ddepth = -1;
    
    //defino el kernel 
    kernel = cv::Mat(kernel_size, kernel_size, CV_32F, m);

    /// Aplicacion del filtro
    cv::filter2D(this->imgFiltrada, this->imgFiltrada, ddepth , kernel, anchor, delta, cv::BORDER_DEFAULT );
    
    
}


void PreFiltro::Achicar(const float& escala_inicial){
    cv::Mat filtrada( cvRound (imgFiltrada.rows/escala_inicial), cvRound(imgFiltrada.cols/escala_inicial), imgFiltrada.type() );
    cv::resize( imgFiltrada, filtrada, filtrada.size(), 0, 0, cv::INTER_LINEAR );
    PreFiltro::imgFiltrada = filtrada.clone();
}




void PreFiltro::FiltroEstandard(){
    
    //cv::medianBlur(this->imgFiltrada, this->imgFiltrada, 5);
    //cv::GaussianBlur(this->imgFiltrada, this->imgFiltrada, cv::Size(5,5), 2, 2);
    
    /// Normalizing
    //cv::normalize( this->imgFiltrada, this->imgFiltrada, 0, 255, cv::NORM_MINMAX, CV_8UC3, cv::Mat() );
    
    
    if(imgFiltrada.type()!= CV_8UC1)
        cv::cvtColor( this->imgFiltrada, this->imgFiltrada, CV_BGR2GRAY );
    
    cv::equalizeHist( imgFiltrada, imgFiltrada );
}




void PreFiltro::BackgroundSubtractorMOG2(){
    //actualizacion del modelo de fondo
    pMOG2->operator()(imgFiltrada, fgMaskMOG2,0.01);
    imgFiltrada = fgMaskMOG2.clone();
}

PreFiltro::~PreFiltro() {
}

