#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>
#include <list>
#include <cmath>

// Estructura que representa un vértice en el grafo (un establecimiento D1)
struct Vertice {
    std::string nombre;  // Nombre del establecimiento
    double latitud;      // Latitud de la ubicación
    double longitud;     // Longitud de la ubicación
};

// Estructura que representa una arista en el grafo (conexión entre establecimientos)
struct Arista {
    int destino;         // Índice del vértice destino
    double distancia;    // Distancia entre los vértices en kilómetros
};

// Clase que representa un grafo de establecimientos D1
class Grafo {
private:
    std::vector<Vertice> vertices;                  // Lista de vértices
    std::vector<std::list<Arista>> adyacencia;      // Lista de adyacencia

    // Calcula la distancia entre dos vértices usando la fórmula del haversine
    double calcularDistancia(const Vertice& v1, const Vertice& v2) const;

public:
    // Agrega un nuevo vértice al grafo
    void agregarVertice(const Vertice& v);

    // Genera las aristas entre todos los vértices
    void generarAristas();

    // Ejecuta el algoritmo de Dijkstra desde un vértice inicial
    std::pair<std::vector<int>, std::vector<double>> dijkstra(int inicio);

    // Obtiene el número de vértices en el grafo
    int size() const;

    // Imprime la estructura del grafo
    void imprimirGrafo() const;

    // Obtiene la lista de vértices del grafo
    std::vector<Vertice> obtenerVertices() const { return vertices; }

    // Obtiene la lista de aristas del grafo
    std::vector<std::list<Arista>> obtenerAristas() const { return adyacencia; }

    // Desvincular vertices
    void borrarVertice(int v);

    // Ejecuta el algoritmo de Kernighan-lin para la particíon del gráfo
    std::pair<std::vector<int>, std::vector<int>> particionar();
};

#endif // GRAFO_H