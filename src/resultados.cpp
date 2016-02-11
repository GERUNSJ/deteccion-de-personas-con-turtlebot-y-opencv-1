#include "resultados.hpp"

std::ostream& operator<<( std::ostream& os, const struct_resultados& res )
{
	return os << res.set << ";" << res.img << ";" << res.prof << ";" << res.comp << ";" <<
			res.tiempo << ";" << res.arr_izq_x << ";" << res.arr_izq_y << ";" <<
			res.arr_der_x << ";" << res.arr_der_y << ";" << res.aba_izq_x << ";" <<
			res.aba_izq_y << ";" << res.aba_der_x << ";" << res.aba_der_y << std::endl;
}



void rect_a_struct_resultados(const cv::Rect rect, struct_resultados& res)
{
    res.aba_der_x = rect.x + rect.width;
    res.aba_der_y = rect.y + rect.height;
    res.aba_izq_x = rect.x;
    res.aba_izq_y = rect.y + rect.height;
    res.arr_der_x = rect.x + rect.width;
    res.arr_der_y = rect.y;
    res.arr_izq_x = rect.x;
    res.arr_izq_y = rect.y;
}


void struct_resultados::calcular()
{
	ancho = aba_der_x - aba_izq_x + 1;
	alto = aba_der_y - arr_der_y + 1;

	centro_x = ancho/2;
	centro_y = alto/2;
}


// Importante el orden de los operadores..
bool operator==(const struct_resultados& real, const struct_resultados& est)
{
	float distancia = sqrt( powf((real.centro_x-est.centro_x),2) + powf((real.centro_y-est.centro_y),2) );
	if( distancia < P_RADIO*real.ancho )
		if( abs(est.ancho - real.ancho)/real.ancho  <  P_ANCHO )	// est.ancho < P_ANCHO*real.ancho
			if( abs(est.alto - real.alto)/real.alto  <  P_ALTO )
				return true;
	return false;
}
