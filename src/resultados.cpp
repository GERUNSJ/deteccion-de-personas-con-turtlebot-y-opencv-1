#include "resultados.hpp"

#define P_RADIO	0.5	// Proporción del ancho real a ser tolerado como máximo al comparar distancias entre centros
#define P_ANCHO 0.5	// Crecimiento o decrecimiento relativo proporcional máximo tolerado. Recordar que algunos detectores están entrenados con un poco de background.
#define P_ALTO	0.5	//

std::ostream& operator<<( std::ostream& os, const struct_resultados& res )
{
	return os << res.set << ";" << res.img << ";" << res.prof << ";" << res.comp << ";" <<
			res.tiempo << ";" << res.arr_izq_x << ";" << res.arr_izq_y << ";" <<
			res.arr_der_x << ";" << res.arr_der_y << ";" << res.aba_izq_x << ";" <<
			res.aba_izq_y << ";" << res.aba_der_x << ";" << res.aba_der_y << /*";" <<*/ std::endl;
}



void rect_a_struct_resultados(const cv::Rect rect, struct_resultados& res)
{
	// OpenCV typically assumes that the top and left boundary of the rectangle are inclusive,
	// while the right and bottom boundaries are not. (de la documentación de Rect_ en core)
	// Sea un punto pt, pertenece al rect si
	// x <= pt.x < x+width
	// y <= pt.y < y+height
	// Por lo tanto nosotros tenemos que restar 1
    res.aba_der_x = rect.x + rect.width - 1;
    res.aba_der_y = rect.y + rect.height - 1;
    res.aba_izq_x = rect.x;
    res.aba_izq_y = rect.y + rect.height - 1;
    res.arr_der_x = rect.x + rect.width - 1;
    res.arr_der_y = rect.y;
    res.arr_izq_x = rect.x;
    res.arr_izq_y = rect.y;
}
// TODO: Hacer una struct_resultados_a_rect

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
