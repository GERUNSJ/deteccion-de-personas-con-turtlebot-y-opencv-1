 
#ifndef DP_DETECTOR_HOG_H
#define DP_DETECTOR_HOG_H

#include "detector.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <vector>
#include <iostream>

// Si es true, mostrar todas las detecciones en cada imagen y esperar tecla
extern bool mostrar_detecciones;


class DetectorHOG : public Detector
{
public:
	// Detector de opencv
	cv::HOGDescriptor hog;

	// PARÁMETROS y SUS VALORES POR DEFECTO
	// Coefficient of the detection window increase.
	double pasoEscala = 1.05;
	// Minimum possible number of rectangles minus 1. The threshold is used in a group of rectangles to retain it.
	// Coefficient to regulate the similarity threshold. When detected, some objects can be covered by many rectangles.
	// 0 means not to perform grouping.
	unsigned int umbralAgrupamiento = 2;
	// Threshold for the distance between features and SVM classifying plane. Usually it is 0 and
	// should be specfied in the detector coefficients (as the last free coefficient).
	// But if the free coefficient is omitted (which is allowed), you can specify it manually here.
	float hit_threshold = 0;
	// Modelo a usar. Puede ser getDefaultPeopleDetector o getDaimlerPeopleDetector. No sabemos cómo usar uno externo
	std::string setSVMDetector;
	// Número por el que se dividirá la imagen inicialmente. Puede servir si es grande.
	float escala_inicial = 1;
	// Convertir a escala de grises antes de detectar
	bool convertir_a_gris = true;
	// Ecualizar histograma antes de detectar, posterior a convertir_a_gris y sólo si convertir_a_gris
	bool ecualizar_histograma = true;
	// Usar suavizado, posterior a convertir_a_gris
	bool blurear = false;
	// Tamaño del filtro de suavizado
	unsigned int tamanio_blur = 3;
	// Pasar filtro de repujado
	bool filtro_repujado = false;
	// Pasar filtro de enfoque  // Sharpen
	bool filtro_enfoque = false;
	// Repujado y enfoque
	bool filtro_repujado_y_enfoque = false;
	// Enfoque y repujado
	bool filtro_enfoque_y_repujado = false;
	// Usar la información de profundidad para filtrar según altura estimada
	bool usar_profundidad_altura = false;

	// Kernels para filtrado
	// Kernels
	cv::Mat kernel_repujado =  (cv::Mat_<float>(3,3) << -2 , -1 , 0 ,
	                                                    -1 ,  1 , 1 ,
	                                                     0 ,  1 , 2 )/1;
	cv::Mat kernel_enfoque = (cv::Mat_<float>(3,3) <<  0 , -1 ,  0 ,
				                                      -1 ,  5 , -1 ,
				                                       0 , -1 ,  0 )/1;



	DetectorHOG(std::vector<std::string>argumentos_nombre, std::vector<std::string>argumentos_valor);

	~DetectorHOG();

	void detectar(const cv::Mat& i_img_color, const cv::Mat& i_img_profundidad, std::vector<struct_resultados>& i_res) override;

private:

};


#endif //DP_DETECTOR_DUMMY_H
