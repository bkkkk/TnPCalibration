#!/bin/bash

T="$(date +%Y%m%d%H%M%S)"

export RUNDIR=/home/jblanco/WorkArea/CalibrationWork/RunPairing
export OUTPUTDIR=/scratch3/jblanco/CalibrationHistograms
export JODIR=$RUNDIR/jobOptions
export CONTROLDIR=$RUNDIR/control
export SCRIPTDIR=$RUNDIR/scripts

echo "Running SF maker"
