//----------------------------------------------------------------------------------------------
// Includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
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









int main(int argc, char* argv[])
{
	string i_reales;	// Ruta y nombre del archivo de los datos reales, sin extensión
	string i_estimados; // Ruta y nombre del archivo de los datos estimados, sin extensión
	string i_carpeta_imagenes_color;
	vector<string> nombres_imagenes_color;

	ayuda( );

	if( argc != 4 )
		// TODO error
		return -1;
	i_reales = argv[1];
	i_estimados = argv[2];
	i_carpeta_imagenes_color = argv[3];

	FILE* arch_reales;
	FILE* arch_estimados;


	string auxstring;
	auxstring = i_reales + ".csv";
	arch_reales = fopen(auxstring.c_str(), "r");

	auxstring = i_estimados + ".csv";
	arch_estimados = fopen(auxstring.c_str(), "r");


	// TODO: Chequear si se abrieron bien
	if( !arch_reales || !arch_estimados )
	{
		cout << "\nNo se pudo abrir algún archivo.\n";
		return -1;
	}



	// Eliminamos la última barra de la carpeta de imágenes, si se ingresó así
	 // if( *(i_nombre_archivos_resultados.end()) == "\\" || *(i_nombre_archivos_resultados.end()) == "/" )
	char ultimochar = i_carpeta_imagenes_color[i_carpeta_imagenes_color.size()-1];
	if( ultimochar == '\\' || ultimochar == '/' )	//
		i_carpeta_imagenes_color.pop_back();	// Elimina la última barra


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


	if( nombres_imagenes_color.size() == 0 )
	{
		cout << "\nNo se pudo cargar ninguna imagen. El programa ha terminado.\n";
		return -1;
	}



	unsigned int max = nombres_imagenes_color.size();



	//-----
	vector<struct_resultados> reales;
	vector<struct_resultados> estimados;
	vector<Frame> frames;


// TODO detecciones multiples...quien las elimina? resultados o detector?

	//Set;Imagen;Profundidad;Completa;Tiempo;Arriba_izq_X;Arriba_izq_Y;Arriba_der_X;Arriba_der_Y;Abajo_izq_X;Abajo_izq_Y;Abajo_der_X;Abajo_der_Y;

	struct_resultados aux;
	//char* aux_string = nullptr;
	char auxs[50];

	// Lectura reales
	while( !feof(arch_reales) )
	{
		fscanf(arch_reales, "%[^;];%u;%u;%d;%f;%u;%u;%u;%u;%u;%u;%u;%u \n",
			auxs, &aux.img, &aux.prof, &aux.comp, &aux.tiempo, &aux.arr_izq_x, &aux.arr_izq_y,
			&aux.arr_der_x, &aux.arr_der_y, &aux.aba_izq_x, &aux.aba_izq_y, &aux.aba_der_x, &aux.aba_der_y);

		aux.set = auxs;

		//cout << aux;
		aux.calcular(); // Calculamos centro, ancho, alto
		reales.push_back(aux);


	}
	fclose(arch_reales);


	// Lectura estimados
	while( !feof(arch_estimados) )
	{
		fscanf(arch_estimados, "%[^;];%u;%u;%d;%f;%u;%u;%u;%u;%u;%u;%u;%u \n",
			auxs, &aux.img, &aux.prof, &aux.comp, &aux.tiempo, &aux.arr_izq_x, &aux.arr_izq_y,
			&aux.arr_der_x, &aux.arr_der_y, &aux.aba_izq_x, &aux.aba_izq_y, &aux.aba_der_x, &aux.aba_der_y);

		aux.set = auxs;

		//cout << aux;
		aux.calcular(); // Calculamos centro, ancho, alto
		estimados.push_back(aux);
	}
	fclose(arch_estimados);


	cout << "\nSe han leído " << reales.size() << " líneas de datos reales\n"
			"y se han leído " << estimados.size() << " líneas de datos estimados.\n";


	// Asignación de reales y estimados a cada frame
	//cout << "\nmax = " << max ;
	frames.resize(max);	// Reservamos espacio
	for( unsigned int i = 0 ; i < frames.size() ; i++ )
	{
		frames.at(i).id = i+1;
		for( auto r : reales)
		{
			if( r.img == (i+1))
				frames.at(i).reales.push_back(r);
		}
		for( auto e : estimados )
		{
			if( e.img == (i+1) )
				frames.at(i).estimados.push_back(e);
		}
	}
	//TODO: no estamos avisando si hay datos que no corresponden a ninguna imagen.











	// Ordenamos. Se asigna a cada imagen el número en que se cargó y no necesariamente el número
	// de archivo. Sin embargo deberían ser iguales.
	sort( nombres_imagenes_color.begin() , nombres_imagenes_color.end() );




	Mat img_color;
	Rect auxrect;
	char c;
	namedWindow("Revision", CV_WINDOW_KEEPRATIO | CV_WINDOW_NORMAL );



	bool coincidencia = false;
	// Suponemos que todas las imagenes son del mismo set..
	// Evaluación: en cada frame comparamos:
	for( auto it_frames = frames.begin() ; it_frames != frames.end() ; it_frames++)
	{
		unsigned int i = (*it_frames).id;
		cout << "\ni = " << i;
		img_color = imread( nombres_imagenes_color.at(i-1) , IMREAD_COLOR ); // 8bit, color or not
		putText(img_color, to_string(i), Point( 2, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 2, 8);

		// Si hay personas reales marcadas,
		if( (*it_frames).reales.size() > 0 )
		{
			// a cada persona real
			for( auto it_reales = (*it_frames).reales.begin() ; it_reales != (*it_frames).reales.end() ; it_reales++)
			{
				coincidencia = false;
				//la dibujamos
				struct_resultados_a_rect( (*it_reales) , auxrect );
				rectangle(img_color, auxrect.tl(), auxrect.br(), cv::Scalar(0,0,0), 3);


				// la comparamos con todas las detecciones (que no han coincidido todavía con una persona real),
				for( auto it_estimados = (*it_frames).estimados.begin() ; it_estimados != (*it_frames).estimados.end() ; )
				{
					// y si hay coincidencia con alguna
					/*(se permiten múltiples detecciones, pero serán asignadas sólo una vez. Si hay una persona
					 * superpuesta a otra, las detecciones serán asignadas sólo a una de ellas.)*/
					if( (*it_reales) == (*it_estimados) )
					{
						// la dibujamos
						struct_resultados_a_rect( (*it_estimados) , auxrect );
						rectangle(img_color, auxrect.tl(), auxrect.br(), cv::Scalar(0,255,0), 2);


						coincidencia = true;
						// contamos la detección como un verdadero positivo
						//(*it_frames).verdaderos_positivos ++;
						// y la borramos del vector, pues ya fue contada.
						it_estimados = (*it_frames).estimados.erase(it_estimados);
					}
					else // Sólo avanza cuando no borró. En caso contrario, estaría saltando un elemento.
						it_estimados ++;
				}

				// Si no hubo coincidencia, se cuenta un falso negativo
				if( coincidencia == false )
				{
					//(*it_frames).falsos_negativos ++;
				}
			}

		}
		// Para todos los estimados que no fueron asignados
		for( auto it_estimados = (*it_frames).estimados.begin() ; it_estimados != (*it_frames).estimados.end() ; it_estimados++)
		{
			// dibujamos
			struct_resultados_a_rect( (*it_estimados) , auxrect );
			rectangle(img_color, auxrect.tl(), auxrect.br(), cv::Scalar(0,0,255),1);
		}

		imshow( "Revision" , img_color );
		c = waitKey(0);
		if( c == 'a')
			it_frames -= 2;
//		// Las detecciones que no coincidieron con ninguna persona real marcada se cuentan como falsos positivos.
//		(*it_frames).falsos_positivos = (*it_frames).estimados.size();
	}


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
		"Uso: dp_cuadros < /dir/al/archivo_de_resultados_reales > (sin extensión)\n"
		"                < /dir/al/archivo_de_resultados_estimados > (sin extensión)\n"
		"                < carpeta/con/imagenes/a/marcar >"
		"\n\n Muestra las imágenes con sus detecciones."
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
