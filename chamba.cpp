#include <iostream>
#include <string>

// Inicializa los vectores paralelos dinámicos
void inicializar(int *&ids, float *&pesos, std::string *&destinos, int *&prioridades, char *&estados, int &capacidad, int tam_inicial) {
    capacidad = tam_inicial;
    ids = new int[capacidad];
    pesos = new float[capacidad];
    destinos = new std::string[capacidad];
    prioridades = new int[capacidad];
    estados = new char[capacidad];
}

// Duplica la capacidad de los vectores cuando están llenos
void duplicarCapacidad(int *&ids, float *&pesos, std::string *&destinos, int *&prioridades, char *&estados, int &capacidad) {
    int nueva_capacidad = capacidad * 2;

    int *ids_aux = new int[nueva_capacidad];
    float *pesos_aux = new float[nueva_capacidad];
    std::string *destinos_aux = new std::string[nueva_capacidad];
    int *prior_aux = new int[nueva_capacidad];
    char *estados_aux = new char[nueva_capacidad];

    for (int i = 0; i < capacidad; i++) {
        ids_aux[i] = ids[i];
        pesos_aux[i] = pesos[i];
        destinos_aux[i] = destinos[i];
        prior_aux[i] = prioridades[i];
        estados_aux[i] = estados[i];
    }

    delete[] ids;
    delete[] pesos;
    delete[] destinos;
    delete[] prioridades;
    delete[] estados;

    ids = ids_aux;
    pesos = pesos_aux;
    destinos = destinos_aux;
    prioridades = prior_aux;
    estados = estados_aux;

    capacidad = nueva_capacidad;
}

// Agrega un paquete nuevo (encolar)
void agregarPaquete(int *&ids, float *&pesos, std::string *&destinos, int *&prioridades, char *&estados,
                    int &num_paquetes, int &capacidad) {

    if (num_paquetes == capacidad) {
        duplicarCapacidad(ids, pesos, destinos, prioridades, estados, capacidad);
    }

    int id, prioridad;
    float peso;
    std::string destino;

    std::cout << "Ingrese ID: ";
    std::cin >> id;
    std::cout << "Ingrese Peso: ";
    std::cin >> peso;
    std::cout << "Ingrese Destino: ";
    std::cin.ignore();
    std::getline(std::cin, destino);
    std::cout << "Ingrese Prioridad (1=Alta,2=Media,3=Baja): ";
    std::cin >> prioridad;

    ids[num_paquetes] = id;
    pesos[num_paquetes] = peso;
    destinos[num_paquetes] = destino;
    prioridades[num_paquetes] = prioridad;
    estados[num_paquetes] = 'E';

    num_paquetes++;

    std::cout << "Paquete " << id << " encolado. Capacidad usada: " << num_paquetes << "/" << capacidad << std::endl;
}

// Despacha el paquete más antiguo (FIFO)
void despacharPaquete(char *&estados, int *&ids, int &inicio_cola, int num_paquetes) {
    if (inicio_cola >= num_paquetes) {
        std::cout << "No hay paquetes en cola." << std::endl;
        return;
    }

    estados[inicio_cola] = 'D';
    std::cout << "Paquete " << ids[inicio_cola] << " despachado. Estado: D" << std::endl;
    inicio_cola++;
}

// Muestra el paquete al frente de la cola
void inspeccionarFrente(int *ids, float *pesos, std::string *destinos, int *prioridades, char *estados, int inicio_cola, int num_paquetes) {
    if (inicio_cola >= num_paquetes) {
        std::cout << "La cola está vacía." << std::endl;
        return;
    }

    if (estados[inicio_cola] == 'E') {
        std::cout << "Frente de la cola:" << std::endl;
        std::cout << "  ID: " << ids[inicio_cola]
                  << " | Peso: " << pesos[inicio_cola]
                  << " | Destino: " << destinos[inicio_cola]
                  << " | Prioridad: " << prioridades[inicio_cola]
                  << std::endl;
    } else {
        std::cout << "El paquete al frente ya fue despachado." << std::endl;
    }
}

// Reporte por destino
void reportePorDestino(int *ids, float *pesos, std::string *destinos, char *estados, int num_paquetes) {
    std::string destino_buscado;
    std::cout << "Ingrese destino para el reporte: ";
    std::cin.ignore();
    std::getline(std::cin, destino_buscado);

    int contador = 0;
    float suma_pesos = 0;

    for (int i = 0; i < num_paquetes; i++) {
        if (estados[i] == 'E' && destinos[i] == destino_buscado) {
            contador++;
            suma_pesos += pesos[i];
        }
    }

    std::cout << "Reporte para destino '" << destino_buscado << "':" << std::endl;
    std::cout << "  Paquetes en cola: " << contador << std::endl;

    if (contador > 0)
        std::cout << "  Peso promedio: " << (suma_pesos / contador) << " kg" << std::endl;
}

// Libera toda la memoria
void liberarMemoria(int *&ids, float *&pesos, std::string *&destinos, int *&prioridades, char *&estados) {
    delete[] ids;
    delete[] pesos;
    delete[] destinos;
    delete[] prioridades;
    delete[] estados;
}

int main() {
    int *ids = nullptr;
    float *pesos = nullptr;
    std::string *destinos = nullptr;
    int *prioridades = nullptr;
    char *estados = nullptr;

    int capacidad = 0;
    int num_paquetes = 0;
    int inicio_cola = 0;

    inicializar(ids, pesos, destinos, prioridades, estados, capacidad, 50);

    int opcion;
    do {
        std::cout << "\n--- Sistema de Despacho Logístico MegaEnvío ---" << std::endl;
        std::cout << "1. Agregar Paquete" << std::endl;
        std::cout << "2. Despachar Paquete" << std::endl;
        std::cout << "3. Inspeccionar Frente de Cola" << std::endl;
        std::cout << "4. Reporte por Destino" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                agregarPaquete(ids, pesos, destinos, prioridades, estados, num_paquetes, capacidad);
                break;
            case 2:
                despacharPaquete(estados, ids, inicio_cola, num_paquetes);
                break;
            case 3:
                inspeccionarFrente(ids, pesos, destinos, prioridades, estados, inicio_cola, num_paquetes);
                break;
            case 4:
                reportePorDestino(ids, pesos, destinos, estados, num_paquetes);
                break;
            case 5:
                liberarMemoria(ids, pesos, destinos, prioridades, estados);
                std::cout << "Memoria liberada. Fin del programa." << std::endl;
                break;
            default:
                std::cout << "Opción no válida." << std::endl;
        }

    } while (opcion != 5);

    return 0;
}
