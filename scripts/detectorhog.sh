#!/bin/bash

# Importamos el script base
source base.sh

# Elegimos set // Mejor hacerlo en llamartodos

###########################################################################################################
#			DETECTORHOG
###########################################################################################################

# DetectorHOG pasoEscala double umbralAgrupamiento int hit_threshold float setSVMDetector <getDefaultPeopleDetector | getDaimlerPeopleDetector> convertir_a_gris bool ecualizar_histograma bool blurear bool tamanio_blur int

SUBCARPETA=detectorhog
# Creamos la carpeta en caso de que no exista
mkdir -p $CARPETA_RESULTADOS/$SUBCARPETA

# Parámetros
DH_PASOESCALA=1.05
DH_UMBRALAGRUPAMIENTO=2
DH_HIT_THRESHOLD=0
DH_SETSVMDETECTOR=getDefaultPeopleDetector
DH_CONVERTIR_A_GRIS=true
DH_ECUALIZAR_HISTOGRAMA=true
DH_BLUREAR=false
DH_TAMANIO_BLUR=3

# Función
funcion_detector_hog ()
{
	# Detecciones
	$PRINCIPAL $CARPETA_RGB $CARPETA_PROFUNDIDAD $CARPETA_RESULTADOS/$SUBCARPETA/$PREFIJO1\_$PREFIJO2\_$NOMBRE_RESULTADOS 0 DetectorHOG pasoEscala $DH_PASOESCALA umbralAgrupamiento $DH_UMBRALAGRUPAMIENTO hit_threshold $DH_HIT_THRESHOLD setSVMDetector $DH_SETSVMDETECTOR convertir_a_gris $DH_CONVERTIR_A_GRIS ecualizar_histograma $DH_ECUALIZAR_HISTOGRAMA blurear $DH_BLUREAR tamanio_blur $DH_TAMANIO_BLUR
	
	# Evaluación
	$RESULTADOS $CARPETA_RESULTADOS/$NOMBRE_REALES $CARPETA_RESULTADOS/$SUBCARPETA/$PREFIJO1\_$PREFIJO2\_$NOMBRE_RESULTADOS $CARPETA_RESULTADOS/$SUBCARPETA/R\_$PREFIJO1\_$PREFIJO2\_$NOMBRE_RESULTADOS.txt
	
}

# Prefijo de los nombres de archivos creados
PREFIJO1=DH


####################################################################################
#			PRUEBAS

# pe pasoEscala
# ua umbralAgrupamiento
# ht hit_threshold
# sd setSVMDetector
# xx otros
#  convertir_a_gris
#  ecualizar_histograma
# bl blurear y tamanio_blur
# zz combinaciones arbitrarias
 


####################################################################################
#			pe - Variamos pasoEscala
PREFIJO2=pe
source detectorhog_pe.sh


####################################################################################
#			ua - Variamos umbralAgrupamiento
PREFIJO2=ua
source detectorhog_ua.sh


####################################################################################
#			ht - Variamos hit_threshold
PREFIJO2=ht
source detectorhog_ht.sh


####################################################################################
#			sd - Variamos setSVMDetector
PREFIJO2=sd
source detectorhog_sd.sh


####################################################################################
#			bl - Variamos blurear y tamanio_blur
PREFIJO2=bl
source detectorhog_bl.sh


####################################################################################
#			xx - Variamos otros parámetros
PREFIJO2=xx
source detectorhog_xx.sh


####################################################################################
#			zz - combinaciones arbitrarias
PREFIJO2=zz
source detectorhog_zz.sh



#exit