#!/bin/bash

source ./setup.sh

SAMPLEPATH=$1

echo "Running skim procedure on local file with path: '$SAMPLEPATH'"

T="$(date +%Y_%m_%d_%H_%M_%S)"

echo "Enter a description of the dataset: "
read DESCRIPTION

echo "Submitting local job"
root -l '../jobOptions/RunSkimLocal.cxx("'$SAMPLEPATH'","dataSet_'"$T"'")'
