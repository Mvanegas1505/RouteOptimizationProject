#include "Parcial.h"
#include <iostream>

// Carga los vértices en el grafo
//
// Pseudocódigo:
// Procedimiento cargar(vertices)
//     Para cada v en vertices
//         grafo.agregarVertice(v)
//     Fin Para
// Fin Procedimiento
//
// Explicación:
// - Iteramos sobre cada vértice en la lista proporcionada.
// - Agregamos cada vértice al grafo utilizando el método agregarVertice().
// - Esto inicializa el grafo con todos los establecimientos D1.
void Parcial::cargar(const std::vector<Vertice>& vertices) {
    for (const auto& v : vertices) {
        grafo.agregarVertice(v);
    }
    if (vertices.size() > 1) {
        grafo.generarAristas();
    }
}

std::vector<std::vector<int>> posiblesRutas;
std::vector<std::vector<int>> Parcial::calcularRutas(int partida, int destino, Grafo& temp){
    // Marcar todos los vertices como no visitados
    std::vector<bool> visitados(temp.size(), false);

    // Crear un vector para guardar las rutas
    std::vector<int> ruta(temp.size(), -1);
    int rutaIndice = 0; // Iniciciar ruta como vacio

    // Llamar a la funcion recursiva para calcular las rutas
    calcularRutasRec(partida, destino, visitados, ruta, rutaIndice, temp);
    return posiblesRutas;
}

// Funcion recursiva para hallar todas las rutas de "actual" a "destino".
// "visitados" registra los vertices en "ruta".
// "ruta" guarda los vertices y "rutaIndice" es el actual
void Parcial::calcularRutasRec(int actual, int destino, std::vector<bool> visitados, std::vector<int> ruta, int& rutaIndice, Grafo& temp){
    
    // Marcar el nodo actual y guardarlo en "ruta"
    visitados[actual] = true;
    ruta[rutaIndice] = actual;
    rutaIndice++;

    // Si vertice "actual" es el mismo que el vertice "destino",
    // agregar la "ruta" a "posiblesRutas"
    if (actual == destino){
        posiblesRutas.push_back(ruta);

    } else { 
        // Recorrer recursivamente todos los vertices adyacentes
        // al vertices "actual"
        std::list<Arista>::iterator i;
        std::list<Arista> vecinos = temp.obtenerAristas()[actual];
        for (i = vecinos.begin(); i != vecinos.end(); i++){
            if (!visitados[(*i).destino]){
                calcularRutasRec((*i).destino, destino, visitados, ruta, rutaIndice, temp);
            }
        }
    }  

    // Remover vertice actual de "ruta" y marcarlos como no visitado
    rutaIndice--;
    visitados[actual] = false;
}

void Parcial::borrarRutas(std::vector<std::vector<int>>& rutas, Grafo temp){
    // Adaptar las rutas de acuerdo a las aristas presentes
    int numNodosConectados = 0;
    for (const auto& adyacencia : temp.obtenerAristas()){
        int sizeAdyacencia = static_cast<int>(adyacencia.size());
        if (sizeAdyacencia > 0){
            numNodosConectados++;
        }
    }

    // Identificar rutas a eliminar
    std::vector<int> borrar;
    int rutasSize = static_cast<int>(rutas.size());
    for (int i = 0; i < rutasSize; ++i){
        bool eliminar = false;
        for (int v = 0; v < numNodosConectados; ++v){
            if (rutas[i][v] == -1){
                eliminar = true;
                break;
            }
        }
        if (eliminar) borrar.push_back(i);
    }
    
    // Borrar todas las rutas de "rutas" por indice
    int count = 0;
    for (int it : borrar){
        rutas.erase(rutas.begin() + (it - count));
        count++;
    }

    // Borrar "-1" de las rutas
    // "-1" significa que no hay vertice
    for (auto& ruta : rutas){
        ruta.erase(ruta.begin() + numNodosConectados, ruta.end());
    }
}

