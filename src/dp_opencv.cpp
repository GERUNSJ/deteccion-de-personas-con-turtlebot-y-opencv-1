//----------------------------------------------------------------------------------------------
// Includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "resultados.hpp"

// Para readDirectory
#if defined(WIN32) || defined(_WIN32)
#include <io.h>
#else
#include <dirent.h>
#endif

using namespace std;
using namespace cv;

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
	vector<string> nombres_imagenes;

	switch (argc)
	{
	case 2: // Una sola imagen, no guarda nada.
	{
		//
		break;
	}
	case 3: // Una carpeta, guarda resultados en el archivo del segundo argumento. Añade.
	{
		//
		i_carpeta_imagenes = argv[1];
		i_nombre_archivos_resultados = argv[2];
		break;
	}
	}
//	cout << i_carpeta_imagenes << endl;
//	cout << i_nombre_archivos_resultados << endl;
//	cout << argv[1] << endl;
//	cout << argv[2] << endl;
	//cout << argv[3] << endl;


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
	// Se escriben los parámetros del detector
	stream_archivo_txt << "Parámetros del detector";

	// Estructura de resultados
	vector<struct_resultados> res; // resultados y forma de imprimirlos deberia estar en un objeto

	// Se procesan las imagenes
	Mat img;
	for( auto i: nombres_imagenes )
	{
		res.clear();
		// Se abre la imagen
		img = imread( i , IMREAD_UNCHANGED ); // 8bit, color or not

		// Procesamiento
		//detector.detectar(img, res);
		//
		struct_resultados res_aux;
		res.push_back(res_aux);

		// Escribir resultados
		stream_archivo_csv << i << "\n";
		for( auto auto_res: res )
			stream_archivo_csv << auto_res; // Escribe la línea de resultados y salto de línea.
	}

	// Se cierran los archivos
	stream_archivo_csv.close();
	stream_archivo_txt.close();


	cout << "El programa ha terminado.\n\n";
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
					" [otras opciones...]\n"
				"\nCrea un archivo csv con los resultados y un txt con información sobre el detector usado.\n"
					"\nUsando OpenCV " << CV_VERSION << endl;
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
