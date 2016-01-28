#ifndef DP_DETECTOR_DUMMY_H
#define DP_DETECTOR_DUMMY_H

#include "detector.hpp"
#include <string>
#include <vector>
#include <iostream>

class DetectorDummy : public Detector
{
public:
	int parametro1;
	int parametro2;
	char parametro3;
	std::string parametro4;
	DetectorDummy(std::vector<std::string>argumentos_nombre, std::vector<std::string>argumentos_valor);
	~DetectorDummy();
	void detectar(const cv::Mat& img, std::vector<struct_resultados>& res) override;

private:

};


#endif //DP_DETECTOR_DUMMY_H
