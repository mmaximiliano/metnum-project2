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

path = '../../ejecucion/outputs/knn-vs-pca/clock/'
results = []
for filename in os.listdir(path):
  time = get_time(path + filename) 
  if '100' in filename: 
    results.append({'alpha': True, 'time':int(time)})
  else:
    results.append({'alpha': False, 'time':int(time)})

## Con y sin PCA
plotA = []
plotB = []
for e in results:
  if e['alpha']:
    plotA.append(e['time'] / 25000.0)
  else:
    plotB.append(e['time'] / 25000.0)

plotA = np.array(plotA)
plotB = np.array(plotB)

plt.boxplot([plotA, plotB], labels=['Con PCA', 'Sin PCA'])

plt.title('Boxplot del tiempo de predicción con y sin PCA', fontsize=15)
plt.ylabel('Tiempo (Ms)')
plt.savefig('graph_knn_vs_pca_time.png')