#include "extractor.hpp"
using namespace std;
using namespace cv;

//--------------------------------------------------------------
// Globales [DUDA] ¿Podrían ser static dentro de la función?
Mat img_orig;
Mat recorte;
string ventana_imagen = "Seleccionar personas";
bool primerclick = false;
Rect roi;
//--------------------------------------------------------------


void onMouse( int event, int x, int y, int flags, void* i_aux_res);





Extractor::Extractor()
{
	this->nombre = "Extractor";
}




Extractor::~Extractor()
{
}



void Extractor::detectar(const Mat& i_img,  vector<struct_resultados>& i_res)
{
	img_orig = i_img.clone();
	struct_resultados aux_res;
	// Mostrar imagen

	namedWindow(ventana_imagen, CV_WINDOW_KEEPRATIO | CV_WINDOW_NORMAL);

    setMouseCallback( ventana_imagen, onMouse, &aux_res ); // El último argumento es un puntero a los datos del usuario

    imshow(ventana_imagen, img_orig);

    unsigned int i = 0;

    char c = 'a';

    // Hasta que aprete enter
    while( c != '\n')	// enter
    {
    	cout << "\nSeleccionar cada una de las personas de la imagen. Seleccionar una persona con dos clicks y apretar espacio.\n"
    			<< "Cuando haya terminado, apretar enter.\n";
    	c = waitKey(0);

    	// Espacio guarda a la persona marcada
    	if( c == ' ' ) // espacio
    	{
    		// Guardar selección como resultado
    		i ++;
    		//i_res.push_back( aux_res );

			cout << "\nSi la persona está completa, de pies a cabeza, apretar 'y', y si no, apretar 'n'.\n";
			while( c != 'y' && c != 'n' )
				c = waitKey(0);

			if( c == 'y' )
				aux_res.comp = 1;
			else
				aux_res.comp = 0;

			// Completamos los datos
			aux_res.tiempo = 0;
			if( i_img.depth() == CV_8U || i_img.depth() == CV_8S )
				aux_res.prof = 8;
			else
				aux_res.prof = 16;

			// Guardamos en el arreglo
			i_res.push_back(aux_res);
    	}
    }


	return;
}


 

void onMouse( int event, int x, int y, int flags, void* i_aux_res)
{

	struct_resultados* aux_res = (struct_resultados*)i_aux_res;

	// No vamos a modificar la original
	Mat img_mouse = img_orig.clone();
//	int ancho;
//	int alto;
	Point punto;
	static Point punto1;
	static Point punto2;
	punto.x = x;
	punto.y = y;
	if( event == EVENT_MOUSEMOVE)
	{
		//cout << "...";
		line( img_mouse, Point2i(punto.x,0), Point2i(punto.x,img_mouse.rows-1), Scalar(0,255,0), 1 ); // Línea vertical
		line( img_mouse, Point2i(0,punto.y), Point2i(img_mouse.cols-1,punto.y), Scalar(0,255,0), 1); // Línea horizontal
		imshow(ventana_imagen, img_mouse);
	}
	else if ( event == EVENT_FLAG_LBUTTON)
	{
		//cout << "\nClick";

		if( !primerclick )
		{
			punto1.x = x;
			punto1.y = y;
			primerclick = true;
			//cout << "\nPrimer click. x = " << x << " y = " << y;
		}
		else
		{
			punto2.x = x;
			punto2.y = y;
			primerclick = false;
			//cout << "\nSegundo click. x = " << x << " y = " << y;

			// OpenCV typically assumes that the top and left boundary of the rectangle are inclusive,
			// while the right and bottom boundaries are not. (de la documentación de Rect_ en core)
			// Sea un punto pt, pertenece al rect si
			// x <= pt.x < x+width
			// y <= pt.y < y+height
			// Por lo tanto tenemos que sumar 1
			roi.width = abs(punto1.x - punto2.x) +1 ;
			roi.height = abs(punto1.y - punto2.y) +1 ;
			roi.x = min(punto1.x , punto2.x);	// Arriba izquierda
			roi.y = min(punto1.y , punto2.y);	// Arriba izquierda
			//cout << "\nROI: " << roi;
			recorte = Mat(img_orig , roi);
	        namedWindow("Extracción");
	        imshow("Extracción",recorte); //showing the cropped image

	        rect_a_struct_resultados(roi, *aux_res);

		}
	}

}

