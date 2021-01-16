
from pathlib import Path
import matplotlib.pyplot as plt
import numpy as np
import os
import sys

AVERAGE_WINDOW = 20

ALGORITHMS = ["Q-leaning", "SARSA", "MENACE Approach"]
POLICY = ["Epsilon Greedy", "Softmax", "Simulated Annealing"]


def read_data(data_path):
    data = []
    f = open(data_path, "r")

    for i, x in enumerate(f):
        if i == 0:
            algorithm = ALGORITHMS[(int)(x.split(",")[0])]
            policy = POLICY[(int)(x.split(",")[1])]
            nIterations = (int)(x.split(",")[2])
            nEpsiodes = (int)(x.split(",")[3])
        elif i == 1:
            average = (float)(x.split(",")[0])
            sd = (float)(x.split(",")[1])
            print("average = {0} with sd = {1}".format(average, sd))
        else:
            data.append((int)(x))
    f.close()

    return data, algorithm, policy, nIterations, nEpsiodes,


def mean(data):
    sum = 0
    for x in data:
        sum += x
    return sum / len(data)


def main():

    data, algorithm, policy, nIterations, nEpisodes = read_data(sys.argv[1])

    data = [mean(data[i:i+AVERAGE_WINDOW])
            for i in range(nEpisodes - AVERAGE_WINDOW)]

    plt.figure(figsize=(8, 5))
    plt.plot(data)
    plt.yscale("log")
    plt.xlabel("epsiode", fontsize=12)
    if nIterations == 1:
        plt.ylabel("Moves", fontsize=12)
    else:
        plt.ylabel("Average moves", fontsize=12)
    title = algorithm + " with " + policy + \
        " running for {0} episodes in {1} iterations".format(
            nEpisodes, nIterations)
    plt.title(title, fontsize=14)
    plt.show()


if __name__ == "__main__":
    main()
