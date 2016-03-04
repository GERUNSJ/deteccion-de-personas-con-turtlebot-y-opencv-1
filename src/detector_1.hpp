 
#ifndef DP_DETECTOR_1_H
#define DP_DETECTOR_1_H

#include "detector.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

//#include "opencv2/imgproc/imgproc.hpp"
#include <string>

#include <vector>
#include <iostream>

//
# include "aux.hpp"
//

// Si es true, mostrar todas las detecciones en cada imagen y esperar tecla
extern bool mostrar_detecciones;



class Predeteccion
{
public:
	// auxiliar
	cv::Mat img;

	// Rect que contiene las coordenadas de interes, referidas a la imagen completa.
	cv::Rect rect;

	// Máscara para aplicar a la imagen completa.
	cv::Mat mascara;

	// Mat que contiene la predetección, como porción de la imagen original.
	cv::Mat img_original;

	// Mat que contiene la predetección, como porción de la imagen normalizada.
	cv::Mat img_normalizada;

	// Mat que contiene la predetección, como porción de la imagen procesada.
	cv::Mat img_procesada;

	// Mat que contiene la predetección, como rectángulo dentro de la imagen original.
	cv::Mat rect_original;

	// Mat que contiene la predetección, como rectángulo dentro de la imagen normalizada.
	cv::Mat rect_normalizada;

	// Mat que contiene la predetección, como rectángulo dentro de la imagen procesada.
	cv::Mat rect_procesada;

	void limpiar(void)
	{
//		img.release();
//		mascara.release();
//		img_original.release();
//		img_normalizada.release();
//		img_procesada.release();

//		img = cv::Mat();
//		mascara = cv::Mat();
//		img_normalizada = cv::Mat();
//		img_original = cv::Mat();
//		img_procesada = cv::Mat();

		//img = cv::Mat::zeros( 1, 1, CV_8UC1);
		mascara = cv::Mat::zeros( 1, 1, CV_8UC1);
		img_original = cv::Mat::zeros( 1, 1, CV_8UC1);
		img_procesada = cv::Mat::zeros( 1, 1, CV_8UC1);
		img_normalizada = cv::Mat::zeros( 1, 1, CV_8UC1);
	}

private:
};



class Detector1 : public Detector
{
public:

	// PARÁMETROS y SUS VALORES POR DEFECTO
//	// Coefficient of the detection window increase.
//	double pasoEscala = 1.05;
//	// TODO: ver como funciona esto
//	double umbralAgrupamiento = 2;
//	// Modelo a usar. Puede ser getDefaultPeopleDetector o getDaimlerPeopleDetector o uno externo
//	std::string setSVMDetector;


	Detector1(std::vector<std::string>argumentos_nombre, std::vector<std::string>argumentos_valor);

	~Detector1();

	void detectar(const cv::Mat& i_img_color, const cv::Mat& i_img_profundidad, std::vector<struct_resultados>& i_res) override;

private:

};




//float a_tamanio_real(const cv::Mat & i_img_profundidad16, unsigned int i_longitud_px, float i_distancia_al_objeto);

//bool es_altura_creible(const cv::Rect & i_rect, const cv::Mat & i_img_profundidad16);



// TODO las predetecciones podrían tener un puntero a la imagen de 16..y también su contorno.
//bool es_gradiente_disperso(std::vector<cv::Point> & contorno, const cv::Mat & i_img_profundidad);


#endif //DP_DETECTOR_1_H
