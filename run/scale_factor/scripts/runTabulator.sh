#!/bin/bash

usage()
{
  cat << EOF
  usage: $0 [options] -i inputDir

  This script runs the scale factor maker

  OPTIONS:
    -h    Show this message
    -i    Path to file
EOF
}

INPUTFILE=
VAR=
while getopts “hi:” OPTION
do
  case $OPTION in
    h)
      usage
      exit 1
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

if [[ -z $INPUTFILE ]]
then
  echo Input File missing
  usage
  exit 1
fi

root -b -q -l '$JODIR/Tabulator.cxx+("'$INPUTFILE'")'
