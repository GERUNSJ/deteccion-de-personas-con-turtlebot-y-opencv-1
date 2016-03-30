#include "detector_hog.hpp"
using namespace std;
using namespace cv;


DetectorHOG::DetectorHOG(vector<string>argumentos_nombre, vector<string>argumentos_valor)
{
	this->nombre = "DetectorHOG";
	unsigned int n = argumentos_nombre.size();
//	if( n != cantidad_de_argumentos )
//	{
//		//error
//	}

	for( unsigned int i = 0 ; i < n ; i++ )
	{
		if( argumentos_nombre.at(i) == "pasoEscala")
		{
			this->pasoEscala = stod(argumentos_valor.at(i));
		}

		else if( argumentos_nombre.at(i) == "umbralAgrupamiento")
		{
			this->umbralAgrupamiento = stoi(argumentos_valor.at(i),nullptr,10);
		}

		else if( argumentos_nombre.at(i) == "hit_threshold")
		{
			this->hit_threshold = stof(argumentos_valor.at(i));
		}

		else if( argumentos_nombre.at(i) == "setSVMDetector")
		{
			this->setSVMDetector = argumentos_valor.at(i);
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

		else if( argumentos_nombre.at(i) == "blurear")
		{
			if( (!strcmp(argumentos_valor.at(i).c_str(), "0") || !strcmp(argumentos_valor.at(i).c_str(), "false")))
				this->blurear = false;
			else
				this->blurear = true;
		}

		else if( argumentos_nombre.at(i) == "tamanio_blur")
		{
			this->tamanio_blur = stoi(argumentos_valor.at(i));
		}

		else if( argumentos_nombre.at(i) == "filtro_repujado")
		{
			if( (!strcmp(argumentos_valor.at(i).c_str(), "0") || !strcmp(argumentos_valor.at(i).c_str(), "false")))
				this->filtro_repujado = false;
			else
				this->filtro_repujado = true;
		}

		else if( argumentos_nombre.at(i) == "filtro_enfoque")
		{
			if( (!strcmp(argumentos_valor.at(i).c_str(), "0") || !strcmp(argumentos_valor.at(i).c_str(), "false")))
				this->filtro_enfoque = false;
			else
				this->filtro_enfoque = true;
		}

		else if( argumentos_nombre.at(i) == "filtro_enfoque_y_repujado")
		{
			if( (!strcmp(argumentos_valor.at(i).c_str(), "0") || !strcmp(argumentos_valor.at(i).c_str(), "false")))
				this->filtro_enfoque_y_repujado = false;
			else
				this->filtro_enfoque_y_repujado = true;
		}

		else if( argumentos_nombre.at(i) == "filtro_repujado_y_enfoque")
		{
			if( (!strcmp(argumentos_valor.at(i).c_str(), "0") || !strcmp(argumentos_valor.at(i).c_str(), "false")))
				this->filtro_repujado_y_enfoque = false;
			else
				this->filtro_repujado_y_enfoque = true;
		}

		else
		{
			cout << "\nNo se reconoció el parámetro " << argumentos_nombre.at(i) << " pasado como argumento." << endl;
		}

	}


//    CV_WRAP HOGDescriptor() : winSize(64,128), blockSize(16,16), blockStride(8,8),
//        cellSize(8,8), nbins(9), derivAperture(1), winSigma(-1),
//        histogramNormType(HOGDescriptor::L2Hys), L2HysThreshold(0.2), gammaCorrection(true),
//        nlevels(HOGDescriptor::DEFAULT_NLEVELS)
//    {}


	// Declaración de parámetros antes de crear el detector
	Size winSize;	// Depende del modelo entrenado
	if(setSVMDetector == "getDefaultPeopleDetector")
		winSize = Size(64,128);
	else if (setSVMDetector == "getDaimlerPeopleDetector")
		winSize = Size(48,96);
	else
	{
		cout << "\nSVMDetector inválido. Debe ser getDefaultPeopleDetector o getDaimlerPeopleDetector\n"
				"Se usará getDefaultPeopleDetector\n";
		winSize = Size(64,128);
	}

	// Parámetros que no se pueden modificar
	//Size winSize=Size(64, 128);	// Depende del modelo entrenado
	Size blockSize = Size(16,16);	// Solo 16*16 soportado
	Size blockStride = Size(8,8);	// Múltiplo de cellSize
	Size cellSize = Size(8,8);	// Solo 8*8 soportado
	int nbins = 9;	// Solo 9 soportado
	int derivAperture = 1;	// ?
	double winSigma =-1;	// Gaussian smoothing window parameter. (-1 por defecto)
	int histogramNormType = HOGDescriptor::L2Hys;
	double L2HysThreshold = 0.2;
	bool gammaCorrection = true;
	int nlevels = HOGDescriptor::DEFAULT_NLEVELS;

	// Se crea el detector de opencv
	hog = HOGDescriptor(winSize, blockSize, blockStride, cellSize, nbins, derivAperture, winSigma,
			histogramNormType, L2HysThreshold, gammaCorrection, nlevels);

	// Configuramos el modelo del clasificador
	// El detector getDefaultPeopleDetector viene hardcodeado en hog.cpp de opencv. También está
	// getDaimlerPeopleDetector, pero para ventanas de 48*96
	if(setSVMDetector == "getDefaultPeopleDetector")
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	else if (setSVMDetector == "getDaimlerPeopleDetector")
		hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());
	else
	{
		cout << "\nSVMDetector inválido. Debe ser getDefaultPeopleDetector o getDaimlerPeopleDetector\n"
				"Se usará getDefaultPeopleDetector\n";
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	}


//    virtual void detectMultiScale(const Mat& img, CV_OUT vector<Rect>& foundLocations,
//                                  double hitThreshold=0, Size winStride=Size(),
//                                  Size padding=Size(), double scale=1.05,
//                                  double finalThreshold=2.0, bool useMeanshiftGrouping = false) const;


	// Se cargan los nombres y valores (strings) de los parámetros del detector.
	// Estos son los que luegos se escriben en el archivo de información txt
	parametros_nombre.push_back("pasoEscala");
	parametros_valor.push_back(to_string(pasoEscala));
	parametros_nombre.push_back("umbralAgrupamiento");
	parametros_valor.push_back(to_string(umbralAgrupamiento));
	parametros_nombre.push_back("hit_threshold");
	parametros_valor.push_back(to_string(hit_threshold));
	parametros_nombre.push_back("setSVMDetector");
	parametros_valor.push_back(setSVMDetector);
	parametros_nombre.push_back("escala_inicial");
	parametros_valor.push_back(to_string(escala_inicial));
	parametros_nombre.push_back("convertir_a_gris");
	if( convertir_a_gris )
		parametros_valor.push_back("true");
	else
		parametros_valor.push_back("false");
	parametros_nombre.push_back("ecualizar_histograma");
	if( ecualizar_histograma )
		parametros_valor.push_back("true");
	else
		parametros_valor.push_back("false");
	parametros_nombre.push_back("blurear");
	if( blurear )
		parametros_valor.push_back("true");
	else
		parametros_valor.push_back("false");
	parametros_nombre.push_back("tamanio_blur");
	parametros_valor.push_back(to_string(tamanio_blur));
	parametros_nombre.push_back("filtro_enfoque");
	if( filtro_enfoque )
		parametros_valor.push_back("true");
	else
		parametros_valor.push_back("false");
	parametros_nombre.push_back("filtro_repujado");
	if( filtro_repujado )
		parametros_valor.push_back("true");
	else
		parametros_valor.push_back("false");
	parametros_nombre.push_back("filtro_enfoque_y_repujado");
	if( filtro_enfoque_y_repujado )
		parametros_valor.push_back("true");
	else
		parametros_valor.push_back("false");
	parametros_nombre.push_back("filtro_repujado_y_enfoque");
	if( filtro_repujado_y_enfoque )
		parametros_valor.push_back("true");
	else
		parametros_valor.push_back("false");

}





