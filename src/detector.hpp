#ifndef DP_DETECTOR_H
#define DP_DETECTOR_H

#include "resultados.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
#include <string>

class Detector
{
public:
	unsigned int cantidad_de_argumentos;
	std::string nombre;
	std::vector<std::string> parametros_nombre;
	std::vector<std::string> parametros_valor;

	virtual void detectar(const cv::Mat& img, std::vector<struct_resultados>& res) = 0;
	friend std::ostream& operator<<(std::ostream& os, Detector& detector );
	virtual ~Detector() = 0;
private:
};


std::ostream& operator<<( std::ostream& os, Detector& detector );


#endif // DP_DETECTOR_H
