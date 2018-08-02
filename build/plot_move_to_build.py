import numpy as np
import matplotlib.pyplot as plt

# mmap = map(str.split, open('vi.txt'))

filename = 'pv.txt'

xv = [float(x.split(' ')[0]) for x in open(filename).readlines()]
yv = [float(x.split(' ')[1]) for x in open(filename).readlines()]

# # Make some fake data.
# a = b = np.arange(0, 3, .02)
# c = np.exp(a)
# d = c[::-1]

fig, ax = plt.subplots()
ax.plot(xv, yv, 'k--', label='Model length')

legend = ax.legend(loc='upper center', shadow=True, fontsize='x-large')

legend.get_frame().set_facecolor('#00FFCC')

plt.show()
