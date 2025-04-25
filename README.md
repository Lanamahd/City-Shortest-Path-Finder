# City Shortest Path Finder

## Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [How It Works](#how-it-works)
4. [File Structure](#file-structure)
    - [Input File (`cities.txt`)](#input-file-citiestxt)
    - [Output File (`shortest_distance.txt`)](#output-file-shortest_distancetxt)
5. [Menu Options](#menu-options)
6. [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Steps to Run the Program](#steps-to-run-the-program)
7. [Example Output](#example-output)
8. [Implementation Details](#implementation-details)
    - [Data Structures](#data-structures)
    - [Algorithms](#algorithms)
9. [Conclusion](#conclusion)

---

## Overview

The **City Shortest Path Finder** is a C-based program that calculates the shortest path between cities using **Dijkstra's Algorithm** and **Breadth-First Search (BFS)**. This program simulates a directed graph where cities are connected by weighted edges representing distances. The program is designed to load city data from a file, allow users to input source and destination cities, and determine the shortest path and total distance between them. The results can also be saved to a file for later reference.

---

## Features

- **Graph Representation**:
  - Cities and distances are represented as an adjacency matrix.
  - Cities are dynamically stored in a linked list to handle unique city names.

- **Algorithms**:
  - Implements **Dijkstra's Algorithm** for weighted shortest path calculation.
  - Implements **Breadth-First Search (BFS)** for unweighted shortest path and traversal.

- **User-Friendly Options**:
  - Load cities from a file.
  - Input source and destination cities.
  - Calculate and display the shortest path and total distance.
  - Save the output to a file (`shortest_distance.txt`).

- **Error Handling**:
  - Detects and handles invalid cities or file errors.
  - Prevents duplicates when loading cities from a file.

---

## How It Works

1. **Linked List for Cities**:
   - Each city is stored as a node in a linked list with a unique index.
   - Duplicate city entries are filtered during file loading.

2. **Graph Construction**:
   - An adjacency matrix is constructed based on the city distances provided in the input file.
   - Directed edges are created between cities with their respective weights.

3. **Shortest Path Calculation**:
   - **Dijkstra's Algorithm**: Finds the shortest weighted path and total distance between the source and destination cities.
   - **BFS**: Explores unweighted shortest paths and prints the traversal route.

4. **File I/O**:
   - Cities and distances are loaded from a file (`cities.txt`).
   - The shortest path and total distance can be saved to an output file (`shortest_distance.txt`).

---

## File Structure

### Input File (`cities.txt`)

The input file should contain city pairs and distances on each line in the following format:
    ```
    CityA CityB Distance
    
    Example:
    City1 City2 50 City2 City3 70 City3 City4 60



### Output File (`shortest_distance.txt`)

The program writes the shortest path and total distance to this file. Example content:

    ```
    BFS PATH: City4 <- City3 <- City2 <- City1 TOTAL DISTANCE FROM City1 TO City4 IS 180.

    DIJKSTRA'S PATH: City4 <- City3 <- City2 <- City1 TOTAL DISTANCE FROM City1 TO City4 IS 180.


---

## Menu Options

The program provides the following menu for user interaction:

1. **Load Cities**:
   - Reads the city data from the input file and constructs the graph.
2. **Enter Source**:
   - Allows the user to specify the source city.
3. **Enter Destination**:
   - Allows the user to specify the destination city.
4. **Find Shortest Path**:
   - Displays the shortest path and total distance using BFS and Dijkstra's Algorithm.
5. **Save to File and Exit**:
   - Saves results to `shortest_distance.txt` and exits the program.

---

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC).
- A text file (`cities.txt`) with city data in the specified format.

### Steps to Run the Program

1. Clone the repository:
   ```bash
   git clone https://github.com/Lanamahd/City-Shortest-Path-Finder.git
   cd City-Shortest-Path-Finder

2. Compile the program:
    ```bash
      gcc main.c -o city_shortest_path_finder

3. Run the executable:
   ```bash
    ./city_shortest_path_finder

4. Follow the menu options to load cities, calculate paths, and save results.


---

## Example Output

### Case 1: BFS and Dijkstra's Results

    ```
    BFS PATH:
    City4 <- City3 <- City2 <- City1
    TOTAL DISTANCE FROM City1 TO City4 IS 180.
    
    DIJKSTRA'S PATH:
    City4 <- City3 <- City2 <- City1
    TOTAL DISTANCE FROM City1 TO City4 IS 180.

### Case 2: Error Handling for Unknown City

    ```
    CITY NOT FOUND!

---

## Implementation Details
### Data Structures
1. **Linked List**: Used to store city names and their unique indices.
2. **Adjacency Matrix**: Represents the graph with distances as weights between cities.

### Algorithms
1. **Dijkstra's Algorithm**: Finds the shortest weighted path using a priority mechanism.
2. **BFS**: Explores paths layer by layer and finds the shortest unweighted route.

---
## Conclusion

The **City Shortest Path Finder** provides an efficient solution for calculating the shortest path between cities using Dijkstra's Algorithm and BFS. By integrating file-based input and output, the program offers a user-friendly interface for managing city data and determining routes. It serves as an excellent tool for understanding graph traversal algorithms and their practical applications in real-world scenarios.

