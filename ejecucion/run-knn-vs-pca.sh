#!/bin/bash

here=$(pwd)


base_dir="outputs/knn-vs-pca"
clock_dir="${base_dir}/clock"
classif_dir="${base_dir}/classif"
cache_dir="${base_dir}/cache"

mkdir -p $clock_dir
mkdir -p $classif_dir
mkdir -p $cache_dir

echo "KNN vs PCA"

echo "PCA:"
c=1
for k in 51
  do
    for a in 100
       do 
       	  for i in {1..20}
       	  	do
	          echo "Loops: $c / 20"
	          $here/../codigo/build/tp2  -m 1 -t 7 -a ${a} -p 20 -k ${k} -c ${clock_dir}/clock_time_${k}-${a}_i${i}.out -o ${classif_dir}/classif_${k}-${a}_i${i}.out -s ${cache_dir}/mat.out
	          echo
	          c=$((c+1))
	        done
      done
 done

rm -rf $cache_dir

echo "KNN:"
c=1
for k in 51
  do
	for i in {1..20}
  	do
		echo "Loops: $c / 20"
		$here/../codigo/build/tp2  -m 0 -k ${k} -c ${clock_dir}/clock_time_${k}_i${i}.out -o ${classif_dir}/classif_${k}_i${i}.out
		echo
		c=$((c+1))
	done
 done

echo "Done."
