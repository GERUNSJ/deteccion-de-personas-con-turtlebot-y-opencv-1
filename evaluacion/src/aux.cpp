#include "aux.hpp"

using namespace std;
using namespace cv;

//--------------------------------------------
string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

void f_histograma(const Mat& img, Mat& hist)
{
	// Initialize parameters

	int histSize = 0;		//bin size
    float range16[] = { 0, 65535 }; //255		//Es un arreglo de 2 elementos.
    const float *ranges16[] = { range16 };		//Es un arreglo de punteros?

    float range8[] = { 0, 255 }; //255
    const float *ranges8[] = { range8 };



    if(img.depth() == CV_8U)
    {
    	histSize = 256;
        calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges8, true, false );
    }
    else if(img.depth() == CV_16U)
    {
    	histSize = 65536;
        calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges16, true, false );
    }

    /*
    for( int h = 0; h < histSize; h++ )
         {
            float binVal = hist.at<float>(h);
            cout<<" "<<binVal;
         }*/


/*
    // Calculate histogram
    //Mat hist;
    calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );
    //calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

    //Mostrar valores del histograma en consola.
    for( int h = 0; h < histSize; h++ )
         {
            float binVal = hist.at<float>(h);
            cout<<" "<<binVal;
         }
*/

    string tipo = type2str(hist.type());
    cout << "\nEl histograma es del tipo " << tipo << "\n" ;
    cout << "\n El histograma tiene " << hist.rows << " filas y " << hist.cols << " columnas.\n";

    return;

}

//...........................................................................

void f_histograma_log(const Mat& img , Mat& hist)
{
	// Initialize parameters

	int histSize = 0;		//bin size
    float range16[] = { 0, 65535 }; //255		//Es un arreglo de 2 elementos.
    const float *ranges16[] = { range16 };		//Es un arreglo de punteros?

    float range8[] = { 0, 255 }; //255
    const float *ranges8[] = { range8 };



    if(img.depth() == CV_8U)
    {
    	histSize = 256;
        calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges8, true, false );
    }
    else if(img.depth() == CV_16U)
    {
    	histSize = 65536;
        calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges16, true, false );
    }




/*

   // Calculate histogram
    //Mat hist;
    //calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );
    //calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

*/



//Logaritmo

    for(int i=0;i<hist.rows;i++)
    {
    	hist.at<float>(i) = log(hist.at<float>(i));
    	if(hist.at<float>(i)<0)hist.at<float>(i)=0;	//satura
    }




/*
    // Show the calculated histogram in command window

    cout << "\ndespues del log" << std::endl;

    for( int h = 0; h < histSize; h++ )
         {
            float binVal = hist.at<float>(h);
            cout<<" "<<binVal;
         }
*/

/*


    // Plot the histogram
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0) );
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < histSize; i++ )
    {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
    }

    namedWindow( "Result", 1 );
    imshow( "Result", histImage );

    waitKey(0);

*/

    string tipo = type2str(hist.type());
    cout << "\nEl histograma es del tipo " << tipo << "\n" ;
    cout << "\nEl histograma tiene " << hist.rows << " filas y " << hist.cols << " columnas.\n";

    return;
}


//------------------------------------------------------------------------------------------------



void mostrar_histograma(const Mat& hist_original, Mat& hist_img, char* nombreventana)
{

    //string tipo = type2str(hist_original.type());
    //cout << "\nEl histograma es del tipo " << tipo << "\n" ;
	Mat hist = hist_original.clone();


    int histSize = V_HIST_ANCHO;
    int i = 0;


/*
    long int nn = 0;
    double suma = 0;


	for( i = 0; i < hist.rows; i++)
	{
		//cout << " "<< hist.at<float>(i);

		if(hist.at<float>(i)!=0)
		{
		//printf("%ld  ",(long int)hist.at<float>(i));
		nn++;
		//cout << " "<< hist.at<float>(i);
		suma += hist.at<float>(i);
		}
	}
	printf("\n\n i = %d\n\n",i);
	printf("\nHay %ld valores no nulos.\n",nn);
	printf("\nSuma es = %f\n\n",suma);
*/



/*

	double min = 0;
	double max = 0;
	Point maxLoc;
	Point minLoc;
	 //C++: void minMaxLoc(InputArray src, double* minVal, double* maxVal=0, Point* minLoc=0, Point* maxLoc=0, InputArray mask=noArray())
	cv::minMaxLoc(hist, &min, &max, &minLoc , &maxLoc);
	cout << "\nAntes del resize" << "\nMax = " << max << " en maxLoc = " << maxLoc << "\n";
	cout << "\nAntes del resize" << "\nMin = " << min << " en minLoc = " << minLoc << "\n";

*/




	if (hist.rows > V_HIST_ANCHO)
	{
		resize(hist, hist, Size(1,V_HIST_ANCHO), 0 ,0, INTER_AREA);		//Interpolación por área para reducir la imagen. Se come el valor en 0 pero no lo necesitamos..
		//cout << "\nAhora el histograma tiene " << hist.rows << " filas y " << hist.cols << " columnas.\n";
	}
	else if(hist.rows < V_HIST_ANCHO)
	{
		resize(hist, hist, Size(1,V_HIST_ANCHO), 0 ,0, INTER_LINEAR);	//Interpolación lineal para agrandar la imagen.
		//cout << "\nAhora el histograma tiene " << hist.rows << " filas y " << hist.cols << " columnas.\n";
	}



/*

    if (hist.rows > 256)
    {
    	histSize = 1024;
      	//C++: void resize(InputArray src, OutputArray dst, Size dsize, double fx=0, double fy=0, int interpola-
    	//tion=INTER_LINEAR )
    	resize(hist, hist, Size(1,1024), 0 ,0, INTER_AREA);
        cout << "\n Ahora el histograma tiene " << hist.rows << " filas y " << hist.cols << " columnas.\n";
    }
*/


	/*
	cv::minMaxLoc(hist, &min, &max, &minLoc , &maxLoc);
	cout << "\nDespues del resize" << "\nMax = " << max << " en maxLoc = " << maxLoc << "\n";
	cout << "\nDespues del resize" << "\nMin = " << min << " en minLoc = " << minLoc << "\n";
*/



    // Plot the histogram
	//					Tal vez se vería mejor un histograma con barras.

    int hist_w = V_HIST_ANCHO; int hist_h = V_HIST_ALTO;
    int bin_w = cvRound( (double) hist_w/histSize );
   // cout << "\nBin_w = " << bin_w << "\n";

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( i = 1; i < histSize; i++ )
    {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                       Scalar( 0, 0, 255), 1, 8, 0  );
    }

    //namedWindow( "Result", 1 );
    imshow( nombreventana, histImage );

    waitKey(0);

    hist_img = histImage.clone();
}



