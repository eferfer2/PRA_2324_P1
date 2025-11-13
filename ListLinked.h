#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <iostream>
#include <stdexcept>
#include "list.h"
#include "node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    int n;

public:
    ListLinked() : first(nullptr), n(0) {}

    ~ListLinked() {
        Node<T>* curr = first;
        while (curr != nullptr) {
            Node<T>* tmp = curr->next;
            delete curr;
            curr = tmp;
        }
    }

    int size() const {
        return n;
    }

    bool empty() const {
        return n == 0;
    }

    void insert(int pos, const T& e) {
        if (pos < 0 || pos > n)
            throw std::out_of_range("Posición inválida");

        if (pos == 0)
            first = new Node<T>(e, first);
        else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i)
                prev = prev->next;
            prev->next = new Node<T>(e, prev->next);
        }
        ++n;
    }

    T remove(int pos) {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida");

        Node<T>* toDelete;
        T value;

        if (pos == 0) {
            toDelete = first;
            value = first->data;
            first = first->next;
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i)
                prev = prev->next;
            toDelete = prev->next;
            value = toDelete->data;
            prev->next = toDelete->next;
        }
        delete toDelete;
        --n;
        return value;
    }

    T get(int pos) const {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("Posición inválida");

        Node<T>* curr = first;
        for (int i = 0; i < pos; ++i)
            curr = curr->next;
        return curr->data;
    }

    // operador []
    T operator[](int pos) const {
        return get(pos);
    }

    // búsqueda lineal
    int search(const T& e) const {
        Node<T>* curr = first;
        int index = 0;
        while (curr != nullptr) {
            if (curr->data == e)
                return index;
            curr = curr->next;
            ++index;
        }
        return -1;
    }

    // métodos extra según tu List.h
    void append(const T& e) {
        insert(n, e);
    }

    void prepend(const T& e) {
        insert(0, e);
    }

    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
        out << "List => [";
        Node<T>* curr = list.first;
        bool firstElem = true;
        while (curr != nullptr) {
            if (!firstElem)
                out << " ";
            out << curr->data;
            curr = curr->next;
            firstElem = false;
        }
        out << "]";
        return out;
    }
};

#endif

