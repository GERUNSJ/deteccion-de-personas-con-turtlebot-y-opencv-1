//----------------------------------------------------------------------------------------------
/* Programa de evaluación de algoritmos de detección de personas para Turtlebot.

 Fabricio Emder - Pablo Aguado
 2014 - 2015 - 2016
 */

//----------------------------------------------------------------------------------------------
// Includes
// Hay que agregar cada detector.
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "resultados.hpp"
#include "detector.hpp"
#include "detector_dummy.hpp"
#include "detector_hog.hpp"
#include "extractor.hpp"
#include "detector_1.hpp"
#include "detector_final.hpp"


// Para readDirectory
#if defined(WIN32) || defined(_WIN32)
#include <io.h>
#else
#include <dirent.h>
#endif


using namespace std;
using namespace cv;


//----------------------------------------------------------------------------------------------
// Defines y globales
bool mostrar_detecciones = true;	// A usar para mostrar cada imagen con lo que se detectó


//----------------------------------------------------------------------------------------------
// Declaración de funciones
static void ayuda(); //static hace que sólo sea usable en este archivo.

static void readDirectory(const string& directoryName,
		vector<string>& filenames, bool addDirectoryName = true);

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
// MAIN

int main(int argc, char* argv[])
{

	// Ayuda de uso
	ayuda();

	string i_carpeta_imagenes_color, i_carpeta_imagenes_profundidad, i_nombre_archivos_resultados;
	string archivo_imagen = "";
	string i_detector;
	string nombre_set;
	vector<string> nombres_imagenes_color, nombres_imagenes_profundidad;
	vector<string> i_parametros_nombres , i_parametros_valores;

//	switch (argc)
//	{
//	case 2: // Una sola imagen, no guarda nada.
//	{
//		//
//		break;
//	}
//	case 3: // Una carpeta, guarda resultados en el archivo del segundo argumento. Añade.
//	{
//		//
//		i_carpeta_imagenes_color = argv[1];
//		i_nombre_archivos_resultados = argv[2];
//		break;
//	}
//	}

	//----------------------------------------------------------------------------------------------
	// INTERPRETACIÓN / PARSEO DE ARGUMENTOS
	// 0 - programa (dp_opencv)
	// 1 - carpeta con las imagenes rgb
	// 2 - carpeta con las imagnes depth o un 0 en caso de que no hayan
	// 3 - resultados
	// 4 - bool mostrar_detecciones
	// 5 - clase de detector
	// 6 en adelante - pares parámetro-valor
	if( argc < 6 || !(argc % 2) == 0 ) // programa,carpetargb,carpetaprofundidad,resultados,mostrar_detecciones,detector,[numero par de parametros]
		return -1; //Error

	i_carpeta_imagenes_color = argv[1];
	i_carpeta_imagenes_profundidad = argv[2];
	i_nombre_archivos_resultados = argv[3];

	if(!strcmp(argv[4], "0") || !strcmp(argv[4], "false"))
		mostrar_detecciones = false;
	else
		mostrar_detecciones = true;
	//mostrar_detecciones = (bool)(int)argv[3];
	i_detector = argv[5];

	if(argc > 6 )
	{
		for( int i = 6  ; i < argc ; i++)
		{
			i_parametros_nombres.push_back(argv[i]);
			i++;
			i_parametros_valores.push_back(argv[i]);
		}
	}

	// Eliminamos la última barra de la carpeta de imágenes, si se ingresó así
	 // if( *(i_nombre_archivos_resultados.end()) == "\\" || *(i_nombre_archivos_resultados.end()) == "/" )
	char ultimochar = i_carpeta_imagenes_color[i_carpeta_imagenes_color.size()-1];
	if( ultimochar == '\\' || ultimochar == '/' )	//
		i_carpeta_imagenes_color.pop_back();	// Elimina la última barra

	// Eliminamos la última barra de la carpeta de imágenes, si se ingresó así
	 // if( *(i_nombre_archivos_resultados.end()) == "\\" || *(i_nombre_archivos_resultados.end()) == "/" )
	ultimochar = i_carpeta_imagenes_profundidad[i_carpeta_imagenes_profundidad.size()-1];
	if( ultimochar == '\\' || ultimochar == '/' )	//
		i_carpeta_imagenes_profundidad.pop_back();	// Elimina la última barra

//	if( i_carpeta_imagenes_color[i_carpeta_imagenes_color.size()-1] == '\\'
//			|| i_carpeta_imagenes_color[i_carpeta_imagenes_color.size()-1] == '/')
//		  i_carpeta_imagenes_color.pop_back();

	// El nombre de carpeta se interpreta como nombre del set
	size_t pos_barra = i_carpeta_imagenes_color.find_last_of("/\\"); // Encuentra la última barra
	nombre_set = i_carpeta_imagenes_color.substr(pos_barra + 1);	// Copia desde la última barra en adelante





	//----------------------------------------------------------------------------------------------
	// LECTURA DE NOMBRES
	// Se lee la carpeta con las imagenes
	readDirectory(i_carpeta_imagenes_color,nombres_imagenes_color);

	// Sólo ruta a imágenes. Borramos el resto.
	for( auto n : nombres_imagenes_color )
	{
		string ext = n.substr( n.find_last_of(".") + 1 );	// Extensión del archivo
		if( ext == "png" || ext == "bmp" || ext == "jpg" || ext == "jpeg"  || ext == "tiff" )
			continue;

		// Eliminamos si no es imagen
		//cout << "\n" << n;
		nombres_imagenes_color.pop_back();
	}


	readDirectory(i_carpeta_imagenes_profundidad,nombres_imagenes_profundidad);

	// Sólo ruta a imágenes. Borramos el resto.
	for( auto n : nombres_imagenes_profundidad )
	{
		string ext = n.substr( n.find_last_of(".") + 1 );	// Extensión del archivo
		if( ext == "png" || ext == "bmp" || ext == "jpg" || ext == "jpeg"  || ext == "tiff" )
			continue;

		// Eliminamos si no es imagen
		//cout << "\n" << n;
		nombres_imagenes_profundidad.pop_back();
	}


	if( nombres_imagenes_color.size() == 0 && nombres_imagenes_profundidad.size() == 0 )
	{
		cout << "\nNo se pudo cargar ninguna imagen. El programa ha terminado.\n";
		return -1;
	}

	if( nombres_imagenes_profundidad.size() == 0 )
	{
		cout << "\nNo se cargó ninguna imagen de profundidad. \n";
	}

	if( nombres_imagenes_profundidad.size() != 0 && nombres_imagenes_profundidad.size() != nombres_imagenes_color.size() )
	{
		cout << "\nEl número de imagenes rgb es distinto al número de imagenes de profundidad. El programa ha terminado. \n";
		return -1;
	}

	// Ordenamos. Se asigna a cada imagen el número en que se cargó y no necesariamente el número
	// de archivo. Sin embargo deberían ser iguales.
	sort( nombres_imagenes_color.begin() , nombres_imagenes_color.end() );
	sort( nombres_imagenes_profundidad.begin() , nombres_imagenes_profundidad.end() );
//	for( auto n : nombres_imagenes_color )
//	{
//		cout << "\n" << n;
//	}

	// Abrimos archivos de resultados
	fstream stream_archivo_csv;
	fstream stream_archivo_txt;
	string aux = i_nombre_archivos_resultados + ".csv"; // Append con +
	stream_archivo_csv.open(aux.c_str(), ios::out | ios::app); // Salida, append(añadir)
	if( !stream_archivo_csv.is_open() )
	{
		cout << "El archivo csv no se pudo abrir.\n";
		return -1; //ver de usar exit o error. Por qué devuelvo -1?
	}
	aux = i_nombre_archivos_resultados + ".txt";
	stream_archivo_txt.open(aux.c_str(), ios::out | ios::app); // Salida, append(añadir)
	if( !stream_archivo_txt.is_open() )
	{
		cout << "El archivo csv no se pudo abrir.\n";
		return -1; //ver de usar exit o error. Por qué devuelvo -1?
	}





	//----------------------------------------------------------------------------------------------
	// PROCESAMIENTO
	// Se crea un detector genérico.
	Detector* detector;
	// Específico. Acá hay que listar todos los detectores que se vayan desarrollando.
	if( i_detector == "DetectorDummy")
		detector = new DetectorDummy(i_parametros_nombres, i_parametros_valores);
	else if( i_detector == "Extractor")
		detector = new Extractor();
	else if( i_detector == "DetectorHOG")
		detector = new DetectorHOG(i_parametros_nombres, i_parametros_valores);
	else if( i_detector == "Detector1")
		detector = new Detector1(i_parametros_nombres, i_parametros_valores);
	else if( i_detector == "DetectorFinal")
		detector = new DetectorFinal(i_parametros_nombres, i_parametros_valores);
	else
	{
		cout << "\nDetector no reconocido.\n";
		return -1;
	}

	// Se escriben los parámetros del detector
	stream_archivo_txt << *detector;

	// Vector de estructura de resultados. Contiene los datos de todas las detecciones correspondientes a UNA imagen.
	vector<struct_resultados> res (nombres_imagenes_color.size());

	// Se procesan las imagenes
	Mat img_color, img_profundidad;
	string string_numero; // Suponemos que se cargaron en orden numérico correcto... poco robusto.
	//int numero;
	for( size_t i = 0 ; i < nombres_imagenes_color.size() ; i++ )
	{
		res.clear();
		// Se abre la imagen
		img_color = imread( nombres_imagenes_color.at(i) , IMREAD_UNCHANGED ); // 8bit, color or not
		if( nombres_imagenes_profundidad.size() != 0 )
			img_profundidad = imread( nombres_imagenes_profundidad.at(i) , IMREAD_GRAYSCALE );
		//set = ?
//		string_numero = nombres_imagenes_color.at(i);
//		cout << "\nstring_numero = " << string_numero << " .\n";
//		string_numero = string_numero.substr(0,2);
//		cout << "\nstring_numero = " << string_numero << " .\n";
//		numero = stoi(string_numero);

		// Procesamiento
		cout << "\nProcesando imagen " << i+1 << " de " << nombres_imagenes_color.size();

		// Será responsabilidad del detector usar o no la imagen de profundidad.
		detector->detectar(img_color, img_profundidad, res);


		// Asignación de número y set. Guardamos resultados
		for( auto auto_res: res )
		{
			//auto_res.img = numero;
			auto_res.img = i+1; // Suponiendo que se cargaron en orden..
			auto_res.set = nombre_set;

			stream_archivo_csv << auto_res; // Escribe la línea de resultados y salto de línea.
		}
	}


	//----------------------------------------------------------------------------------------------
	// Se cierran los archivos
	stream_archivo_csv.close();
	stream_archivo_txt.close();


	cout << "\nEl programa ha terminado.\n\n";
	return 0;
}






