#ifndef DP_DETECTOR_H
#define DP_DETECTOR_H

#include "resultados.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
#include <string>

// Clase padre detector. Las subclases deberán implementar los métodos declarados como virtuales.
// No hay un constructor genérico por las dudas...Aunque tal vez debería haber uno.
class Detector
{
public:
	// Pensado para verificar si la cantidad de argumentos pasados está bien. Mejor usar valores
	// por defecto en caso de que no se pase alguno.
	unsigned int cantidad_de_argumentos; // No está en uso.

	// Nombre del detector. Se imprime en los resultados. Asignar en constructor.
	std::string nombre;

	// Vectores de string para luego imprimir los parámetros. Los valores deben ser asignados al
	// crear el constructor. Los pares nombre-valor están asociados por índice.
	std::vector<std::string> parametros_nombre;
	std::vector<std::string> parametros_valor;

	//
	virtual void detectar(const cv::Mat& i_img_color, const cv::Mat& i_img_profundidad, std::vector<struct_resultados>& i_res) = 0;

	//
	//virtual void detectar(const cv::Mat& i_img_color, const cv::Mat& i_img_profundidad, std::vector<struct_resultados>& i_res);

	// Sobrecarga de << para imprimir los resultados.
	// Se declara como friend para que pueda acceder a los miembros privados. [DUDA] Por qué
	// no hacerla función pública? De cualquier manera no hay miembros privados.
	friend std::ostream& operator<<(std::ostream& os, Detector& detector );

	// Destructor
	virtual ~Detector() = 0;
private:
};


std::ostream& operator<<( std::ostream& os, Detector& detector );



#endif // DP_DETECTOR_H
