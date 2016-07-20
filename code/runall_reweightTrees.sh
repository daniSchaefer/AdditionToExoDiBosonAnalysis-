#!/bin/bash

# masses=(800 900 1000 1500 1800 2000 2500 3000 3500 4500)
# rel_width=(0.009 0.012 0.015 0.034 0.048 0.060 0.093 0.135 0.183 0.303)

# for i in {0..9}
# do
#   w=$(echo ${rel_width[$i]}*${masses[$i]} | bc)
#   namelep="RSGrav_WW_WlepWhad_width${rel_width[$i]}_M${masses[$i]}.root"
#   namehad="RSGrav_WW_WhadWhad_width${rel_width[$i]}_M${masses[$i]}.root"
#   ./reweightTree.exe $namelep em
#   #./reweightTree.exe $namehad had
# done

masses=(800 1200 1500 2000 3000 3500 4000 4500)
rel_width=(0.02 0.02 0.02 0.02 0.02 0.02 0.02 0.02)

for i in {0..7}
do
  namelep="RSGrav_WW_WlepWhad_width${rel_width[$i]}_M${masses[$i]}.root"
  #namehad="RSGrav_WW_WhadWhad_width${rel_width[$i]}_M${masses[$i]}.root"
  ./reweightTree.exe $namelep em
  #./reweightTree.exe $namehad had
done

masses=(800 800 1200 1200 1200 1500 1500 1500 2000 2000 3000 3500 3500 4000)
rel_width=(0.09 0.17 0.12 0.24 0.43 0.05 0.15 0.34 0.26 0.10 0.21 0.29 0.05 0.07)

for i in {0..13}
do
  namelep="RSGrav_WW_WlepWhad_width${rel_width[$i]}_M${masses[$i]}.root"
  #namehad="RSGrav_WW_WhadWhad_width${rel_width[$i]}_M${masses[$i]}.root"
  ./reweightTree.exe $namelep em
  #./reweightTree.exe $namehad had
done
