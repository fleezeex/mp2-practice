#pragma once
#include "head_list.h"

template <typename TElem>
class RingHeadList : public HeadList<TElem> {
public:
    RingHeadList();
    RingHeadList(const TElem& val);
    RingHeadList(const TNode<TElem>* Node);
    RingHeadList(const HeadList<TElem>& list);
    RingHeadList(const RingHeadList<TElem>& list);
    ~RingHeadList() = default;

    void clear();
    const RingHeadList<TElem>& operator=(const RingHeadList<TElem>& list);
    size_t size() const;

    void push_front(TElem val);
    void push_back(TElem val);
    void remove(TElem val);

    bool operator==(const RingHeadList<TElem>& s) const;
    bool operator!=(const RingHeadList<TElem>& rl) const;
};

template <typename TElem>
RingHeadList<TElem>::RingHeadList() : HeadList<TElem>() {}

template <typename TElem>
RingHeadList<TElem>::RingHeadList(const TElem& val) : HeadList<TElem>(val) {}

template <typename TElem>
RingHeadList<TElem>::RingHeadList(const TNode<TElem>* Node) : HeadList<TElem>(Node) {}

template <typename TElem>
RingHeadList<TElem>::RingHeadList(const HeadList<TElem>& list) : HeadList<TElem>(list) {}

template <typename TElem>
RingHeadList<TElem>::RingHeadList(const RingHeadList<TElem>& list) : HeadList<TElem>(list) {}


template <typename TElem>
void RingHeadList<TElem>::clear() {
    if (this->isEmpty()) {
        return;
    }

    this->reset();
    while (!this->isEnded()) {
        TNode<TElem>* temp = this->pCurr;
        this->next();
        delete temp;
    }
    this->pFirst = nullptr;
    this->pLast = nullptr;
    this->pCurr = nullptr;
    this->pPrev = nullptr;
    this->pHead->pNext = this->pHead;  
}

template <typename TElem>
const RingHeadList<TElem>& RingHeadList<TElem>::operator=(const RingHeadList<TElem>& list) {
    if (this != &list) {
        clear();
        if (!list.isEmpty()) {
            TNode<TElem>* src = list.pFirst;
            while (src != list.pHead && src != nullptr) {
                this->push_back(src->value);
                src = src->pNext;
            }
        }
    }
    return *this;
}

template <typename TElem>
void RingHeadList<TElem>::push_front(TElem val) {
    HeadList<TElem>::push_front(new TNode<TElem>(val));
}

template <typename TElem>
void RingHeadList<TElem>::push_back(TElem val) {
    HeadList<TElem>::push_back(new TNode<TElem>(val));
}


template <typename TElem>
void RingHeadList<TElem>::remove(TElem val) {
    if (this->isEmpty()) {
        return;
    }
    HeadList<TElem>::remove(val);
    if (this->pFirst && this->pFirst->value == val) {
        this->pHead->pNext = this->pFirst;
    }
    if (this->pLast && this->pLast->value == val) {
        if (this->pLast) {
            this->pLast->pNext = this->pHead;
        }
    }
}

template <typename TElem>
size_t RingHeadList<TElem>::size() const {
    return HeadList<TElem>::size();
}

template <typename TElem>
bool RingHeadList<TElem>::operator==(const RingHeadList<TElem>& s) const {
    return HeadList<TElem>::operator==(s);
}

template <typename TElem>
bool RingHeadList<TElem>::operator!=(const RingHeadList<TElem>& rl) const {
    return !(*this == rl);
}
