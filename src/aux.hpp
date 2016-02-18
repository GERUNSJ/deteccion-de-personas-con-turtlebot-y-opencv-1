#ifndef DP_AUX
#define DP_AUX
/* Funciones del programa viejo
 * */

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cstdio> //???

#define V_HIST_ANCHO	512		//El ancho de la ventana del histograma. Múltiṕlo entero de 256 para facilitar el pintado
#define V_HIST_ALTO		480


void f_histograma(const cv::Mat& img, cv::Mat& hist);
/*	Calcula el histograma de img y lo devuelve en hist. Funciona para imagenes
 * 	de un solo canal, tanto 16UC1 como 8UC1. *
 */
void f_histograma_log(const cv::Mat& img, cv::Mat& hist);
/*	Lo mismo que la anterior, pero en forma logarítmica. Los máximos y mínimos
 *	se preservan (con lo cual sigue sirviendo para la segmentación),
 *	y es más fácil de visualizar.
 *
 */
void mostrar_histograma(const cv::Mat& hist_original, cv::Mat& img_hist, char* nombreventana);
/*	Dibuja el histograma con líneas en una imagen de tamaño definido por las constantes
 * 	V_HIST_ANCHO y V_HIST_ALTO. Antes de dibujar, los histogramas se resizean al tamaño
 * 	de la ventana.
 *
 */


void suavizar_histograma(cv::Mat& histograma, int ancho_filtro);

void encontrar_valles(cv::Mat& histograma, std::vector< std::vector<int> > &pares);


class Color
{
private:

	cv::Point3_<uchar> color;
	
public:
	Color();
	~Color();
	void generocolor();
	Color& operator= (const Color&);
	//int operator!= (const Color&, const Color&);
	cv::Point3_<uchar> devuelvocolor(void);
	void setcolor(cv::Point3_<uchar>);

	Color(cv::Point3_<uchar>);

	//operator cv::Point3_() {return color;} //No anda
};

void Pintar(const cv::Mat &src, cv::Mat &dst, std::vector<std::vector<int> > LimiteEObjeto, Color *vectorColor);



void pintar_histograma(const cv::Mat& img_hist_original, cv::Mat& img_hist_pintada, std::vector< std::vector<int> > pares, Color *vectorColor);

std::string type2str(int type);



#endif //DP_AUX
