#!bin/bash

# PRUEBAS VARIANDO EL CLASIFICADOR O CASCADA
# Podría llegar a ser inválido o no muy válido, ya que puede ser que hayan sido entrenadas con 
# distintos tamaños y esto influya en la efectividad de los otros parámetros (particularmente
# scaleFactor y minNeighbors).

# Otros parámetros
#DF_DIR_CASCADA=./../clasificadores/visionary.net_pedestrian_cascade_web_LBP.xml
DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

####################################################################################
#			PRUEBA 01
NOMBRE_RESULTADOS=01

DF_DIR_CASCADA=./../clasificadores/visionary.net_pedestrian_cascade_web_LBP.xml

funcion_detector_final


####################################################################################
#			PRUEBA 02
NOMBRE_RESULTADOS=02

DF_DIR_CASCADA=./../clasificadores/haarcascade_fullbody.xml

funcion_detector_final


####################################################################################
#			PRUEBA 03
NOMBRE_RESULTADOS=03

DF_DIR_CASCADA=./../clasificadores/haarcascade_lowerbody.xml

funcion_detector_final


####################################################################################
#			PRUEBA 04
NOMBRE_RESULTADOS=04

DF_DIR_CASCADA=./../clasificadores/haarcascade_upperbody.xml

funcion_detector_final


####################################################################################
#			PRUEBA 05
NOMBRE_RESULTADOS=05

DF_DIR_CASCADA=./../clasificadores/haarcascade_mcs_upperbody.xml

funcion_detector_final
 
