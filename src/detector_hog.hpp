 
#ifndef DP_DETECTOR_HOG_H
#define DP_DETECTOR_HOG_H

#include "detector.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
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
	// TODO: ver como funciona esto
	double umbralAgrupamiento = 2;
	// Modelo a usar. Puede ser getDefaultPeopleDetector o getDaimlerPeopleDetector o uno externo
	std::string setSVMDetector;


	DetectorHOG(std::vector<std::string>argumentos_nombre, std::vector<std::string>argumentos_valor);

	~DetectorHOG();

	void detectar(const cv::Mat& i_img, std::vector<struct_resultados>& i_res) override;

private:

};


#endif //DP_DETECTOR_DUMMY_H
