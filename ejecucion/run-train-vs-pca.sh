#!/bin/bash

here=$(pwd)

# Sin PCA
base_dir="outputs/con_pca/train_size"
clock_dir="${base_dir}/clock"
classif_dir="${base_dir}/classif"
cache_dir="${base_dir}/cache"
mkdir -p $clock_dir
mkdir -p $classif_dir
mkdir -p $cache_dir



echo "Corriendo con PCA cambiando train size"

c=1

# Solo con k = 51 para tiempos

for k in 51 
do 
  for size in 15000 25000 35000 45000 49000
  do
  	for i in {1..20}
  	do
	    echo "Loops: $c / 100"
	    echo "Usando k=$k y size=$size"
	    $here/../codigo/build/tp2  -m 1 -t 7 -p 20 -a 100 -k $k -d ../datos/imdb_tokenized_shuf${size}.csv -c ${clock_dir}/clock_time_k${k}_size${size}_i${i}.out -o ${classif_dir}/classif_k${k}_size${size}_i${i}.out -s ${cache_dir}/mat_${size}.out
	    echo
	    c=$((c+1))
	done
  done
done

c=1

for k in 501 1001 
do 
  for size in 15000 25000 35000 45000 49000
  do
  	for i in 1
  	do
	    echo "Loops: $c / 10"
	    echo "Usando k=$k y size=$size"
	    $here/../codigo/build/tp2  -m 1 -t 7 -p 20 -a 100 -k $k -d ../datos/imdb_tokenized_shuf${size}.csv -c ${clock_dir}/clock_time_k${k}_size${size}_i${i}.out -o ${classif_dir}/classif_k${k}_size${size}_i${i}.out -s ${cache_dir}/mat_${size}.out
	    echo
	    c=$((c+1))
	done
  done
done

echo "Done."
echo

