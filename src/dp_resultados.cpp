//----------------------------------------------------------------------------------------------
// Includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include "resultados.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	string i_reales;	// Ruta y nombre del archivo de los datos reales, con extensión
	string i_estimados;	// Ruta y nombre del archivo de los datos estimados, con extensión
	string i_resultados;// Ruta y nombre del archivo de los resultados generados, con extensión

	// TODO ayuda

	if( argc != 4 )
		// TODO error
		return -1;
	i_reales = argv[1];
	i_estimados = argv[2];
	i_resultados = argv[3];

//	fstream stream_reales, stream_estimados, stream_resultados;
//	stream_reales.open(i_reales.c_str(), ios::in );
//	stream_estimados.open(i_estimados.c_str(), ios::in);
//	stream_resultados.open(i_resultados.c_str(), ios::out);
	FILE* arch_reales;
	FILE* arch_estimados;
	fstream stream_resultados;

	arch_reales = fopen(i_reales.c_str(), "r");
	arch_estimados = fopen(i_estimados.c_str(), "r");
	stream_resultados.open(i_resultados.c_str(), ios::out);
	// TODO: Chequear si se abrieron bien

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
			"y se han le[ido " << estimados.size() << " líneas de datos estimados.\n";


	// Asignación de reales y estimados a cada frame
	cout << "\nmax = " << max ;
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

	cout << "\n\n\n\n-----------\n";

	unsigned int vpos = 0;
	unsigned int fpos = 0;
	unsigned int fneg = 0;

	for( auto f: frames )
	{
		vpos += f.verdaderos_positivos;
		fpos += f.falsos_positivos;
		fneg += f.falsos_negativos;
	}

	stream_resultados << "Imagenes analizadas" << "\t" << max << endl;
	stream_resultados << "Total de detecciones" << "\t" << vpos + fpos << endl;
	stream_resultados << "Verdaderos positivos" << "\t" << vpos << endl;
	stream_resultados << "Falsos positivos" << "\t" << fpos << endl;
	stream_resultados << "Falsos negativos" << "\t" << fneg << endl;

	stream_resultados.close();

	//stream_resultados
	cout << "\nImagenes analizadas: " << max;
	cout << "\nTotal de detecciones: " << vpos + fpos;
	cout << "\nVerdaderos positivos = " << vpos;
	cout << "\nFalsos positivos = " << fpos;
	cout << "\nFalsos negativos = " << fneg;

	// TODO: Qué hacemos con las personas incompletas? Podrían descartarse las imágenes

	stream_resultados.close();
	cout << "\n\nEl programa ha terminado.\n\n";
	return 0;
}
