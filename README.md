# Implement F-M-Heurisic Alogorithm EDA_Project
In the circuit design, after designers put different elements in a circuti. Practically, in the IC design, it need to be processed by partition to let it can distribute fairly on a chip.

The problem is :
Given a net-list for a circuit, partition the 
circuit to two subcircuits A and B so that the cut-set of subcircuits A and B is 
minimized under the constraint of |size(A) -size(B)| < 0.01*n

This program is to implement F-M Heurisic algorithm
In the program,
Cell and Net in the circuir are stroed by linking list separately.
User can input the number of Cell and Net, and also the info of Cell and Net.

As for other functions

- void printlist(Cell*,Net*) : analyze users' input and print out
- void gain_initial(Cell*,Net*) : calculate every cell initial gain value
- void swap(Cell*,Net*,int) : to deal with all "swqp" in the cells and end at total_gain<0
