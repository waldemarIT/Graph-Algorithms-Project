Graph Analysis Project (C++)
🧠 Project Overview
This project is a comprehensive implementation of graph analysis in modern C++, utilizing object-oriented programming (OOP) principles and custom-built data structures. It is designed to read and process multiple graphs and compute various graph-theoretical properties that are common in computer science and algorithmic applications.

Notably, the project includes a custom implementation of core data structures such as vectors and queues — without using the STL — to demonstrate a deeper understanding of memory and algorithm mechanics.

Although initially developed as part of a university assignment, the project structure, algorithms, and coding approach reflect professional software engineering standards.

🔍 Features
For each input graph, the following parameters are computed:

Degree sequence

Number of connected components

Bipartiteness check

Vertex eccentricity (within components)

Graph planarity

Vertex coloring using:

Greedy coloring (by vertex ID order)

LF method (Largest First, tiebreaker by vertex ID)

SLF method (Smallest Last First, tiebreaker by degree and then ID)

Count of distinct C4 subgraphs (cycles of length 4)

Number of edges in the graph complement

If any optional parameter is not implemented, the program outputs ? as specified.

🧰 Technical Details
Language: C++

Programming Paradigm: Object-Oriented Programming (OOP)

Main Class: Graph — encapsulates all logic and graph data

Custom Data Structures:

MyVector — dynamic array replacement

MyQueue — queue used in BFS and other traversal algorithms

Algorithms Used:

Breadth-First Search (BFS) and Depth-First Search (DFS)

Graph coloring (Greedy, LF, SLF)

Bipartiteness check using BFS

Eccentricity calculation using BFS

Detection of C4 cycles

Edge counting in graph complement

Input/Output: Processes multiple graphs as per custom input format and outputs required results in strict order.

🧑‍💻 About the Developer
I'm a student with a solid foundation in algorithms, data structures, and software engineering practices. This project showcases my ability to:

Write clean and modular code using OOP in C++

Build custom implementations of core data structures

Implement non-trivial graph algorithms from scratch

Understand both theoretical concepts and practical application

I intentionally avoided using STL to reinforce my grasp of memory management, dynamic arrays, and queues. The codebase is structured, scalable, and reflects a problem-solving mindset.
