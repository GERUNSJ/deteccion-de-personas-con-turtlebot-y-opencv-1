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
DH_ESCALA_INICIAL=1.3
DH_PASOESCALA=1.05
DH_UMBRALAGRUPAMIENTO=2
DH_HIT_THRESHOLD=0
DH_SETSVMDETECTOR=getDefaultPeopleDetector
DH_CONVERTIR_A_GRIS=true
DH_ECUALIZAR_HISTOGRAMA=true
DH_BLUREAR=false
DH_TAMANIO_BLUR=3
DH_FILTRO_ENFOQUE=false
DH_FILTRO_REPUJADO=false
DH_FILTRO_ENFOQUE_Y_REPUJADO=false
DH_FILTRO_REPUJADO_Y_ENFOQUE=false
DH_USAR_PROFUNDIDAD=false

# Función
funcion_detector_hog ()
{
	# Detecciones
	$PRINCIPAL $CARPETA_RGB $CARPETA_PROFUNDIDAD $IMAGEN_INICIAL $IMAGEN_FINAL $CARPETA_RESULTADOS/$SUBCARPETA/$PREFIJO1\_$PREFIJO2\_$NOMBRE_RESULTADOS 0 DetectorHOG escala_inicial $DH_ESCALA_INICIAL pasoEscala $DH_PASOESCALA umbralAgrupamiento $DH_UMBRALAGRUPAMIENTO hit_threshold $DH_HIT_THRESHOLD setSVMDetector $DH_SETSVMDETECTOR convertir_a_gris $DH_CONVERTIR_A_GRIS ecualizar_histograma $DH_ECUALIZAR_HISTOGRAMA blurear $DH_BLUREAR tamanio_blur $DH_TAMANIO_BLUR filtro_enfoque $DH_FILTRO_ENFOQUE filtro_repujado $DH_FILTRO_REPUJADO filtro_enfoque_y_repujado $DH_FILTRO_ENFOQUE_Y_REPUJADO filtro_repujado_y_enfoque $DH_FILTRO_REPUJADO_Y_ENFOQUE usar_profundidad_altura $DH_USAR_PROFUNDIDAD
	
	# Evaluación
	$RESULTADOS $CARPETA_RGB $CARPETA_RESULTADOS/$NOMBRE_REALES $CARPETA_RESULTADOS/$SUBCARPETA/$PREFIJO1\_$PREFIJO2\_$NOMBRE_RESULTADOS $CARPETA_RESULTADOS/$SUBCARPETA/R\_$PREFIJO1\_$PREFIJO2\_$NOMBRE_RESULTADOS.txt
	
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
# ff filtrado
#  filtro_enfoque
#  filtro_repujado
#  filtro_enfoque_y_repujado
#  filtro_repujado_y_enfoque
# bl blurear y tamanio_blur
# ei escala_inicial
# zz combinaciones arbitrarias
 


####################################################################################
#			zz - combinaciones arbitrarias
PREFIJO2=zz
source detectorhog_zz_mejores.sh



#exit