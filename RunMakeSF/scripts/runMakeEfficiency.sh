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

if [[ -z $LABEL ]] || [[ -z $DATAINPUTDIR ]] || [[ -z $MCINPUTDIR ]]
then
  echo variable missing
  usage
  exit 1
fi

echo "Please enter a description of the files to be outputted: "
read DESCRIPTION

T="$(date +%Y%m%d%H%M%S)"
FULLOUTPUTDIR="$OUTPUTDIR/output_"$T"_$LABEL"

mkdir $FULLOUTPUTDIR
cd $FULLOUTPUTDIR

root -b -l -q "$JODIR/MakeEfficiency.cxx(\"$DATAINPUTDIR\", \"$MCINPUTDIR\",\"$LABEL\")"

echo $DESCRIPTION >> $FULLOUTPUTDIR/description.txt

if [[ -d $FULLOUTPUTDIR ]]
then
  echo $MCINPUTDIR >> $FULLOUTPUTDIR/mcSource.txt
  echo $DATAINPUTDIR >> $FULLOUTPUTDIR/dataSource.txt
fi

echo "See output in $FULLOUTPUTDIR"
