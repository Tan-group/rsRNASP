#!/bin/bash

 N=`ls *.pdb | wc -l`
 ./rsRNASP-batch ./ ${N} energy_list2.txt
