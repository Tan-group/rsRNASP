#!/bin/bash

for pdblist in `ls *.pdb`
do
 ./rsRNASP ${pdblist} energy_list.txt
done
