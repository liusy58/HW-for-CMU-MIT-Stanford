import sys
import numpy as np
import random


def simulator():
    x = 0
    y = 0
    sum = 0
    while sum <= 100:
        temp = random.randint(1, 100)
        sum += temp
        x = temp
    while sum <= 200:
        temp = random.randint(1, 100)
        sum += temp
        y = temp
    return x < y

if __name__ == "__main__":
    num = 0
    for i in range(100000):
        num += simulator()
    print(num/100000)
