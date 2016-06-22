#!/bin/bash

#makes plots for narrow fit to these models 
#saves the picutes in /usr/users/dschaefer/root/results/testFit/semileptonic/ToWW/narrow/
#and saves the fit result in /usr/users/dschaefer/root/results/testFit/semileptonic/ToWW/logfiles/
#the bulk graviton is saved as: Narrow_Fit_BulkGrav__M2000_el_HP.txt


category=(\"HP\" \"HPW\" \"HPZ\")
model=(\"BulkGrav\" \"Wprime\" \"Zprime\")
decayMode=("WW_lvjj")

for c in "${category[@]}"
do
  for m in "${model[@]}"
  do
    for d in "${decayMode[@]}"
    do
      root -b -q "run_checkFitCBBW.C($m,\"el\",$c,$d,1) "
      root -b -q "run_checkFitCBBW.C($m,\"mu\",$c,$d,1) "
      
    done
  done
done


#check fits for wide samples (here the narrow fit for RSGrav is used!)

category=(\"HP\" \"HPW\" \"HPZ\")
model=(\"BulkGrav\" \"Wprime\" \"Zprime\" \"RSGrav\" \"Radion\")
decayMode=("WW_lvjj")

for c in "${category[@]}"
do
  for m in "${model[@]}"
  do
    for d in "${decayMode[@]}"
    do
      root -b -q "run_checkFitCBBW.C($m,\"el\",$c,$d,) "
      root -b -q "run_checkFitCBBW.C($m,\"mu\",$c,$d,) "
      
    done
  done
done


# now that all the fit results are there, the interpolation files can be made:
#saved in: /home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/interpolationFiles/BulkG_WW_lvjj_el_HPZ_my.root
#if Overwrite =1 we omit the _my and jennifers files get overwritten.

for c in "${category[@]}"
do
  root -b -q "makeInterpolationFile.C(\"el\",$c,0)"
  root -b -q "makeInterpolationFile.C(\"mu\",$c,0)"
done

#make interpolation files for the additional degrees of freedom:
# write them here:  "/home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/interpolationFiles/InterpolateHighMassCorrections_ModelName_category.root
category=(\"HP\" \"HPW\" \"HPZ\")
model=(\"BulkGrav\" \"Wprime\" \"Zprime\" \"RSGrav\" \"Radion\")
decayMode=("WW_lvjj")

for c in "${category[@]}"
do
  for m in "${model[@]}"
  do
    for d in "${decayMode[@]}"
    do
      root -b -q "makeInterpolationFileForDoF.C($m,$c,$d)"
    done
  done
done

root -b -q 'run_PrintTablesForEffTests.C'




