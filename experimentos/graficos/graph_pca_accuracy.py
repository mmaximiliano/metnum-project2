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


path = '../../ejecucion/outputs/PCA/test-alpha/classif/'
results = []
for filename in os.listdir(path):
  k = int(filename[0:-4][8:].split('-')[0])
  alpha = int(filename[0:-4][8:].split('-')[1])
  accuracy = get_accuracy(path + filename)  
  results.append({'k':k, 'alpha':alpha, 'accuracy':accuracy})


## K = 51
plotA = []
for e in results:
  if e['k'] == 51:
    plotA.append((e['alpha'], e['accuracy']))

plotA.sort(key=lambda e: e[0])

## K = 101
plotB = []
for e in results:
  if e['k'] == 101:
    plotB.append((e['alpha'], e['accuracy']))

plotB.sort(key=lambda e: e[0])

## K = 1
plotC = []
for e in results:
  if e['k'] == 1:
    plotC.append((e['alpha'], e['accuracy']))

plotC.sort(key=lambda e: e[0])

## K = 1001
plotD = []
for e in results:
  if e['k'] == 1001:
    plotD.append((e['alpha'], e['accuracy']))

plotD.sort(key=lambda e: e[0])

## K = 10001
plotE = []
for e in results:
  if e['k'] == 10001:
    plotE.append((e['alpha'], e['accuracy']))

plotE.sort(key=lambda e: e[0])

## K = 24999
plotF = []
for e in results:
  if e['k'] == 24999:
    plotF.append((e['alpha'], e['accuracy']))

plotF.sort(key=lambda e: e[0])


plt.plot(*zip(*plotC), label='K = 1')

m = max(plotC, key=lambda e : e[1])

plt.plot(*zip(*plotA), label='K = 51')

m = max(plotA, key=lambda e : e[1])

plt.annotate('Max: ' + str(m[1]) + ', con Alpha = ' + str(m[0]), xy=(m[0], m[1]), xytext=(m[0], 0.55),
              arrowprops=dict(facecolor='red', arrowstyle='->'),
            )

plt.plot(*zip(*plotB), label='K = 101')

m = max(plotB, key=lambda e : e[1])

plt.annotate('Max: ' + str(m[1]) + ', con Alpha = ' + str(m[0]), xy=(m[0], m[1]), xytext=(m[0]+110, m[1]-0.03),
              arrowprops=dict(facecolor='red', arrowstyle='->'),
            )

plt.plot(*zip(*plotD), label='K = 1001')

m = max(plotD, key=lambda e : e[1])

plt.annotate('Max: ' + str(m[1]) + ', con Alpha = ' + str(m[0]), xy=(m[0], m[1]), xytext=(300, m[1]-0.05),
              arrowprops=dict(facecolor='red', arrowstyle='->'),
            )

plt.plot(*zip(*plotE), label='K = 10001')

plt.plot(*zip(*plotF), label='K = 24999')


plt.title('Accuracy en función de alpha', fontsize=20)
plt.ylabel('Accuracy')
plt.xlabel('Alpha')
plt.legend()
plt.savefig('graph_pca_accuracy.png')