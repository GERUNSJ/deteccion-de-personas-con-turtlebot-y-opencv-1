 
#ifndef DP_DETECTOR_HOG_H
#define DP_DETECTOR_HOG_H

#include "detector.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <vector>
#include <iostream>


extern bool mostrar_detecciones;

class DetectorHOG : public Detector
{
public:
	cv::HOGDescriptor hog;
	double pasoEscala = 1.05;
	double umbralAgrupamiento = 2;
	std::string setSVMDetector;
	DetectorHOG(std::vector<std::string>argumentos_nombre, std::vector<std::string>argumentos_valor);
	~DetectorHOG();
	void detectar(const cv::Mat& i_img, std::vector<struct_resultados>& i_res) override;

private:

};


#endif //DP_DETECTOR_DUMMY_H
