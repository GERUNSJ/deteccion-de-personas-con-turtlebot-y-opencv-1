#!bin/bash

# Otras pruebas

# Parámetros
DH_ESCALA_INICIAL=1.3
DH_PASOESCALA=1.05
DH_UMBRALAGRUPAMIENTO=2
DH_HIT_THRESHOLD=0
DH_SETSVMDETECTOR=getDefaultPeopleDetector
# DH_CONVERTIR_A_GRIS=true
# DH_ECUALIZAR_HISTOGRAMA=true
DH_BLUREAR=false
DH_TAMANIO_BLUR=3


####################################################################################
#			PRUEBA 01
NOMBRE_RESULTADOS=01

DH_CONVERTIR_A_GRIS=true
DH_ECUALIZAR_HISTOGRAMA=true

funcion_detector_hog
funcion_csv_headers
funcion_csv_normal


####################################################################################
#			PRUEBA 02
NOMBRE_RESULTADOS=02

DH_CONVERTIR_A_GRIS=true
DH_ECUALIZAR_HISTOGRAMA=false

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 03
NOMBRE_RESULTADOS=03

DH_CONVERTIR_A_GRIS=false
DH_ECUALIZAR_HISTOGRAMA=false

funcion_detector_hog
funcion_csv_normal

