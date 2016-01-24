//----------------------------------------------------------------------------------------------
// Includes
#include <iostream>
#include <opencv2/core/core.hpp>

//----------------------------------------------------------------------------------------------
// Declaración de funciones
void ayuda();

//----------------------------------------------------------------------------------------------
// MAIN

int main(int argc, char** argv)
{
  using namespace std;
  // Ayuda de uso
  ayuda();
  
  // Se lee la carpeta con las imagenes, o la imagen según corresponda
  
  // Se crea un detector
  
  // Se procesan las imagenes
  
  // Se guardan los resultados
  
  return 0;
}




//----------------------------------------------------------------------------------------------
// Funciones auxiliares

// AYUDA
void ayuda()
{
  using namespace std;
  cout << "\nDetección de personas en opencv para Turtlebot - Fabricio Emder, Pablo Aguado\n"
	  "Uso: dp_opencv <carpeta_con_imagenes | imagen >  </dir/al/archivo_de_resultados.csv>"
	  " [otras opciones...]\n"
	  "\nUsando OpenCV " << CV_VERSION << endl;
  
  return;
}
