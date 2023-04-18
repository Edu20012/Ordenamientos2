#include <iostream>
#include <string>
using namespace std;

template<typename T>
struct Solicitud {
    T nombre;
    T carrera;
    T preparatoria;
    double promedio;
};

template<typename T>
class Nodo {
public:
    Solicitud<T> dato;
    Nodo<T>* siguiente;
    Nodo(Solicitud<T> datoNodo, Nodo<T>* siguienteNodo = nullptr) {
        dato = datoNodo;
        siguiente = siguienteNodo;
    }
};

template<typename T>
class Lista {
private:
    Nodo<T>* cabeza;
    int tam;
public:
    Lista() {
        cabeza = nullptr;
        tam = 0;
    }

    void insertarAlFinal(Solicitud<T> dato) {
        Nodo<T>* nuevoNodo = new Nodo<T>(dato);
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        tam++;
    }

    Solicitud<T> obtenerElemento(int indice) {
        Nodo<T>* actual = cabeza;
        int contador = 0;
        while (actual != nullptr && contador < indice) {
            actual = actual->siguiente;
            contador++;
        }
        if (actual == nullptr) {
            throw "Índice fuera de rango";
        } else {
            return actual->dato;
        }
    }

    int tamano() {
        return tam;
    }
};

template<typename T>
int busquedaBinaria(Lista<T>& lista, T elemento, int izquierda, int derecha) {
    if (derecha < izquierda) {
        return -1;
    }
    int medio = (izquierda + derecha) / 2;
    Solicitud<T> solicitudEnMedio = lista.obtenerElemento(medio);
    if (solicitudEnMedio.nombre == elemento) {
        return medio;
    } else if (elemento < solicitudEnMedio.nombre) {
        return busquedaBinaria(lista, elemento, izquierda, medio - 1);
    } else {
        return busquedaBinaria(lista, elemento, medio + 1, derecha);
    }
}

template<typename T>
void quicksort(Lista<T>& lista, int izquierda, int derecha) {
    int i = izquierda;
    int j = derecha;
    Solicitud<T> pivote = lista.obtenerElemento((izquierda + derecha) / 2);

    while (i <= j) {
        while (lista.obtenerElemento(i).promedio < pivote.promedio) {
            i++;
        }
        while (lista.obtenerElemento(j).promedio > pivote.promedio) {
            j--;
        }
        if (i <= j) {
            Solicitud<T> temp = lista.obtenerElemento(i);
            lista.obtenerElemento(i) = lista.obtenerElemento(j);
            lista.obtenerElemento(j) = temp;
            i++;
            j--;
        }
    }
    if (izquierda < j) {
        quicksort(lista, izquierda, j);
    }
    if (i < derecha) {
        quicksort(lista, i, derecha);
    }
}

// Función principal del programa
int main() {
    Lista<string> listaSolicitudes;
    int opcion = 0;
    while (opcion != 3){
        cout <<"****************************************************" << endl;
        cout <<"\n\n" << endl;
        cout <<"Seleccione una opcion: \n\n" << endl;
        cout <<"\n\n" << endl;
        cout << "1. Agregar solicitud \n\n" << endl;
        cout <<"\n\n" << endl;
        cout << "2. Buscar solicitud por nombre \n\n" << endl;
        cout <<"\n\n" << endl;
        cout << "3. Salir \n\n" << endl;
        cout <<"****************************************************" << endl;
        cin >> opcion;
        if (opcion == 1){
            Solicitud<string> nuevaSolicitud;
            cout << "Ingrese el nombre del alumno: ";
            cin >> nuevaSolicitud.nombre;
            cout << "Ingrese la carrera a cursar: ";
            cin >> nuevaSolicitud.carrera;
            cout << "Ingrese la preparatoria procedente: ";
            cin >> nuevaSolicitud.preparatoria;
            cout << "Ingrese el promedio general obtenido: ";
            cin >> nuevaSolicitud.promedio;
            listaSolicitudes.insertarAlFinal(nuevaSolicitud);
            cout << "Solicitud agregada correctamente." << endl;
            }else if (opcion == 2){
                string nombreBuscado;
                cout << "Ingrese el nombre del alumno a buscar: ";
                cin >> nombreBuscado;
                int indice = busquedaBinaria(listaSolicitudes, nombreBuscado, 0, listaSolicitudes.tamano() - 1);
                if (indice == -1){
                    cout << "No se encontró la solicitud correspondiente. Por favor, dé de alta la solicitud." << endl;
                    } else{
                        Solicitud<string> solicitudEncontrada = listaSolicitudes.obtenerElemento(indice);
                        cout << "Solicitud encontrada:" << endl;
                        cout << "Nombre: " << solicitudEncontrada.nombre << endl;
                        cout << "Carrera: " << solicitudEncontrada.carrera << endl;
                        cout << "Preparatoria procedente: " << solicitudEncontrada.preparatoria << endl;
                        cout << "Promedio general obtenido: " << solicitudEncontrada.promedio << endl;
                        cout << "Posición en la lista: " << indice << endl;
                   }
            }
        }
    return 0;
}
