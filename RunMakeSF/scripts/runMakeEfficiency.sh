#!/bin/bash

usage()
{
  cat << EOF
  usage: $0 [options] -i inputDir

  This script runs the scale factor maker

  OPTIONS:
    -h    Show this message
    -l    Label for output dataset
    -m    MC Calibration Histograms
    -d    Data Calibration Histograms
EOF
}

LABEL=
DATAINPUTDIR=
MCINPUTDIR=
while getopts “hl:m:d:” OPTION
do
  case $OPTION in
    h)
      usage
      exit 1
      ;;
    l)
      LABEL=$OPTARG
      ;;
    d)
      DATAINPUTDIR=$OPTARG
      ;;
    m)
      MCINPUTDIR=$OPTARG
      ;;
    ?)
      usage
      exit
      ;;
  esac
done

# Sets up output, scripts and jO directories
source ./setup.sh

if [[ -z $DATAINPUTDIR ]]
then 
  echo "Missing Data Input Directory, use flag -d to set it"
  exit
fi

if [[ -z $MCINPUTDIR ]]
then 
  echo "Missing Data Input Directory, use flag -m to set it"
  exit
fi

if [[ -z $LABEL ]]
then
  echo "Output label missing, use flag -l to set it"
  exit 1
fi

T="$(date +%Y%m%d%H%M%S)"
FULLOUTPUTDIR="$OUTPUTDIR/SFResult_"$LABEL"_$T"

mkdir $FULLOUTPUTDIR
cd $FULLOUTPUTDIR

root -b -l -q "$JODIR/MakeEfficiency.cxx(\"$DATAINPUTDIR\", \"$MCINPUTDIR\",\"$LABEL\")"

echo "See output in $FULLOUTPUTDIR"
