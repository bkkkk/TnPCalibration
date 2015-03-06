#!/bin/bash

if [[ -z $ROOTCOREDIR ]]; then
  echo "Setting RootCore"
  cd /home/jblanco/WorkArea/CalibrationWork/
  source RootCore/scripts/setup.sh
  cd /home/jblanco/WorkArea/CalibrationWork/run/skim/scripts
fi

source $ROOTCOREDIR/../run/skim/scripts/setup.sh

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
while getopts “hi:p:l:tb” OPTION
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

if [[ -z $INPUTTAG ]]
  then
  echo "Input tag not set"
  usage 
  exit 1
fi

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
  PROCESSINGTAGNAME=p1067
  LUMIFILE="$ROOTCOREDIR/data/GoodRunsLists/data12_8TeV.periodAllYear_DetStatus-v54-pro13-04_DQDefects-00-00-33_PHYS_StandardGRL_All_Good.xml"
  if [[ $INPUTTAG == "PeriodA" ]]; then DATASET="data12_8TeV.periodA.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067/";
  elif [[ $INPUTTAG == "PeriodB" ]]; then DATASET="data12_8TeV.periodB.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067/";
  elif [[ $INPUTTAG == "PeriodC" ]]; then DATASET="data12_8TeV.periodC.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067/";
  elif [[ $INPUTTAG == "PeriodD" ]]; then DATASET="data12_8TeV.periodD.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067/";
  elif [[ $INPUTTAG == "PeriodE" ]]; then DATASET="data12_8TeV.periodE.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067/";
  elif [[ $INPUTTAG == "PeriodG" ]]; then DATASET="data12_8TeV.periodG.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067/";
  elif [[ $INPUTTAG == "PeriodH1" ]]; then DATASET="data12_8TeV.periodH1.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067/";
  elif [[ $INPUTTAG == "PeriodH2" ]]; then DATASET="data12_8TeV.periodH2.physics_Muons.PhysCont.NTUP_SMWZ.grp13_v01_p1067/";
  elif [[ $INPUTTAG == "PromptJPsi" ]]; then DATASET="mc12_8TeV.208001.Pythia8B_AU2_CTEQ6L1_pp_Jpsimu4mu4.merge.NTUP_SMWZ.e1331_a159_a173_r3549_p1067/";
  else 
    echo "Period not available in p1067";
    exit 1
  fi
else
  PROCESSINGTAGNAME=p1328
  LUMIFILE="$ROOTCOREDIR/data/GoodRunsLists/data12_8TeV.periodAllYear_DetStatus-v58-pro14-01_DQDefects-00-00-33_PHYS_StandardGRL_All_Good.xml"
  if [[ $INPUTTAG == "PeriodA" ]]; then DATASET="data12_8TeV.periodA.physics_Muons.PhysCont.NTUP_SMWZ.grp14_v01_p1328_p1329/";
  elif [[ $INPUTTAG == "PeriodB" ]]; then DATASET="data12_8TeV.periodB.physics_Muons.PhysCont.NTUP_SMWZ.grp14_v01_p1328_p1329/";
  elif [[ $INPUTTAG == "PeriodC" ]]; then DATASET="data12_8TeV.periodC.physics_Muons.PhysCont.NTUP_SMWZ.grp14_v01_p1328_p1329/";
  elif [[ $INPUTTAG == "PeriodD" ]]; then DATASET="data12_8TeV.periodD.physics_Muons.PhysCont.NTUP_SMWZ.grp14_v01_p1328_p1329/";
  elif [[ $INPUTTAG == "PeriodE" ]]; then DATASET="data12_8TeV.periodE.physics_Muons.PhysCont.NTUP_SMWZ.grp14_v01_p1328_p1329/";
  elif [[ $INPUTTAG == "PeriodG" ]]; then DATASET="data12_8TeV.periodG.physics_Muons.PhysCont.NTUP_SMWZ.grp14_v01_p1328_p1329/";
  elif [[ $INPUTTAG == "PeriodH" ]]; then DATASET="data12_8TeV.periodH.physics_Muons.PhysCont.NTUP_SMWZ.grp14_v01_p1328_p1329/";
  elif [[ $INPUTTAG == "PeriodI" ]]; then DATASET="data12_8TeV.periodI.physics_Muons.PhysCont.NTUP_SMWZ.grp14_v01_p1328_p1329/";
  elif [[ $INPUTTAG == "PeriodJ" ]]; then DATASET="data12_8TeV.periodJ.physics_Muons.PhysCont.NTUP_SMWZ.grp14_v01_p1328_p1329/";
  elif [[ $INPUTTAG == "PeriodL" ]]; then DATASET="data12_8TeV.periodL.physics_Muons.PhysCont.NTUP_SMWZ.grp14_v01_p1328_p1329/";
  elif [[ $INPUTTAG == "PromptJPsi" ]]; then DATASET="mc12_8TeV.208002.Pythia8B_AU2_CTEQ6L1_pp_Jpsimu6mu6.merge.NTUP_SMWZ.e1331_a159_a180_r3549_p1328/";
  elif [[ $INPUTTAG == "NonPromptJPsi" ]]; then DATASET="mc12_8TeV.208202.Pythia8B_AU2_CTEQ6L1_bb_Jpsimu6mu6.merge.NTUP_SMWZ.e1454_a159_a180_r3549_p1328/";
  else
    echo "Period not available in p1328";
    exit 1
  fi
fi

echo "Submitting Grid job with dataset name $DATASET"
T="$(date +%Y%m%d%H%M%S)"
SUBMITDIR="skim_$INPUTTAG.${PROCESSINGTAGNAME}_$T.$OUTPUTLABEL"
SUBMITPATH="/scratch3/jblanco/SMTMiniNtuplesSubmitDir/$SUBMITDIR"
OUTPUTSET="user.jayb88.$SUBMITDIR"
echo "Submission directory is $SUBMITDIR with output dataset name: $OUTPUTSET"

root -l -q -b "../jobOptions/RunSkimGridSubmit.cxx(\"$DATASET\",\"$OUTPUTSET\",\"$SUBMITPATH\",\"$BRANCHESFILE\",\"$TRIGGERFILE\",\"$LUMIFILE\")"
