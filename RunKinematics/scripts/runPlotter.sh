#!/bin/bash
source ./setup.sh

root -q -b -l '$JODIR/AllPlotter.cxx+("'$1'","'$2'","'$FOUTPUTDIR'/'$3'")'
