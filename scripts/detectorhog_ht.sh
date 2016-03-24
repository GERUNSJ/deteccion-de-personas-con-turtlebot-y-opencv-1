#!bin/bash

# PRUEBAS VARIANDO EL FACTOR DE ESCALADO

# Parámetros
DH_PASOESCALA=1.05
DH_UMBRALAGRUPAMIENTO=2
#DH_HIT_THRESHOLD=0
DH_SETSVMDETECTOR=getDefaultPeopleDetector
DH_CONVERTIR_A_GRIS=true
DH_ECUALIZAR_HISTOGRAMA=true
DH_BLUREAR=false
DH_TAMANIO_BLUR=3


####################################################################################
#			PRUEBA 01
NOMBRE_RESULTADOS=01

DH_HIT_THRESHOLD=0

funcion_detector_hog
funcion_csv_headers
funcion_csv_normal


####################################################################################
#			PRUEBA 02
NOMBRE_RESULTADOS=02

DH_HIT_THRESHOLD=0.1

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 03
NOMBRE_RESULTADOS=03

DH_HIT_THRESHOLD=0.2

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 04
NOMBRE_RESULTADOS=04

DH_HIT_THRESHOLD=0.3

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 05
NOMBRE_RESULTADOS=05

DH_HIT_THRESHOLD=0.4

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 06
NOMBRE_RESULTADOS=06

DH_HIT_THRESHOLD=0.5

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 07
NOMBRE_RESULTADOS=07

DH_HIT_THRESHOLD=1

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 08
NOMBRE_RESULTADOS=08

DH_HIT_THRESHOLD=2

funcion_detector_hog 
funcion_csv_normal


####################################################################################
#			PRUEBA 09
NOMBRE_RESULTADOS=09

DH_HIT_THRESHOLD=4

funcion_detector_hog 
funcion_csv_normal
