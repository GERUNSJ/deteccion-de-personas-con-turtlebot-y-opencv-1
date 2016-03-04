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
CARPETA_RESULTADOS=./../resultados/

#dp_opencv  <carpeta/con/imagenes/rgb>
#                <carpeta/con/imagenes/profundidad | 0 >
#                </dir/al/archivo_de_resultados> (sin extensión)
#                <(1 | 0>(mostrar_detecciones)
#                <clase_de_detector> [parámetro_1_nombre parámetro_1_valor ...]

# DetectorFinal direccion_a_cascada string escala_inicial float convertir_a_gris bool ecualizar_histograma bool scaleFactor float minNeighbors int usar_profundidad_altura bool

CASCADA=./../clasificadores/visionary.net_pedestrian_cascade_web_LBP.xml

# DetectorFinal
NOMBRE_RESULTADOS=final
$PRINCIPAL $CARPETA_RGB $CARPETA_PROFUNDIDAD $CARPETA_RESULTADOS/$NOMBRE_RESULTADOS 0 DetectorFinal direccion_a_cascada $CASCADA

#Uso: dp_resultados /ruta/a/datos_reales (sin extensión)
#                   /ruta/a/datos_estimados (sin extensión)
#                   /ruta/a/archivo_de_resultados.txt (con extensión)

ARCHIVO_RESULTADOS=rfinal
$RESULTADOS $CARPETA_RESULTADOS/$NOMBRE_RESULTADOS $CARPETA_RESULTADOS/$NOMBRE_RESULTADOS $CARPETA_RESULTADOS/$ARCHIVO_RESULTADOS.txt