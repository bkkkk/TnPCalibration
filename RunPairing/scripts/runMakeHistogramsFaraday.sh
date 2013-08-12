#!/bin/bash

source ./setup.sh

usage() {
  cat << EOF
  usage: $0 [options] -i inputDir

  This script runs the histogram factory, see MakeHistograms.cxx for more info

  OPTIONS:
    -h    Show this message
    -i    Period name
    -p    p1067
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

if [[ -z $LABEL ]] || [[ -z $INPUTSAMPLE ]] || [[ -z $PROCESSINGTAG ]]
then
  echo variable missing
  exit 1
fi

root -q -b -l "$JODIR/MakeHistogramsFaraday.cxx(\"$PROCESSINGTAG\", \"$INPUTSAMPLE\",\"$LABEL\",\"$ILUMICALCFILE\")"

echo "All Done"