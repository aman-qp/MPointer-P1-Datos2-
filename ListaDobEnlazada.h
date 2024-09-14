#ifndef LISTADOBENLAZADA_H
#define LISTADOBENLAZADA_H

#include "MPointer.h"
#include <iostream>
#include <stdexcept>

template<typename T>
class Node {
public:
    T value;
    MPointer<Node<T>> next;
    MPointer<Node<T>> prev;

    Node() : value(T()), next(nullptr), prev(nullptr) {}
    explicit Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
};

template<typename T>
class ListaDobEnlazada {
public:
    void add(const T& value);
    void printList() const;
    void bubbleSort();
    void insertionSort();
    void quickSort();
    void append(const T& value);
    T get(int index) const;
    int size() const;
    void remove(int index);

private:
    MPointer<Node<T>> first = nullptr;
    MPointer<Node<T>> last = nullptr;
    int listSize = 0;

    int partition(int low, int high);
    void quickSortRecursive(int low, int high);
    MPointer<Node<T>> getNode(int index) const;
    void set(int index, const T& value);
    void swap(int i, int j);
};

template<typename T>
void ListaDobEnlazada<T>::add(const T& value) {
    MPointer<Node<T>> newNode = MPointer<Node<T>>::New(value);
    if (first == nullptr) {
        first = last = newNode;
    } else {
        newNode->prev = last;
        last->next = newNode;
        last = newNode;
    }
    ++listSize;
}

template<typename T>
void ListaDobEnlazada<T>::remove(int index) {
    if (index < 0 || index >= size()) {
        throw std::out_of_range("Index out of bounds");
    }

    MPointer<Node<T>> current = getNode(index);

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        first = current->next;
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    } else {
        last = current->prev;
    }

    --listSize;
}

//Imprime la lista
template<typename T>
void ListaDobEnlazada<T>::printList() const {
    MPointer<Node<T>> current = first;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
T ListaDobEnlazada<T>::get(int index) const {
    MPointer<Node<T>> node = getNode(index);
    if (node == nullptr) {
        throw std::out_of_range("Index out of bounds");
    }
    return node->value;
}


template<typename T>
void ListaDobEnlazada<T>::set(int index, const T& value) {
    MPointer<Node<T>> node = getNode(index);
    if (node != nullptr) {
        node->value = value;
    } else {
        throw std::out_of_range("Index out of bounds");
    }
}

//Realiza el swap necesario en lo algoritmos de ordenamiento
template<typename T>
void ListaDobEnlazada<T>::swap(int i, int j) {
    if (i == j) return;
    T temp = get(i);
    set(i, get(j));
    set(j, temp);
}

//Obtener el tamaño
template<typename T>
int ListaDobEnlazada<T>::size() const {
    return listSize;
}

//Obtener el nodo
template<typename T>
MPointer<Node<T>> ListaDobEnlazada<T>::getNode(int index) const {
    if (index < 0 || index >= listSize) {
        return nullptr;
    }

    MPointer<Node<T>> current = first;
    for (int i = 0; i < index && current != nullptr; i++) {
        current = current->next;
    }

    return current;
}

//Agregar elementos a la lista
template<typename T>
void ListaDobEnlazada<T>::append(const T& value) {
    add(value);
}

//Algoritmos de ordenamiento
template<typename T>
void ListaDobEnlazada<T>::bubbleSort() {
    for (int i = 0; i < size() - 1; i++) {
        for (int j = 0; j < size() - i - 1; j++) {
            if (get(j) > get(j + 1)) {
                swap(j, j + 1);
            }
        }
    }
}

template<typename T>
void ListaDobEnlazada<T>::insertionSort() {
    for (int i = 1; i < size(); i++) {
        T key = get(i);
        int j = i - 1;

        while (j >= 0 && get(j) > key) {
            set(j + 1, get(j));
            j--;
        }
        set(j + 1, key);
    }
}

template<typename T>
void ListaDobEnlazada<T>::quickSort() {
    quickSortRecursive(0, size() - 1);
}

template<typename T>
int ListaDobEnlazada<T>::partition(int low, int high) {
    T pivot = get(high);
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (get(j) < pivot) {
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, high);
    return (i + 1);
}

template<typename T>
void ListaDobEnlazada<T>::quickSortRecursive(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSortRecursive(low, pi - 1);
        quickSortRecursive(pi + 1, high);
    }
}

#endif // LISTADOBENLAZADA_H