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

