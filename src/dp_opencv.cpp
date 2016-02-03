//----------------------------------------------------------------------------------------------
/* Programa de evaluación de algoritmos de detección de personas para Turtlebot.

 Fabricio Emder - Pablo Aguado
 2014 - 2015 - 2016
 */

//----------------------------------------------------------------------------------------------
// Includes
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
bool mostrar_detecciones = true;


//----------------------------------------------------------------------------------------------
// Declaración de funciones
static void ayuda(); //static hace que sólo sea usable en este archivo.

static void readDirectory(const string& directoryName,
		vector<string>& filenames, bool addDirectoryName = true);

//----------------------------------------------------------------------------------------------
// MAIN

int main(int argc, char* argv[])
{

	// Ayuda de uso
	ayuda();
	string i_carpeta_imagenes, i_nombre_archivos_resultados;
	string archivo_imagen = "";
	string i_detector;
	string nombre_set;
	vector<string> nombres_imagenes;
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
//		i_carpeta_imagenes = argv[1];
//		i_nombre_archivos_resultados = argv[2];
//		break;
//	}
//	}

	if( argc < 4 || (argc % 2) != 0 ) // programa,carpeta,resultados,detector,[numero par de parametros]
		return -1; //Error


	i_carpeta_imagenes = argv[1];
	i_nombre_archivos_resultados = argv[2];
	i_detector = argv[3];

	for( int i = 4  ; i < argc ; i++)
	{
		i_parametros_nombres.push_back(argv[i]);
		i++;
		i_parametros_valores.push_back(argv[i]);
	}


	 // if( *(i_nombre_archivos_resultados.end()) == "\\" || *(i_nombre_archivos_resultados.end()) == "/" )
	char ultimochar = i_carpeta_imagenes[i_carpeta_imagenes.size()-1];
	if( ultimochar == '\\' || ultimochar == '/' )
		i_carpeta_imagenes.pop_back();

//	if( i_carpeta_imagenes[i_carpeta_imagenes.size()-1] == "\\"
//			|| i_carpeta_imagenes[i_carpeta_imagenes.size()-1] == "/")
//		  i_carpeta_imagenes.pop_back();

	  size_t pos_barra = i_carpeta_imagenes.find_last_of("/\\"); // Encuentra la última barra
	  nombre_set = i_carpeta_imagenes.substr(pos_barra + 1);



	// Se lee la carpeta con las imagenes, o la imagen según corresponda
	readDirectory(i_carpeta_imagenes,nombres_imagenes);

	//	nombres_imagenes.erase(nombres_imagenes.begin()); // Borra el .
	//	nombres_imagenes.erase(nombres_imagenes.begin()); // Borra el ..
//	    for( auto i: nombres_imagenes) //c++11
//	    	cout << i << '\n';

	if( nombres_imagenes.size() == 0 )
		return -1;

	// Archivo csv
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


	// Se crea un detector
	Detector* detector;
	if( i_detector == "DetectorDummy")
		detector = new DetectorDummy(i_parametros_nombres, i_parametros_valores);
	else if( i_detector == "Extractor")
		detector = new Extractor();
	else if( i_detector == "DetectorHOG")
		detector = new DetectorHOG(i_parametros_nombres, i_parametros_valores);
	else
		return -1;

	// Se escriben los parámetros del detector
	stream_archivo_txt << *detector;

	// Estructura de resultados. Todas las detecciones correspondientes a una imagen.
	vector<struct_resultados> res (nombres_imagenes.size()); // resultados y forma de imprimirlos deberia estar en un objeto

	// Se procesan las imagenes
	Mat img;
	string string_numero;
	//int numero;
	for( size_t i = 0 ; i < nombres_imagenes.size() ; i++ ) //convertir a for normal
	{
		res.clear();
		// Se abre la imagen
		img = imread( nombres_imagenes.at(i) , IMREAD_UNCHANGED ); // 8bit, color or not
		//set = ?
//		string_numero = nombres_imagenes.at(i);
//		cout << "\nstring_numero = " << string_numero << " .\n";
//		string_numero = string_numero.substr(0,2);
//		cout << "\nstring_numero = " << string_numero << " .\n";
//		numero = stoi(string_numero);

		// Procesamiento
		detector->detectar(img, res);


		// Escribir resultados
		//stream_archivo_csv << nombres_imagenes.at(i) << "\n";
		for( auto auto_res: res )
		{
			//auto_res.img = numero;
			auto_res.img = i+1; // Suponiendo que se cargaron en orden..
			auto_res.set = nombre_set;
			stream_archivo_csv << auto_res; // Escribe la línea de resultados y salto de línea.
		}
	}

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
					"Uso: dp_opencv <carpeta_con_imagenes | imagen >  </dir/al/archivo_de_resultados> (sin extensión)"
					"<clase_de_detector> [parámetro_1_nombre parámetro_1_valor ...]\n"
				"\nCrea un archivo csv con los resultados y un txt con información sobre el detector usado.\n"
				"\nDetectores válidos: "
				"\n* DetectorDummy parametro1 int parametro2 int parametro3 char parametro4 string"
				"\n* Extractor"
				"\n* DetectorHOG pasoEscala double umbralAgrupamiento int setSVMDetector <getDefaultPeopleDetector | getDaimlerPeopleDetector"
					"\n\nUsando OpenCV " << CV_VERSION << endl;
	cout	<< "\n------------------------------------------------------------------------------------------------------------------\n";

	return;
}





// Lectura de archivos (tomada del svm)
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
			if ( sss[0] != '.' )
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
