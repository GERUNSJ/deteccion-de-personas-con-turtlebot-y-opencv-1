#include "detector.hpp"

using namespace std;

Detector::~Detector()
{
}



ostream& operator<<( ostream& os, Detector& detector )
{
	string aux;
	aux += string("El detector usado fue ") += detector.nombre += "\n";
	for( unsigned int i = 0; i < detector.parametros_nombre.size() ; i++ )
	{
		aux += detector.parametros_nombre.at(i) + "\t" + detector.parametros_valor.at(i) + "\n";
	}
	return os << aux;
}
