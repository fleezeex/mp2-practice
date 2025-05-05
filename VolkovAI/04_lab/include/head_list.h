#pragma once
#include "list.h"

template <typename TElem> class HeadList : public TList<TElem> {
protected:
    TNode<TElem>* pHead;
public:
    HeadList();
    HeadList(const TNode<TElem>& Node);
    HeadList(const TElem& elem);
    HeadList(const TList<TElem>& list);
    HeadList(const HeadList<TElem>& list);
    virtual ~HeadList();

    const HeadList<TElem>& operator=(const HeadList<TElem>& list);

    virtual void push_front(TNode<TElem>* Node);
    virtual void push_back(TNode<TElem>* Node);
    virtual void insert_after(TNode<TElem>* Node, TElem key);
    virtual void insert_before(TNode<TElem>* Node, TElem key);
    void remove(TElem key);
    size_t size() const;


    bool operator==(const HeadList<TElem>& s) const;
    bool operator!=(const HeadList<TElem>& list) const;

};

template <typename TElem>
HeadList<TElem>::HeadList() : TList<TElem>() {
    pHead = new TNode<TElem>(TElem());
}

template <typename TElem>
HeadList<TElem>::HeadList(const TNode<TElem>& Node) : TList<TElem>(Node) {
    pHead = new TNode<TElem>(TElem(), this->pFirst);
}

template <typename TElem>
HeadList<TElem>::HeadList(const TElem& elem) : TList<TElem>(elem) {
    pHead = new TNode<TElem>(TElem(), this->pFirst);
}

template <typename TElem>
HeadList<TElem>::HeadList(const TList<TElem>& list) : TList<TElem>(list) {
    pHead = new TNode<TElem>(TElem(), this->pFirst);
}

template <typename TElem>
HeadList<TElem>::HeadList(const HeadList<TElem>& list) : TList<TElem>(list) {
    pHead = new TNode<TElem>(TElem(), this->pFirst);
}

template <typename TElem>
HeadList<TElem>::~HeadList() {
    delete pHead;
}

template <typename TElem>
const HeadList<TElem>& HeadList<TElem>::operator=(const HeadList<TElem>& list) {
    if (this == &list) {
        return *this;
    }
    TList<TElem>::operator=(list);
    pHead->pNext = this->pFirst;
    return *this;
}

template <typename TElem>
void HeadList<TElem>::push_front(TNode<TElem>* Node) {
    TList<TElem>::push_front(Node);
    pHead->pNext = pFirst;
}

template <typename TElem>
void HeadList<TElem>::push_back(TNode<TElem>* Node) {
    TList<TElem>::push_back(Node);
    pHead->pNext = pFirst;
}

template <typename TElem>
void HeadList<TElem>::insert_after(TNode<TElem>* Node, TElem key) {
    if (Node == nullptr) {
        throw "Node cannot be nullptr";
    }
    TList<TElem>::insert_after(Node, key);
}

template <typename TElem>
void HeadList<TElem>::insert_before(TNode<TElem>* Node, TElem key) {
    if (Node == nullptr) {
        throw "Node cannot be nullptr";
    }
    TList<TElem>::insert_before(Node, key);
    pHead->pNext = pFirst;
}

template <typename TElem>
void HeadList<TElem>::remove(TElem key) {
    TList<TElem>::remove(key);
    pHead->pNext = this->pFirst;
}

template <typename TElem>
size_t HeadList<TElem>::size() const {
    return TList<TElem>::size();
}

template <typename TElem>
bool HeadList<TElem>::operator==(const HeadList<TElem>& s) const {
    return TList<TElem>::operator==(s);
}

template <typename TElem>
bool HeadList<TElem>::operator!=(const HeadList<TElem>& list) const {
    return !(*this == list);
}