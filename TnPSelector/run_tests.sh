#!/bin/bash

echo "Running unit tests:"

for test_runner in test-bin/*
do
  if test -f $test_runner
  then
    if $test_runner
    then
      echo $test_runner PASS
    else
      echo "Error in test"
    fi
    echo ""
  fi
done