#include "resultados.hpp"

std::ostream& operator<<( std::ostream& os, const struct_resultados& res )
{
	return os << res.set << ";" << res.img << ";" << res.prof << ";" << res.comp << ";" <<
			res.tiempo << ";" << res.arr_izq_x << ";" << res.arr_izq_y << ";" <<
			res.arr_der_x << ";" << res.arr_der_y << ";" << res.aba_izq_x << ";" <<
			res.aba_izq_y << ";" << res.aba_der_x << ";" << res.aba_der_y << std::endl;
}
