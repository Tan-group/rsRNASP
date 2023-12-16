
# rsRNASP

rsRNASP: A distance-dependent statistical potential based on residue separation for RNA 3D structure evaluation

# Compilation and usage under linux

```
# Compilation

gcc rsRNASP.c -lm -o rsRNASP      //  scoring one conformation
or
gcc rsRNASP-batch.c -lm -o rsRNASP-batch      // scoring a batch of conformations; updated on December 16, 2023 for improving the scoring efficiency

# Usage

./rsRNASP   XXX.pdb   energy.txt
or
./rsRNASP-batch   ${path}   ${N}   energy_list.txt     // "path" is the folder path where the batch of conformations are located, and "N" is the number of conformations to be evaluated;
                                                                                                     //  updated on December 16, 2023 for improving the scoring efficiency

Note: the subfolder "data/" and the compiled file "rsRNASP" or "rsRNASP-batch" should be in the same folder.
```

# An example running in the “example” dir
```
 ./rsRNASP 1a9nR.pdb  energy.txt
or
 N=`ls *.pdb | wc -l`
 ./rsRNASP-batch   ./   ${N}   energy_list.txt     // updated on December 16, 2023 for improving the scoring efficiency

 Output:

 1a9nR.pdb     -3055.902390 kBT
or
 1h4sT.pdb     -7743.385764 kBT
 1a9nR.pdb     -3055.902390 kBT

```
Please feel free to contact us if you have any question!
zjtan@whu.edu.cn

Reference:                                      
[1] Tan YL, Wang X, Shi YZ, Zhang W, & Tan ZJ. 2022. rsRNASP: A residue-separation-based statistical potential for RNA 3D structure
evaluation. Biophys J. 121(1): 142-156.


