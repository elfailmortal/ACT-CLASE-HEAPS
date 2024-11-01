#include <iostream>
#include <math.h>
#include <cstdlib>
using namespace std;

/* un heap implementado sobre un arreglo de cualquier tipo de dato */ 
template <class T>
class Heap 
{    
public:
    // un arreglo de tipo T, tamaño máximo y actual del heap
    T *data;				 				
    int maxSize;
    int currentSize; 

    // Constructor que inicializa el heap con un tamaño máximo
    // Complejidad: O(1)
    Heap(int n)
    {	
        maxSize = n;
        currentSize = 0;
        data = new T[maxSize]; // Crear el arreglo del heap
    }

    // Destructor que libera la memoria del heap
    // Complejidad: O(1)
    ~Heap() 
    {	
        delete[] data;
        maxSize = 0; 
        currentSize = 0;
    }		

    bool isEmpty(); // Verifica si el heap está vacío
    bool isFull(); // Verifica si el heap está lleno
	
    T getTop(); // Devuelve el elemento superior del heap
    int parent(int); // Devuelve el índice del padre de un nodo dado
    int left(int); // Devuelve el índice del hijo izquierdo de un nodo dado
    int right(int); // Devuelve el índice del hijo derecho de un nodo dado

    // Inserta un nuevo valor en el heap
    // Complejidad: O(log n)
    void push(T);
    
    // Elimina y devuelve el elemento superior del heap
    // Complejidad: O(log n)
    T pop();
    
    // Reajusta el heap a partir de un índice dado
    // Complejidad: O(log n)
    void heapify(int);
    
    // Intercambia los valores de dos posiciones a y b
    // Complejidad: O(1)
    void swap(int, int);
    
    // Muestra todos los valores del heap de forma ascendente
    // Complejidad: O(n)
    void show();
};

template <class T>
bool Heap<T>::isEmpty()
{	
    return currentSize == 0; // Retorna verdadero si el heap está vacío
}

template <class T>
bool Heap<T>::isFull()
{	
    return currentSize == maxSize; // Retorna verdadero si el heap está lleno
}

// Regresa la raíz del heap
template <class T>
T Heap<T>::getTop()
{	
    return data[0]; // Retorna el elemento en la cima del heap
}

template <class T>
int Heap<T>::parent(int j)
{	
    int p = (j - 1) / 2; // Calcula el índice del padre
    return p;  	
}

template <class T>
int Heap<T>::left(int j)
{	
    int l = 2 * j + 1; // Calcula el índice del hijo izquierdo
    return l;	
}

template <class T>
int Heap<T>::right(int j)
{	
    int r = 2 * j + 2; // Calcula el índice del hijo derecho
    return r; 	
}

// Inserta un nuevo valor en el heap
template <class T>
void Heap<T>::push(T value)
{	
    if (isFull()) {
        cout << "HEAP LLENA" << endl; // Mensaje si el heap está lleno
        return;
    }
    int i = currentSize; // Posición donde se insertará el nuevo valor
    currentSize++; // Incrementa el tamaño actual

    // Coloca el nuevo valor en la posición correcta
    while (i > 0 && value < data[parent(i)]) {
        data[i] = data[parent(i)];
        i = parent(i);
    }
    data[i] = value; // Inserta el nuevo valor
}

// Intercambia los valores de dos posiciones a y b
template <class T>
void Heap<T>::swap(int a, int b)
{	
    T aux = data[a];
    data[a] = data[b];
    data[b] = aux; // Realiza el intercambio
}

template <class T>
void Heap<T>::heapify(int index)
{	
    int l = left(index); // Índice del hijo izquierdo
    int r = right(index); // Índice del hijo derecho
    int top = index; // Inicializa el top como el índice actual

    // Encuentra el menor entre el nodo y sus hijos
    if (l < currentSize && data[l] < data[top]) {
        top = l; // Actualiza el índice del menor
    }
    if (r < currentSize && data[r] < data[top]) {
        top = r; // Actualiza el índice del menor
    }
    
    // Si el nodo no es el menor, intercámbialo y continúa
    if (top != index) {
        swap(index, top);
        heapify(top); // Llama a heapify recursivamente
    }
}

/**
 * Funcion para eliminar el elemento de la cima, es decir, el elemento más pequeño
 * Complejidad: O(log n)
 */
template <class T>
T Heap<T>::pop()
{	
    if (currentSize <= 0) {
        cout << "Heap vacío" << endl;
        return T(); // Regresar valor por defecto
    }
    if (currentSize == 1) {
        currentSize--;
        return data[0]; // Devuelve el único elemento y decremente el tamaño
    }
    
    T root = data[0]; // Almacena el valor de la raíz
    data[0] = data[currentSize - 1]; // Reemplaza la raíz con el último elemento
    currentSize--; // Disminuye el tamaño
    heapify(0); // Reajusta el heap desde la raíz
    return root; // Retorna el valor eliminado
}

/**
 * Funcion para mostrar todos los valores del heap de forma ascendente
 * Complejidad: O(n)
 */
template <class T>
void Heap<T>::show()
{	
    int i;          // Índice del elemento a imprimir.
    int level = 0;  // Nivel actual del heap, comenzando desde la raíz (nivel 0).

    // Muestra el tamaño actual del heap
    cout << "Size: " << currentSize << endl;

    // Inicializa 'i' como la posición correspondiente al primer nodo en el nivel actual.
    i = pow(2, level);

    // Recorre los elementos del heap hasta que todos los elementos se hayan impreso.
    while (i - 1 < currentSize)
    {
        // Imprime el valor del elemento actual y el nivel correspondiente.
        cout << "\t" << data[i - 1] << "(" << level << ")";
        
        // Incrementa el índice para pasar al siguiente elemento.
        i++;

        // Comprueba si ha alcanzado el final del nivel actual.
        if (i == pow(2, level + 1))
        {
            // Realiza un salto de línea para iniciar una nueva fila para el siguiente nivel.
            cout << endl;
            // Incrementa el nivel actual.
            level++;
        }
    }

    // Salto de línea final después de imprimir todos los elementos.
    cout << endl;
}

int main(int argc, char* argv[]) 
{	
    int n = 12;

    Heap<int> heap(n); // recibe tamaño máximo
    // 1.- Agregar los elementos: 2, 1, 5, 7, 9, 8, 4, 3, 6, 7
    heap.push(2);
    heap.push(1);
    heap.push(5);
    heap.push(7);
    heap.push(9);
    heap.push(8);
    heap.push(4);
    heap.push(3);
    heap.push(6);
    heap.push(7);
	
    // 2.- Eliminar el valor en el top. 
    int fuera = heap.pop();
    cout << "Se elimina: " << fuera << endl;

    // 3.- Agregar los valores 3, 1 y 4.
    heap.push(3);
    heap.push(1);
    heap.push(4);
    
    // 4.- Extraer los valores del montículo hasta que quede vacío. Muestra los valores extraídos. 
    heap.show(); 
    exit(0);
}
