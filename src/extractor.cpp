#include "extractor.hpp"
using namespace std;
using namespace cv;

// Globales
Mat img_orig;
string ventana_imagen = "Seleccionar personas";

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

	namedWindow(ventana_imagen, CV_WINDOW_KEEPRATIO);

    setMouseCallback( ventana_imagen, onMouse, 0 );

    imshow(ventana_imagen, img_orig);

    unsigned int i = 0;

    char c = 'a';
    while( c != 16)	// enter
    {
    	c = waitKey(0);

    	if( c == ' ' ) // espacio
    	{
    		// Guardar selección como resultado
    		i ++;
    	}


    }

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


 

static void onMouse( int event, int x, int y, int flags, void* )
{
	Mat img_mouse = img_orig.clone();
	Point punto;
	punto.x = x;
	punto.y = y;
	if( event == EVENT_MOUSEMOVE)
	{
		//cout << "...";
		line( img_mouse, Point2i(punto.x,0), Point2i(punto.x,img_mouse.rows-1), Scalar(0,255,0), 1 ); // Línea vertical
		line( img_mouse, Point2i(0,punto.y), Point2i(img_mouse.cols-1,punto.y), Scalar(0,255,0), 1); // Línea horizontal
		imshow(ventana_imagen, img_mouse);
	}
	else if ( event == EVENT_FLAG_LBUTTON )
	{
		cout << "\nClick";
	}
	else
	{
		cout << "\nOtros";
	}

//
//    Point seed = Point(x,y);
//    int lo = ffillMode == 0 ? 0 : loDiff;
//    int up = ffillMode == 0 ? 0 : upDiff;
//    int flags = connectivity + (newMaskVal << 8) +
//                (ffillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
//    int b = (unsigned)theRNG() & 255;
//    int g = (unsigned)theRNG() & 255;
//    int r = (unsigned)theRNG() & 255;
//    Rect ccomp;
//
//    Scalar newVal = isColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);
//    Mat dst = isColor ? image : gray;
//    int area;
//
//    if( useMask )
//    {
//        threshold(mask, mask, 1, 128, CV_THRESH_BINARY);
//        area = floodFill(dst, mask, seed, newVal, &ccomp, Scalar(lo, lo, lo),
//                  Scalar(up, up, up), flags);
//        imshow( "mask", mask );
//    }
//    else
//    {
//        area = floodFill(dst, seed, newVal, &ccomp, Scalar(lo, lo, lo),
//                  Scalar(up, up, up), flags);
//    }
//
//    imshow("image", dst);
//    cout << area << " pixels were repainted\n";
}

