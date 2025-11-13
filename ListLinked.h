#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include <stdexcept>
#include "list.h"
#include "node.h"

template<typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    int n;

public:
    // constructor
    ListLinked() : first(nullptr), n(0) { }

    // destructor
    ~ListLinked() {
        Node<T>* cur = first;
        while (cur != nullptr) {
            Node<T>* aux = cur->next;
            delete cur;
            cur = aux;
        }
    }

    // tamaño de la lista
    int size() const override {
        return n;
    }

    // vacía?
    bool empty() const override {
        return (n == 0);
    }

    // insertar en posición pos el valor v
    void insert(int pos, const T& v) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("Posición inválida!");
        }
        if (pos == 0) {
            first = new Node<T>(v, first);
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos-1; ++i) {
                prev = prev->next;
            }
            prev->next = new Node<T>(v, prev->next);
        }
        ++n;
    }

    // eliminar en posición pos y devolver el valor eliminado
    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posición inválida!");
        }
        Node<T>* toDelete = nullptr;
        T valor;
        if (pos == 0) {
            toDelete = first;
            valor = first->elem;
            first = first->next;
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos-1; ++i) {
                prev = prev->next;
            }
            toDelete = prev->next;
            valor = toDelete->elem;
            prev->next = toDelete->next;
        }
        delete toDelete;
        --n;
        return valor;
    }

    // obtener el valor en posición pos (sin modificar)
    T get(int pos) const override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posición inválida!");
        }
        Node<T>* cur = first;
        for (int i = 0; i < pos; ++i) {
            cur = cur->next;
        }
        return cur->elem;
    }

    // sobrecarga del operador []
    T operator[](int pos) const {
        return get(pos);
    }

    // buscar valor v: devuelve índice o -1 si no lo encuentra
    int search(const T& v) const override {
        Node<T>* cur = first;
        int idx = 0;
        while (cur != nullptr) {
            if (cur->elem == v) {
                return idx;
            }
            cur = cur->next;
            ++idx;
        }
        return -1;
    }

    // imprimir por flujo de salida
    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
        out << "List => [";
        Node<T>* cur = list.first;
        bool firstElem = true;
        while (cur != nullptr) {
            if (!firstElem) {
                out << "  ";
            } else {
                out << " ";
                firstElem = false;
            }
            out << cur->elem;
            cur = cur->next;
        }
        if (!firstElem) {
            out << " ";
        }
        out << "]";
        return out;
    }
};

#endif
