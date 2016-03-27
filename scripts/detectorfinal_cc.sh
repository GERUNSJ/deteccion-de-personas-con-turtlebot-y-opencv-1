#!bin/bash

# PRUEBAS VARIANDO EL CLASIFICADOR O CASCADA
# Podría llegar a ser inválido o no muy válido, ya que puede ser que hayan sido entrenadas con 
# distintos tamaños y esto influya en la efectividad de los otros parámetros (particularmente
# scaleFactor y minNeighbors).

# Otros parámetros
#DF_DIR_CASCADA=./../clasificadores/visionary.net_pedestrian_cascade_web_LBP.xml
DF_ESCALA_INICIAL=1.3
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false
DF_BLUREAR=false
DF_TAMANIO_BLUR=3


####################################################################################
#			PRUEBA 01
NOMBRE_RESULTADOS=01

DF_DIR_CASCADA=./../clasificadores/visionary.net_pedestrian_cascade_web_LBP.xml

funcion_detector_final
funcion_csv_headers
funcion_csv_normal


####################################################################################
#			PRUEBA 02
NOMBRE_RESULTADOS=02

DF_DIR_CASCADA=./../clasificadores/haarcascade_fullbody.xml

funcion_detector_final
funcion_csv_normal



####################################################################################
#			PRUEBA 03
NOMBRE_RESULTADOS=03

DF_DIR_CASCADA=./../clasificadores/haarcascade_lowerbody.xml

funcion_detector_final
funcion_csv_normal



####################################################################################
#			PRUEBA 04
NOMBRE_RESULTADOS=04

DF_DIR_CASCADA=./../clasificadores/haarcascade_upperbody.xml

funcion_detector_final
funcion_csv_normal



####################################################################################
#			PRUEBA 05
NOMBRE_RESULTADOS=05

DF_DIR_CASCADA=./../clasificadores/haarcascade_mcs_upperbody.xml

funcion_detector_final
funcion_csv_normal

 
