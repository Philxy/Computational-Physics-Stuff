import numpy as np
import matplotlib.pyplot as plt

s = 0.02
x0 = 0.5
dt = 0.006
h = 0.006
D = 10 ** (-3)
ALPHA = D * dt / (h * h)
tMax = 10

N = int(2 * x0 / h)
b = [1 for i in range(N)]
d = [0 for i in range(N)]
x = [0 for i in range(N)]
f1 = open("2result2d.txt", "w")
f2 = open("resultB.txt", "w")


def phi(x):
    return np.exp(-(x - x0) ** 2 / (2 * s * s))


for i in range(0, N):
    x[i] = phi(i * h)


def solveThomas(B, D, X):
    for i in range(1, N):
        m = 1 / B[i - 1]
        B[i] = B[i] - m
        D[i] = D[i] - m * D[i - 1]
    X[N - 1] = D[N - 1] / B[N - 1]
    for i in range(N - 2, -1, -1):
        X[i] = (D[i] - X[i + 1]) / B[i]
    return X


t = 0
while t < tMax:
    for i in range(0, N):
        b[i] = -2 * (1 + 1 / ALPHA)
    for i in range(1, N - 1):
        d[i] = - x[i - 1] - x[i + 1] + 2 * (1 - 1 / ALPHA) * x[i]
    d[0] = 2 * (1 - 1 / ALPHA) * x[0] - x[1]
    d[N - 1] = 2 * (1 - 1 / ALPHA) * x[N - 1] - x[N - 2]
    u = str(t) + " " + str(x[int(N / 2)]) + "\n"
    f1.write(u)
    for i in range(0, N):
        s = str(i * h) + "  " + str(t) + "  " + str(x[i]) + "\n"
        f2.write(s)

    x = solveThomas(b, d, x)
    t += dt
f1.close()
f2.close()
