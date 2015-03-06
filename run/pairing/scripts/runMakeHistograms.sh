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
    -e    Number of events to run over (number)
    -L    iLumiCalc File for period
    -i    Input Directory
EOF
}

LABEL=
MAXEVENTS=
ILUMICALCFILE=
INPUTDIR=
while getopts “hL:l:e:i:” OPTION
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
    e)
      MAXEVENTS=$OPTARG
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

echo "Please enter a description of the files to be outputted: "
read DESCRIPTION

OUTPUTDIRNAME="$OUTPUTDIR/dataSet_"$T"_$LABEL"

echo "Looping over : ""$MAXEVENTS"

root -q -b -l ''$JODIR'/MakeHistograms.cxx("'$INPUTDIR'","'$OUTPUTDIRNAME'","'$ILUMICALCFILE'")'

echo $DESCRIPTION >> $OUTPUTDIRNAME/description.txt

if [[ -d $OUTPUTDIRNAME ]]
then
  echo $INPUTDIR >> $OUTPUTDIRNAME/source.txt
fi

echo "All Done"
