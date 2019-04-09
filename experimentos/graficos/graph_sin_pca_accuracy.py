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


path = '../../ejecucion/outputs/sin_pca/test-k/classif/'
results = []
for filename in os.listdir(path):
  k = int(filename[0:-4][8:])
  accuracy = get_accuracy(path + filename)  
  results.append({'k':k, 'accuracy':accuracy})

plotA = []
for e in results:
  plotA.append((e['k'], e['accuracy']))

plotA.sort(key=lambda e: e[0])

plt.plot(*zip(*plotA))

m = max(plotA, key=lambda e : e[1])

plt.annotate('Max: ' + str(m[1]) + ', con K = ' + str(m[0]), xy=(m[0], m[1]), xytext=(m[0]+100, m[1]-0.03),
              arrowprops=dict(facecolor='red', arrowstyle='->'),
            )

plt.title('Accuracy en función de K', fontsize=20)
plt.ylabel('Accuracy')
plt.xlabel('K')
plt.savefig('graph_sin_pca_accuracy_FREQ_ORIGINAL.png')