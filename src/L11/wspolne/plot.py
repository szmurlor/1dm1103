import matplotlib.pyplot as plt
import matplotlib

#matplotlib.use('Qt5Agg')
x = []
y = []

#i = 0
with open("w.txt") as f:
    for line in f:
        cols = line.split(',')
        #print(f"{i}: {line.strip():25} {cols[0]:10} {cols[1]:10}")
        #i += 1
        x.append(float(cols[0]))
        y.append(float(cols[1]))

fig, ax = plt.subplots(figsize=(6,4), dpi=100)
ax.plot(x,y, "--s")
plt.show()