//----------------------------------------------------------------------------------------------
// Funciones auxiliares

// AYUDA
static void ayuda()
{
	cout	<< "\n------------------------------------------------------------------------------------------------------------------\n";
	cout
			<< "\nDetección de personas en opencv para Turtlebot - Fabricio Emder, Pablo Aguado\n"
					"Uso: dp_opencv  <carpeta/con/imagenes/rgb>\n"
					"                <carpeta/con/imagenes/profundidad | 0 >\n"
					"                </dir/al/archivo_de_resultados> (sin extensión)\n"
					"                <(1 | 0>(mostrar_detecciones)\n"
					"                <clase_de_detector> [parámetro_1_nombre parámetro_1_valor ...]\n"
				"\nCrea un archivo csv con los resultados y un txt con información sobre el detector usado.\n"
				"\nDetectores válidos: "
				"\n* DetectorDummy parametro1 int parametro2 int parametro3 char parametro4 string"
				"\n* Extractor"
				"\n* DetectorHOG pasoEscala double umbralAgrupamiento int setSVMDetector <getDefaultPeopleDetector | getDaimlerPeopleDetector"
				"\n* Detector1 \n"
					"\n\nUsando OpenCV " << CV_VERSION << endl;
	cout	<< "\n------------------------------------------------------------------------------------------------------------------\n";

	return;
}





