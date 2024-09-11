#ifndef LISTADOBENLAZADA_H
#define LISTADOBENLAZADA_H

#include "MPointer.h"
#include <iostream>

class Node {
public:
    int value;
    MPointer<Node> next;
    MPointer<Node> prev;

    Node() : value(0), next(nullptr), prev(nullptr) {}
    explicit Node(int val) : value(val), next(nullptr), prev(nullptr) {}
};

class ListaDobEnlazada {
public:
    void add(int value);
    void printList() const;
    void bubbleSort();
    void insertionSort();
    void quickSort();
    void append(int value);

private:
    MPointer<Node> first = nullptr;
    MPointer<Node> last = nullptr;

    int partition(int low, int high);
    void quickSortRecursive(int low, int high);
    MPointer<Node> getNode(int index) const;
    int get(int index) const;
    void set(int index, int value);
    void swap(int i, int j);
    int size() const;
};

void ListaDobEnlazada::add(int value) {
    MPointer<Node> newNode = MPointer<Node>::New(value);
    if (first == nullptr) {
        first = last = newNode;
    } else {
        newNode->prev = last;
        last->next = newNode;
        last = newNode;
    }
}


void ListaDobEnlazada::printList() const {
    MPointer<Node> current = first;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void ListaDobEnlazada::bubbleSort() {
    if (first == nullptr) {
        return;
    }
    int n = size();
    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (get(j) > get(j + 1)) {

                swap(j, j + 1);
            }
        }
    }
}

void ListaDobEnlazada::insertionSort() {
    int n = size();
    for (int i = 1; i < n; i++) {
        int key = get(i);
        int j = i - 1;

        while (j >= 0 && get(j) > key) {
            set(j + 1, get(j));
            j--;
        }
        set(j + 1, key);
    }
}

void ListaDobEnlazada::quickSort() {
    quickSortRecursive(0, size() - 1);
}

int ListaDobEnlazada::partition(int low, int high) {
    int pivot = get(high);
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

void ListaDobEnlazada::quickSortRecursive(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSortRecursive(low, pi - 1);
        quickSortRecursive(pi + 1, high);
    }
}

int ListaDobEnlazada::get(int index) const {
    MPointer<Node> node = getNode(index);
    if (node == nullptr) {
        return -1;  // Error, valor no encontrado
    }
    return node->value;
}

void ListaDobEnlazada::set(int index, int value) {
    MPointer<Node> node = getNode(index);
    if (node != nullptr) {
        node->value = value;
    } else {
    }
}

void ListaDobEnlazada::swap(int i, int j) {
    if (i == j) return;
    MPointer<Node> node_i = getNode(i);
    MPointer<Node> node_j = getNode(j);
    if (node_i == nullptr || node_j == nullptr) return;

    int temp = node_i->value;
    node_i->value = node_j->value;
    node_j->value = temp;
}

int ListaDobEnlazada::size() const {
    int count = 0;
    MPointer<Node> current = first;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

MPointer<Node> ListaDobEnlazada::getNode(int index) const {
    if (index < 0) {
        std::cerr << "Error: Índice negativo en getNode()" << std::endl;
        return nullptr;
    }

    MPointer<Node> current = first;
    for (int i = 0; i < index && current != nullptr; i++) {
        current = current->next;
    }

    if (current == nullptr) {
        std::cerr << "Error: Índice fuera de rango en getNode()" << std::endl;
    }

    return current;
}

void ListaDobEnlazada::append(int value) {
    MPointer<Node> newNode = MPointer<Node>::New();
    *newNode = Node(value);

    if (first == nullptr) {
        first = last = newNode;  // Si la lista está vacía
    } else {
        newNode->prev = last;  // El nuevo nodo apunta al actual último nodo como su anterior
        last->next = newNode;  // El actual último nodo apunta al nuevo nodo como su siguiente
        last = newNode;  // Ahora, el nuevo nodo se convierte en el último nodo
    }
}


#endif // LISTADOBENLAZADA_H
