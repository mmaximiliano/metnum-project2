#!/bin/bash

here=$(pwd)

mkdir -p outputs/sin_pca/frec/clock
mkdir -p outputs/sin_pca/frec/classif

for i in 51 101
  do
    for f in 0 0.001 0.01 0.015
      do
        for F in 0.9 0.99 0.995 1
          do
          echo "K: $i"
          echo "f: $f"
          echo "F: $F"
           echo "Loops: $c"
           $here/../codigo/build/tp2  -m 0 -k $i -f $f -F $F -c outputs/sin_pca/frec/clock/clock_time_$i_f$f_F$F.out -o outputs/sin_pca/frec/classif/classif_$i_f$f_F$F.out
           echo
           c=$((c+1))
        done
    done
done

 echo "Done."
