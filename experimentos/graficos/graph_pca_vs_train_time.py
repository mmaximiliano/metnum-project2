import csv
import sys
import matplotlib.pyplot as plt
import os
import numpy as np


def get_time(path):
  with open(path, 'r') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',')

    for row in spamreader:
      if row[0] == 'knn':
        return row[1]


path = '../../ejecucion/outputs/con_pca/train_size/clock/'
results = []
for filename in os.listdir(path):
  if (filename[12:14] == '51'):
    size = int(filename[0:-4][19:].split('_i')[0])
    i = int(filename[0:-4][19:].split('_i')[1])
    time = get_time(path + filename)  
    results.append({'size':size, 'i':i, 'time':int(time)})


## Size = 15000
plotA = []
for e in results:
  if e['size'] == 15000:
    plotA.append(e['time'] / (35000.0))

plotA = np.array(plotA)

## Size = 25000
plotB = []
for e in results:
  if e['size'] == 25000:
    plotB.append(e['time'] / (25000.0))

plotB = np.array(plotB)

## Size = 35000
plotC = []
for e in results:
  if e['size'] == 35000:
    plotC.append(e['time'] / (15000.0))

plotC = np.array(plotC)

## Size = 45000
plotD = []
for e in results:
  if e['size'] == 45000:
    plotD.append(e['time'] / (5000.0))

plotD = np.array(plotD)

## Size = 49000
plotE = []
for e in results:
  if e['size'] == 49000:
    plotE.append(e['time'] / (1000.0))

plotE = np.array(plotE)

plt.hist(plotA, label='15000', histtype='stepfilled')

plt.hist(plotB, label='25000')

plt.hist(plotC, label='35000')

plt.hist(plotD, label='45000')

plt.hist(plotE, label='49000')

_, max_ = plt.ylim()

plt.text(plotA.mean() + 0.2, 
         3, 
         '{:.2f}'.format(plotA.mean()))


plt.text(plotB.mean() + 0.2, 
         3, 
         '{:.2f}'.format(plotB.mean()))


plt.text(plotC.mean() + 0.5, 
         max_ - max_/10, 
         '{:.2f}'.format(plotC.mean()))

plt.text(plotD.mean() + 0.2, 
         max_ - max_/10, 
         '{:.2f}'.format(plotD.mean()))

plt.text(plotE.mean() + 0.0, 
         4, 
         '{:.2f}'.format(plotE.mean()))

plt.title('Histograma del tiempo de predicción por cada \n tamaño del Training Dataset', fontsize=15)
plt.ylabel('Frequencia')
plt.xlabel('Tiempo (Ms)')
plt.legend()
plt.savefig('graph_pca_vs_train_time.png')