// Lectura de archivos (tomada del ejemplo de svm y añadido el filtro de . y ..)
static void readDirectory(const string& directoryName,
		vector<string>& filenames, bool addDirectoryName)
{
	filenames.clear();

#if defined(WIN32) | defined(_WIN32)
	struct _finddata_t s_file;
	string str = directoryName + "\\*.*";

	intptr_t h_file = _findfirst( str.c_str(), &s_file );
	if( h_file != static_cast<intptr_t>(-1.0) )
	{
		do
		{
			if( addDirectoryName )
			filenames.push_back(directoryName + "\\" + s_file.name);
			else
			filenames.push_back((string)s_file.name);
		}
		while( _findnext( h_file, &s_file ) == 0 );
	}
	_findclose( h_file );
#else
	DIR* dir = opendir(directoryName.c_str());
	if (dir != NULL)
	{
		struct dirent* dent;
		while ((dent = readdir(dir)) != NULL)
		{
			string sss = string(dent->d_name);
			if ( sss[0] != '.' )	// Eliminamos el . y el ..
			{
				if (addDirectoryName)
						filenames.push_back(directoryName + "/" + sss);
					else
						filenames.push_back(sss);
			}
		}

		closedir(dir);
	}
#endif

	sort(filenames.begin(), filenames.end());
}
