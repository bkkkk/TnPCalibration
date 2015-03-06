#!/bin/bash
source ./setup.sh

root -q -b -l '$JODIR/ComparePlotter.cxx("'$1'","'$2'")'