Grafo Parcial::creacionSubgrafo(Grafo temp, std::vector<int> subgrafo){
    // Identificar que vertices que no se encuentran en subgrafo
    std::vector<int> borrar;
    int sizeVertices = static_cast<int>(temp.size());
    for (int i = 0; i < sizeVertices; ++i){
        bool eliminar = true;
        for (int verticesB : subgrafo){
            if (i == verticesB){
                eliminar = false;
            }
        }
        if (eliminar) borrar.push_back(i);
    }

    // Borrar las aristas de los nodos que no estan en el subgrafo
    // De esta manera se desvincula el subgrafo del grafo original
    for (int verticeB : borrar){
        temp.borrarVertice(verticeB);
    }

    return temp;
}

std::pair<std::vector<int>, double> Parcial::hallarRutaEficiente(int verticeInit, Grafo temp){
    // Obtener los nodos vecinos de un vertice
    std::list<Arista> vecinos = temp.obtenerAristas()[verticeInit];

    // Iterar sobre cada vecino para hallar la ruta mas corta
    std::pair<std::vector<int>, double> rutaEficiente = {{}, std::numeric_limits<double>::infinity()};
    for (const auto& arista : vecinos){

        // Obtener todas las rutas posibles de un punto "a" a un punto "b"
        std::vector<std::vector<int>> rutas = calcularRutas(verticeInit, arista.destino, temp);
        posiblesRutas = {}; // Resetear las posible rutas de la funcion calcularRutas()

        // Borrar rutas que no pasen por todos los vertices
        borrarRutas(rutas, temp);

        int indiceRuta = 0;
        double distanciaMasCorta = std::numeric_limits<double>::infinity();

        // Iterar sobre cada ruta para hallar la ruta mas eficiente
        // que recorre todos los nodos en la menor distancia total
        int rutasSize = static_cast<int>(rutas.size());
        for (int i = 0; i < rutasSize; ++i){
            double distanciaTotal = 0;

            int rutaSize = static_cast<int>(rutas[i].size());
            for (int j = 0; j < rutaSize; ++j){

                std::list<Arista> vecinos = temp.obtenerAristas()[rutas[i][j]];
                for (const auto& vecino : vecinos){
                    if (j != rutaSize - 1){
                        if (vecino.destino == rutas[i][j + 1]){
                            distanciaTotal += vecino.distancia;
                        }
                    }
                }
            }
            
            // Guardar la ruta y la distancia total mas corta
            if (distanciaMasCorta > distanciaTotal){
                distanciaMasCorta = distanciaTotal;
                indiceRuta = i;
            }
        }

        // Par {ruta, distancia recorrida}
        std::pair<std::vector<int>, double> rutaMasCorta = {rutas[indiceRuta], distanciaMasCorta}; 

        // Comparar ruta actual para un destino "b" con la
        // ruta mas eficiente hasta el momento
        if (rutaEficiente.second > rutaMasCorta.second){
            rutaEficiente = rutaMasCorta;
        }
    }
    return rutaEficiente;
}

std::pair<std::pair<std::vector<int>, double>, std::pair<std::vector<int>, double>> Parcial::run() {
    // Partir el grafo en 2 de forma eficiente
    std::pair<std::vector<int>, std::vector<int>> particion = grafo.particionar();

    std::vector<int> subGraph1 = particion.first;
    std::vector<int> subGraph2 = particion.second;   

    Grafo subgrafo1 = creacionSubgrafo(grafo, subGraph1);
    Grafo subgrafo2 = creacionSubgrafo(grafo, subGraph2);

    // Dados los D1s donde van a comenzar los camiones...
    int camion1 = 0; // 0 o 7 son los puntos de partida mas eficientes
    int camion2 = 8; // 8 o 14 son los puntos de partida mas eficientes

    std::pair<std::vector<int>, double> rutaEficiente1 = hallarRutaEficiente(camion1, subgrafo1);
    std::pair<std::vector<int>, double> rutaEficiente2 = hallarRutaEficiente(camion2, subgrafo2);
    // std::pair<std::vector<int>, double> rutaEficiente3 = hallarRutaEficiente(14, grafo);
    
    std::pair<std::pair<std::vector<int>, double>, std::pair<std::vector<int>, double>> rutas = {rutaEficiente1, rutaEficiente2};
    return rutas;
}

// Imprime la estructura del grafo
//
// Explicación:
// - Simplemente llamamos al método imprimirGrafo() del objeto grafo.
// - Esto mostrará todos los vértices y sus conexiones.
void Parcial::imprimirGrafo() const {
    grafo.imprimirGrafo();
}