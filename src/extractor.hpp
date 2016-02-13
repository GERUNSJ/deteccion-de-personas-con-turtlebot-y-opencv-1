#ifndef DP_DETECTOR_EXTRACTOR_H
#define DP_DETECTOR_EXTRACTOR_H

#include "detector.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <vector>
#include <iostream>

class Extractor : public Detector
{
public:
	//int parametro1;
	//std::string parametro4;
	Extractor();
	~Extractor();
	void detectar(const cv::Mat& i_img, std::vector<struct_resultados>& i_res) override;

private:

};


//static void onMouse( int event, int x, int y, int flags, void* i_aux_res);

#endif //DP_DETECTOR_EXTRACTOR_H
 
