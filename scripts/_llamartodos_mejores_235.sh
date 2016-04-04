#!/bin/bash

echo `date` >> run.txt


# Importamos el script base
source base.sh


####################################################################################
#			SET 235
source set235nuevo.sh

TIEMPOINICIO=$SECONDS
source detectorfinal_mejores.sh
TIEMPODF=$(($SECONDS-$TIEMPOINICIO))
source detectorhog_mejores.sh
TIEMPOHOG=$(($SECONDS-$TIEMPODF))

echo "SET235" >> run.txt
echo " TIEMPODF = $TIEMPODF" >> run.txt
echo " TIEMPOHOG = $TIEMPOHOG" >> run.txt