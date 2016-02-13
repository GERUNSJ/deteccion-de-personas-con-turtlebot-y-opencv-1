//----------------------------------------------------------------------------------------------
// Includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include "resultados.hpp"

static void ayuda();

using namespace std;

int main(int argc, char* argv[])
{
	string i_reales;	// Ruta y nombre del archivo de los datos reales, sin extensión
	string i_estimados;	// Ruta y nombre del archivo de los datos estimados, sin extensión
	string i_resultados;// Ruta y nombre del archivo de los resultados generados, con extensión

	ayuda( );

	if( argc != 4 )
		// TODO error
		return -1;
	i_reales = argv[1];
	i_estimados = argv[2];
	i_resultados = argv[3];

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
	stream_resultados.open(i_resultados.c_str(), ios::out);

	// TODO: Chequear si se abrieron bien
	if( !arch_reales || !arch_estimados || !stream_info || !stream_resultados )
	{
		cout << "\nNo se pudo abrir algún archivo.\n";
		return -1;
	}

	//-----
	vector<struct_resultados> reales;
	vector<struct_resultados> estimados;
	vector<Frame> frames;

	unsigned int max = 0;

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

		if( aux.img > max )
			max = aux.img;
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

	// Calculamos el tiempo promedio
	double tiempo_promedio = 0;
	for( auto e : estimados )
		tiempo_promedio += e.tiempo;
	tiempo_promedio /= estimados.size();


	bool coincidencia = false;
	// Suponemos que todas las imagenes son del mismo set..
	// Evaluación: en cada frame comparamos:
	for( auto& f : frames )	// Range-based for. Atento al & para pasar por referencia.
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

	cout << "\n-----------\n";

	unsigned int vpos = 0;
	unsigned int fpos = 0;
	unsigned int fneg = 0;

	for( auto f: frames )
	{
		vpos += f.verdaderos_positivos;
		fpos += f.falsos_positivos;
		fneg += f.falsos_negativos;
	}
	float miss_rate = (float)fneg/(vpos+fneg);
	float FPPW = (float)fpos/max;
	float cociente = 100*miss_rate/FPPW;

	// SALIDA
	size_t pos_barra = i_reales.find_last_of("/\\"); // Encuentra la última barra
	string nombre_reales = i_reales.substr(pos_barra +1);
	pos_barra = i_estimados.find_last_of("/\\"); // Encuentra la última barra
	string nombre_estimados = i_estimados.substr(pos_barra + 1);

	stream_resultados << "Archivo estimados" << "\t" << nombre_estimados << endl;
	stream_resultados << "Archivo reales" << "\t" << nombre_reales << endl;
	stream_resultados << endl;
	stream_resultados << "Imagenes analizadas" << "\t" << max << endl;
	stream_resultados << "Total de detecciones" << "\t" << vpos + fpos << endl;
	stream_resultados << "Verdaderos positivos" << "\t" << vpos << endl;
	stream_resultados << "Falsos positivos" << "\t" << fpos << endl;
	stream_resultados << "Falsos negativos" << "\t" << fneg << endl;
	stream_resultados << endl;
	stream_resultados << "Miss rate" << "\t" << miss_rate << endl;
	stream_resultados << "FPPW" << "\t" << FPPW << endl;
	stream_resultados << "100*Miss rate / FPPW" << "\t" << cociente << endl;
	stream_resultados << endl;
	stream_resultados << "Tiempo promedio de detección" << "\t" << tiempo_promedio << " ms" << endl;

	stream_resultados << "\n\n--------------------\n\n";

	// Copiamos la información del detector usado
	while( !stream_info.eof() )
	{
		getline(stream_info, auxstring);
		stream_resultados << auxstring << "\n";
	}

	stream_resultados.close();

	//stream_resultados
	cout << "\nImagenes analizadas: " << max;
	cout << "\nTotal de detecciones: " << vpos + fpos;
	cout << "\nVerdaderos positivos = " << vpos;
	cout << "\nFalsos positivos = " << fpos;
	cout << "\nFalsos negativos = " << fneg;
	cout << "\nMiss rate = " << miss_rate;
	cout << "\nFPPW = " << FPPW;
	cout << "\n100*Miss rate / FPPW = " << cociente;
	cout << "\nTiempo promedio de detección: " << tiempo_promedio << " ms" << endl;

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
					"Uso: dp_resultados /ruta/a/datos_reales (sin extensión)\n"
					"                   /ruta/a/datos_estimados (sin extensión)\n"
					"                   /ruta/a/archivo_de_resultados.txt (con extensión)\n";
	cout	<< "\n------------------------------------------------------------------------------------------------------------------\n";

	return;
}
