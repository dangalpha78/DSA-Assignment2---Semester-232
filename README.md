# KNN-MNIST
The major assignment for the Data Structures and Algorithms course in the  semester 232 at VNU - HCMUT

__I. Theory__

In Assignment 1, students are tasked with implementing a simple k-nearest neighbors (kNN) classification algorithm using a brute-force approach. However, this approach has a time complexity of O(k * n * d), where k is the number of nearest neighbors to find, n is the number of data points, and d is the number of dimensions (features).

To improve the efficiency of the kNN algorithm, students are required to implement a data structure called kD-Tree. This data structure aims to reduce the time complexity by organizing data points in a hierarchical binary tree format, allowing for faster nearest neighbor search operations.

In this assignment, students will:

Implement the kD-Tree data structure.
1. Modify the kNN class to utilize the kD-Tree for nearest neighbor searches.
2. Apply these implementations to the MNIST dataset, which is familiar from Assignment 1.
3. Key concepts covered include the MNIST dataset, k-nearest neighbors algorithm, Euclidean distance calculation, training, and prediction processes, as previously detailed in Assignment 1.


__II. k-D Tree__

You can find detailed information about the kD-Tree data structure and its operations on the Wikipedia page

https://en.wikipedia.org/wiki/K-d_tree


# Usage Summary
1. Open main.cpp: Open main.cpp in your editor.

2. Compile: Use g++ to compile with main.cpp, kDTree.cpp, and Dataset.o:

g++ -o main main.cpp kDTree.cpp Dataset.o -I . -std=c++11

3. Execute: Run the compiled program:

./main

Ensure g++ is installed and Dataset.o is correctly included and accessible during compilation. Adjust paths as needed for your project setup.
