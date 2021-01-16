
from pathlib import Path
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os
import sys

AVERAGE_WINDOW = 20

DATA = Path("Data")


ALGORITHM = ["Q-leaning", "SARSA", "MENACE Approach"]
POLICY = ["Epsilon Greedy", "Softmax"]


def open_data(data_path):
    data = [[] for _ in range(len(ALGORITHM))]
    for file in os.listdir(data_path):
        if file.endswith(".csv"):
            df = pd.read_csv(data_path / file, header=None)
            data_read = []
            data_read.append(df.values[0].astype(int))
            data_read.append(df.values[1][0:2])
            data_read.append(df.values[2:].transpose()[0].astype(int))

            algorithm = data_read[0][0]
            data[algorithm].append(data_read)
    return data


def plot_results(data):
    first_entry = data[0][0]
    algorithm = ALGORITHM[first_entry[0]]
    iterations = first_entry[2]
    episodes = first_entry[3]
    plt.figure(figsize=(8, 5))
    for pol in data:
        policy = POLICY[pol[0][1]]
        plt.plot(pol, label=policy)
    plt.yscale("log")
    plt.xlabel("Episode", fontsize=12)

    if iterations == 1:
        plt.ylabel("Number of moves", fontsize=12)
    else:
        plt.ylabel("Average moves", fontsize=12)
    title = algorithm + "running for {0} episodes in {1} iterations".format(
        episodes, iterations)
    plt.title(title, fontsize=14)
    plt.show()


def main():
    data_path = Path(os.path.dirname(os.path.abspath(__file__))).parent / DATA
    data = open_data(data_path)

    for alg in data:
        plot_results(alg)


if __name__ == "__main__":
    main()
