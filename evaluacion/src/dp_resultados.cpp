//----------------------------------------------------------------------------------------------
// Includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include "resultados.hpp"

// Para readDirectory
#if defined(WIN32) || defined(_WIN32)
#include <io.h>
#else
#include <dirent.h>
#endif

using namespace std;


static void ayuda();

static void readDirectory(const string& directoryName,
		vector<string>& filenames, bool addDirectoryName = true);



int main(int argc, char* argv[])
{
	string i_carpeta_imagenes_color;
	string i_reales;	// Ruta y nombre del archivo de los datos reales, sin extensión
	string i_estimados;	// Ruta y nombre del archivo de los datos estimados, sin extensión
	string i_resultados;// Ruta y nombre del archivo de los resultados generados, con extensión
	vector<string> nombres_imagenes_color;

	ayuda( );

	if( argc != 5 )
		// TODO error
		return -1;
	i_carpeta_imagenes_color = argv[1];
	i_reales = argv[2];
	i_estimados = argv[3];
	i_resultados = argv[4];

//	cout << i_reales << endl;
//	cout << i_estimados << endl;
//	cout << i_resultados << endl;

//	fstream stream_reales, stream_estimados, stream_resultados;
//	stream_reales.open(i_reales.c_str(), ios::in );
//	stream_estimados.open(i_estimados.c_str(), ios::in);
//	stream_resultados.open(i_resultados.c_str(), ios::out);
	FILE* arch_reales;
	FILE* arch_estimados;
	fstream stream_resultados;
	fstream stream_info;

	string auxstring;
	auxstring = i_reales + ".csv";
	arch_reales = fopen(auxstring.c_str(), "r");
	auxstring = i_estimados + ".csv";
	arch_estimados = fopen(auxstring.c_str(), "r");
	auxstring = i_estimados + ".txt";
	stream_info.open(auxstring.c_str(), ios::in);
	stream_resultados.open(i_resultados.c_str(), ios::out | ios::trunc); // Salida y borrar lo que ya exista

	// TODO: Chequear si se abrieron bien
	if( !arch_reales || !arch_estimados || !stream_info || !stream_resultados )
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


//	for(  unsigned int i = 0 ; i < frames.size() ; i++  )
//	{
//		cout << "\nframe: " << i << "\treales: " << frames.at(i).reales.size() <<
//				"\testimados: " << frames.at(i).estimados.size();
//	}

	// Calculamos el tiempo promedio en ms
	double tiempo_promedio = 0;
	for( auto e : estimados )
		tiempo_promedio += e.tiempo;
	tiempo_promedio /= estimados.size();


	bool coincidencia = false;
	// Suponemos que todas las imagenes son del mismo set..
	// Evaluación: en cada frame comparamos:
	for( auto it_frames = frames.begin() ; it_frames != frames.end() ; it_frames++)
	{
		// Si hay personas reales marcadas,
		if( (*it_frames).reales.size() > 0 )
		{
			// a cada persona real
			for( auto it_reales = (*it_frames).reales.begin() ; it_reales != (*it_frames).reales.end() ; it_reales++)
			{
				coincidencia = false;

				// la comparamos con todas las detecciones (que no han coincidido todavía con una persona real),
				for( auto it_estimados = (*it_frames).estimados.begin() ; it_estimados != (*it_frames).estimados.end() ; )
				{
					// y si hay coincidencia con alguna
					/*(se permiten múltiples detecciones, pero serán asignadas sólo una vez. Si hay una persona
					 * superpuesta a otra, las detecciones serán asignadas sólo a una de ellas.)*/
					if( (*it_reales) == (*it_estimados) )
					{
						coincidencia = true;
						// contamos la detección como un verdadero positivo
						(*it_frames).verdaderos_positivos ++;
						// y la borramos del vector, pues ya fue contada.
						it_estimados = (*it_frames).estimados.erase(it_estimados);
					}
					else // Sólo avanza cuando no borró. En caso contrario, estaría saltando un elemento.
						it_estimados ++;
				}

				// Si no hubo coincidencia, se cuenta un falso negativo
				if( coincidencia == false )
				{
					(*it_frames).falsos_negativos ++;
				}
			}
		}

		// Las detecciones que no coincidieron con ninguna persona real marcada se cuentan como falsos positivos.
		(*it_frames).falsos_positivos = (*it_frames).estimados.size();
	}

	/* Lo siguiente es lo mismo de arriba, pero implementado con range-based for. Lo dejo para futura referencia. Nótese
	 * su simplicidad. El for más interno (for( auto& e: f.estimados )) elimina elementos adentro, EL PROBLEMA ES QUE EL RANGE-BASED-FOR NO
	 * ESTÁ PREPARADO PARA ESTO. POR TANTO, SALTEA ELEMENTOS.
	 */
	/*for( auto& f : frames )	// Range-based for. Atento al & para pasar por referencia.
	{
		if( f.reales.size() > 0 )
		{
			// A cada persona real
			for( auto& r: f.reales)
			{
				coincidencia = false;
				// la comparamos con todas las detecciones
				for( auto& e: f.estimados )
				{
					// y si es correcto
					if( r == e )
					{
						coincidencia = true;
						//cout << "\n iguales";
						f.verdaderos_positivos ++;
						// eliminamos el elemento del vector
						f.estimados.pop_back();
					}
				}
				// Si no coincidió con niguna detección, es un falso negativo
				if( coincidencia == false )
					f.falsos_negativos ++;
				// una vez comparado con todos, eliminamos el elemento del vector
				f.reales.pop_back(); // Esto es innecesario..
			}
		}
		// y al final:
		f.falsos_positivos = f.estimados.size();
//		cout << "\nVerdaderos positivos = " << f.verdaderos_positivos;
//		cout << "\nFalsos positivos = " << f.falsos_positivos;
//		cout << "\nFalsos negativos = " << f.falsos_negativos;
	}
	*/

	cout << "\n-----------\n";

	unsigned int vpos = 0;
	unsigned int fpos = 0;
	unsigned int fneg = 0;

	for( auto& f: frames )
	{
		vpos += f.verdaderos_positivos;
		fpos += f.falsos_positivos;
		fneg += f.falsos_negativos;
	}
	float miss_rate = (float)fneg/(vpos+fneg);
	float FPPW = (float)fpos/max;
	float metrica1 = 100*miss_rate*FPPW;
	float metrica2 = 100*miss_rate*FPPW*tiempo_promedio;
	float metrica3 = miss_rate*tiempo_promedio; // En caso de FPPW = 0
	float precision = (float)vpos / (vpos + fpos); // De los que encontró, cuantos son buenos
	float recall = (float)vpos / (vpos + fneg); // De los buenos, cuantos encontró
	float metrica4 = precision*recall;
	float metrica5 = 2*(precision*recall)/(precision+recall); // F1
	float metrica6 = 100.0* metrica5 / tiempo_promedio;
	float metrica7 = (1+0.25)*precision*recall/((0.25*precision)+recall); // F0.5

	// SALIDA
	size_t pos_barra = i_reales.find_last_of("/\\"); // Encuentra la última barra
	string nombre_reales = i_reales.substr(pos_barra +1);
	pos_barra = i_estimados.find_last_of("/\\"); // Encuentra la última barra
	string nombre_estimados = i_estimados.substr(pos_barra + 1);


	vector<string> informe_nombres;
	vector<string> informe_valores;

	// Llenado
	informe_nombres.push_back("Archivo estimados");
	informe_valores.push_back(nombre_estimados);

	informe_nombres.push_back("Archivo reales");
	informe_valores.push_back(nombre_reales);

	informe_nombres.push_back("Imagenes analizadas");
	informe_valores.push_back(to_string(max));

	informe_nombres.push_back("Total de detecciones");
	informe_valores.push_back(to_string( vpos + fpos ));

	informe_nombres.push_back("Verdaderos positivos");
	informe_valores.push_back(to_string(vpos));

	informe_nombres.push_back("Falsos positivos");
	informe_valores.push_back(to_string( fpos ));

	informe_nombres.push_back("Falsos negativos");
	informe_valores.push_back(to_string( fneg ));

	informe_nombres.push_back("Miss rate: fneg/(vpos+fneg)");
	informe_valores.push_back(to_string( miss_rate ));

	informe_nombres.push_back("Miss rate * tiempo promedio");
	informe_valores.push_back(to_string( metrica3 ));

	informe_nombres.push_back("FFPW");
	informe_valores.push_back(to_string( FPPW ));

	informe_nombres.push_back("100*Miss rate * FPPW");
	informe_valores.push_back(to_string( metrica1 ));

	informe_nombres.push_back("100*Miss rate * FPPW * tiempo promedio");
	informe_valores.push_back(to_string( metrica2 ));

	informe_nombres.push_back("Tiempo promedio de detección");
	informe_valores.push_back(to_string( tiempo_promedio ));

	informe_nombres.push_back("precision: vpos/(vpos+fpos)");
	informe_valores.push_back(to_string( precision ));

	informe_nombres.push_back("recall: vpos/(vpos+fneg)");
	informe_valores.push_back(to_string( recall ));

	informe_nombres.push_back("precision*recall");
	informe_valores.push_back(to_string( metrica4 ));

	informe_nombres.push_back("F1: 2*(precision*recall)/(precision+recall)");
	informe_valores.push_back(to_string( metrica5 ));

	informe_nombres.push_back("100*F1/tiempo promedio");
	informe_valores.push_back(to_string( metrica6 ));

	informe_nombres.push_back("F0.5: (1+0.25)*precision*recall/((0.25*precision)+recall)");
	informe_valores.push_back(to_string( metrica7 ));


//	informe_nombres.push_back("");
//	informe_valores.push_back(to_string(  ));


//	stream_resultados << "Archivo estimados" << "\t" << nombre_estimados << endl;
//	stream_resultados << "Archivo reales" << "\t" << nombre_reales << endl;
//	stream_resultados << endl;
//	stream_resultados << "Imagenes analizadas" << "\t" << max << endl;
//	stream_resultados << "Total de detecciones" << "\t" << vpos + fpos << endl;
//	stream_resultados << "Verdaderos positivos" << "\t" << vpos << endl;
//	stream_resultados << "Falsos positivos" << "\t" << fpos << endl;
//	stream_resultados << "Falsos negativos" << "\t" << fneg << endl;
//	stream_resultados << endl;
//	stream_resultados << "Miss rate: fneg/(vpos+fneg)" << "\t" << miss_rate << endl;
//	stream_resultados << "Miss rate * tiempo promedio" << "\t" << metrica3 << endl;
//	stream_resultados << "FPPW" << "\t" << FPPW << endl;
//	stream_resultados << "100*Miss rate * FPPW" << "\t" << metrica1 << endl;
//	stream_resultados << "100*Miss rate * FPPW * tiempo promedio" << "\t" << metrica2 << endl;
//	stream_resultados << endl;
//	stream_resultados << "Tiempo promedio de detección" << "\t" << tiempo_promedio << " ms" << endl;

	// Para facil lectura en txt, y para mostrar en pantalla
	unsigned int i = 0;
	for( i = 0 ; i < informe_nombres.size() ; i++)
	{
		stream_resultados << informe_nombres.at(i) << " = " << informe_valores.at(i) << endl;
		cout << informe_nombres.at(i) << " = " << informe_valores.at(i) << endl;
	}

	stream_resultados << "\n\n--------------------\n\n";

	// Copiamos la información del detector usado
	while( !stream_info.eof() )
	{
		getline(stream_info, auxstring);
		stream_resultados << auxstring << "\n";
	}

	// Imprimimos estilo csv para luego importar a tabla
	// Nombres
	for( i = 0 ; i < informe_nombres.size() ; i++)
	{
		stream_resultados << informe_nombres.at(i) << ";" ;
	}

	stream_resultados << "\n" ;

	// Valores
	for( i = 0 ; i < informe_valores.size() ; i++)
	{
		stream_resultados << informe_valores.at(i) << ";" ;
	}
	//stream_resultados << informe_valores.at(i); // último



	stream_resultados.close();

	//stream_resultados
//	cout << "\nImagenes analizadas: " << max;
//	cout << "\nTotal de detecciones: " << vpos + fpos;
//	cout << "\nVerdaderos positivos = " << vpos;
//	cout << "\nFalsos positivos = " << fpos;
//	cout << "\nFalsos negativos = " << fneg;
//	cout << "\nMiss rate: fneg/(vpos+fneg) = " << miss_rate;
//	cout << "\nMiss rate * tiempo promedio = " << metrica3;
//	cout << "\nFPPW = " << FPPW;
//	cout << "\n100*Miss rate * FPPW = " << metrica1;
//	cout << "\n100*Miss rate * FPPW * tiempo promedio = " << metrica2;
//	cout << "\nTiempo promedio de detección: " << tiempo_promedio << " ms" << endl;

	// TODO: Qué hacemos con las personas incompletas? Podrían descartarse las imágenes

	stream_resultados.close();
	cout << "\n\nEl programa ha terminado.\n\n";
	return 0;
}


// ----------


// AYUDA
static void ayuda()
{
	cout	<< "\n------------------------------------------------------------------------------------------------------------------\n";
	cout
			<< "\nDetección de personas en opencv para Turtlebot - Fabricio Emder, Pablo Aguado - 2016\n"
					"Uso: dp_resultados /ruta/a/set/de/imagenes\n"
					"                   /ruta/a/datos_reales (sin extensión)\n"
					"                   /ruta/a/datos_estimados (sin extensión)\n"
					"                   /ruta/a/archivo_de_resultados.txt (con extensión)\n";
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