DetectorHOG::~DetectorHOG()
{
}





void DetectorHOG::detectar(const Mat& i_img_color, const Mat& i_img_profundidad, vector<struct_resultados>& i_res)
{
	// Más o menos lo mismo del ejemplo samples/cpp/peopledetect.cpp

//	 C++: void gpu::HOGDescriptor::detectMultiScale(const GpuMat& img, vector<Rect>& found_locations, double hit_threshold=0, Size win_stride=Size(), Size padding=Size(), double scale0=1.05, int group_threshold=2)
//	    Parameters:
//
//	        img – Source image. See gpu::HOGDescriptor::detect() for type limitations.
//	        found_locations – Detected objects boundaries.
//	        hit_threshold – Threshold for the distance between features and SVM classifying plane. See gpu::HOGDescriptor::detect() for details.
//	        win_stride – Window stride. It must be a multiple of block stride.
//	        padding – Mock parameter to keep the CPU interface compatibility. It must be (0,0).
//	        scale0 – Coefficient of the detection window increase.
//	        group_threshold – Coefficient to regulate the similarity threshold. When detected, some objects can be covered by many rectangles. 0 means not to perform grouping. See groupRectangles() .

	//    virtual void detectMultiScale(const Mat& img, CV_OUT vector<Rect>& foundLocations,
	//                                  double hitThreshold=0, Size winStride=Size(),
	//                                  Size padding=Size(), double scale=1.05,
	//                                  double finalThreshold=2.0, bool useMeanshiftGrouping = false) const;

	// Verificamos entrada de 8 bits
	if( i_img_color.depth() != CV_8U && i_img_color.depth() != CV_8S )
	{
		cout << "\nHOGDescriptor solo soporta 8 bits\n";
		/// TODO: Error
		return;
	}



	Mat con_detecciones = i_img_color.clone(); // Para mostrar en caso de mostrar_detecciones = true
	struct_resultados aux_res;	// Acá llenamos los datos de cada detección para guardarlo en i_res

    vector<Rect> found, found_filtered;

    // Achicamos la imagen original, de acuerdo al factor escala_inicial
	Mat gray;
	Mat smallImg( cvRound (i_img_color.rows/escala_inicial), cvRound(i_img_color.cols/escala_inicial), i_img_color.type() ); // Constructor, pero mat vacía


	// Medimos el tiempo
	double t = (double)getTickCount();

	// Preprocesamiento con la imagen grande para no perder información
	// HOG acepta 1 o 3 canales, como se ve en la línea 177 de modules/objdetect/src/hog.cpp
	if( convertir_a_gris )
		cvtColor( i_img_color, gray, CV_BGR2GRAY );
	else gray = i_img_color.clone();

	if( ecualizar_histograma && convertir_a_gris)
		equalizeHist( gray, gray );

	if( blurear )
		blur( gray, gray, Size(tamanio_blur,tamanio_blur) );


    if( filtro_repujado && !filtro_repujado_y_enfoque && !filtro_enfoque_y_repujado )
    	filter2D( gray, gray, -1, kernel_repujado);

    if( filtro_enfoque && !filtro_repujado_y_enfoque && !filtro_enfoque_y_repujado )
    	filter2D( gray, gray, -1, kernel_enfoque);

    if( filtro_repujado_y_enfoque && !filtro_enfoque_y_repujado )
    {
    	filter2D( gray, gray, -1, kernel_repujado);
    	filter2D( gray, gray, -1, kernel_enfoque);
    }

    if( filtro_enfoque_y_repujado && !filtro_enfoque_y_repujado )
    {
    	filter2D( gray, gray, -1, kernel_enfoque);
    	filter2D( gray, gray, -1, kernel_repujado);
    }



	// Achicamos la imagen original, de acuerdo al factor escala_inicial
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );


	if( mostrar_detecciones )
	{
		namedWindow("Preprocesada",0);
		imshow("Preprocesada",smallImg);
	}


    // run the detector with default parameters. to get a higher hit-rate
    // (and more false alarms, respectively), decrease the hitThreshold and
    // groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
    // hog.detectMultiScale(img, found, 0, Size(8,8), Size(32,32), 1.05, 2);
    hog.detectMultiScale(smallImg, found, hit_threshold, Size(8,8), Size(), pasoEscala , umbralAgrupamiento);


    t = (double)getTickCount() - t;

    printf("\ndetection time = %gms\n", t*1000./cv::getTickFrequency());
