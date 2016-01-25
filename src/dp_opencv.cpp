//----------------------------------------------------------------------------------------------
// Includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/core/core.hpp>

// Para readDirectory
#if defined(WIN32) || defined(_WIN32)
#include <io.h>
#else
#include <dirent.h>
#endif

using namespace std;

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
	string carpeta_imagenes, archivo_resultados;
	string archivo_imagen = "";
	vector<string> nombre_imagenes;

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
		carpeta_imagenes = argv[1];
		archivo_resultados = argv[2];
		break;
	}
	}
//	cout << carpeta_imagenes << endl;
//	cout << archivo_resultados << endl;
//	cout << argv[1] << endl;
//	cout << argv[2] << endl;
	//cout << argv[3] << endl;


	// Se lee la carpeta con las imagenes, o la imagen según corresponda
	readDirectory(carpeta_imagenes,nombre_imagenes);

	//	nombre_imagenes.erase(nombre_imagenes.begin()); // Borra el .
	//	nombre_imagenes.erase(nombre_imagenes.begin()); // Borra el ..
//	    for( auto i: nombre_imagenes) //c++11
//	    	cout << i << '\n';

	if( nombre_imagenes.size() == 0 )
		return -1;

	// Archivo csv
	fstream stream_archivo_resultados;
	stream_archivo_resultados.open(archivo_resultados.c_str(), ios::out | ios::app); // Salida, append(añadir)
	if( !stream_archivo_resultados.is_open() )
	{
		cout << "El archivo no se pudo abrir.\n";
		return -1; //ver de usar exit. Por qué devuelvo -1?
	}


	// Se crea un detector

	// Se procesan las imagenes
	for( auto i: nombre_imagenes )
	{
		// Procesar
		// Escribir resultados
		stream_archivo_resultados << i << "\n";
	}

	// Se cierra el archivo
	stream_archivo_resultados.close();


//	help();
//
//	float overlapThreshold = 0.2f;
//	int numThreads = -1;
//	if (argc > 2)
//	{
//		images_folder = argv[1];
//		models_folder = argv[2];
//		if (argc > 3)
//			overlapThreshold = (float) atof(argv[3]);
//		if (overlapThreshold < 0 || overlapThreshold > 1)
//		{
//			cout << "overlapThreshold must be in interval (0,1)." << endl;
//			exit(-1);
//		}
//
//		if (argc > 4)
//			numThreads = atoi(argv[4]);
//	}
//
//	vector<string> images_filenames, models_filenames;
//	readDirectory(images_folder, images_filenames);
//	readDirectory(models_folder, models_filenames);
//
//	models_filenames.erase(models_filenames.begin()); // Borra el .
//	models_filenames.erase(models_filenames.begin()); // Borra el ..
//	images_filenames.erase(images_filenames.begin()); // Borra el .
//	images_filenames.erase(images_filenames.begin()); // Borra el ..

	return 0;
}

//----------------------------------------------------------------------------------------------
// Funciones auxiliares

// AYUDA
static void ayuda()
{
	cout
			<< "\nDetección de personas en opencv para Turtlebot - Fabricio Emder, Pablo Aguado\n"
					"Uso: dp_opencv <carpeta_con_imagenes | imagen >  </dir/al/archivo_de_resultados.csv>"
					" [otras opciones...]\n"
					"\nUsando OpenCV " << CV_VERSION << endl;

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
