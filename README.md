# Non-Linear Data Structures in C++

This repository contains from-scratch implementations of fundamental **non-linear data structures** in modern C++, built without using the Standard Template Library (STL) for internal mechanics.

The focus is on understanding how trees and graphs behave internally, developing recursive logic, and mastering memory and pointer management through clean and modular code.

---

## Data Structures Implemented

- Binary Trees
- General Trees (any arity)
- Binary Search Trees (BST)
- Heaps
- Graphs
---

## Core Skills Practiced

- How non-linear structures work under the hood  
- Recursive algorithms for tree and graph traversal  
- Memory and pointer management in C++  
- Tree rebalancing, mirroring, and structural checks  
- Graph analysis and traversal with cost matrices  
- Writing STL-free, reusable, and readable code

---

## Example Exercises

These exercises apply the implemented structures to solve meaningful problems and demonstrate their usage in algorithmic scenarios.

### Tree-Based Examples

#### Binary Tree Mirror

Generate the mirror image of a binary tree by recursively swapping the left and right subtrees of every node.

#### Pseudocomplete Binary Tree Check

A binary tree is **pseudocomplete** if, on the second-to-last level, each node has either two children or none. This function verifies whether a binary tree satisfies that condition.

#### Balance Factor of a General Tree

Calculate the imbalance of a general (n-ary) tree, defined as the maximum difference between the heights of the shallowest and deepest subtrees at each level.

#### Rebalance a Binary Search Tree

Balance a binary search tree (BST) by first performing an in-order traversal to obtain a sorted list of elements, then recursively placing the median as the root and rebuilding the left and right subtrees accordingly.

#### Strictly Ternary Tree Check

A general tree is **strictly ternary** if every non-leaf node has exactly three children. This function determines whether a given tree satisfies this property.

---

### Graph-Based Examples

#### Graph Diameter via Pseudocenter

Define the **pseudocenter** of a connected graph as the node that minimizes the sum of shortest distances to its two most distant nodes. The **diameter** is then the sum of those two distances. Given a graph as a cost matrix, this algorithm computes its diameter.

#### Multi-Modal Travel Planning with Constraints

Given three graphs representing transportation costs by road, rail, and air (each with the same set of cities), compute the set of cities reachable from a starting city. The traveler:

- Has a fixed budget,  
- Is allergic to one transport mode,  
- Must avoid that mode entirely.

The solution must combine the remaining two graphs accordingly.

#### Minimum Fiber Network

A telecom company must connect every city in the country using fiber optic cable. Given a weighted graph representing distances between cities, compute the **minimum total fiber length** required to connect all cities. This is a classic **Minimum Spanning Tree** problem.

---

## Features

- No use of STL containers (everything built manually)
- Extensive use of recursion and templates
- Clean class interfaces and separation of concerns
- Fully commented source code
- Written using modern C++ (C++11)

---

## 🛠️ Tech & Tools

- Language: C++
- Standard: C++11 
- Compiler: `g++`, `clang++`

---

## 🚀 How to Compile

```bash
g++ -std=c++17 trees/FileName.cpp -o filename
./mirror
