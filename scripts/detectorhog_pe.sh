#!bin/bash

# PRUEBAS VARIANDO EL FACTOR DE ESCALADO

# Parámetros
DH_ESCALA_INICIAL=1.3
#DH_PASOESCALA=1.05
DH_UMBRALAGRUPAMIENTO=2
DH_HIT_THRESHOLD=0
DH_SETSVMDETECTOR=getDefaultPeopleDetector
DH_CONVERTIR_A_GRIS=true
DH_ECUALIZAR_HISTOGRAMA=true
DH_BLUREAR=false
DH_TAMANIO_BLUR=3


# ####################################################################################
# #			PRUEBA 01
# NOMBRE_RESULTADOS=01
# 
# DH_PASOESCALA=1.01
# 
# funcion_detector_hog
# funcion_csv_headers
# funcion_csv_normal


####################################################################################
#			PRUEBA 02
NOMBRE_RESULTADOS=02

DH_PASOESCALA=1.05

funcion_detector_hog
funcion_csv_headers
funcion_csv_normal


####################################################################################
#			PRUEBA 03
NOMBRE_RESULTADOS=03

DH_PASOESCALA=1.1

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 04
NOMBRE_RESULTADOS=04

DH_PASOESCALA=1.15

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 05
NOMBRE_RESULTADOS=05

DH_PASOESCALA=1.2

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 06
NOMBRE_RESULTADOS=06

DH_PASOESCALA=1.4

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 07
NOMBRE_RESULTADOS=07

DH_PASOESCALA=2

funcion_detector_hog
funcion_csv_normal


####################################################################################
#			PRUEBA 08
NOMBRE_RESULTADOS=08

DH_PASOESCALA=4

funcion_detector_hog 
funcion_csv_normal
