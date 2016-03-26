#!/bin/bash
# Programa principal, que crea los archivos de resultados
PRINCIPAL=./../ejecutables/dp_opencv
# Programa que evalúa los resultados
RESULTADOS=./../ejecutables/dp_resultados

# Límites: todas las imágenes. Es reemplazado por lo que se ponga en el script del set correspondiente.
IMAGEN_INICIAL=1
IMAGEN_FINAL=0


#dp_opencv  <carpeta/con/imagenes/rgb>
#                <carpeta/con/imagenes/profundidad | 0 >
#                </dir/al/archivo_de_resultados> (sin extensión)
#                <(1 | 0>(mostrar_detecciones)
#                <clase_de_detector> [parámetro_1_nombre parámetro_1_valor ...]

#Uso: dp_resultados /ruta/a/datos_reales (sin extensión)
#                   /ruta/a/datos_estimados (sin extensión)
#                   /ruta/a/archivo_de_resultados.txt (con extensión)



# 	# Evaluación
# 	$RESULTADOS $CARPETA_RESULTADOS/$NOMBRE_REALES $CARPETA_RESULTADOS/$SUBCARPETA/$PREFIJO1\_$PREFIJO2\_$NOMBRE_RESULTADOS $CARPETA_RESULTADOS/$SUBCARPETA/R\_$PREFIJO1\_$PREFIJO2\_$NOMBRE_RESULTADOS.txt


funcion_csv_headers () 
{
	ARCHIVO_CSV=$CARPETA_RESULTADOS/$SUBCARPETA/R\_$PREFIJO1\_$PREFIJO2.csv
	
	# Le adjuntamos los headers. Si 1 es la última línea, los headers son 2 y 5, pero hay un \n que borramos, así que 2 y 4.
	printf "$(cat $CARPETA_RESULTADOS/$SUBCARPETA/R\_$PREFIJO1\_$PREFIJO2\_$NOMBRE_RESULTADOS.txt | grep "." | tail -2 | head -1)" > $ARCHIVO_CSV # > overwrite
	printf "$(cat $CARPETA_RESULTADOS/$SUBCARPETA/R\_$PREFIJO1\_$PREFIJO2\_$NOMBRE_RESULTADOS.txt | grep "." | tail -4 | head -1)" >> $ARCHIVO_CSV # >> append
	# Y nueva línea
	printf "\n" >> $ARCHIVO_CSV
}

funcion_csv_normal ()
{	
	ARCHIVO_CSV=$CARPETA_RESULTADOS/$SUBCARPETA/R\_$PREFIJO1\_$PREFIJO2.csv
	
	# Adjuntamos los valores
	printf "$(cat $CARPETA_RESULTADOS/$SUBCARPETA/R\_$PREFIJO1\_$PREFIJO2\_$NOMBRE_RESULTADOS.txt | grep "." | tail -1)" >> $ARCHIVO_CSV # > overwrite
	printf "$(cat $CARPETA_RESULTADOS/$SUBCARPETA/R\_$PREFIJO1\_$PREFIJO2\_$NOMBRE_RESULTADOS.txt | grep "." | tail -3 | head -1)" >> $ARCHIVO_CSV # >> append
	# Y nueva línea
	printf "\n" >> $ARCHIVO_CSV
}
