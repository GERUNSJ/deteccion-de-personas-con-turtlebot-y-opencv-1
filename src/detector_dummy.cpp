#include "detector_dummy.hpp"


using namespace std;
using namespace cv;


// Este detector no hace nada. Para mejor ejemplo, mirar el detector HOG.
DetectorDummy::DetectorDummy(vector<string>argumentos_nombre, vector<string>argumentos_valor)
{
	this->nombre = "DetectorDummy";	// Se imprime en la información del detector.
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

		else if( argumentos_nombre.at(i) == "parametro2")
		{
			this->parametro2 = stoi(argumentos_valor.at(i),nullptr,10);
			j++;
		}

		else if( argumentos_nombre.at(i) == "parametro3")
		{
			this->parametro3 = (argumentos_valor.at(i)).at(0);
			j++;
		}

		else if( argumentos_nombre.at(i) == "parametro4")
		{
			this->parametro4 = argumentos_valor.at(i);
			j++;
		}

		else
		{
			cout << "\nNo se reconoció el parámetro " << argumentos_nombre.at(i) << " pasado como argumento." << endl;
		}

	}
	if( j != n ) // No se cargaron todos los parámetros
	{
		// Error? Podrían tener valores por defecto. O comprobar solo algunos.
	}

	// Se cargan los nombres (string) de los parámetros del detector.
	// Estos son los que luegos se escriben en el archivo de información txt
	parametros_nombre.push_back("parametro1");
	parametros_valor.push_back(to_string(parametro1));
	parametros_nombre.push_back("parametro2");
	parametros_valor.push_back(to_string(parametro2));
	parametros_nombre.push_back("parametro3");
	string aux;
	aux.push_back(parametro3);
	parametros_valor.push_back(aux);
	parametros_nombre.push_back("parametro4");
	parametros_valor.push_back(parametro4);
}



// Destructor bobo
DetectorDummy::~DetectorDummy()
{
}



void DetectorDummy::detectar(const Mat& i_img,  vector<struct_resultados>& i_res)
{
	for( int i = 0 ; i < 3 ; i++) // Simulamos 3 detecciones.
	{
		struct_resultados aux;

		aux.aba_der_x = 1;
		aux.aba_der_y = 2;
		aux.aba_izq_x = 3;
		aux.aba_izq_y = 4;
		aux.arr_der_x = 5;
		aux.arr_der_y = 6;
		aux.arr_izq_x = 7;
		aux.arr_izq_y = 8;
		aux.comp = 1;
		//aux.img = 4;
		aux.prof = 8;
		//aux.set = 1;
		aux.tiempo = 222;
		i_res.push_back(aux);
	}

	return;
}


