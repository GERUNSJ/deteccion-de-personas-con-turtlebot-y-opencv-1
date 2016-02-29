#include "detector_1.hpp"
using namespace std;
using namespace cv;

// ---
#define A_BORRAR_PRINCIPIO	1	// Cuantos segmentos se borran, desde el principio del vector
#define A_BORRAR_FINAL		2	// Cuantos segmentos se borran, desde el final
#define DISTANCIA_FOCAL		570
#define ALTURA_MAXIMA_M		2.2
#define ALTURA_MINIMA_M		0.8
#define UMBRAL_STD 			20


Detector1::Detector1(vector<string>argumentos_nombre, vector<string>argumentos_valor)
{
	this->nombre = "Detector1";
	//unsigned int n = argumentos_nombre.size();



}





Detector1::~Detector1()
{
}







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


	cout << "---- La imagen en detector1 es del tipo " << type2str(i_img.type()) << endl;


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

    // Borramos algunos que no aportan
    for( unsigned int i = 0 ; i < A_BORRAR_PRINCIPIO ; i++ )
    	pares.erase(pares.begin());

    for( unsigned int i = 0; i < A_BORRAR_FINAL ; i++ )
    	pares.erase(pares.end());

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
    	//imshow("ventana",auxmat);
    	//waitKey(0);
    	// TODO roi
    	auxp.img = auxmat.clone();

    	predetecciones.push_back(auxp);
    }

    for( unsigned int i = 0; i < predetecciones.size() ; i++)
    {
    	//imshow("ventana",predetecciones.at(i).img);
    	//waitKey(0);
    	// Preprocesamos predetecciones: Apertura y cierre
    	// Apertura: Erosión y dilatación
    	erode(predetecciones.at(i).img , predetecciones.at(i).img, Mat::ones(5,5,CV_8UC1), Point(-1,-1), 1);
    	dilate(predetecciones.at(i).img, predetecciones.at(i).img, Mat::ones(5,5,CV_8UC1), Point(-1,-1), 1);
    	erode(predetecciones.at(i).img , predetecciones.at(i).img, Mat::ones(10,8,CV_8UC1), Point(-1,-1), 1);
    	dilate(predetecciones.at(i).img, predetecciones.at(i).img, Mat::ones(10,8,CV_8UC1), Point(-1,-1), 1);

    	// Cierre: Dilatación y erosión
//    	dilate(predetecciones.at(i).img, predetecciones.at(i).img, Mat::ones(5,5,CV_8UC1), Point(-1,-1), 1);
//    	erode(predetecciones.at(i).img , predetecciones.at(i).img, Mat::ones(5,5,CV_8UC1), Point(-1,-1), 1);
//    	dilate(predetecciones.at(i).img, predetecciones.at(i).img, Mat::ones(5,5,CV_8UC1), Point(-1,-1), 1);


    	//    	erode(predetecciones.at(i).img , predetecciones.at(i).img, Mat::ones(20,10,CV_8UC1), Point(-1,-1), 1);
    	//    	dilate(predetecciones.at(i).img, predetecciones.at(i).img, Mat::ones(20,10,CV_8UC1), Point(-1,-1), 1);
    	//imshow("ventana",predetecciones.at(i).img);
    	//waitKey(0);

    	// Encontramos contornos

    }

    // Encontramos contornos - esto se podría fusionar con el for anterior
    vector<vector<Point> > contours, contours_filtrados;
    vector<Vec4i> hierarchy, hierarchy_filtrados;
    Rect auxrect;
    Mat copia;
    float r_aspecto = 0;
    unsigned int cant_predetecciones1 = predetecciones.size();
    unsigned int ii = 0;
    namedWindow("contornos" , 0);

    // Para todas las predetecciones
    for( unsigned int i = 0; i < cant_predetecciones1; i++ )
    {
    	// Encontramos contornos. Siempre en la primera predetección, ya que las vamos eliminando.
    	// ...The function modifies the image while extracting the contours...así que procesamos en una copia
    	auxmat = predetecciones.at(0).img.clone();
    	findContours( auxmat, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE );

    	// Si no hay contornos, borramos y seguimos con la siguiente predetección.
    	if( contours.size() == 0 )
    	{
    		predetecciones.erase(predetecciones.begin());
    		continue;
    	}

    	// Si hay contornos, los procesamos.
    	// Para cada contorno:
		for(unsigned int j = 0 ; j < hierarchy.size() ; j++)
		{
			// // Eliminamos los que tienen agujeros. Si tiene padres, es un agujero
			if( hierarchy[j][3] >= 0 ) // [3] son los padres
			{
//				hierarchy.pop_back();
//				contours.erase(contours.begin()+j);
				// No es necesario borrar, simplemente seguimos.
				//cout << "\nTiene padres";
				//cvtColor(normalizada, copia, CV_GRAY2BGR);
				//normalizada.convertTo(copia, CV_8UC3);
				//drawContours(copia, contours, j, Scalar(0,0,255), 2,8);
				//imshow("contornos", copia);
				//waitKey(0);
				continue;
			}
			// Encontramos el rectangulo que envuelve
			else
			// TODO: approxPolyDP , tal vez agiliza boundingRect
			{
				auxrect = boundingRect(contours.at(j));
				r_aspecto = (float)auxrect.width / auxrect.height;
				//cout << "\nr_aspecto = " << r_aspecto;
				if( r_aspecto > 0.6)
				{
//					hierarchy.pop_back();
//					contours.erase(contours.begin()+j);
					// No es necesario borrar, simplemente seguimos.
					continue;
				}
				else if( !es_altura_creible(auxrect, i_img) )
				{
					continue;
				}
				else if( !es_gradiente_disperso(contours.at(j) , normalizada) )
				{
					continue;
				}
				else
				{
					// Lo guardamos como predetección nueva, al final del vector de predetecciones.
					// No se analizará en este for debido al límite fijo usado.

					auxp.rect = auxrect;

					// Creamos la máscara
					auxmat = Mat::zeros(i_img.size(),CV_8UC1); // Por las dudas.
					drawContours(auxmat, contours, j, Scalar(255), CV_FILLED);
					imshow("contornos", auxmat); waitKey(0);
					auxp.mascara = auxmat.clone();

					// Aplicamos la máscara y guardamos las imágenes.
					i_img.copyTo(auxp.img_original,auxmat); // auxmat es la máscara
					predetecciones.at(0).img.copyTo(auxp.img_procesada, auxmat);
					normalizada.copyTo(auxp.img_normalizada,auxmat);

					// Extraemos los rectángulos sin máscara
					auxp.rect_original = i_img(auxp.rect);
					auxp.rect_procesada = predetecciones.at(0).img(auxp.rect);
					auxp.rect_normalizada = normalizada(auxp.rect);

//					// Extraemos el rectángulo de interés
//					auxp.img_normalizada = predetecciones.at(0).img(auxrect);

//
//					//auxp.img = normalizada(auxrect);
//
//					copia = predetecciones.at(0).img.clone();
//					drawContours(copia,contours,j,Scalar(255),CV_FILLED);
//					predetecciones.at(0).img.copyTo(copia,copia);
//					auxp.img = copia;


					predetecciones.push_back(auxp);
					auxp.limpiar();
					//auxp = Predeteccion(); // Constructores vacíos?  // TODO

					j++;
				}
			}
		}
		// Borramos la predetección procesada
		predetecciones.erase(predetecciones.begin()); //
    }

    cout << "\nQuedaron " << predetecciones.size() << " predetecciones" << endl;

    namedWindow("original",CV_WINDOW_KEEPRATIO);
    namedWindow("normalizada",CV_WINDOW_KEEPRATIO);
    namedWindow("procesada",CV_WINDOW_KEEPRATIO);
    for( unsigned int i = 0; i < predetecciones.size() ; i++)
    {
    	imshow("ventana",predetecciones.at(i).img);
    	imshow("normalizada",predetecciones.at(i).img_normalizada);
    	imshow("procesada",predetecciones.at(i).img_procesada);
    	imshow("original",predetecciones.at(i).img_original);
    	waitKey(0);

    	imshow("normalizada", predetecciones.at(i).rect_normalizada);
    	imshow("procesada",predetecciones.at(i).rect_procesada);
    	imshow("original",predetecciones.at(i).rect_original);
    	waitKey(0);
    }
    //waitKey(0);

	return;
}


 



