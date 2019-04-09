import matplotlib.pyplot as plt
import numpy as np

results = [
  {'k':101, 'f': 0.001, 'F': 0.9, 'accuracy': 0.74444},
  {'k':101, 'f': 0.001, 'F': 0.99, 'accuracy': 0.75616},
  {'k':101, 'f': 0.001, 'F': 0.995, 'accuracy': 0.75184},
  {'k':101, 'f': 0.01, 'F': 0.9, 'accuracy': 0.74616},
  {'k':101, 'f': 0.01, 'F': 0.99, 'accuracy': 0.74404},
  {'k':101, 'f': 0.01, 'F': 0.995, 'accuracy': 0.74068},
  {'k':101, 'f': 0.015, 'F': 0.9, 'accuracy': 0.7466},
  {'k':101, 'f': 0.015, 'F': 0.99, 'accuracy': 0.74276},
  {'k':101, 'f': 0.015, 'F': 0.995, 'accuracy': 0.73656}
]

# K = 51
f = list(set([x['f'] for x in results]))
F = list(set([x['F'] for x in results]))
l = []
for i in F:
    y = []
    for j in f:
      y.append([e['accuracy'] for e in results if e['f'] == j and e['F'] == i][0])
    l.append(y)

accuracy = np.array(l)

fig, ax = plt.subplots()
im = ax.imshow(accuracy)

ax.set_xticks(np.arange(len(f)))
ax.set_yticks(np.arange(len(F)))

ax.set_xticklabels(f)
ax.set_yticklabels(F)

plt.setp(ax.get_xticklabels(), rotation=45, ha="right",
         rotation_mode="anchor")

for i in range(len(F)):
    for j in range(len(f)):
        text = ax.text(j, i, accuracy[i, j],
                       ha="center", va="center", color="w")

ax.set_title("Accuracy en funcion de distintas frecuencias (K = 101, Sin PCA)")
fig.tight_layout()
plt.ylabel('F')
plt.xlabel('f')
plt.savefig('graph_freq_accuracy101.png')
