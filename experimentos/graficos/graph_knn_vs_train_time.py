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


path = '../../ejecucion/outputs/sin_pca/train_size-time/clock/'
results = []
for filename in os.listdir(path):
  size = int(filename[0:-4][19:].split('_i')[0])
  i = int(filename[0:-4][19:].split('_i')[1])
  time = get_time(path + filename)  
  results.append({'size':size, 'i':i, 'time':int(time)})


## Size = 15000
plotA = []
for e in results:
  if e['size'] == 15000:
    plotA.append(e['time'] / 35000.0)

plotA = np.array(plotA)

## Size = 25000
plotB = []
for e in results:
  if e['size'] == 25000:
    plotB.append(e['time'] / 25000.0)

plotB = np.array(plotB)

## Size = 35000
plotC = []
for e in results:
  if e['size'] == 35000:
    plotC.append(e['time'] / 15000.0)

plotC = np.array(plotC)

## Size = 45000
plotD = []
for e in results:
  if e['size'] == 45000:
    plotD.append(e['time'] / 5000.0)

plotD = np.array(plotD)

## Size = 49000
plotE = []
for e in results:
  if e['size'] == 49000:
    plotE.append(e['time'] / 1000.0)

plotE = np.array(plotE)

plt.hist(plotA, label='15000')
#plt.axvline(plotA.mean(), color='k', linestyle='dashed', linewidth=1)

plt.hist(plotB, label='25000')
#plt.axvline(plotB.mean(), color='k', linestyle='dashed', linewidth=1)

plt.hist(plotC, label='35000')
#plt.axvline(plotC.mean(), color='k', linestyle='dashed', linewidth=1)

plt.hist(plotD, label='45000')

plt.hist(plotE, label='49000')

_, max_ = plt.ylim()

plt.text(50, 
         8, 
         'Media: {:.2f}'.format(plotA.mean()), color='blue')


plt.text(60, 
         0.2, 
         'Media: {:.2f}'.format(plotB.mean()), color='orange')


plt.text(79, 
         3, 
         'Media: {:.2f}'.format(plotC.mean()), color='green')


plt.text(103, 
         2.7, 
         'Media: {:.2f}'.format(plotD.mean()), color='red')


plt.text(110, 
         6, 
         'Media: {:.2f}'.format(plotE.mean()), color='purple')

plt.title('Histograma del tiempo de predicción por cada \n tamaño del Training Dataset', fontsize=15)
plt.ylabel('Frequencia')
plt.xlabel('Tiempo (Ms)')
plt.legend()
plt.savefig('graph_knn_vs_train_time.png')