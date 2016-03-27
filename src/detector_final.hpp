 
#ifndef DP_DETECTOR_FINAL_H
#define DP_DETECTOR_FINAL_H

#include "detector.hpp"
#include "aux.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <vector>
#include <iostream>

// Si es true, mostrar todas las detecciones en cada imagen y esperar tecla. Está en el programa principal.
extern bool mostrar_detecciones;


class DetectorFinal : public Detector
{
public:
	// Detector de opencv
	cv::CascadeClassifier cascada;

	// PARÁMETROS y SUS VALORES POR DEFECTO
	// Dirección del classificador en cascada, entrenado con features LBP o HAAR, en formato XML apto para OpenCV
	std::string direccion_a_cascada;
	// Número por el que se dividirá la imagen inicialmente. Puede servir si es grande.
	float escala_inicial = 1;
	// Tamaño mínimo de las personas a buscar, en pixeles. (Columnas,filas)
	cv::Size tamanio_minimo{10,30};
	// Tamaño máximo de las personas a buscar, en pixeles.
	cv::Size tamanio_maximo{100,300};
	// Convertir a escala de grises antes de detectar
	bool convertir_a_gris = true;
	// Ecualizar histograma antes de detectar, posterior a convertir_a_gris
	bool ecualizar_histograma = true;
	// scaleFactor – Parameter specifying how much the image size is reduced at each image scale. > 1
	float scaleFactor = 1.1;
	// minNeighbors – Parameter specifying how many neighbors each candidate rectangle should have to retain it.
	int minNeighbors = 5;
	// Usar la información de profundidad para filtrar según altura estimada
	bool usar_profundidad_altura = false;
	// Usar suavizado (box blur)
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


	// Kernels para filtrado
	// Kernels
	cv::Mat kernel_repujado =  (cv::Mat_<float>(3,3) << -2 , -1 , 0 ,
	                                                    -1 ,  1 , 1 ,
	                                                     0 ,  1 , 2 )/1;
	cv::Mat kernel_enfoque = (cv::Mat_<float>(3,3) <<  0 , -1 ,  0 ,
				                                      -1 ,  5 , -1 ,
				                                       0 , -1 ,  0 )/1;




	DetectorFinal(std::vector<std::string>argumentos_nombre, std::vector<std::string>argumentos_valor);

	~DetectorFinal();

	void detectar(const cv::Mat& i_img_color, const cv::Mat& i_img_profundidad, std::vector<struct_resultados>& i_res) override;

private:

};

//bool es_altura_creible(const cv::Rect & i_rect, const cv::Mat & i_img_profundidad16);

//float a_tamanio_real(const cv::Mat & i_img_profundidad16, unsigned int i_longitud_px, float i_distancia_al_objeto);


#endif //DP_DETECTOR_FINAL
