//----------------------------------------------------------------------------------------------
// Includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "resultados.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	string i_reales;	// Ruta y nombre del archivo de los datos reales, con extensión
	string i_estimados;	// Ruta y nombre del archivo de los datos estimados, con extensión
	string i_resultados;// Ruta y nombre del archivo de los resultados generados, con extensión

	if( argc != 4 )
		// TODO error
		return -1;
	i_reales = argv[1];
	i_estimados = argv[2];
	i_resultados = argv[3];

	fstream stream_reales, stream_estimados, stream_resultados;
	stream_reales.open(i_reales.c_str(), ios::in );
//
//	string aux = i_nombre_archivos_resultados + ".csv"; // Append con +
//	stream_archivo_csv.open(aux.c_str(), ios::out | ios::app); // Salida, append(añadir)

	return 0;
}
