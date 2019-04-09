import csv
from wordcloud import WordCloud
import matplotlib.pyplot as plt
from wordcloud import WordCloud, STOPWORDS
from PIL import Image
import numpy as np

with open('../../datos/imdb_dataset.csv', 'r') as csvfile:
  spamreader = csv.DictReader(csvfile, delimiter=',')

  txt = ''
  for row in spamreader:
    txt += (row['review'] + ' ')

  nic_cage = np.array(Image.open("nic_cage2_2_1.png"))

  stopwords = set(STOPWORDS)
  stopwords.add("br")
  wordcloud = WordCloud(background_color="white", stopwords=stopwords, mask=nic_cage,
                        contour_width=1, contour_color='steelblue')
  wordcloud.generate(txt)

  plt.figure( figsize=(20,10) )
  plt.imshow(wordcloud, interpolation='bilinear', aspect='auto')
  plt.axis("off")
  plt.savefig('wordcloud4.png')
  plt.show()