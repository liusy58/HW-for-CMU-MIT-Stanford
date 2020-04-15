import numpy as np
import matplotlib
import matplotlib.pyplot as plt


def CosineTrans(x, B):
    return np.dot(np.linalg.inv(B), x)


def InvCosineTrans(a, B):
    return np.dot(B, a)


def gen_basis(N):
    K = N
    B = np.zeros(shape=(N, K))
    for k in range(K):
        for n in range(N):
            if k == 0:
                B[n, k] = 1 / np.sqrt(N)
            else:
                B[n, k] = np.sqrt(2 / N) * np.cos((n + 0.5) * k * np.pi / N)
    return B


def plot_wave(x, path="wave.png"):
    plt.gcf().clear()
    plt.plot(x)
    plt.xlabel('n')
    plt.ylabel('xn')
    plt.savefig(path)


def plot_ak(a, path="freq.png"):
    a = np.abs(a)
    plt.plot(a)
    plt.xlabel('k')
    plt.ylabel('ak')
    plt.savefig(path)


if __name__ == "__main__":
    path = "1.txt"
    x = np.loadtxt(path)

    plot_wave(x, path="wave.png")

    N = len(x)

    B = gen_basis(N)

    a = CosineTrans(x, B)

    plot_ak(a)
    mask = np.where(a > 5)[0]

    a_f1 = np.array(
        [a[index] if index == mask[0] else 0 for index in range(len(a))])
    f1 = InvCosineTrans(a_f1, B)

    a_f3 = np.array(
        [a[index] if index == mask[2] else 0 for index in range(len(a))])
    f3 = InvCosineTrans(a_f3, B)

    print("plot particular signal")
    plot_wave(f1, path='./wave_{}.png'.format(mask[0]))
    plot_wave(f3, path='./wave_{}.png'.format(mask[2]))
