#include "detector_final.hpp"


#define DISTANCIA_FOCAL		570
#define ALTURA_MAXIMA_M		2.5 // Está entrenado con un poco de background, entonces las personas detectadas son más altas..
#define ALTURA_MINIMA_M		0.8


using namespace std;
using namespace cv;



static float a_tamanio_real(const Mat & i_img_profundidad16, unsigned int i_longitud_px, float i_distancia_al_objeto)
{
	return (float) i_longitud_px * i_distancia_al_objeto / DISTANCIA_FOCAL;
}





static bool es_altura_creible(const cv::Rect & i_rect, const cv::Mat & i_img_profundidad16)
{
	namedWindow("asdasd",0);
//	imshow("asdasd", i_img_profundidad16);
//	waitKey(0);
	Mat auxmat = i_img_profundidad16.clone();
	//auxmat.convertTo(auxmat,CV_16UC3);


	int altura_px = i_rect.height;
	int centro_x = i_rect.x + ((i_rect.width-1)/2);
	int centro_y = i_rect.y + ((i_rect.height-1)*1/3); // 1/3 para centro de torso
	ushort valor;


	auxmat.at<ushort>(centro_y,centro_x) = 65535;
	imshow("asdasd", auxmat);
		waitKey(0);

		rectangle(auxmat, i_rect, Scalar(65535));
		imshow("asdasd", auxmat);
		waitKey(0);


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







DetectorFinal::DetectorFinal(vector<string>argumentos_nombre, vector<string>argumentos_valor)
{
	this->nombre = "DetectorFinal";
	unsigned int n = argumentos_nombre.size();
//	if( n != cantidad_de_argumentos )
//	{
//		//error
//	}

	for( unsigned int i = 0 ; i < n ; i++ )
	{
		if( argumentos_nombre.at(i) == "direccion_a_cascada")
		{
			this->direccion_a_cascada= (argumentos_valor.at(i));
		}

		else if( argumentos_nombre.at(i) == "escala_inicial")
		{
			this->escala_inicial= stof(argumentos_valor.at(i));
		}

		else if( argumentos_nombre.at(i) == "convertir_a_gris")
		{
			if( (!strcmp(argumentos_valor.at(i).c_str(), "0") || !strcmp(argumentos_valor.at(i).c_str(), "false")))
				this->convertir_a_gris = false;
			else
				this->convertir_a_gris = true;
		}

		else if( argumentos_nombre.at(i) == "ecualizar_histograma")
		{
			if( (!strcmp(argumentos_valor.at(i).c_str(), "0") || !strcmp(argumentos_valor.at(i).c_str(), "false")))
				this->ecualizar_histograma = false;
			else
				this->ecualizar_histograma = true;
		}

		else if( argumentos_nombre.at(i) == "scaleFactor")
		{
			this->scaleFactor = stof(argumentos_valor.at(i));
		}

		else if( argumentos_nombre.at(i) == "minNeighbors")
		{
			this->minNeighbors= stoi(argumentos_valor.at(i));
		}

		else if( argumentos_nombre.at(i) == "usar_profundidad_altura")
		{
			if( (!strcmp(argumentos_valor.at(i).c_str(), "0") || !strcmp(argumentos_valor.at(i).c_str(), "false")))
				this->usar_profundidad_altura = false;
			else
				this->usar_profundidad_altura = true;
		}

		else
		{
			cout << "\nNo se reconoció el parámetro " << argumentos_nombre.at(i) << " pasado como argumento." << endl;
		}

	}

	// Cargamos la el modelo o cascada
    if( !cascada.load( direccion_a_cascada ) )
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return;
    }

//	// Se cargan los nombres y valores (strings) de los parámetros del detector.
//	// Estos son los que luegos se escriben en el archivo de información txt
//	parametros_nombre.push_back("pasoEscala");
//	parametros_valor.push_back(to_string(pasoEscala));
//	parametros_nombre.push_back("umbralAgrupamiento");
//	parametros_valor.push_back(to_string(umbralAgrupamiento));
//	parametros_nombre.push_back("setSVMDetector");
//	parametros_valor.push_back(setSVMDetector);
//	// Podríamos guardar todos...

}





DetectorFinal::~DetectorFinal()
{
}





void DetectorFinal::detectar(const Mat& i_img_color, const Mat& i_img_profundidad, vector<struct_resultados>& i_res)
{
	// Más o menos lo mismo del ejemplo samples/cpp/peopledetect.cpp pero con cascada.


	// Verificamos entrada de 8 bits
	if( i_img_color.depth() != CV_8U && i_img_color.depth() != CV_8S )
	{
		cout << "\nSolo soporta 8 bits\n"; //
		/// TODO: Error
		return;
	}


	Mat con_detecciones = i_img_color.clone(); // Para mostrar en caso de mostrar_detecciones = true
	struct_resultados aux_res;	// Acá llenamos los datos de cada detección para guardarlo en i_res

    vector<Rect> found;

    // Achicamos la imagen original, de acuerdo al factor escala_inicial
    Mat gray, smallImg( cvRound (i_img_color.rows/escala_inicial), cvRound(i_img_color.cols/escala_inicial), CV_8UC1 );
    if( convertir_a_gris )
    	cvtColor( i_img_color, gray, CV_BGR2GRAY );
    resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    if( ecualizar_histograma )
    	equalizeHist( smallImg, smallImg );

    namedWindow("ventana1",0);
    imshow("ventana1",smallImg);

    double t = (double)getTickCount();	// Medimos el tiempo

    cascada.detectMultiScale( smallImg,
            found,
            scaleFactor,
            minNeighbors,
            0 /*| CASCADE_SCALE_IMAGE*/, /*flags*/
            tamanio_minimo,
            tamanio_maximo );
    t = (double)getTickCount() - t;

    printf("\ndetection time = %gms\n", t*1000./cv::getTickFrequency());
//    for( auto i: found)
//    	cout << "\nFound = " << i << endl;

//    for( auto i: found_filtered)
//    	cout << "\nFound_filtered = " << i << endl;


    // Para cada detección
    for( unsigned int i = 0; i < found.size(); i++ )
    {
        Rect r = found[i];

        // Des-escalamos
        r.x = floor(r.x * escala_inicial);
        r.y = floor(r.y * escala_inicial);
        r.height = floor(r.height * escala_inicial);
        r.width = floor(r.width * escala_inicial);

        // Filtramos según la altura real estimada
        if( usar_profundidad_altura )
        {
        	if( !es_altura_creible(r, i_img_profundidad) )
        		continue; // Termina con esta predetección y continúa el for
        }


        // Completamos y guardamos los datos de cada detección
        rect_a_struct_resultados(r,aux_res);
        aux_res.tiempo = t*1000./cv::getTickFrequency(); // Tiempo en ms

		if( i_img_color.depth() == CV_8U || i_img_color.depth() == CV_8S ) // La cascada sólo soporta 8..
			aux_res.prof = 8;
		else
			aux_res.prof = 16;


        i_res.push_back(aux_res); // Guardamos en el vector de detecciones para esta imagen


        // Show
        if( mostrar_detecciones )
        {
        	// Creamos un rectángulo en una copia de la imagen original. tl es top-left, br es bottom-right
            rectangle(con_detecciones, r.tl(), r.br(), cv::Scalar(0,255,0), 3);
        }
    }


    // Show
    if( mostrar_detecciones )
    {
    	namedWindow("Detecciones", CV_WINDOW_KEEPRATIO | CV_WINDOW_NORMAL);
    	imshow("Detecciones", con_detecciones);
    	waitKey(0);
    }

	return;
}






