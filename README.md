# Métodos Numéricos - TP2
Análisis de Sentimiento

## Ejecutable
Para compilar el ejecutable, correr
```
mkdir -p codigo/build
cd codigo/build
cmake ..
make tp2
```

Luego, este se puede correr de la siguiente manera:
```
 ./tp2 -m <method> -d <dataset_path> -o <classif>
```
La misma corresponde a lo requerido en el enunciado del TP.

Además, el ejecutable acepta la opción customizar la configuración de la ejecución. Se corre de la siguiente manera:
```
./tp2 -m <method> -d <dataset_path> -o <classif> -a <alpha = 100> -p <iteraciones potencia = 100>  -k <k = 5> -t <thread_count = 1> -f <frecuencia_minima = 0.01> -F <frecuencia_maxima = 0.99> -c <clock_output_path> -s <cache-covarianza = NULL> -v <cache-autovectores = NULL>
```
Aclaracion: Los datos incluidos por la cátedra no se encuentran en la entrega ya que hacian pesar el zip más de lo pedido.

Ejemplo:
```
./tp2 -m 1 -d datos/imbd_tokenized.csv -o result.csv
```

## Suite de tests
Para correr la suite de tests:
```
mkdir -p codigo/build
cd codigo/build
cmake ..
make correrTests
./correrTests
```
La suite está compuesta por 2 conjuntos de tests:
- Tests de la clase PCA
- Tests de  la clase KNN

## Experimentos
Los ejecutables de los experimentos se encuentran en el directorio `ejecucion/`. Se pueden encontrar los siguientes scripts:
- `run.sh`: Corre kNN con distintos valores de k y kNN + PCA con distintos valores de PCA y los k 51 y 101.
- `run-train-size.sh`: Corre kNN con distintos tamaños de training dataset y los k 51 y 101.
- `run-power-method.sh`: Corre kNN + PCA con distintos numeros de iteraciones para el Método de la Potencia, con el alpha 100 y los k 51 y 101.
- `run-knn-frec.sh`: Corre kNN con distintos valores de f y F (frecuencia mínima y máxima de token), y con los k 51 y 101.
- `run-knn-vs-traing.sh`: Corre 20 veces kNN con 3 tamaños distintos de training y k = 51.
- `run-train-vs-pca.sh`: Idem con kNN + PCA y alpha = 100.
- `run-knn-vs-pca.sh`: Corre 20 veces kNN con k = 51 y 20 veces kNN + PCA con k 51 y alpha 100.

Todos los scripts guardan tiempos de ejecucion y resultados en el directorio `ejecucion/outputs/`.
Además, **TODOS** requieren que se compile el tp antes, como se explica más arriba. Los que utilizan distintos tamaños de training requieren que dichos datasets sean creados. Para eso, se puede ejecutar el script `data_shuf.py`, que se encuentra en el directorio `datos/`, pasandole el tamaño deseado. Por ejemplo, para crear un dataset con 15000 reseñas de training:

```
cd datos
python data_shuf.py 15000
```