void encontrar_valles(cv::Mat& histograma, std::vector< std::vector<int> > &pares) {
    std::vector<int> par;
    std::vector<int>::iterator it1;
    std::vector< std::vector<int> >::iterator it2;
    int i = 0; //Valles
    int j = 0; //Pares de valles


    //Primer elemento
    par.push_back(0);

    for (i = 1; i < histograma.rows - 1; i++) //Del 1 al 254
    {
        if ((histograma.at<float>(i) <= histograma.at<float>(i - 1)) &&
                (histograma.at<float>(i) < histograma.at<float>(i + 1))) {
            j++;
            par.push_back(i);
            pares.push_back(par);
            par.erase(par.begin(), par.end());
            par.push_back(i);

        }
    }

    //Último elemento
    par.push_back(255);
    pares.push_back(par);

    for (it2 = pares.begin(); it2 != pares.end(); it2++) {
        par = *it2;

        std::cout << par.at(0) << '\t' << par.at(1) << '\n';
    }


    std::cout << '\n';

    std::cout << "\n\nHay " << j << " minimos y " << pares.size() << " pares.\n";

    return;
}




void pintar_histograma(const Mat& img_hist_original, Mat& img_hist_pintada, std::vector< std::vector<int> > pares, Color *vectorColor)
{
	std::vector< std::vector<int> >::iterator it1;	//índice pares
	int i = 0;	//Índice bins
	int j = 0;	//Índice pixeles imagen
	int k = 0;	//Índice pixels bin
	int l = 0;	//Longitud línea
	int ancho_bin = 0;
	Point3_<uchar> color(0, 0, 0);
	//Point punto_1 = (0,0);
	//Point punto_2 = (0,0);
	Scalar_<uchar> colorScalar(0, 0, 0);
	//Vec3b rojo(0,0,255);
	//Vec3b punto;
	//int cantidad = pares.size();



	img_hist_pintada = img_hist_original.clone();


	// Vamos
	/*if (img_hist_pintada.rows > 256)
	{
		resize(img_hist_pintada, img_hist_pintada, Size(1,V_HIST_ANCHO), 0 ,0, INTER_AREA);		//Interpolación por área para reducir la imagen. Se come el valor en 0 pero no lo necesitamos..
	}
	else if(img_hist_pintada.rows < 256)
	{
		resize(img_hist_pintada, img_hist_pintada, Size(1,V_HIST_ANCHO), 0 ,0, INTER_LINEAR);	//Interpolación lineal para agrandar la imagen.
	}*/

	cout << "\nEl histograma_pintado tiene " << img_hist_pintada.rows << " filas y " << img_hist_pintada.cols << " columnas.\n";

	ancho_bin = cvRound((double) V_HIST_ANCHO / 256);
	//cout << "Ancho_bin = " << ancho_bin << endl;

	/*{
		cout << "-" << (img_hist_pintada.at<Vec3b>(0,0))[0] << endl;
		cout << "-" << (img_hist_pintada.at<Vec3b>(0,0))[1] << endl;
		cout << "-" << (img_hist_pintada.at<Vec3b>(0,0))[2] << endl;
	}*/


	for( it1 = pares.begin(); it1 != pares.end(); it1++)	//Para cada par
	{
		color = vectorColor[distance(pares.begin(),it1)].devuelvocolor();
		colorScalar.val[0] = color.x;
		colorScalar.val[1] = color.y;
		colorScalar.val[2] = color.z;

		//cout << "asdasdassd" << colorScalar << endl;

		do
		{
			for( k = 0; k < ancho_bin ; k++ )	//Para todos los pixeles del bin
			{
				//while( img_hist_pintada.at<Vec3b>(j,l) == Vec3b(0,0,0))
				if( img_hist_pintada.at<Vec3b>(V_HIST_ALTO-1, j) != Vec3b(0,0,0) )	//Si el primero no es cero.
				{
					l = 0;
				}
				else
				{
					while( img_hist_pintada.at<Vec3b>(V_HIST_ALTO-1-l, j) == Vec3b(0,0,0) && l < V_HIST_ALTO-1)
					{
						/*cout << (img_hist_pintada.at<Vec3b>(V_HIST_ALTO-1-l, j)[0]) << " " <<
								(img_hist_pintada.at<Vec3b>(V_HIST_ALTO-1-l, j)[1]) << " " <<
								(img_hist_pintada.at<Vec3b>(V_HIST_ALTO-1-l, j)[2]) << endl;*/
						//waitKey(0);
						//cout << l++ << endl;
						l++;

					}
				}
				if( l == V_HIST_ALTO-1 && img_hist_pintada.at<Vec3b>(0, j) == Vec3b(0,0,0))	// Si son todos nulos.
					l = 0;
				//l++;
				//cout << "L es " << l << endl;
				//waitKey(0);
				//cout << img_hist_pintada.at<Vec3b>(V_HIST_ALTO-1-l, j).val[0] << endl;
				//cout << l++ << endl;

				//line(img_hist_pintada, Point(j,0), Point(j,l), colorScalar, 2, 8, 0 );
				//line(img_hist_pintada, Point(V_HIST_ALTO-1,j), Point((V_HIST_ALTO-1+l),j), colorScalar, 2, 8, 0 );
				//line(img_hist_pintada, Point(j,0), Point(j,V_HIST_ALTO-1-l), colorScalar, 2, 8, 0 );
				//line(img_hist_pintada, Point(V_HIST_ALTO-1,j), Point(V_HIST_ALTO-1-l,j), colorScalar, 2, 8, 0 );
				line(img_hist_pintada, Point(j,V_HIST_ALTO-1), Point(j,V_HIST_ALTO-1-l), colorScalar, 1, 8, 0 );
				l = 0;
				//cout << "j = " << j << endl;
				j++;

			}

			i++;
			if ( j == V_HIST_ANCHO-1)
			{
				cout << "J pasado" << endl;
				break;
			}
		} while ( i != ((std::vector<int>)*it1)[1]);	//Hasta el segundo elemento del par.
		//i++;
	}


	{
		line(img_hist_pintada, Point(600, 20), Point(630, V_HIST_ALTO-1), Scalar(255,255,255), 1, 8 , 0);
	}

}




