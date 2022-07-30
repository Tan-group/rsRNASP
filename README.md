
# rsRNASP

rsRNASP: A distance-dependent statistical potential based on residue separation for RNA 3D structure evaluation

# Compilation and usage under linux

```
# Compilation

gcc rsRNASP.c -lm -o rsRNASP

# Usage
```
./rsRNASP XXX.pdb  energy.txt

# A usege example running the “example” dir

 ./rsRNASP 1a9nR.pdb  energy.txt

 Output:
   
 1a9nR.pdb     -3055.902390 kBT
 
Note: the subfolder "data/" and compiled file "rsRNASP" should be in the same folder.
```

Please feel free to contact us if you have any question!
zjtan@whu.edu.cn

References:
[1] Tan YL, Wang X, Shi YZ, Zhang W, Tan ZJ. 2022. rsRNASP: A residue-separation-based statistical potential for RNA 3D structure evaluation. Biophys J. 121: 142-156.
