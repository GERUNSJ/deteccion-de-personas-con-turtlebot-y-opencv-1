#!/bin/bash
# Programa principal, que crea los archivos de resultados
PRINCIPAL=./../ejecutables/dp_opencv
# Programa que evalúa los resultados
RESULTADOS=./../ejecutables/dp_resultados
# Carpeta con imagenes rgb
CARPETA_RGB=./../../dp_databases/set1_color
# Carpeta con imagenes de profundidad
CARPETA_PROFUNDIDAD=./../../dp_databases/set1_depth16
# Carpeta con los resultados
CARPETA_RESULTADOS=./../resultados
# Archivo con las coordenadas reales de las personas en las imágenes
NOMBRE_REALES=reales

#dp_opencv  <carpeta/con/imagenes/rgb>
#                <carpeta/con/imagenes/profundidad | 0 >
#                </dir/al/archivo_de_resultados> (sin extensión)
#                <(1 | 0>(mostrar_detecciones)
#                <clase_de_detector> [parámetro_1_nombre parámetro_1_valor ...]

#Uso: dp_resultados /ruta/a/datos_reales (sin extensión)
#                   /ruta/a/datos_estimados (sin extensión)
#                   /ruta/a/archivo_de_resultados.txt (con extensión)

