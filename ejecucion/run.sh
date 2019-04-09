!/bin/sh

here=$(pwd)

# Sin PCA
mkdir -p outputs/sin_pca/test-k/clock
mkdir -p outputs/sin_pca/test-k/classif

echo "Corriendo sin PCA"

c=1

for i in 1 3 5 11 51 101 501 1001 10001 24999
#for i in 10001 24999
  do 
     echo "Loops: $c/10"
     $here/../codigo/build/tp2  -m 0 -k $i -c outputs/sin_pca/test-k/clock/clock_time_$i.out -o outputs/sin_pca/test-k/classif/classif_$i.out
     echo
     c=$((c+1))
 done

 echo "Done."
 echo

here=$(pwd)

# Sin PCA
mkdir -p outputs/sin_pca/test-k/frec/clock
mkdir -p outputs/sin_pca/test-k/frec/classif

echo "Corriendo sin PCA con f = 0.001 y F = 0.995"

c=1

for i in 1 5 51 101 1001 10001 24999
#for i in 10001 24999
 do 
    echo "Loops: $c/7"
    $here/../codigo/build/tp2  -m 0 -k $i -f 0.001 -F 0.995 -c outputs/sin_pca/test-k/frec/clock/clock_time_$i.out -o outputs/sin_pca/test-k/frec/classif/classif_$i.out
    echo
    c=$((c+1))
done

echo "Done."
echo

# #Con PCA
# mkdir -p outputs/PCA/test-alpha/clock
# mkdir -p outputs/PCA/test-alpha/classif
# mkdir -p outputs/PCA/test-alpha/autovecs
# mkdir -p outputs/PCA/test-alpha/matcov

# echo "Corriendo con PCA"

# c=1
# for j in 10 50 100 300 500
#   do
#     for i in 1 51 101 501 1001 10001 24999
#        do 
#           echo "Loops: $c / 35"
#           $here/../codigo/build/tp2  -m 1 -t 7 -a $j -p 20 -k $i -c outputs/PCA/test-alpha/clock/clock_time_$i-$j.out -o outputs/PCA/test-alpha/classif/classif_$i-$j.out -v outputs/PCA/test-alpha/autovects/autovec_$j.out -s outputs/PCA/test-alpha/matcov/mat.out
#           echo
#           c=$((c+1))
#       done
#  done

#  echo "Done."
