#!bin/bash

# Otras pruebas

# Otros parámetros
DF_DIR_CASCADA=./../clasificadores/visionary.net_pedestrian_cascade_web_LBP.xml
DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

####################################################################################
#			PRUEBA 01
NOMBRE_RESULTADOS=01

DF_CONVERTIR_A_GRIS=false
DF_ECUALIZAR_HISTOGRAMA=false

funcion_detector_final


####################################################################################
#			PRUEBA 02
NOMBRE_RESULTADOS=02

DF_CONVERTIR_A_GRIS=false
DF_ECUALIZAR_HISTOGRAMA=true

funcion_detector_final


####################################################################################
#			PRUEBA 03
NOMBRE_RESULTADOS=03

DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=false

funcion_detector_final


####################################################################################
#			PRUEBA 04
NOMBRE_RESULTADOS=04

DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true

funcion_detector_final


####################################################################################
#			PRUEBA 05
NOMBRE_RESULTADOS=05

DF_USAR_PROFUNDIDAD=true

funcion_detector_final