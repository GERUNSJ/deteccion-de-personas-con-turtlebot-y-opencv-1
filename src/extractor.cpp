#include "extractor.hpp"
using namespace std;
using namespace cv;

Extractor::Extractor()
{
	this->nombre = "Extractor";
}




Extractor::~Extractor()
{
}



void Extractor::detectar(const Mat& img,  vector<struct_resultados>& res)
{
	for( int i = 0 ; i < 3 ; i++) // Simulamos 3 detecciones.
	{
		struct_resultados aux;

		aux.aba_der_x = 1;
		aux.aba_der_y = 2;
		aux.aba_izq_x = 3;
		aux.aba_izq_y = 4;
		aux.arr_der_x = 5;
		aux.arr_der_y = 6;
		aux.arr_izq_x = 7;
		aux.arr_izq_y = 8;
		aux.comp = 1;
		//aux.img = 4;
		aux.prof = 8;
		//aux.set = 1;
		aux.tiempo = 222;
		res.push_back(aux);
	}

	return;
}


 
