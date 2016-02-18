#include "detector_1.hpp"
using namespace std;
using namespace cv;

Detector1::Detector1(vector<string>argumentos_nombre, vector<string>argumentos_valor)
{
	this->nombre = "Detector1";
	//unsigned int n = argumentos_nombre.size();



}





Detector1::~Detector1()
{
}




class Predeteccion
{
public:
	Mat img;

private:
};




void Detector1::detectar(const Mat& i_img,  vector<struct_resultados>& i_res)
{
	/* Pasos:
	 * 		0. A gris
	 * 		1. Segmentar
	 * 			1. Segmentar por histograma. En 16 bits.
	 * 			2. Normalizar imagen.
	 * 				. A mano para conocer el procedimiento?
	 * 			3. Pasar a 8 bits.
	 * 				. Y pasar los valles a 8 bits
	 * 			4. Guardar cada predetección
	 * 				. Separar objetos diferentes que están en el mismo segmento. Blobs????
	 * 		2. Filtrado por relación de aspecto
	 *		2. Filtrado por dispersión del gradiente, en cada predetección
	 * 			1. Crear imagen de gradiente horizontal
	 * 			2. Calcular histograma positivo y negativo
	 * 			3. Calcular dispersión / varianza / desviación de los histogramas
	 *			4. Eliminar según umbral.
	 * 		3. Filtrado por contornos
	 * 			1. Encontrar contornos de cada predetección
	 * 			2. Eliminar si tiene agujeros
	 * 		4. Devolver resultados
	 */

	vector<Predeteccion> predetecciones;

	namedWindow("ventana",1);


	// Convertir a gris
	Mat gris = i_img.clone();

	// Normalización
	Mat normalizada;

    if(gris.depth() == CV_8U)
    {
        normalize(gris, normalizada, 0, 255, NORM_MINMAX, -1);
    }
    else if (gris.depth() == CV_16U)
    {
        normalize(gris, normalizada, 0, 65535, NORM_MINMAX, -1);
        //Conversión a 8 bits:
        normalizada.convertTo(normalizada,CV_8UC1,255.0/65535, -0);
    }


	// SEGMENTACIÓN POR HISTOGRAMA - lamentablemente en 8 bits.
	//  Creamos histograma
    Mat histograma;
    Mat histograma_suavizado;

	f_histograma(normalizada,histograma);

    histograma_suavizado = histograma.clone();
    suavizar_histograma(histograma_suavizado, 9);
    suavizar_histograma(histograma_suavizado, 5); //5
    suavizar_histograma(histograma_suavizado, 3); //5
    //suavizar_histograma(histograma_suavizado, 3); //3
    // TODO mostrar_histograma(histograma_suavizado, img_histograma_s,(char*)"HISTOGRAMA_SUAVIZADO");

    //  Segmentación
    vector<vector<int>> pares;
    encontrar_valles(histograma_suavizado , pares);

    //
    Predeteccion auxp;
    Mat lut = Mat::zeros(1,256,CV_8U);
//	cout << "\nLUT: ";
//	cout << lut;
	cout << endl;

    Mat auxmat;


    for(unsigned int i = 0; i < pares.size() ; i++)
    {
    	lut = Mat::zeros(1,256,CV_8U); // lut en cero
    	// LUT según pares
    	//cout << "\nPar: " << pares.at(i)[0] << " , " << pares.at(i)[1] << endl;
    	for( int j = pares.at(i)[0] ; j <= pares.at(i)[1] ; j++ )
    		lut.at<uchar>(j) = 255;

//    	cout << "\nLUT llena: ";
//    	cout << lut;

    	LUT(normalizada, lut, auxmat);
    	imshow("ventana",auxmat);
    	waitKey(0);
    	// TODO roi
    	auxp.img = auxmat;

    	predetecciones.push_back(auxp);
    }


	return;
}


 
