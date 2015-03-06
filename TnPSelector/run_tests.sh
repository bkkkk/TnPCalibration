#!/bin/bash

VALGRIND=

echo "Running unit tests:"

for test_runner in test-bin/*
do
  if test -f $test_runner
  then
    if $VALGRIND $test_runner 2>> test-bin/tests.log
    then
      echo $test_runner PASS
    else
      echo "Error in test"
    fi
    echo ""
  fi
done