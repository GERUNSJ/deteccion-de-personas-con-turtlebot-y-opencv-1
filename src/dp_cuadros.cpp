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
	string i_carpeta_imagenes_color;
	vector<string> nombres_imagenes_color;

	ayuda( );

	if( argc != 3 )
		// TODO error
		return -1;
	i_reales = argv[1];
	i_carpeta_imagenes_color = argv[2];

	FILE* arch_reales;


	string auxstring;
	auxstring = i_reales + ".csv";
	arch_reales = fopen(auxstring.c_str(), "r");


	// TODO: Chequear si se abrieron bien
	if( !arch_reales )
	{
		cout << "\nNo se pudo abrir algún archivo.\n";
		return -1;
	}

	//-----
	vector<struct_resultados> reales;
	//vector<Frame> frames;

	unsigned int max = 0;


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

		if( aux.img > max )
			max = aux.img;
	}
	fclose(arch_reales);



	cout << "\nSe han leído " << reales.size() << " líneas de datos reales\n";



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


	// Ordenamos. Se asigna a cada imagen el número en que se cargó y no necesariamente el número
	// de archivo. Sin embargo deberían ser iguales.
	sort( nombres_imagenes_color.begin() , nombres_imagenes_color.end() );


	//
	//	// Asignación de reales y estimados a cada frame
	//	//cout << "\nmax = " << max ;
	//	frames.resize(max);	// Reservamos espacio
	//	for( unsigned int i = 0 ; i < frames.size() ; i++ )
	//	{
	//		for( auto r : reales)
	//		{
	//			if( r.img == (i+1))
	//				frames.at(i).reales.push_back(r);
	//		}
	//		for( auto e : estimados )
	//		{
	//			if( e.img == (i+1) )
	//				frames.at(i).estimados.push_back(e);
	//		}
	//	}

	Mat img_color;
	Rect auxrect;
	char c;
	namedWindow("Revision", CV_WINDOW_KEEPRATIO | CV_WINDOW_NORMAL );

	for( unsigned int i = 0; i < nombres_imagenes_color.size() ; i++ )
	{
		img_color = imread( nombres_imagenes_color.at(i) , IMREAD_COLOR ); // 8bit, color or not

		for( auto r : reales )
		{
			if( r.img == i+1 )
			{
				struct_resultados_a_rect( r , auxrect );
				rectangle(img_color, auxrect.tl(), auxrect.br(), cv::Scalar(0,255,0), 2);
				// Se podría optimizar borrando los reales que ya se usaron.
			}

		}
		//C++: void putText(Mat& img, const string& text, Point org, int fontFace, double fontScale,
		// Scalar color, int thickness=1, int lineType=8, bool bottomLeftOrigin=false )
		putText(img_color, to_string(i+1), Point( 2, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 2, 8);
		imshow( "Revision" , img_color );
		c = waitKey(0);
		if( c == 'a')
			i = i-2;
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
		"Uso: dp_cuadros < /dir/al/archivo_de_resultados > (sin extensión)\n"
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
