#!/bin/sh

here=$(pwd)

# Sin PCA
base_dir="outputs/sin_pca/train_size"
clock_dir="${base_dir}/clock"
classif_dir="${base_dir}/classif"
mkdir -p $clock_dir
mkdir -p $classif_dir



echo "Corriendo sin PCA cambiando train size"

c=1

for k in 51 101 501 1001
do 
  for size in 3000 7000 15000 25000 35000 45000 49000
  do
    echo "Loops: $c / 24"
    echo "Usando k=$k y size=$size"
    $here/../codigo/build/tp2  -m 0 -k $k -d ../datos/imdb_tokenized_shuf${size}.csv -c ${clock_dir}/clock_time_k${k}_size${size}.out -o ${classif_dir}/classif_k${k}_size${size}.out
    echo
    c=$((c+1))
  done
done

echo "Done."
echo

