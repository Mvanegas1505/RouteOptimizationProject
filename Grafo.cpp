#include "Grafo.h"
#include <limits>
#include <queue>
#include <iostream>
#include <iomanip>
#include <climits>
#include <algorithm>
#include <numeric>   // std::accumulate
#include <cmath>

const double PI = 3.14159265358979323846;
const double RADIO_TIERRA = 6371.0; // Radio de la Tierra en kilómetros

// Calcula la distancia entre dos vértices usando la fórmula del haversine
//
// Pseudocódigo:
// Función calcularDistancia(v1, v2)
//     lat1 = v1.latitud * PI / 180  // Convertir a radianes
//     lon1 = v1.longitud * PI / 180
//     lat2 = v2.latitud * PI / 180
//     lon2 = v2.longitud * PI / 180
//     
//     dlon = lon2 - lon1
//     dlat = lat2 - lat1
//     
//     a = sin²(dlat/2) + cos(lat1) * cos(lat2) * sin²(dlon/2)
//     c = 2 * atan2(√a, √(1-a))
//     
//     distancia = RADIO_TIERRA * c
//     return distancia
// Fin Función
//
// Explicación:
// - Convertimos las coordenadas de grados a radianes para los cálculos trigonométricos.
// - Calculamos las diferencias de longitud y latitud.
// - Aplicamos la fórmula del haversine para obtener la distancia angular entre los puntos.
// - Multiplicamos por el radio de la Tierra para obtener la distancia en kilómetros.
// Esta fórmula tiene en cuenta la curvatura de la Tierra, proporcionando una distancia más precisa.

double Grafo::calcularDistancia(const Vertice& v1, const Vertice& v2) const {
    double lat1 = v1.latitud * PI / 180.0;
    double lon1 = v1.longitud * PI / 180.0;
    double lat2 = v2.latitud * PI / 180.0;
    double lon2 = v2.longitud * PI / 180.0;

    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;

    double a = std::sin(dlat/2) * std::sin(dlat/2) + std::cos(lat1) * std::cos(lat2) * std::sin(dlon/2) * std::sin(dlon/2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1-a));

    return RADIO_TIERRA * c;
}

// Genera todas las aristas del grafo conectando cada vértice con todos los demás
//
// Pseudocódigo:
// Procedimiento generarAristas()
//     Para i desde 0 hasta tamaño(vertices) - 1
//         Para j desde i + 1 hasta tamaño(vertices) - 1
//             distancia = calcularDistancia(vertices[i], vertices[j])
//             agregarArista(i, j, distancia)
//             agregarArista(j, i, distancia)
//         Fin Para
//     Fin Para
// Fin Procedimiento
//
// Explicación:
// - Usamos dos bucles anidados para comparar cada vértice con todos los demás.
// - Calculamos la distancia entre cada par de vértices.
// - Añadimos una arista en ambas direcciones (grafo no dirigido) con la distancia calculada.
// Este enfoque crea un grafo completo donde cada vértice está conectado con todos los demás.

void Grafo::generarAristas() {
    for (size_t i = 0; i < vertices.size(); ++i) {
        for (size_t j = i + 1; j < vertices.size(); ++j) {
            double distancia = calcularDistancia(vertices[i], vertices[j]);
            adyacencia[i].push_back({static_cast<int>(j), distancia});
            adyacencia[j].push_back({static_cast<int>(i), distancia});
        }
    }
}

void Grafo::agregarVertice(const Vertice& v) {
    vertices.push_back(v);
    adyacencia.push_back(std::list<Arista>());
}

// Implementa el algoritmo de Dijkstra para encontrar las rutas más cortas desde un vértice inicial
//
// Pseudocódigo:
// Función dijkstra(inicio)
//     distancias = vector de tamaño vertices lleno con infinito
//     previos = vector de tamaño vertices lleno con -1
//     cola_prioridad = nueva cola de prioridad mínima
//     
//     distancias[inicio] = 0
//     insertar (0, inicio) en cola_prioridad
//     
//     Mientras cola_prioridad no esté vacía
//         u = extraer mínimo de cola_prioridad
//         
//         Para cada arista (v, peso) adyacente a u
//             Si distancias[u] + peso < distancias[v]
//                 distancias[v] = distancias[u] + peso
//                 previos[v] = u
//                 insertar (distancias[v], v) en cola_prioridad
//             Fin Si
//         Fin Para
//     Fin Mientras
//     
//     return (previos, distancias)
// Fin Función
//
// Explicación:
// - Inicializamos las distancias a infinito y los previos a -1.
// - Usamos una cola de prioridad para seleccionar siempre el vértice no visitado más cercano.
// - Comenzamos con el vértice inicial, estableciendo su distancia a 0.
// - En cada iteración:
//   * Seleccionamos el vértice u con la menor distancia.
//   * Para cada vecino v de u, actualizamos su distancia si encontramos un camino más corto a través de u.
// - El proceso continúa hasta que se han visitado todos los vértices alcanzables.
// - Retornamos los vectores de previos (para reconstruir las rutas) y distancias.
std::pair<std::vector<int>, std::vector<double>> Grafo::dijkstra(int inicio) {
    std::vector<double> distancias(vertices.size(), std::numeric_limits<double>::infinity());
    std::vector<int> previos(vertices.size(), -1);
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;

    distancias[inicio] = 0;
    pq.push({0, inicio});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& arista : adyacencia[u]) {
            int v = arista.destino;
            double peso = arista.distancia;

            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                previos[v] = u;
                pq.push({distancias[v], v});
            }
        }
    }

    return {previos, distancias};
}

