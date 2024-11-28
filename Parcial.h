#ifndef PARCIAL_H
#define PARCIAL_H

#include "Grafo.h"
#include <vector>

// Clase que encapsula la funcionalidad del grafo para el parcial
class Parcial {
private:
    Grafo grafo;  // Grafo que representa los establecimientos D1

public:
    // Carga los vértices en el grafo
    void cargar(const std::vector<Vertice>& vertices);

    // Ejecuta el algoritmo de Dijkstra en el grafo
    std::pair<std::pair<std::vector<int>, double>, std::pair<std::vector<int>, double>> run();

    // Imprime la estructura del grafo
    void imprimirGrafo() const;

    // Obtiene la lista de vértices del grafo
    std::vector<Vertice> obtenerVertices() const { return grafo.obtenerVertices(); }
    
    // Calcular todas las posibles rutas desde "partida" a "destino"
    std::vector<std::vector<int>> calcularRutas(int partida, int destino, Grafo& temp);

    // Encontrar rutas por medio de DFS para la funcion calcularRutas()
    void calcularRutasRec(int actual, int destino, std::vector<bool> visitados, std::vector<int> ruta, int& rutaIndice, Grafo& temp);

    // Borrar rutas que no pasen por todos los vertices
    void borrarRutas(std::vector<std::vector<int>>& rutas, Grafo temp);
    
    // Crear un subgrafo a partir de una sublista de vertices y el grafo original
    Grafo creacionSubgrafo(Grafo temp, std::vector<int> subgrafo);

    // Hallar la ruta mas eficiente que pasa por todos los vertices
    // Este metodo utliza fuerza bruta para encontrar la ruta
    std::pair<std::vector<int>, double> hallarRutaEficiente(int verticeInit, Grafo temp);
};

#endif // PARCIAL_H