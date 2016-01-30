#ifndef DP_DETECTOR_EXTRACTOR_H
#define DP_DETECTOR_EXTRACTOR_H

#include "detector.hpp"
#include <string>
#include <vector>
#include <iostream>

class Extractor : public Detector
{
public:
	//int parametro1;
	std::string parametro4;
	Extractor();
	~Extractor();
	void detectar(const cv::Mat& img, std::vector<struct_resultados>& res) override;

private:

};


#endif //DP_DETECTOR_EXTRACTOR_H
 