//    for( auto i: found)
//    	cout << "\nFound = " << i << endl;

    // Esta parte..qué hace? [DUDA]
    // Borra duplicados, pero dudo que justo hayan 2 rects iguales...luego borramos nosotros
    /* Edit: Funciona y filtra. Al parecer si hay rects iguales.
     * template<typename _Tp> static inline bool operator == (const Rect_<_Tp>& a, const Rect_<_Tp>& b)
     * 	{
     * 	return a.x == b.x && a.y == b.y && a.width == b.width && a.height == b.height;
     * 	}
     * 	*/

    size_t i, j;
    for( i = 0; i < found.size(); i++ )
    {
        Rect r = found[i];
        for( j = 0; j < found.size(); j++ ) // Para todos los rects encontrados
            if( j != i && (r & found[j]) == r) // si hay dos iguales
                break;
        if( j == found.size() ) // Si no hubieron dos iguales, lo guarda
            found_filtered.push_back(r);
    }

//    for( auto i: found_filtered)
//    	cout << "\nFound_filtered = " << i << endl;


    // Invertimos el orden, para ordenarlos de menor a mayor. Así, preservamos los rectángulos más chicos
    // al comparar coincidencias a continuación.
    // La comparacion entre struct_resultados toma como referencia de tamaño al primer elemento.
   // reverse( found_filtered.begin() , found_filtered.end() );
    /* TODO: Ordenarl los rects encontrados según su área, de menor a mayor, por la razón de arriba.
     * El detector los devuelve en un orden aleatorio a primera vista.
     */


    // Para cada detección
    for( i = 0; i < found_filtered.size(); i++ )
    {
    	// Achicamos los rectangulos detectados
        Rect r = found_filtered[i];


        // the HOG detector returns slightly larger rectangles than the real objects.
        // so we slightly shrink the rectangles to get a nicer output.
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);

        // Des-escalamos
		r.x = floor(r.x * escala_inicial);
		r.y = floor(r.y * escala_inicial);
		r.height = floor(r.height * escala_inicial);
		r.width = floor(r.width * escala_inicial);


        // Completamos y guardamos los datos de cada detección
        rect_a_struct_resultados(r,aux_res);
        aux_res.tiempo = t*1000./cv::getTickFrequency(); // Tiempo en ms

		if( i_img_color.depth() == CV_8U || i_img_color.depth() == CV_8S ) // Actualmente hog solo soporta 8...
			aux_res.prof = 8;
		else
			aux_res.prof = 16;


		// Calculamos centros y medidas, para las comparaciones.
		aux_res.calcular();


		//cout << "\nr["<<i<<"] = " << r;

		/* TODO: Hacer una mejor función de agrupamiento, que compare todos con todos
		 * y deje rects promedios. La de OpenCV (groupRectangles) no está funcionando como debería
		 * en 2.4.8.*/


		// Si es la primera detección en esta imagen, la guardamos.
		if( i_res.empty() )
			 i_res.push_back(aux_res); // Guardamos en el vector de detecciones para esta imagen
		else
		/*{
			// Eliminamos detecciones superpuestas, con el mismo criterio de igualdad que para la comparación entre reales y estimados.
			bool distinto = true;
			for( auto j: i_res)
			{
				if(aux_res == j) // aux_res es la referencia de tamaño
				{
					//cout << "\nSon iguales";
					distinto = false;
					break;
				}
			}
			if( distinto )
			{
				i_res.push_back(aux_res); // Guardamos en el vector de detecciones para esta imagen
			}
		}*/
		i_res.push_back(aux_res); // Guardamos en el vector de detecciones para esta imagen



        // Show
        if( mostrar_detecciones )
        {
        	// Creamos un rectángulo en una copia de la imagen original. tl es top-left, br es bottom-right
            rectangle(con_detecciones, r.tl(), r.br(), cv::Scalar(0,255,0), 2);
        }
    }



    // Show
    if( mostrar_detecciones )
    {
    	for( auto r : i_res )
    	{
    		Rect auxrect;
    		struct_resultados_a_rect(r, auxrect);
    		rectangle(con_detecciones, auxrect.tl(), auxrect.br(), cv::Scalar(0,0,255), 1);
    	}
    	namedWindow("Detecciones", CV_WINDOW_KEEPRATIO | CV_WINDOW_NORMAL);
    	imshow("Detecciones", con_detecciones);
    	waitKey(0);
    }

	return;
}
