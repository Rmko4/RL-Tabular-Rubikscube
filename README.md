# Reinforcement Learning with tabular methods
## Rubik's cube restricted to 180 degree turns
The program is able to run several instances of an algorithm on the Rubik's cube restricted to only 180 degree turns (double turns).
Through providing arguments, the following parameters for the problem can be set:
* The learning algorithm to perform on the problem.
* The action selection policy used by the algorithm.
* The number of instances of the algorithm to run.
* The number of episodes per instance.

And optionally:
* Epsilon greedy and Q-Learning parameters:
    * Learning rate (Alpha) - Default 0.4
    * Discount factor (Gamma) - Default: 0.95
* MENACE Approach parameters:
    * Base factor (Lambda) - Default: 0.78
    * Reward (Reward) - Default: 1
* Action Selection parameters:
    * Epsilon greedy (Epsilon) - Default: 0.2
    * Softmax temperature (Tau) - Default: 0.2
    * Simulated annealing (Temperature scale) - Default: 0.2

A more detailed description of how to run the program with these parameters is described in: [Run the program](#run-the-program).

## Compile the C source code (gcc)
The code can be compiled through:  
`gcc *.c -o cube -O3 -lm`  
For support on running multiple threads (OpenMp), add flag:  
`-fopenmp`

## Run the program
The program can be run through:  
`./cube <Algorithm> <Policy> <# Instances> <# Episodes> [Param1] [Param2] [Param3]`

The arguments need to be specified following the rules:

**Algorithm:** The learning algorithm to perform on the problem. Select either 0, 1 or 2.
* _Q-Learning_: 0
* _SARSA_: 1
* _MENACE Approach_: 2

**Policy:** The action selection policy used by the algorithm. Select 0, 1 or 2.
* _Espilon Greedy_: 0
* _Softmax_: 1  
* _Simulated Annealing_: 2 - (Only available for _MENACE Approach_)

**# Instances:** The number of instances of the algorithm to run. Select any integer > 0.

**# Episodes:** The number of The number of episodes per instance. Select any integer > 0.

**Param 1:** _(Optional)_ Parameter for the algorithm. Select any float > 0.
* _Q-Learning_: Param 1 = Alpha
* _SARSA_: Param 1 = Alpha
* _MENACE Approach_: Param 1 = Lambda

**Param 2:** _(Optional)_ Parameter for the algorithm. Select any float > 0.
* _Q-Learning_: Param 2 = Gamma
* _SARSA_: Param 2 = Gamma
* _MENACE Approach_: Param 2 = Reward

**Param 3:** _(Optional)_ Parameter for the action seletion policy. Select any float > 0.
* _Epsilon Greedy_: Param 3 = Alpha
* _Softmax_: Param 3 = Tau
* _Simulated Annealing_: Param 3 = Temperature Scale

## Output
The output will be written in csv format to the standard output. The first row contains information on the algorithm. The second row provides statistics on the performance of the run. The other rows all contain a single data entry, containing the average number of turns in each episode.

**First row:**
_Algorithm_, _Policy_, _# Instances_, _# Episodes_

**Second Row:** _Xbar_, _SD_  
* _Xbar_: The mean number of turns in all episodes from all instances.
* _SD_: The standard deviation between the mean number of turns over all episodes of each instance.

**Third Row and onwards:** _# actions_
* _# actions_: The mean number of turns of the Nth-episode in all instances. For the third row N = 0. For the fourth N = 1 etc.