float a_tamanio_real(const cv::Mat & i_img_profundidad16, unsigned int i_longitud_px, float i_distancia_al_objeto)
{
	return (float) i_longitud_px * i_distancia_al_objeto / DISTANCIA_FOCAL;
}







bool es_altura_creible(const cv::Rect & i_rect, const cv::Mat & i_img_profundidad16)
{
//	namedWindow("asdasd",0);
//	imshow("asdasd", i_img_profundidad16);
//	waitKey(0);
	Mat auxmat = i_img_profundidad16.clone();
	//auxmat.convertTo(auxmat,CV_16UC3);


	int altura_px = i_rect.height;
	int centro_x = i_rect.x + ((i_rect.width-1)/2);
	int centro_y = i_rect.y + ((i_rect.height-1)*1/3); // 1/3 para centro de torso
	ushort valor;


//	auxmat.at<ushort>(centro_y,centro_x) = 65535;
//	imshow("asdasd", auxmat);
//		waitKey(0);
//
//		rectangle(auxmat, i_rect, Scalar(65535));
//		imshow("asdasd", auxmat);
//		waitKey(0);


	valor = i_img_profundidad16.at<ushort>(centro_y,centro_x);
	//cout << "\nvalor " << valor;

	float distancia_al_objeto = (float) valor / 1000; // Viene en mm, la pasamos a metros.

	float altura_m = a_tamanio_real(i_img_profundidad16, altura_px, distancia_al_objeto);
	/*cout << "\naltura_m " << altura_m << "  altura_px " << altura_px << "  dist " << distancia_al_objeto <<
			"   val " << (float) i_img_profundidad16.at<uchar>(centro_y,centro_x) << " -centro_x" << centro_x <<
			"  -centro_y" << centro_y;*/
	cout << "\naltura_m " << altura_m;

	if( altura_m < ALTURA_MINIMA_M || altura_m > ALTURA_MAXIMA_M )
	{
		//cout << "\nALTURA MALA: " << altura_m;

		return false;
	}
	else
		return true;
}






