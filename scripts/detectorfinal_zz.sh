#!bin/bash

# Combinaciones arbitrarias

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


####################################################################################
#			PRUEBA 01
NOMBRE_RESULTADOS=01

DF_ESCALA_INICIAL=1
DF_SCALEFACTOR=1.1
DF_MINNEIGHBORS=4

funcion_detector_final
funcion_csv_headers
funcion_csv_normal