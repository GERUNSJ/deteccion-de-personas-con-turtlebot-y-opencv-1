#!/bin/bash

echo `date` >> run.txt


# Importamos el script base
source base.sh

####################################################################################
#			SET 1
source set1.sh

TIEMPOINICIO=$SECONDS
source detectorfinal_segunda.sh
TIEMPODF=$(($SECONDS-$TIEMPOINICIO))
source detectorhog_segunda.sh
TIEMPOHOG=$(($SECONDS-$TIEMPODF))

echo "SET1" >> run.txt
echo " TIEMPODF = $TIEMPODF" >> run.txt
echo " TIEMPOHOG = $TIEMPOHOG" >> run.txt

#source otrodetector.sh



####################################################################################
#			SET 235nuevo
source set235nuevo.sh

TIEMPOINICIO=$SECONDS
source detectorfinal_segunda.sh
TIEMPODF=$(($SECONDS-$TIEMPOINICIO))
source detectorhog_segunda.sh
TIEMPOHOG=$(($SECONDS-$TIEMPODF))

echo "SET235nuevo" >> run.txt
echo " TIEMPODF = $TIEMPODF" >> run.txt
echo " TIEMPOHOG = $TIEMPOHOG" >> run.txt