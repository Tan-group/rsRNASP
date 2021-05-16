#!/bin/bash
for i in 3D2V  3RG5  4ENC  4JRC  4LVW  4WFL  4ZNP  5M0H  5U3G  6DVK  6JXM  6N5P 3Q3Z  3SKL  4FRN  4K27  4PLX  4Y1M  5BTM  5ML7  6DLR  6E8U  6MJ0  6P2H 3R4F  3SUX  4JF2  4KQY  4PQV  4YAZ  5LYS  5OB3  6DME  6H0R  6N2V
do
 cd RMSD/
 wc -l ${i}.rmsd
 cd ../DI/
 wc -l ${i}.DI
 cd ../
done
