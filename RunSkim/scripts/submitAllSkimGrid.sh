#!/bin/bash

while read sample; do 
  ./submitSkimGrid.sh -i $sample -l full -p 0
done < ../control/samples_p1328.txt
