#!/bin/bash

if [[ -z $ROOTCOREDIR ]]; then
  echo "Setting RootCore"
  cd /home/jblanco/WorkArea/CalibrationWork/
  source RootCore/scripts/setup.sh
  cd /home/jblanco/WorkArea/CalibrationWork/RunKinematics/scripts
fi

source $ROOTCOREDIR/../RunKinematics/scripts/setup.sh

usage()
{
  cat << EOF
  usage: $0 [options] -i inputDir

  This script runs the SampleHistograms factory, see MakeKinematics.cxx for more info

  OPTIONS:
    -h    Show this message
    -i    Input dataset (PeriodA, NonPromptJPsi, PromptJPsi)
    -p    post or pre-reprocessing
    -l    Label for output directory
    -e    Number of events to run over (number)
    -t    Which PU profile to use (PeriodA, PeriodB)
EOF
}

INPUTTAG=
LABEL=
MAXEVENTS=0
DOPU=1
PUPROFILE=PeriodA
PROCESSINGFLAG=
while getopts “hi:p:l:e:t:” OPTION
do
  case $OPTION in
    h)
      usage
      exit 1
      ;;
    i)
      INPUTTAG=$OPTARG
      ;;
    p)
      PROCESSINGFLAG=$OPTARG
      ;;
    l)
      LABEL=$OPTARG
      ;;
    e)
      MAXEVENTS=$OPTARG
      ;;
    t)
      PUPROFILE=$OPTARG
      ;;
    ?)
      usage
      exit
      ;;
  esac
done

echo "$PROCESSINGFLAG"

if [[ -z $LABEL ]]; then
  echo Label Missing
  usage
  exit 1
fi

if [[ -z $INPUTTAG ]]; then
  echo Label missing
  usage
  exit 1
fi

if [[ -z $PROCESSINGFLAG ]]; then
  echo Processing flag missing
  usage
  exit 1
fi

PROCESSINGTAGNAME=
INPUTDIRNAME=
if [[ $PROCESSINGFLAG == 1 ]]; then
  INPUTDIRNAME="Batch-13-06-17_VxpVariables"
  PROCESSINGTAGNAME="p1067"
else
  INPUTDIRNAME="Batch-p1328"
  PROCESSINGTAGNAME="p1328"
fi

LUMIFILE="$ROOTCOREDIR/data/PileupReweighting/ilumicalc_histograms_$PUPROFILE.root"
INPUTDIR="/scratch3/jblanco/SMTMiniNtuples/$INPUTDIRNAME/$INPUTTAG/"

echo $INPUTDIR

T="$(date +%Y%m%d%H%M%S)"
OUTPUTDIRNAME="$OUTPUTDIR/kinematics."$T"_"$INPUTTAG"."$PROCESSINGTAGNAME"_"$LABEL""$PUPROFILE""

root -b -l -q "$JODIR/MakeKinematics.cxx(\"$INPUTDIR\",\"$OUTPUTDIRNAME\",\"$LUMIFILE\",$DOPU,$MAXEVENTS)"
echo -e "\v"
echo "Output files in : $OUTPUTDIRNAME"
