<img src="https://github.com/mahyarmohammadimatin/data_structure_exercises/blob/main/49.png">

This C++ program is designed to solve mazes using a B-Tree data structure. 
It efficiently finds the shortest path in a maze and provides a visualization of the solution.

This program takes a maze as input, represented as a grid of cells, where each cell has a weight indicating the cost of traversing it. 
The goal is to find the shortest path from the start to the end of the maze while avoiding obstacles.

## Maze Solver
The core functionality of this program is the maze solver. It uses a modified Dijkstra's algorithm to find the shortest path through the maze. The algorithm takes into account the weights of the cells, allowing for more complex maze scenarios where certain paths are costlier to traverse than others.

The maze solver uses a B-Tree data structure to efficiently manage and update the maze data as it explores possible paths. It optimally selects the next cell to explore, gradually building the path from the start to the end.

## B-Tree Implementation
The B-Tree is a self-balancing tree structure that ensures efficient insertion and deletion of elements. In this program, the B-Tree is used to manage the cells in the maze efficiently. When the program explores a new cell, it inserts it into the B-Tree. If it finds a shorter path to a cell it has already explored, it updates the cell's information in the B-Tree.

The B-Tree implementation includes functionalities for insertion, deletion, and balancing to maintain optimal performance throughout the maze-solving process.

## Usage

The first line specifies the dimensions of the maze (rows and columns).
Subsequent lines represent the maze grid, where each number indicates the weight of a cell.

View the Solution: The program will solve the maze and display the solution, including the shortest path from the start to the end. Obstacles are indicated by 0, and the path is marked with -1.

Explore Further: Feel free to experiment with different maze configurations and weights to see how the program efficiently finds the shortest path.
