import utility
import numpy as np
import matplotlib.pyplot as plt


solution = utility.RK2(1,0)
x_values = []
v_values = []

dt = 2*np.pi/utility.OMEGA
index = int(dt/utility.H)

i = 2*index

while i < len(solution[1]):
    x_values.append(solution[1][i])
    v_values.append(solution[2][i])
    i+=index


plt.plot(x_values, v_values, ".")
plt.show()