bool es_gradiente_disperso(std::vector<cv::Point>& contorno, const cv::Mat & i_img_profundidad8)
{
	vector<vector<Point>> v_contorno;
	v_contorno.push_back(contorno);
	Mat mascara = Mat::zeros(i_img_profundidad8.size(), CV_8UC1);
	drawContours(mascara, v_contorno, 0, Scalar(255), CV_FILLED);
	namedWindow("gd",0);
	imshow("gd",mascara);
	//waitKey(0);

	Rect auxrect = boundingRect(contorno);
	//mascara = mascara(auxrect);
//	imshow("gd",mascara);
//	waitKey(0);
	Mat roi;
	i_img_profundidad8.copyTo(roi,mascara);
//	imshow("gd",roi);
//	waitKey(0);
	roi = roi(auxrect);

//	namedWindow("gd",0);
//	imshow("gd",roi);
//	waitKey(0);

	// Calculamos la matriz de gradiente
	Mat gradiente;
	Mat kernel = (Mat_<int>(1,3) << -1, 0 , 1 );
	filter2D(roi, gradiente, CV_32F , kernel);

	Mat gradiente_positivo;
	gradiente.copyTo(gradiente_positivo, gradiente >= 0); // compare to

	Mat gradiente_negativo;
	gradiente.copyTo(gradiente_negativo, gradiente < 0);

	//cout << "\nGRADIENTE: " << gradiente << endl;

//	imshow("gd",gradiente_positivo);
//	waitKey(0);
//	imshow("gd",gradiente_negativo);
//	waitKey(0);

	Mat roimask = mascara(auxrect);


	// Calculamos la desviación del gradiente
	Scalar media_pos, media_neg;
	Scalar std_pos, std_neg;
	meanStdDev(gradiente_positivo, media_pos, std_pos, roimask);
	meanStdDev(gradiente_negativo, media_neg, std_neg, roimask);

	cout << "\nmedia_pos " << media_pos[0] << "  std_pos " << std_pos[0];
	cout << "\nmedia_neg " << media_neg[0] << "  std_neg " << std_neg[0];

	float std_promedio = ( std_pos[0] + std_neg[0] ) / 2;

	cout << "\nstd_promedio = " << std_promedio;
	waitKey(0);

	// TODO; esto debería ir como argumento
	if( std_promedio >= UMBRAL_STD )
		return true;
	else
		return false;
}
