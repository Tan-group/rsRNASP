
# rsRNASP

rsRNASP: A distance-dependent statistical potential based on residue separation for RNA 3D structure evaluation.

# Compilation and usage under linux

```
gcc rsRNASP.c -lm -o rsRNASP

# Run in the example dir

rsRNASP 1a9nR.pdb  energy.txt

# output:
   
# 1a9nR.pdb     -3055.902390

Note: the subfolder "data/" and compiled "rsRNASP" should be in the same folder.
```

Please feel free to contact us if you have any question!
zjtan@whu.edu.cn
