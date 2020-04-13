import sys
import numpy as np


def has_cycle(graph):
    graph1 = np.array(graph)
    graph2 = np.array(graph)

    cnt = graph.shape[0]

    while cnt > 0:
        graph2 = np.dot(graph1, graph2)

        for i in range(graph.shape[0]):
            if graph2[i, i] >= 1:
                return True
        cnt = cnt - 1
    return False
