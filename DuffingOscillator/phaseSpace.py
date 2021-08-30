import numpy as np
import matplotlib.pyplot as plt
import utility



solution = utility.RK2(1, 0)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.plot(solution[0], solution[1], solution[2])
plt.show()