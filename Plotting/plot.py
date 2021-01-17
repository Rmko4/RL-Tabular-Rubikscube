
from pathlib import Path
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os
import sys

AVERAGE_WINDOW = 20

DATA = Path("Data")


ALGORITHM = ["Q-Learning", "SARSA", "MENACE Approach"]
POLICY = ["Epsilon Greedy", "Softmax"]


def open_data(data_path):
    data = [[] for _ in range(len(POLICY))]
    for file in os.listdir(data_path):
        if file.endswith(".csv"):
            df = pd.read_csv(data_path / file, header=None)
            data_read = []
            data_read.append(df.values[0].astype(int))
            data_read.append(df.values[1][0:2])
            data_read.append(df.values[2:].transpose()[0].astype(int))

            policy = data_read[0][1]
            data[policy].append(data_read)
    return data


def plot_results(data):
    first_entry = data[0][0]
    policy = POLICY[first_entry[1]]
    iterations = first_entry[2]
    episodes = first_entry[3]

    plt.figure(figsize=(8, 5))
    for alg in data:
        algorithm = ALGORITHM[alg[0][1]]
        mean_window = np.convolve(alg[2], np.ones(
            AVERAGE_WINDOW)/AVERAGE_WINDOW, mode='valid')
        plt.plot(mean_window, label=algorithm)

    plt.yscale("log")
    plt.xlabel("Episode", fontsize=12)
    if iterations == 1:
        plt.ylabel("Number of moves", fontsize=12)
    else:
        plt.ylabel("Average number of moves", fontsize=12)

    title = "Algorithm using " + policy + " for " + \
        f"{episodes:,}" + " episodes on " + f"{iterations:,}" + " instances"
    plt.title(title, fontsize=14)
    plt.legend(fontsize=12)
    plt.show()


def main():
    data_path = Path(os.path.dirname(os.path.abspath(__file__))).parent / DATA
    data = open_data(data_path)

    for pol in data:
        plot_results(pol)


if __name__ == "__main__":
    main()
