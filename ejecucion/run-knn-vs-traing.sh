#!/bin/bash

here=$(pwd)

# Sin PCA
base_dir="outputs/sin_pca/train_size-time"
clock_dir="${base_dir}/clock"
mkdir -p $clock_dir
mkdir -p $classif_dir

echo "Corriendo sin PCA cambiando train size muchas veces"

c=1

for k in 51
do 
  for size in 25000 35000 45000 49000
  do
  	for i in {1..20}
  	do
		echo "Loops: $c / 60"
		echo "Usando k=$k y size=$size, iteracion $i"
		$here/../codigo/build/tp2  -m 0 -k $k -d ../datos/imdb_tokenized_shuf${size}.csv -c ${clock_dir}/clock_time_k${k}_size${size}_i${i}.out -o ${classif_dir}/classif_k${k}_size${size}_i${i}.out
		echo
		c=$((c+1))
	done
  done
done

echo "Done."
echo
