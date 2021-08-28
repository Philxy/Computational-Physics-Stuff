import multiprocessing
import numpy as np
import matplotlib.pyplot as plt
from multiprocessing.dummy import Pool as ThreadPool

# Constants
H = 0.01
t_max = 20
t_0 = 0
ALPHA = -2
BETA = 4
GAMMA = 0.2
A = 0.8
OMEGA = 0.5


def potential(x):
    return ALPHA / 2 * x * x + BETA / 4 * x * x * x * x


def F(t):
    return A * np.cos(OMEGA * t)


# Gibt Array mit Zeit und entsprechender Auslenkung oder Geschwindigkeit zurück
def RK2(x_0, v_0):
    x = x_0
    v = v_0
    t = t_0
    v_n = v
    x_n = x
    X = []
    V = []
    time = []

    def v_dot(T, x, v):
        return A * np.cos(OMEGA * T) - GAMMA * v - ALPHA * x - BETA * x * x * x

    while t < t_max:
        time.append(t)
        X.append(x)
        V.append(v)
        k1_x = H * v
        k2_x = H * (v + H / 2 * (F(t) - GAMMA * v - ALPHA * x - BETA * x * x * x))
        k1_v = H * (F(t) - GAMMA * v - ALPHA * x - BETA * x * x * x)
        k2_v = H * v_dot(t + H / 2, x + k1_x / 2, v + k1_v / 2)
        x_n = x + k2_x
        v_n = v + k2_v
        x = x_n
        v = v_n
        t += H
    return X


# Erstellt einen Array mit Punkten (x,v) einer beliebigen Größe
def init_points(v_range, x_range):
    h_x = 0.1
    h_v = 0.1
    tuples = []
    for x in np.arange(-x_range, x_range, h_x):
        for v in np.arange(-v_range, v_range, h_v):
            tuples.append([x, v])
    return tuples


# Gibt  Endposition zurück (true = rechts, false = links)
def get_end_position(pos):
    return RK2(pos[0], pos[1])[-1] > 0


initial_values = init_points(2, 2)
pool = ThreadPool(multiprocessing.cpu_count())
results = pool.map(get_end_position, initial_values)
rightX = []
rightV = []
leftX = []
leftV = []
for i in range(0, len(initial_values)):
    if results[i]:
        rightX.append(initial_values[i][0])
        rightV.append(initial_values[i][1])
    else:
        leftX.append(initial_values[i][0])
        leftV.append(initial_values[i][1])

title ="$A=" +str(A) + "$ " + "$\omega = " + str(OMEGA) + "$"

plt.plot(leftX, leftV, 'o', color='r', label='linkes Minimum')
plt.plot(rightX, rightV, 'o', color='b', label="rechtes Minimum")
plt.xlabel("Startpunkt")
plt.ylabel("Startgeschwindigkeit")
plt.title(title)
plt.legend()
plt.show()
