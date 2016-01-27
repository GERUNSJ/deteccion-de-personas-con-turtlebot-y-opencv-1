#include "detector_dummy.hpp"
using namespace std;

DetectorDummy::DetectorDummy(vector<string>argumentos_nombre, vector<string>argumentos_valor)
{
	unsigned int n = argumentos_nombre.size();
	if( n != cantidad_de_argumentos )
	{
		//error
	}

	unsigned int j = 0;
	for( unsigned int i = 0 ; i < n ; i++ )
	{
		if( argumentos_nombre.at(i) == "parametro1")
		{
			this->parametro1 = stoi((argumentos_valor.at(i)),nullptr,10);
			j++;
		}

		if( argumentos_nombre.at(i) == "parametro2")
		{
			this->parametro2 = stoi(argumentos_valor.at(i),nullptr,10);
			j++;
		}

		if( argumentos_nombre.at(i) == "parametro3")
		{
			this->parametro3 = (argumentos_valor.at(i)).at(0);
			j++;
		}

		if( argumentos_nombre.at(i) == "parametro4")
		{
			this->parametro4 = argumentos_valor.at(i);
			j++;
		}

	}
	if( j != n ) // No se cargaron todos los parámetros
	{
		// Error? Podrían tener valores por defecto. O comprobar solo algunos.
	}
	parametros_nombre.push_back("parametro1");
	parametros_valor.push_back(to_string(parametro1));
	parametros_nombre.push_back("parametro2");
	parametros_valor.push_back(to_string(parametro2));
	parametros_nombre.push_back("parametro3");
	parametros_valor.push_back(to_string(parametro3));
	parametros_nombre.push_back("parametro4");
	parametros_valor.push_back(parametro4);
}

DetectorDummy::~DetectorDummy()
{
}

void DetectorDummy::detectar()
{
}


