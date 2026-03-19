#ifndef MERGESORT_H
#define MERGESORT_H

template <typename NoTipo, typename T>
NoTipo* dividir(NoTipo* head){
    if(!head || !head->prox){
        return nullptr;
    }
    
    NoTipo* slow = head;
    NoTipo* fast = head->prox;
    
    while(fast && fast->prox){
        slow = slow->prox;
        fast = fast->prox->prox;
    }
    
    NoTipo* meio = slow->prox;
    slow->prox = nullptr;
    return meio;
}

template <typename NoTipo, typename T>
NoTipo* mesclar(NoTipo* esq, NoTipo* dir, bool (*comp)(T, T)){
    if(!esq) return dir;
    if(!dir) return esq;

    NoTipo* resultado = nullptr;

    if(comp(esq->dado, dir->dado)){
        resultado = esq;
        resultado->prox = mesclar<NoTipo, T>(esq->prox, dir, comp);
    } else{
        resultado = dir;
        resultado->prox = mesclar<NoTipo, T>(esq, dir->prox, comp);
    }

    return resultado;
}

template <typename NoTipo, typename T>
NoTipo* mergeSort(NoTipo* head, bool (*comp)(T, T)){
    if(!head || !head->prox){
        return head;
    }

    NoTipo* meio = dividir<NoTipo, T>(head);
    NoTipo* esq = mergeSort<NoTipo, T>(head, comp);
    NoTipo* dir = mergeSort<NoTipo, T>(meio, comp);
    
    return mesclar<NoTipo, T>(esq, dir, comp);
}

#endif