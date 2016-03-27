#!/bin/bash

# Importamos el script base
source base.sh

####################################################################################
#			SET 1
source set1.sh

TIEMPOINICIO=$SECONDS
source detectorfinal.sh
TIEMPODF=$(($SECONDS-$TIEMPOINICIO))
source detectorhog.sh
TIEMPOHOG=$(($SECONDS-$TIEMPODF))

echo "SET1" >> run.txt
echo " TIEMPODF = $TIEMPODF" >> run.txt
echo " TIEMPOHOG = $TIEMPOHOG" >> run.txt

#source otrodetector.sh



####################################################################################
#			SET 235
source set235.sh

TIEMPOINICIO=$SECONDS
source detectorfinal.sh
TIEMPODF=$(($SECONDS-$TIEMPOINICIO))
source detectorhog.sh
TIEMPOHOG=$(($SECONDS-$TIEMPODF))

echo "SET235" >> run.txt
echo " TIEMPODF = $TIEMPODF" >> run.txt
echo " TIEMPOHOG = $TIEMPOHOG" >> run.txt