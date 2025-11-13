#ifndef LISTARRAY_H
#define LISTARRAY_H

#include <ostream>
#include "list.h"

template <typename T>
class ListArray: public List<T>{
    private:

        //Atributos
        T* arr;
        int max;
        int n;
        static const int MINSIZE = 2;

        //Metodo privado
        void resize(int new_size);
    public:
        //constructor
        ListArray();
        //destructor
        ~ListArray();
        //sobrecarga del operador []
        T operator[](int pos);

        // Sobrecarga del operador<<
        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, const ListArray<U>& list);

        //Metodos heredados
        void insert(int pos, const T& e);
        void append(const T& e);
        void prepend(const T& e);
        T remove(int pos);
        T get(int pos) const;
        int search(const T& e) const;
        bool empty() const;
        int size() const;
};

#endif
