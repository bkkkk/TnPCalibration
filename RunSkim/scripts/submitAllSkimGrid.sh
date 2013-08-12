#!/bin/bash

if [[ -z $ROOTCOREDIR ]]; then
  echo "Setting RootCore"
  cd /home/jblanco/WorkArea/CalibrationWork/
  source RootCore/scripts/setup.sh
  cd /home/jblanco/WorkArea/CalibrationWork/RunSkim/scripts
fi

source $ROOTCOREDIR/../RunSkim/scripts/setup.sh

# Print help
usage()
{
  cat << EOF
  usage: $0 [options] -i inputDir

  Grid submission tool for TnP skimming

  OPTIONS:
    -h    Show this message
    -i    Input Sample (PeriodA, ppJPsi, bbJPsi)
    -p    (0, 1) Preprocessed or Reprocessed
    -l    Label appends to the end of the submission directory
    -t    Trigger file for data
    -b    Branches file for skimming
EOF
}

if which dq2-ls &> /dev/null; then
  echo "All is well"
else
  echo "Setup dq2 yourself you lazy git"
  exit 1
fi

INPUTTAG=
PROCESSINGFLAG=
OUTPUTLABEL=
TRIGGERFILE=$CONTROLDIR/triggers.txt
BRANCHESFILE=$CONTROLDIR/branches.txt
while getopts “hp:l:tb” OPTION
do
  case $OPTION in
    h)
      usage
      exit 1
      ;;
    p)
      PROCESSINGFLAG=$OPTARG
      ;;
    l)
      OUTPUTLABEL=$OPTARG
      ;;
    t)
      TRIGGERFILE=$OPTARG
      ;;
    b)
      BRANCHESFILE=$OPTARG
      ;;
    ?)
      usage
      exit
      ;;
  esac
done

if [[ -z $PROCESSINGFLAG ]]
  then
  echo "Processing tag not set"
  usage 
  exit 1
fi

if [[ -z $OUTPUTLABEL ]]; then
  echo "Output label is missing"
  usage
  exit 1
fi

PROCESSINGTAGNAME=
LUMIFILE=
if [[ $PROCESSINGFLAG == 1 ]]; then
  LUMIFILE="$ROOTCOREDIR/data/GoodRunsLists/data12_8TeV.periodAllYear_DetStatus-v54-pro13-04_DQDefects-00-00-33_PHYS_StandardGRL_All_Good.xml"
  DATASET="data12_8TeV.*.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067/";
else
  LUMIFILE="$ROOTCOREDIR/data/GoodRunsLists/data12_8TeV.periodAllYear_DetStatus-v58-pro14-01_DQDefects-00-00-33_PHYS_StandardGRL_All_Good.xml"
  DATASET="data12_8TeV.*.physics_Muons.PhysCont.NTUP_SMWZ.grp14_v01_p1328_p1329/";
fi

echo "Submitting Grid job with dataset name $DATASET"
T="$(date +%Y%m%d%H%M%S)"
SUBMITDIR="skim_AllData12.${PROCESSINGTAGNAME}_$T.$OUTPUTLABEL"
SUBMITPATH="/scratch3/jblanco/SMTMiniNtuplesSubmitDir/$SUBMITDIR"
OUTPUTSET="user.jayb88.$SUBMITDIR"
echo "Submission directory is $SUBMITDIR with output dataset name: $OUTPUTSET"

root -l -q -b "../jobOptions/RunSkimGridSubmit.cxx(\"$DATASET\",\"$OUTPUTSET\",\"$SUBMITPATH\",\"$BRANCHESFILE\",\"$TRIGGERFILE\",\"$LUMIFILE\")"
