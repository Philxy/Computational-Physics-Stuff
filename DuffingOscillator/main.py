import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter

H = 0.001
t_max = 100
t_0 = 0

ALPHA = -2
BETA = 4
GAMMA = 0.2
A = 1
OMEGA = 0.5



def potential(x):
    return ALPHA / 2 * x * x + BETA / 4 * x * x * x * x


def init_Potential(x_min, x_max):
    x = x_min
    X = []
    pot = []
    while x < x_max:
        X.append(x)
        pot.append(potential(x))
        x += H
    return [X, pot]


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
    return [V, X]


duff_Pot = init_Potential(-1.2, 1.2)

# subplots
"""
fig, axs = plt.subplots(3)
fig.text(0.06, 0.5, 'Auslenkung', ha='center', va='center', rotation='vertical')
fig.text(0.5, 0.04, 'Zeit', ha='center', va='center')
axs[0].plot(result1[0], result1[1], color='b', label='$x_0$ = 1')
axs[1].plot(result2[0], result2[1], color='g', label='$x_0$ = 1.1')
axs[2].plot(result3[0], result3[1], color='r', label='$x_0$ = 3')
axs[0].legend(loc="upper right")
axs[1].legend(loc="upper right")
axs[2].legend(loc="upper right")
axs[0].tick_params(labelbottom=False, bottom=False)
axs[1].tick_params(labelbottom=False, bottom=False)
axs[2].tick_params(labelbottom=False, bottom=False)
"""
# Phasenraum typische Bahnen 4er Subplots
"""
fig, axs = plt.subplots(2, 2)
axs[0, 0].plot(result[1], result[0], color='b', label='$x_0$ = 1')
axs[0, 0].set_title('$x_0 = 1$')
axs[0, 1].plot(result1[1], result1[0], color='r', label='$x_0$= 3')
axs[0, 1].set_title('$x_0 = 3$')
axs[1, 0].plot(result2[1], result2[0], color='g', label='$x_0$= 1.1')
axs[1, 0].set_title('$x_0 = 1.1$')
axs[1, 1].plot(result3[1], result3[0], color='g', label='$x_0$= 1.1')
axs[1, 1].set_title('$x_0 = 1.1$, $\gamma = 0$')
fig.text(0.03, 0.5, 'Geschw.', ha='center', va='center', rotation='vertical')
fig.text(0.55, 0.02, 'Auslenkung', ha='center', va='center')
fig.tight_layout()
"""

fig, axs = plt.subplots(2, 2)
A = 0.35
ALPHA = -1
BETA = 1
OMEGA = 1
result = RK2(1.5, 0)
axs[0, 0].plot(result[1], result[0], color='b')
axs[0, 0].set_title("$A =" + str(A) + "$")
A = 1
result1 = RK2(1, 0)
axs[0, 1].plot(result1[1], result1[0], color='r')
axs[0, 1].set_title("$A =" + str(A) + "$")
A = 2
result2 = RK2(1, 0)
axs[1, 0].plot(result2[1], result2[0], color='g')
axs[1, 0].set_title("$A =" + str(A) + "$")
A = 4
result3 = RK2(1, 0)
axs[1, 1].plot(result3[1], result3[0], color='g')
axs[1, 1].set_title("$A =" + str(A) + "$")
fig.text(0.03, 0.5, 'Geschw.', ha='center', va='center', rotation='vertical')
fig.text(0.55, 0.02, 'Auslenkung', ha='center', va='center')
fig.tight_layout()

# plt.grid(linestyle='-', linewidth=0.4)

# plt.title('$V(x) =  x^4 -  x^2$')
# plt.plot(duff_Pot[0], duff_Pot[1])
plt.show()
