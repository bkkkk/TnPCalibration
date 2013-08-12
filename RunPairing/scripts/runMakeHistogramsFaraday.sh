#!/bin/bash

source ./setup.sh

usage() {
  cat << EOF
  usage: $0 [options] -i inputDir

  This script runs the histogram factory, see MakeHistograms.cxx for more info

  OPTIONS:
    -h    Show this message
    -i    Period name
    -p    Processing Tag. p1067/p1328
    -l    Label for output dataset
    -L    Which Period to use for prw

EOF
}

LABEL=
MAXEVENTS=
ILUMICALCFILE=
INPUTSAMPLE=
PROCESSINGTAG=
while getopts “hL:l:i:p:” OPTION
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
      INPUTSAMPLE=$OPTARG
      ;;
    p)
      PROCESSINGTAG=$OPTARG
      ;;
    ?)
      usage
      exit
      ;;
  esac
done

if [[ -z $LABEL ]]
then
  echo "Label is missing please use -l to set the output label"
  exit 1
fi

if [[ -z $INPUTSAMPLE ]]
  then
  echo "Input sample is missing use -i to set the input sample"
  exit 1
fi

if [[ -z $PROCESSINGTAG ]]
  then
  echo "Processing tag is missing, use -p to set processing tag"
  exit 1
fi


root -q -b -l "$JODIR/MakeHistogramsFaraday.cxx(\"$PROCESSINGTAG\", \"$INPUTSAMPLE\",\"$LABEL\",\"$ILUMICALCFILE\")"

echo "All Done"