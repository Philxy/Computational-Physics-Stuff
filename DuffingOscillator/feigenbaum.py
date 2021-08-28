import numpy as np
import matplotlib.pyplot as plt

H = 0.01
t_0 = 0
t_max = 40
ALPHA = -1
BETA = 1
GAMMA = 0.2


def potential(x):
    return ALPHA / 2 * x * x + BETA / 4 * x * x * x * x


def F(t, A, OMEGA):
    return A * np.cos(OMEGA * t)


# Gibt Array mit Zeit und entsprechender Auslenkung oder Geschwindigkeit zurück
def RK2(x_0, v_0, A, OMEGA):
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
        k2_x = H * (v + H / 2 * (F(t, A, OMEGA) - GAMMA * v - ALPHA * x - BETA * x * x * x))
        k1_v = H * (F(t, A, OMEGA) - GAMMA * v - ALPHA * x - BETA * x * x * x)
        k2_v = H * v_dot(t + H / 2, x + k1_x / 2, v + k1_v / 2)
        x_n = x + k2_x
        v_n = v + k2_v
        x = x_n
        v = v_n
        t += H
    return X


def get_max_amplitude(anregeamplitude):
    solve = RK2(1, 0, anregeamplitude, 1)
    del solve[:int(len(solve) / 2)]
    return max(solve)


def get_min_amplitude(anregeamplitude):
    solve = RK2(1, 0, anregeamplitude, 1)
    del solve[:int(len(solve) / 2)]
    return min(solve)


result1 = []
result2 = []
result3 = []
for a in np.arange(0.1, 2, 0.005):
    result1.append(a)
    result1.append(a)
    result2.append(get_max_amplitude(a))
    result2.append(get_min_amplitude(a))

plt.plot(result1, result2, ".")
plt.show()