int Grafo::size() const {
    return vertices.size();
}

void Grafo::imprimirGrafo() const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        std::cout << "Vértice " << i << " (" << vertices[i].nombre << "):" << std::endl;
        for (const auto& arista : adyacencia[i]) {
            std::cout << "  -> Vértice " << arista.destino << " (Distancia: " 
                      << std::fixed << std::setprecision(2) << arista.distancia << " km)" << std::endl;
        }
        std::cout << std::endl;
    }
}

void Grafo::borrarVertice(int v){
    for (size_t i = 0; i < vertices.size(); ++i){
        for (auto it = adyacencia[i].begin(); it != adyacencia[i].end(); ++it){
            if ((*it).destino == v){
                adyacencia[i].erase(it);
                break;
            }
        } 
    }
    adyacencia[v].erase(adyacencia[v].begin(), adyacencia[v].end());
}

// Realiza la partición del grafo en dos subgrafos 
std::pair<std::vector<int>, std::vector<int>> Grafo::particionar() {
    int n = static_cast<int>(vertices.size());
 
    std::vector<int> A;
    std::vector<int> B;
 
    // Seleccionar un vértice inicial de forma arbitraria
    int verticeA = 0;
    int verticeB = -1;
    int minDistancia = INT_MAX;
 
    // Buscar el vértice más cercano al vérticeA
    for (const auto& arista : adyacencia[verticeA]) {
        if (arista.distancia < minDistancia) {
            minDistancia = arista.distancia;
            verticeB = arista.destino;
        }
    }
 
    // Asignar los vértices iniciales al subgrafo A y B
    A.push_back(verticeA);
    B.push_back(verticeB);
 
    // Función para calcular la suma de distancias de un vértice a todos los vértices de un subgrafo
    auto sumaDistancias = [&](int vertice, const std::vector<int>& subgrafo) -> double {
        double suma = 0;
        for (int u : subgrafo) {
            for (const auto& arista : adyacencia[vertice]) {
                if (arista.destino == u) {
                    suma += arista.distancia;
                }
            }
        }
        return suma;
    };
 
    // Asignar los vértices restantes al subgrafo con menor suma de distancias
    for (int i = 0; i < n; ++i) {
        if (i != verticeA && i != verticeB) {  // Saltar los vértices ya asignados
            double sumaDistanciasA = sumaDistancias(i, A);
            double sumaDistanciasB = sumaDistancias(i, B);
 
            // Asigna el vértice al subgrafo con la menor suma de distancias
            if (sumaDistanciasA < sumaDistanciasB) {
                A.push_back(i);
            } else {
                B.push_back(i);
            }
        }
    }
 
    // Función para calcular la suma total de distancias dentro de un subgrafo
    auto calcularSumaTotalDistancias = [&](const std::vector<int>& subgrafo) -> double {
        double sumaTotal = 0;
        for (int u : subgrafo) {
            sumaTotal += sumaDistancias(u, subgrafo);
        }
        return sumaTotal;
    };
 
    // Verificación: intentar intercambiar vértices entre A y B para minimizar distancias
    bool huboMejora = true;
    while (huboMejora) {
        huboMejora = false;  // Asumimos que no hay mejora inicialmente
 
        double sumaA_actual = calcularSumaTotalDistancias(A);
        double sumaB_actual = calcularSumaTotalDistancias(B);
 
        for (size_t i = 0; i < A.size(); ++i) {
            for (size_t j = 0; j < B.size(); ++j) {
                // Intercambiar A[i] con B[j] temporalmente
                std::swap(A[i], B[j]);
 
                // Calcular las nuevas sumas de distancias
                double nuevaSumaA = calcularSumaTotalDistancias(A);
                double nuevaSumaB = calcularSumaTotalDistancias(B);
 
                // Si el intercambio mejora las distancias, mantener el cambio
                if (nuevaSumaA + nuevaSumaB < sumaA_actual + sumaB_actual) {
                    huboMejora = true;
                    sumaA_actual = nuevaSumaA;
                    sumaB_actual = nuevaSumaB;
                } else {
                    // Si no mejora, revertir el cambio
                    std::swap(A[i], B[j]);
                }
            }
        }
    }
 
    return {A, B};
}