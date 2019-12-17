import matplotlib.pyplot as plt
x = []
y = []
with open('wynik.txt') as f:
    i = 0
    for line in f:
        #line = line.strip()
        #cols = line.split(',')
        dcols = [float(s) for s in line.split(',')]
        print(f'{i}: {line.strip():20} {dcols[0]:10} {dcols[1]:10}')
        i += 1
        x.append(dcols[0])
        y.append(dcols[1])

fig, ax = plt.subplots(dpi=250,figsize=(5,3))
ax.plot(x,y,'--s')        
plt.show()