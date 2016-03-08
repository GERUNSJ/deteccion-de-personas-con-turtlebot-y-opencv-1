#!bin/bash

# PRUEBAS VARIANDO LA ESCALA INICIAL

# Otros parámetros
DF_DIR_CASCADA=./../clasificadores/visionary.net_pedestrian_cascade_web_LBP.xml
#DF_ESCALA_INICIAL=1
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false

####################################################################################
#			PRUEBA 01
NOMBRE_RESULTADOS=01

DF_ESCALA_INICIAL=1

funcion_detector_final
funcion_csv_headers
funcion_csv_normal



####################################################################################
#			PRUEBA 02
NOMBRE_RESULTADOS=02

DF_ESCALA_INICIAL=1.2

funcion_detector_final
funcion_csv_normal


####################################################################################
#			PRUEBA 03
NOMBRE_RESULTADOS=03

DF_ESCALA_INICIAL=1.3

funcion_detector_final
funcion_csv_normal


####################################################################################
#			PRUEBA 04
NOMBRE_RESULTADOS=02

DF_ESCALA_INICIAL=1.5

funcion_detector_final
funcion_csv_normal


####################################################################################
#			PRUEBA 05
NOMBRE_RESULTADOS=05

DF_ESCALA_INICIAL=2

funcion_detector_final
funcion_csv_normal


####################################################################################
#			PRUEBA 06
NOMBRE_RESULTADOS=06

DF_ESCALA_INICIAL=3

funcion_detector_final
funcion_csv_normal