#!/bin/bash

usage()
{
  cat << EOF
  usage: $0 [options] -i inputDir

  This script runs the scale factor maker

  OPTIONS:
    -h    Show this message
    -l    Label for output dataset
    -i    Path to file
EOF
}

LABEL=
INPUTFILE=
VAR=
while getopts “hl:i:” OPTION
do
  case $OPTION in
    h)
      usage
      exit 1
      ;;
    l)
      LABEL=$OPTARG
      ;;
    i)
      INPUTFILE=$OPTARG
      ;;
    ?)
      usage
      exit
      ;;
  esac
done

# Sets up output, scripts and jO directories
source ./setup.sh

if [[ -z $LABEL ]] || [[ -z $INPUTFILE ]]
then
  echo variable missing
  usage
  exit 1
fi

OUTPUTPATH=$ROOTCOREDIR/../run/scale_factor/finalOutput/SFPlot-$LABEL/

root -b -q -l "$JODIR/Plotter.cxx(\"$INPUTFILE\",\"$OUTPUTPATH\")"
root -b -q -l "$JODIR/PlotterSingle.cxx(\"$INPUTFILE\",\"$OUTPUTPATH\")"
