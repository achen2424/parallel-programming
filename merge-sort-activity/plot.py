import matplotlib.pyplot as plt
import numpy as np

x, y = np.loadtxt('mergesort_output.csv', delimiter=',', unpack=True)
plt.xlabel('Size of Array')
plt.ylabel('Time (microseconds)')
plt.title('Time Complexity of Merge Sort')
plt.plot(x, y)
plt.show()