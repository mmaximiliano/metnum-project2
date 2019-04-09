import csv
import sys
import matplotlib.pyplot as plt
import os
from functools import reduce

get_real_label = {}
with open('../../datos/imdb_dataset.csv', 'r') as csvfile:
  spamreader = csv.DictReader(csvfile, delimiter=',')
  for row in spamreader:
    get_real_label[row['index']] = row['label']


def get_accuracy(path):
  with open(path, 'r') as csvfile:
    spamreader = csv.DictReader(csvfile, delimiter=',')

    tp = tn = ammount = 0.0
    for row in spamreader:
      label = get_real_label[row['id']]
      ammount+=1

      if (row['label'] == 'pos') and (label == 'pos'):
        tp+=1

      if (row['label'] == 'neg') and (label == 'neg'):
        tn+=1

    return (tp + tn) / ammount


path = '../../ejecucion/outputs/con_pca/power_iterations/classif/'
results = []
for filename in os.listdir(path):
  power = int(filename[0:-4][11:].split('_a100_k')[0])
  k = int(filename[0:-4][11:].split('_a100_k')[1])
  accuracy = get_accuracy(path + filename)  
  results.append({'k':k, 'power':power, 'accuracy':accuracy})


## K = 51
plotA = []
for e in results:
  if e['k'] == 51:
    plotA.append((e['power'], e['accuracy']))

plotA.sort(key=lambda e: e[0])

## K = 101
plotB = []
for e in results:
  if e['k'] == 101:
    plotB.append((e['power'], e['accuracy']))

plotB.sort(key=lambda e: e[0])

plt.plot(*zip(*plotA), label='K = 51')

m = max(plotA, key=lambda e : e[1])

plt.annotate('Max: ' + str(m[1]) + ', con P = ' + str(m[0]), xy=(m[0], m[1]), xytext=(m[0]-11, m[1]-0.025),
              arrowprops=dict(facecolor='red', arrowstyle='->'),
            )

plt.plot(*zip(*plotB), label='K = 101')

m = max(plotB, key=lambda e : e[1])

plt.annotate('Max: ' + str(m[1]) + ', con P = ' + str(m[0]), xy=(m[0], m[1]), xytext=(m[0], m[1]-0.01),
              arrowprops=dict(facecolor='red', arrowstyle='->'),
            )

plt.title('Accuracy en función de la cantidad de \n iteraciones del metodo de la potencia', fontsize=10)
plt.ylabel('Accuracy')
plt.xlabel('Iteraciones (P) (con Alpha = 100)')
plt.legend()
plt.savefig('graph_power_accuracy.png')