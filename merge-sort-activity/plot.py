import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("mergesort_output.csv")

sizes = data["size"]
times = data["time(microseconds)"]

plt.figure(figsize=(8, 6))
plt.plot(sizes, times, "o-")

plt.xscale("log")
plt.yscale("log")

plt.xticks(sizes)
plt.yticks(times, times)

plt.xlabel("Number of elements")
plt.ylabel("Time (microseconds)")
plt.title("Time Complexity of Merge Sort")
plt.grid()

plt.savefig("plot.png")
plt.show()