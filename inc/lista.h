#ifndef LISTA_H
#define LISTA_H

#include "mergesort.h"

template <typename T>
class Lista{
public:
    struct No{
        T dado;
        No* prox;
        No(const T& val) : dado(val), prox(nullptr){}
    };

private:
    No* inicio;

public:
    Lista() : inicio(nullptr){}
    ~Lista();

    void inserir(const T& val);
    void ordenar(bool (*comp)(T, T));
    void percorrer(void (*func)(T));

    No* getInicio(){ 
        return inicio; 
    }
};

template <typename T>
Lista<T>::~Lista(){
    No* atual = inicio;
    while (atual){
        No* temp = atual;
        atual = atual->prox;
        delete temp;
    }
}

template <typename T>
void Lista<T>::inserir(const T& val){
    No* novo = new No(val);
    novo->prox = inicio;
    inicio = novo;
}

template <typename T>
void Lista<T>::ordenar(bool (*comp)(T, T)){
    inicio = mergeSort<No, T>(inicio, comp);
}

template <typename T>
void Lista<T>::percorrer(void (*func)(T)){
    No* atual = inicio;
    while (atual){
        func(atual->dado);
        atual = atual->prox;
    }
}

#endif
