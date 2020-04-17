import sys
import numpy as np
import pandas as pd


def load(fname):
    f = open(fname, 'r').readlines()
    n = len(f)
    ret = {}
    for line in f:
        line = line.split('\n')[0].split(',')
        i = int(line[0])
        ret[i] = {}
        for j in range(n):
            if str(j) in line[1:]:
                ret[i][j] = 1
            else:
                ret[i][j] = 0
    ret = pd.DataFrame(ret).values
    return ret


def get_tran(graph):
    graph = np.array(g, dtype=float)
    nodes = graph.shape[1]
    for node in range(nodes):
        non_zero_nbr = np.count_nonzero(graph[:, node])
        graph[:, node] = graph[:, node] / non_zero_nbr
    return graph


def cal_rank(t, d=0.85, max_iterations=1000, alpha=0.001):
    line = t.size[0]
    for _ in range(max_iterations):



def save(t, r):
    np.save("1.txt", t)
    np.save("2.txt", r)


def dist(a, b):
    return np.sum(np.abs(a - b))


def main():
    graph = load(sys.argv[1])
    transition_matrix = get_tran(graph)
    rank = cal_rank(transition_matrix)
    save(transition_matrix, rank)


if __name__ == '__main__':
    main()
