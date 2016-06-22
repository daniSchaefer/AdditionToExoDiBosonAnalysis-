#!bin/bash


mass=(800 1000 1200 1400 1600 1800 2000 2500 3000 3500 4000 4500)
category=(\"HPW\" \"HPZ\" \"HP\")
for i in "${mass[@]}"
do
    for cate in "${category[@]}"
    do
	root -b -q "narrowShapes.C(\"el\", ${cate}, ${i})"
# 	root -b -q 'narrowShapes.C("mu",$cate,$i)'
    done
done


# root -b -q 'narrowShapes.C("el","HPW",800)'