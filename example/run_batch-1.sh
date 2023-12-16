#!/bin/bash

for pdblist in `ls *.pdb`
do
 ./rsRNASP ${pdblist} energy_list1.txt
done
