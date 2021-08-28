import numpy as np
import matplotlib.pyplot as plt

H = 0.001
t_0 = 0
t_max = 5000
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
    return [V, X]


x = 1.5
v = 0
amplitude = 0.35
w = 1

# OMEGA_0 = np.sqrt(ALPHA + 3 / 4 * BETA * amplitude ** 2)  # Eigenkreisfrequenz

x_dots = []
v_dots = []
dt = np.pi * 2 / w
solve = RK2(x, v, amplitude, w)
T = int(10 / H) + int(dt / H)

while T < len(solve[0]):
    x_dots.append(solve[1][T])
    v_dots.append(solve[0][T])
    T += int(dt / H)

plt.plot(x_dots, v_dots, ".")

# plt.plot(solve[1], solve[0])


plt.show()
