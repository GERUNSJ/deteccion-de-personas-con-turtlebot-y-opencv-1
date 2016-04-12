#include "detector.hpp"

using namespace std;

Detector::~Detector()
{
}


ostream& operator<<( ostream& os, Detector& detector )
{
	unsigned int i = 0;
	string aux;
	aux += string("El detector usado fue ") += detector.nombre += "\n";
	for( i = 0; i < detector.parametros_nombre.size() ; i++ )
	{
		aux += detector.parametros_nombre.at(i) + "\t" + detector.parametros_valor.at(i) + "\n";
	}

	aux += "\n";

	// Imprimimos estilo csv para luego importar a tabla
	// Nombres
	for( i = 0; i < detector.parametros_nombre.size() ; i++ )
	{
		aux += detector.parametros_nombre.at(i) + ";" ;
	}
	aux += "\n";
	//aux += detector.parametros_nombre.at(i) + "\n" ; // último elemento

	// Valores
	for( i = 0; i < detector.parametros_valor.size() ; i++ )
	{
		aux += detector.parametros_valor.at(i) + ";" ;
	}
	aux += "\n";
	//aux += detector.parametros_valor.at(i) + "\n" ; // último elemento

	return os << aux;
}



