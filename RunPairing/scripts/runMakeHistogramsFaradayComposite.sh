#!/bin/bash

source ./setup.sh

usage()
{
  cat << EOF
  usage: $0 [options] -i inputDir

  This script runs the histogram factory for multiple samples, see MakeHistograms.cxx for more info

  OPTIONS:
    -h    Show this message
    -l    Label for output dataset
    -L    iLumiCalc File for composite period
    -i    List of periods to composite
EOF
}

LABEL=
MAXEVENTS=
ILUMICALCFILE=
INPUTDIRS=
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
      INPUTDIRS=$OPTARG
      ;;
    ?)
      usage
      exit
      ;;
  esac
done

if [[ -z $LABEL ]]
then
  echo "Output label is missing, use -l LABEL to set it"
  exit 1
fi

if [[ -z $INPUTDIRS ]]
then
  echo "Input samples list not set, use -i flag"
  exit 1
fi

INPUTDIRLIST=$(awk -v ORS=, '{ print $1 }' $INPUTDIRS | sed 's/,$//')

OUTPUTDIRNAME="$OUTPUTDIR/CompositePairing_"$T"_$LABEL"

root -q -b -l "$JODIR/MakeHistogramsFaradayComposite.cxx(\"$INPUTDIRLIST\",\"$LABEL\",\"$OUTPUTDIRNAME\",\"$ILUMICALCFILE\")"

echo "All Done"
