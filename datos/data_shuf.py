import csv
import sys
import random

toWrite = []
train_size = int(sys.argv[1])
pos_cant = neg_cant = train_size / 2

with open('imdb_tokenized.csv', 'r') as csvfile:
  spamreader = list(csv.reader(csvfile, delimiter=','))
  
  random.Random(1234).shuffle(spamreader) # Seed: 1234

  for row in spamreader:
    if train_size > 0:
      if row[2] == 'pos' and pos_cant > 0:
        row[1] = 'train'
        toWrite.append(row)
        pos_cant-=1
        train_size-=1
        continue
      elif row[2] == 'pos':
        row[1] = 'test'
        toWrite.append(row)
        continue

      if row[2] == 'neg' and neg_cant > 0:
        row[1] = 'train'
        toWrite.append(row)
        neg_cant-=1
        train_size-=1
        continue
      elif row[2] == 'neg':
        row[1] = 'test'
        toWrite.append(row)
        continue

    row[1] = 'test'
    toWrite.append(row)


with open('imdb_tokenized_shuf' + sys.argv[1] + '.csv', 'w') as csvfile:
  writer = csv.writer(csvfile, delimiter=',')
  #writer.writeheader()

  for e in toWrite:
    writer.writerow(e)
