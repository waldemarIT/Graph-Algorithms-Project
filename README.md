# Graph Analysis Engine (C++ / Embedded-Oriented)

This project is a comprehensive implementation of graph analysis algorithms in C++, developed with embedded constraints and low-level programming in mind. Originally designed as a university assignment, it was intentionally extended and engineered as a lightweight and modular simulation of how graph algorithms can be used in embedded systems, such as smart city infrastructure or sensor network control modules.

## Project Purpose

Many modern embedded systems rely on structural analysis of real-world topologies — for example, modeling traffic systems, wireless sensor deployment, or route optimization in logistics. This project simulates such use cases using undirected graphs, where each node represents a device, location, or controller, and each edge represents a communication or physical link.

By implementing this system without STL containers and focusing on memory-efficient, custom-built data structures, the project aims to model how embedded hardware could perform localized, algorithmic reasoning under resource constraints.

## Features

The system processes `k` graphs per run, and for each graph computes:

- Degree sequence of all vertices
- Number of connected components
- Bipartiteness test
- Vertex eccentricity (per component)
- Planarity check
- Vertex coloring using:
  - Greedy strategy (by vertex number)
  - Largest First (LF)
  - Smallest Last First (SLF)
- Count of distinct C4 subgraphs (4-node cycles)
- Number of edges in the graph complement

If a specific feature is not implemented, the output uses `'?'` as a placeholder (per task specification). Only features 1 and 2 are mandatory; this implementation includes **all** features.

## Technical Highlights

- Language: C++
- Programming Paradigm: Object-Oriented Design
- STL: **Not used** — all containers implemented manually for memory transparency
  - `MyVector` — dynamic array implementation
  - `MyQueue` — queue used in BFS traversals
- Algorithms: BFS, DFS, coloring heuristics, planarity test, eccentricity calculation
- Input: CLI or file stream
- Output: Printed responses per graph dataset

## Example Input
2 4 2 2 3 2 1 4 1 2 1 1 3 2 2 3 1 1 0


Each graph starts with a number of vertices `n`, followed by `n` lines of adjacency info. See `sample_input.txt` for more examples.

## Use Case Context

Although this program was built and run in a standard environment, its structure is meant to reflect **embedded-inspired system design**. In a real use case such as smart traffic control:

- Graph planarity helps layout intersection maps efficiently
- Vertex coloring avoids interference among wireless units
- Component detection identifies isolated subnetworks
- C4 detection flags circular congestion structures
- Eccentricity analysis supports better signal propagation paths

This approach shows how algorithmic thinking can power useful decisions in real-time embedded logic controllers, even without access to high-level libraries or dynamic memory abstraction layers.

## Compilation & Run

```bash
g++ -std=c++17 main.cpp -o graph_engine
./graph_engine < input.txt > output.txt
