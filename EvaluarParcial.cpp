#include "Parcial.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <queue>
#include <cstring>

// Clase para evaluar el rendimiento y resultados del parcial
class EvaluarParcial {
public:
    // Ejecuta la evaluación del parcial
    //
    // Pseudocódigo:
    // Procedimiento ejecutar()
    //     parcial = nuevo objeto Parcial
    //     vertices = lista de vértices con datos de ejemplo
    //     
    //     parcial.cargar(vertices)
    //     imprimir "Grafo generado:"
    //     parcial.imprimirGrafo()
    //     
    //     inicio_tiempo = obtener tiempo actual
    //     resultado = parcial.run()
    //     previos = resultado.first
    //     distancias = resultado.second
    //     fin_tiempo = obtener tiempo actual
    //     
    //     duracion = fin_tiempo - inicio_tiempo
    //     
    //     imprimir "Tiempo de ejecución: " + duracion
    //     
    //     imprimir "Rutas más cortas desde D1 Centro:"
    //     Para cada vértice destino en vertices (excluyendo el primero)
    //         ruta = lista vacía
    //         v = índice del vértice destino
    //         Mientras v != -1
    //             añadir v al inicio de ruta
    //             v = previos[v]
    //         Fin Mientras
    //         
    //         imprimir "A " + nombre del vértice destino + ":"
    //         imprimir "  Ruta: " + nombres de los vértices en ruta
    //         imprimir "  Distancia total: " + distancias[índice del vértice destino]
    //     Fin Para
    // Fin Procedimiento
    //
    // Explicación:
    // 1. Creamos un objeto Parcial y cargamos los datos de ejemplo.
    // 2. Imprimimos la estructura del grafo para visualización.
    // 3. Medimos el tiempo de ejecución del algoritmo de Dijkstra.
    // 4. Para cada destino (excluyendo el vértice inicial):
    //    a. Reconstruimos la ruta más corta usando el vector de 'previos'.
    //    b. Imprimimos la ruta completa y la distancia total.
    // Este proceso nos permite visualizar y analizar las rutas más cortas y el rendimiento del algoritmo

    void ejecutar() {
        Parcial parcial;

        // Datos de ejemplo (coordenadas aproximadas de algunos barrios de Medellín)
        std::vector<Vertice> vertices = {
            {"D1 Centro", 6.1445, -75.3408},
            {"D1 Poblado", 6.1219, -75.3401},
            {"D1 Laureles", 6.1404, -75.3452},
            {"D1 Belén", 6.1601, -75.3351},
            {"D1 Envigado", 6.1016, -75.3458},
            {"D1 Estadio", 6.1457, -75.3412},
            {"D1 Castilla", 6.1706, -75.3335},
            {"D1 Robledo", 6.1755, -75.3514},
            {"D1 Buenos Aires", 6.1425, -75.3432},
            {"D1 Manrique", 6.1626, -75.3307},
            {"D1 Aranjuez", 6.1529, -75.3340},
            {"D1 Floresta", 6.1348, -75.3442},
            {"D1 Guayabal", 6.1306, -75.3535},
            {"D1 Itagüi", 6.0945, -75.3606},
            {"D1 Sabaneta", 6.0845, -75.3637}  
        };

        // Cargar datos
        parcial.cargar(vertices);

        std::cout << "Grafo generado:" << std::endl;
        parcial.imprimirGrafo();

        // Medir tiempo de ejecución de run()
        auto inicio = std::chrono::high_resolution_clock::now();
        
        // Ejecutar el algoritmo y obtener resultados
        std::pair<std::pair<std::vector<int>, double>, std::pair<std::vector<int>, double>> resultado = parcial.run();
        
        auto fin = std::chrono::high_resolution_clock::now();

        // Calcular duración
        auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio);

        // Imprimir resultados
        std::cout << "Tiempo de ejecución del método run(): " 
                  << duracion.count() << " microsegundos" << std::endl;
        std::cout << std::endl;

        std::pair<std::vector<int>, double> rutaEficiente1 = resultado.first;
        std::pair<std::vector<int>, double> rutaEficiente2 = resultado.second;
        
        std::cout << "Ruta mas corta del primer camion: ";
        for (auto it = rutaEficiente1.first.begin(); it != rutaEficiente1.first.end(); ++it) {
            std::cout << parcial.obtenerVertices()[*it].nombre << " (V" << *it << ")";
            if (std::next(it) != rutaEficiente1.first.end()) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl << "Distancia recorrida: " << rutaEficiente1.second << " km" << std::endl;
        std::cout << std::endl;

        std::cout << "Ruta mas corta del segundo camion: ";
        for (auto it = rutaEficiente2.first.begin(); it != rutaEficiente2.first.end(); ++it) {
            std::cout << parcial.obtenerVertices()[*it].nombre << " (V" << *it << ")";
            if (std::next(it) != rutaEficiente2.first.end()) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl << "Distancia recorrida: " << rutaEficiente2.second << " km" << std::endl;
        std::cout << std::endl;

        double distanciaTotalR = rutaEficiente1.second + rutaEficiente2.second;
        std::cout << "En total, se recorrio entre los 2 camiones: " << distanciaTotalR << " km" << std::endl;
    }
};

int main() {
    EvaluarParcial evaluador;
    evaluador.ejecutar();
    return 0;
}