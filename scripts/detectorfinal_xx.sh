#!bin/bash

# Otras pruebas

# Otros parámetros
DF_DIR_CASCADA=./../clasificadores/visionary.net_pedestrian_cascade_web_LBP.xml
DF_ESCALA_INICIAL=1.3
DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4
DF_USAR_PROFUNDIDAD=false
DF_BLUREAR=false
DF_TAMANIO_BLUR=3
DF_FILTRO_ENFOQUE=false
DF_FILTRO_REPUJADO=false
DF_FILTRO_ENFOQUE_Y_REPUJADO=false
DF_FILTRO_REPUJADO_Y_ENFOQUE=false


####################################################################################
#			PRUEBA 01
NOMBRE_RESULTADOS=01

DF_CONVERTIR_A_GRIS=false
DF_ECUALIZAR_HISTOGRAMA=false

funcion_detector_final
funcion_csv_headers
funcion_csv_normal


####################################################################################
#			PRUEBA 02
NOMBRE_RESULTADOS=02

DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=false

funcion_detector_final
funcion_csv_normal


####################################################################################
#			PRUEBA 03
NOMBRE_RESULTADOS=03

DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true

funcion_detector_final
funcion_csv_normal


####################################################################################
#			PRUEBA 04
NOMBRE_RESULTADOS=04

DF_CONVERTIR_A_GRIS=true
DF_ECUALIZAR_HISTOGRAMA=true
DF_USAR_PROFUNDIDAD=true

funcion_detector_final
funcion_csv_normal