# Reinforcement Learning Practical - Project 2
## Rubik's cube restricted to 180 degree turns
The program is able to run several instances of an algorithm on the Rubik's cube restricted to only 180 degree turns (double turns).
Through providing arguments, the following parameters for the problem can be set:
* The learning algorithm to perform on the problem.
* The action selection policy used by the algorithm
* The number of instances of the algorithm to run.
* The number of episodes per instance.

And optionally: // FIX
* The number of instances (N runs) - Default: 20000
* The number of arms (K actions) - Default: 10
* The number of time steps in a run (T steps) - Default: 1000

A more detailed description of how to run the program with these parameters is described in: [Run the program](#run-the-program).

## Compile the C source code (gcc)
The code can be compiled through:  
`gcc *.c -o cube -O3 -lm`

## Run the program
The program can be run through:  
`./cube <Value distribution> <Algorithm> <Param 1> [N-Runs] [K-Arms] [T-Steps]`

The arguments need to be specified following the rules:

**Value distribution:** The value distribution of the arms. Select either 0 or 1.
* _Gaussian_: 0
* _Bernoulli_: 1

**Algorithm:** The learning algorithm to perform on the problem. Select 0, 1, 2 or 3.
* _Espilon Greedy_: 0
* _Reinforcement Comparison_: 1
* _Pursuit Method_: 2
* _Stochastic Gradient Ascent_: 3

**Param 1:** Parameter for the algorithm. Select any float > 0.
* _Epsilon Greedy_: Param 1 = Epsilon
* _Reinforcement Comparison_: Param 1 = Beta
* _Pursuit Method_: Param 1 = Beta
* _Stochastic Gradient Ascent_: Param 1 = Alpha

**N-Runs:** (_Optional_) The number of instances (N runs). Select any integer N > 0.

**K-Arms:** (_Optional_) The number of arms (K actions). Select any integer K > 0.  
(Note that this parameter can not be selected without providing N-Runs)

**T-Steps:** (_Optional_) The number of time steps in a run (T steps). Select any integer T > 0.  
(Note that this parameter can not be selected without providing N-Runs and K-Arms)