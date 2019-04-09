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


path = '../../ejecucion/outputs/con_pca/train_size/classif/'
results = []
for filename in os.listdir(path):
  k = int(filename[0:-4][9:].split('_size')[0])
  size = int(filename[0:-4][9:].split('_size')[1])
  accuracy = get_accuracy(path + filename)  
  results.append({'k':k, 'size':size, 'accuracy':accuracy})


## K = 51
plotA = []
for e in results:
  if e['k'] == 51:
    plotA.append((e['size'], e['accuracy']))

plotA.sort(key=lambda e: e[0])

## K = 101
plotB = []
for e in results:
  if e['k'] == 101:
    plotB.append((e['size'], e['accuracy']))

plotB.sort(key=lambda e: e[0])

## K = 501
plotC = []
for e in results:
  if e['k'] == 501:
    plotC.append((e['size'], e['accuracy']))

plotC.sort(key=lambda e: e[0])

## K = 1001
plotD = []
for e in results:
  if e['k'] == 1001:
    plotD.append((e['size'], e['accuracy']))

plotD.sort(key=lambda e: e[0])

plt.plot(*zip(*plotA), label='K = 51')

m = max(plotA, key=lambda e : e[1])

plt.annotate('Max: ' + str(m[1]) + ', con Size = ' + str(m[0]), xy=(m[0], m[1]), xytext=(20000, m[1]),
              arrowprops=dict(facecolor='red', arrowstyle='->'),
            )

plt.plot(*zip(*plotB), label='K = 101')

m = max(plotB, key=lambda e : e[1])

plt.annotate('Max: ' + str(m[1]) + ', con Size = ' + str(m[0]), xy=(m[0], m[1]), xytext=(20000, m[1]),
              arrowprops=dict(facecolor='red', arrowstyle='->'),
            )

plt.plot(*zip(*plotC), label='K = 501')

m = max(plotC, key=lambda e : e[1])

plt.annotate('Max: ' + str(m[1]) + ', con Size = ' + str(m[0]), xy=(m[0], m[1]), xytext=(19000, 0.71),
              arrowprops=dict(facecolor='red', arrowstyle='->'),
            )

plt.plot(*zip(*plotD), label='K = 1001')

m = max(plotD, key=lambda e : e[1])

plt.annotate('Max: ' + str(m[1]) + ', con Size = ' + str(m[0]), xy=(m[0], m[1]), xytext=(m[0]-20000, 0.70),
              arrowprops=dict(facecolor='red', arrowstyle='->'),
            )

plt.title('Accuracy en función del tamaño del conjunto de train', fontsize=15)
plt.ylabel('Accuracy')
plt.xlabel('Training Dataset Size')
plt.legend()
plt.savefig('graph_train_size_accuracy.png')