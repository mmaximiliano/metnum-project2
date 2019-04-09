#!/bin/sh

here=$(pwd)

# Sin PCA
base_dir="outputs/con_pca/power_iterations"
clock_dir="${base_dir}/clock"
classif_dir="${base_dir}/classif"
cache_dir="${base_dir}/cache"
mkdir -p $clock_dir
mkdir -p $classif_dir
mkdir -p $cache_dir

echo "Corriendo con PCA cambiando numero de iteraciones en metodo de la potencia"

c=1

for k in 51 101
do 
  for its in 3 5 10 20 30
  do
    echo "Loops: $c / 10"
    echo "Usando k=$k y power iterations=$its"
    $here/../codigo/build/tp2  -m 1 -t 7 -a 100 -k $k -p $its -d ../datos/imdb_tokenized.csv -c ${clock_dir}/clock_time_its${its}_a100_k${k}.out -o ${classif_dir}/classif_its${its}_a100_k${k}.out -v ${cache_dir}/autovec_its${its}_alpha100.out -s ${cache_dir}/mat_covarianza.out
    echo
    c=$((c+1))
  done
done

echo "Done."
echo