void suavizar_histograma(Mat& histograma, int ancho_filtro)
{
	//C++: void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int border-type=BORDER_DEFAULT )
	blur(histograma, histograma, Size(1,ancho_filtro), Point(-1,-1), BORDER_REFLECT_101);	//Size(columnas,filas)
	//BORDER_REPLICATE supone que los valores de borde se mantienen constantes.
	//BORDER_REFLECT_101 gfedcb|abcdefgh|gfedcba
}


uchar d;

void Pintar(const cv::Mat &src, cv::Mat &dst, std::vector<std::vector<int> > LimiteEObjeto, Color *vectorColor)
{        
	int dim = 256;
	cv::Mat lut(1, dim, CV_8UC(dst.channels()));
	for (int i = 0; i < 256; i++) {
		lut.at<cv::Vec3b>(i) = cv::Point3_<uchar>(0, 0,0);
	}
	for(int j=0; j< LimiteEObjeto.size();j++) {
		Color Objeto;
		//Objeto = new Color;
		Objeto.generocolor();
		for(int i= LimiteEObjeto[j][0]; i < LimiteEObjeto[j][1];i++)
		{
			
			lut.at<cv::Vec3b>(i)=Objeto.devuelvocolor();
		}
		//delete Objeto;
		// std::cout<<  lut.at<cv::Vec3b>(i) << std::endl;
		vectorColor[j] = Objeto;
		Objeto.~Color();
	}
	//delete Objeto;
	cv::LUT(src,lut,dst,0);
}

Color::Color()
{

}


Color& Color::operator= (const Color& cd){
	//if (*this != cd)
		color = cd.color;
	return *this;
}



cv::Point3_<uchar> Color::devuelvocolor()
{
	return color;
}



void Color::generocolor()
{
	
	color = cv::Point3_<uchar>(rand()%255 , rand()%255, rand()%255);
	/*{
		std::cout << (int)color.x << " ";
		std::cout << (int)color.y << " ";
		std::cout << (int)color.z << std::endl;
	}*/
}


Color::~Color()
{
	// destruir el numero complejo...
}

