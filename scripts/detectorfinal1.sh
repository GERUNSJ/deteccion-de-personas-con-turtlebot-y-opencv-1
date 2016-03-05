#!/bin/bash

# Importamos el script base
source base.sh

###########################################################################################################
#			DETECTORFINAL
###########################################################################################################

# DetectorFinal direccion_a_cascada string escala_inicial float convertir_a_gris bool ecualizar_histograma bool scaleFactor float minNeighbors int usar_profundidad_altura bool

SUBCARPETA=detectorfinal
# Creamos la carpeta en caso de que no exista
mkdir -p $CARPETA_RESULTADOS/$SUBCARPETA

# Parámetros
DF_DIR_CASCADA=./../clasificadores/visionary.net_pedestrian_cascade_web_LBP.xml
DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

# Función
funcion_detector_final ()
{
	# Detecciones
	$PRINCIPAL $CARPETA_RGB $CARPETA_PROFUNDIDAD $CARPETA_RESULTADOS/$SUBCARPETA/$NOMBRE_RESULTADOS 0 DetectorFinal direccion_a_cascada $DF_DIR_CASCADA escala_inicial $DF_ESCALA_INICIAL convertir_a_gris $DF_CONVERTIR_A_GRIS ecualizar_histograma $DF_ECUALIZAR_HISTOGRAMA scaleFactor $DF_SCALEFACTOR minNeighbors $DF_MINNEIGHBORS usar_profundidad_altura $DF_USAR_PROFUNDIDAD
	
	# Evaluación
	$RESULTADOS $CARPETA_RESULTADOS/$NOMBRE_REALES $CARPETA_RESULTADOS/$SUBCARPETA/$NOMBRE_RESULTADOS $CARPETA_RESULTADOS/$SUBCARPETA/R\_"$NOMBRE_RESULTADOS".txt
}

####################################################################################
#			PRUEBA 01
NOMBRE_RESULTADOS=DF_01

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=false
DF_ECUALIZAR_HISTOGRAMA=false
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 02
NOMBRE_RESULTADOS=DF_02

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=false
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 03
NOMBRE_RESULTADOS=DF_03

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=false
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 04
NOMBRE_RESULTADOS=DF_04

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 05
NOMBRE_RESULTADOS=DF_05

DF_ESCALA_INICIAL=1.2
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 06
NOMBRE_RESULTADOS=DF_06

DF_ESCALA_INICIAL=1.5
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 07
NOMBRE_RESULTADOS=DF_07

DF_ESCALA_INICIAL=2
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 08
NOMBRE_RESULTADOS=DF_01

DF_ESCALA_INICIAL=1.5
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.01
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 09
NOMBRE_RESULTADOS=DF_09

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.2
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 10
NOMBRE_RESULTADOS=DF_10

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.5
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 11
NOMBRE_RESULTADOS=DF_11

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=5
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 12
NOMBRE_RESULTADOS=DF_12

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=6
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 13
NOMBRE_RESULTADOS=DF_13

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=7
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 14
NOMBRE_RESULTADOS=DF_14

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=3
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 15
NOMBRE_RESULTADOS=DF_15

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=2
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 16
NOMBRE_RESULTADOS=DF_16

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.3
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

####################################################################################
#			PRUEBA 17
NOMBRE_RESULTADOS=DF_17

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.3
DF_MINNEIGHBORS=5
DF_USAR_PROFUNDIDAD=false

funcion_detector_final


####################################################################################
#			PRUEBA 16
NOMBRE_RESULTADOS=DF_16

DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.3
DF_MINNEIGHBORS=6
DF_USAR_PROFUNDIDAD=false

funcion_detector_final

