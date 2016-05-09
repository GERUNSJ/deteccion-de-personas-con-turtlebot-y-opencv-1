Comenzamos nuevamente lo iniciado en https://github.com/GERUNSJ/detecciondepersonas_opencv , esta vez para terminarlo.

---------

# Detección de personas para un robot TurtleBot usando OpenCV  #
Este es el informe (y los archivos relacionados) del trabajo integrador final de la materia Temas Específicos de Control I: Visión Artificial, dictada en la carrera Ingeniería Electrónica de la Universidad Nacional de San Juan. La consigna es llevar a cabo un proyecto que en el se apliquen todos los conocimientos adquiridos en la materia, asimilándolos con práctica y complementándolos con más conceptos.

Se planteó como objetivo principal del proyecto realizar la detección de personas desde un robot móvil con un grado aceptable de aciertos. Para ello se probaron la eficiencia y eficacia de distintos algoritmos que fueron implementados en OpenCV sobre un robot TurtleBot, equipado con una cámara RGB+D Microsoft Kinect y trabajando bajo el sistema ROS (Robot Operative System). El programa desarrollado fue luego adaptado para poder utilizarse en otras cámaras sin información de profundidad, como una webcam de una PC o una mini-computadora Raspberry Pi 2 con cámara.

El informe se extiende sobre algunas alternativas de trabajo, conceptos de los detectores utilizados y también sobre ROS, ya que fue una herramienta de uso constante. Se abordan también las pruebas realizadas, su evaluación e interpretación, terminando con algunas conclusiones obtenidas y posibles mejoras.

## Estructura de archivos ##
* ``informe_Aguado_Emder.pdf`` — Informe del trabajo. https://github.com/GERUNSJ/deteccion-de-personas-con-turtlebot-y-opencv-1/raw/master/informe_Aguado_Emder.pdf
* ``evaluacion/`` — Lo referido a la evaluación de algoritmos
* ``evaluacion/clasificadores/`` — Los clasificadores utilizados
* ``evaluacion/ejecutables/`` — Ejecutables compilados para Linux x64
* ``evaluacion/resultados/`` — Resultados sobre los sets de prueba
* ``evaluacion/scripts/`` — Scripts de evaluación
* ``evaluacion/src/`` — Código fuente de los programas de evaluación
* ``implementacion/`` — Nodos de ROS para funcionamiento en línea. Ver Apéndice B
* ``otros/calibracion_turtlebot/`` — Archivos de calibración de las cámaras
* ``otros/raspicam_node-master.zip`` — [Nodo Raspicam para ROS](https://github.com/fpasteau/raspicam_node)
* ``resultados/`` — Imágenes y videos de los resultados sobre los sets de prueba y validación. [Videos en Youtube](https://www.youtube.com/watch?v=mL0oSrWRbu4&list=PLsvvKr5lc8GL_7z07W-cz3wgEu_0JelXX)


## Nodos ##

El workspace de ROS contiene el nodo de detección y un nodo publicador de video para la webcam. Para poder ejecutarlos, primero hay que compilarlos. 
Los pasos a seguir:

1. Modificar el código (``src/detpeople/src/ImageConverter.cpp``, líneas 48 y 51) para que se suscriba a los mensajes de la Kinect o de la webcam o de la cámara de la Raspberry Pi. Por defecto está suscripto a los mensajes bajo el topic ``/camera/image`` , que son los de la webcam o de la cámara de la Raspberry.
2. Compilar:
  1. Situarse dentro de la carpeta implementacion
  2. Ejecutar ``catkin_make`` . Esto compila los nodos.
  3. Se le informa a ROS la existencia de esos paquetes con ``source devel/setup.bash``
3. Se ejecutan los nodos con rosrun
  1. [Opcional] ``rosrun detpeople publicador_video`` — Ejecuta un nodo que publica video desde la webcam de la PC.
  2. ``rosrun detpeople detpeople`` — Ejecuta el detector.


Para recibir imágenes desde el TurtleBot, ver 7.2. Para transmitir imágenes desde la Raspberry Pi, referirse a 7.3; el nodo Raspicam se puede compilar de forma similar a lo realizado en el punto 2 anterior.

---

>>*Pablo Aguado - ELO 23724*

>>*Fabricio Emder - ELO 23764*

**Ingeniería Electrónica - Universidad Nacional de San Juan**

*Abril de 2016*



