#ifndef LISTARRAY_H
#define LISTARRAY_H

#include <iostream>
#include <stdexcept>
#include "list.h"

template <typename T>
class ListArray : public List<T> {
private:
    T* arr;
    int max;
    int n;
    static const int MINSIZE = 2;

    void resize(int new_size) {
        if (new_size < MINSIZE) new_size = MINSIZE;

        T* new_arr = new T[new_size];
        int limit = (n < new_size) ? n : new_size;

        for (int i = 0; i < limit; ++i)
            new_arr[i] = arr[i];

        delete[] arr;
        arr = new_arr;
        max = new_size;
    }

public:
    // Constructor
    ListArray() {
        arr = new T[MINSIZE];
        max = MINSIZE;
        n = 0;
    }

    // Destructor
    ~ListArray() {
        delete[] arr;
    }

    // Tamaño actual
    int size() {
        return n;
    }

    // ¿Está vacía?
    bool empty() {
        return n == 0;
    }

    // Insertar elemento en posición pos (pasa por valor para aceptar literales)
    void insert(int pos, T e) {
        if (pos < 0 || pos > n)
            throw std::out_of_range("Posición inválida");

        if (n == max)
            resize(2 * max);

        for (int i = n; i > pos; --i)
            arr[i] = arr[i - 1];

        arr[pos] = e;
        ++n;
    }

    // Añadir al final
    void append(T e) {
        insert(n, e);
    }

    // Añadir al principio
    void prepend(T e) {
        insert(0, e);
    }

    // Eliminar elemento en posición pos y devolverlo
    T remove(int pos) {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida");

        T removed = arr[pos];

        for (int i = pos; i < n - 1; ++i)
            arr[i] = arr[i + 1];

        --n;

        if (n < max / 4 && max > MINSIZE)
            resize(max / 2);

        return removed;
    }

    // Obtener elemento en posición pos (sin usar const)
    T get(int pos) {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida");
        return arr[pos];
    }

    // Operador []
    T operator[](int pos) {
        return get(pos);
    }

    // Buscar elemento: devuelve índice o -1 si no está
    int search(T e) {
        for (int i = 0; i < n; ++i) {
            if (arr[i] == e)
                return i;
        }
        return -1;
    }

    // Sobrecarga del operador<< (acepta const referencia para permitir imprimir)
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const ListArray<U>& list);
};

// Implementación de operator<<
template <typename U>
std::ostream& operator<<(std::ostream& out, const ListArray<U>& list) {
    out << "List => [";
    for (int i = 0; i < list.n; ++i) {
        if (i > 0) out << " ";
        out << list.arr[i];
    }
    out << "]";
    return out;
}

#endif

