#!/bin/bash

source ./setup.sh

usage()
{
  cat << EOF
  usage: $0 [options] -i inputDir

  This script runs the histogram factory, see MakeHistograms.cxx for more info

  OPTIONS:
    -h    Show this message
    -l    Label for output dataset
    -L    iLumiCalc File for period
    -i    Input Directory
EOF
}

LABEL=
MAXEVENTS=
ILUMICALCFILE=
INPUTDIR=
while getopts “hL:l:i:” OPTION
do
  case $OPTION in
    h)
      usage
      exit 1
      ;;
    L)
      ILUMICALCFILE=$OPTARG
      ;;
    l)
      LABEL=$OPTARG
      ;;
    i)
      INPUTDIR=$OPTARG
      ;;
    ?)
      usage
      exit
      ;;
  esac
done

if [[ -z $LABEL ]] || [[ -z $INPUTDIR ]]
then
  echo variable missing
  usage
  exit 1
fi

OUTPUTDIRNAME="$OUTPUTDIR/dataSet_"$T"_$LABEL"

root -q -b -l ''$JODIR'/MakeHistogramsFaraday.cxx("'$INPUTDIR'","'$OUTPUTDIRNAME'","'$ILUMICALCFILE'")'

echo "All Done"
