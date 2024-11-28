
# Logistical Route Optimization for D1 in Medellín

## Introduction

This project is an exam of the Estructuras de Datos II course, focused on optimizing logistical routes for the D1 store chain in Medellín. The objective is to develop an efficient system to calculate the shortest routes between D1 locations using a brute force algorithm.

## Context

The scenario is described as follows:

- D1 has more than 10 stores distributed across Medellín and El Valle de Aburrá.
- There are two strategically located warehouses: one in the northern zone and the other in the southern zone of the city.
- Two trucks, each assigned to a warehouse, are responsible for supplying all the stores.

The challenge was to develop a C++ program to determine the two shortest and most efficient routes for the trucks to supply all stores, visiting each one only once.

## Project Extension

In this extended version of the project, we expanded the scope to include:

1. Implementation of an efficient graph data structure.
2. Loading D1 store data.
3. Execution of a brute-force algorithm to find the shortest routes.
4. Implementation of an efficient partitioning algorithm of the graph structure
5. Precise measurement of the algorithm's execution time.

## Project Structure

The project consists of three main classes:

1. `Grafo`: Represents the network of D1 stores.
2. `Parcial`: Encapsulates the graph functionality and route search algorithms.
3. `EvaluarParcial`: Manages the performance evaluation and presentation of results.

## Step-by-Step Process

### 1. Grafo Class Implementation

- Create the structure to represent vertices (stores) and edges (connections).
- Implement methods to add vertices and calculate distances between them.

### 2. Parcial Class Implementation

Develop two key methods:

a) `cargar` Method:
```cpp
void cargar(const std::vector<Vertice>& vertices);
```
- Receives D1 store data.
- Adds each store as a vertex to the graph.
- Generates connections (edges) between all vertices.

b) `run` Method:
```cpp
std::pair<std::vector<int>, std::vector<double>> run();
```
- Executes the brute-force algorithm to find the shortest paths.
- Returns:
  - A vector of previous vertex indices in the shortest routes.
  - A vector of shortest distances from the start to each vertex.

### 3. EvaluarParcial Class Implementation

This class orchestrates the whole process:
- Creates sample D1 store data.
- Instantiates the `Parcial` class and loads the data.
- Executes the algorithm and measures the execution time.
- Presents the results: optimal routes and execution time.

### 4. Execution and Evaluation

```cpp
int main() {
    EvaluarParcial evaluador;
    evaluador.ejecutar();
    return 0;
}
```
- Creates an instance of `EvaluarParcial`.
- Calls the `ejecutar()` method to start the process.
- Displays the results on the console.

## Compilation and Execution

1. Ensure all source files are in the same directory.
2. Use the provided Makefile to compile:
   ```
   make
   ```
3. Run the program:
   ```
   ./run
   ```
## Example Output:

- **Truck 1 (South Warehouse)**:
  - Route: South Warehouse → D1 Guayabal → D1 Poblado → D1 Envigado → D1 Itagüí → D1 Sabaneta
  - Total Distance: 23.5 km
  
- **Truck 2 (North Warehouse)**:
  - Route: North Warehouse → D1 Robledo → D1 Castilla → D1 Manrique → D1 Belén → D1 Aranjuez → D1 Centro → D1 Estadio → D1 Laureles → D1 Floresta → D1 Buenos Aires
  - Total Distance: 35.8 km

## Notes

- Haversine formula is used to calculate distances between stores, accounting for the Earth's curvature.
- It implements an undirected graph, ensuring bidirectional connections between stores.
- The graph partitioning algorithm is the key function used to solve this project, as the brute-force search algorithm is implemented. Dividing the graph into two subgraphs simplifies the problem and makes it more efficient in terms of both time complexity and computational resources, allowing the algorithm to focus on smaller, more manageable sections of the overall graph. This partitioning helps improve the scalability and performance of the route optimization process, ensuring faster results while maintaining accuracy. 

## Conclusion

This project challenges you to apply your knowledge of data structures and algorithms to a real-world scenario. Route optimization is a common problem in logistics, and your solution could have significant practical applications.

Remember to consult the original assignment document frequently to ensure that all specific requirements are met.
