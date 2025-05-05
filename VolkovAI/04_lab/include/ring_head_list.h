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
    ~RingHeadList();

    void clear();
    const RingHeadList<TElem>& operator=(const RingHeadList<TElem>& list);
    size_t size() const;

    void push_front(TElem val);
    void push_front(TNode<TElem>* Node) override;
    void push_back(TElem val);
    void push_back(TNode<TElem>* Node) override;
    void insert_after(TNode<TElem>* Node, TElem val);
    void insert_before(TNode<TElem>* Node, TElem val);
    void remove(TElem val); // разобратсья с методами

    bool operator==(const RingHeadList<TElem>& s) const;
    bool operator!=(const RingHeadList<TElem>& rl) const;

private:
    void do_ringlist();  // убить он ваще не нужен
};

template <typename TElem>
RingHeadList<TElem>::RingHeadList() : HeadList<TElem>() {
    do_ringlist();
}

template <typename TElem>
RingHeadList<TElem>::RingHeadList(const TElem& val) : HeadList<TElem>(val) {
    do_ringlist();
}

template <typename TElem>
RingHeadList<TElem>::RingHeadList(const TNode<TElem>* Node) : HeadList<TElem>(Node) {
    do_ringlist();
}

template <typename TElem>
RingHeadList<TElem>::RingHeadList(const HeadList<TElem>& list) : HeadList<TElem>(list) {
    do_ringlist();
}

template <typename TElem>
RingHeadList<TElem>::RingHeadList(const RingHeadList<TElem>& list) : HeadList<TElem>(list) {
    do_ringlist();
}

template <typename TElem>
RingHeadList<TElem>::~RingHeadList() {
    clear();
}

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
        this->clear();
        if (!list.isEmpty()) {
            TNode<TElem>* src = list.pFirst;
            size_t count = 0;
            const size_t max_size = 10000;

            while (src != list.pHead && src != nullptr && count < max_size) {
                this->push_back(new TNode<TElem>(src->value));
                src = src->pNext;
                count++;
            }

            if (count >= max_size) {
                this->clear();
                throw "Assignment failed: circular reference";
            }
        }
        this->do_ringlist();
    }
    return *this;
}

template <typename TElem>
void RingHeadList<TElem>::do_ringlist() {
    if (this->pHead == nullptr) {
        return;
    }
    this->pStop = this->pHead;
    if (this->pFirst == nullptr) {
        this->pHead->pNext = this->pHead;
        this->pLast = this->pHead;
    }
    else {
        if (this->pLast) {
            this->pLast->pNext = this->pHead;
        }
    }
}

template <typename TElem>
void RingHeadList<TElem>::push_front(TElem val) {
    TNode<TElem>* node = new TNode<TElem>(val);
    if (node == nullptr) {
        throw "Node cannot be nullptr";
    }
    HeadList<TElem>::push_front(node);
    if (this->pLast) {
        this->pLast->pNext = this->pHead;
    }
    this->pStop = this->pHead;
}

template <typename TElem>
void RingHeadList<TElem>::push_front(TNode<TElem>* Node) {
    if (Node == nullptr) {
        throw "Node cannot be nullptr";
    }
    HeadList<TElem>::push_front(Node);  
    do_ringlist();
}

template <typename TElem>
void RingHeadList<TElem>::push_back(TNode<TElem>* Node) {
    if (Node == nullptr) {
        throw "Node cannot be nullptr";
    }
    HeadList<TElem>::push_back(Node); 
    do_ringlist();
}

template <typename TElem>
void RingHeadList<TElem>::push_back(TElem val) {
    TNode<TElem>* node = new TNode<TElem>(val);
    if (node == nullptr) {
        throw "Node cannot be nullptr";
    }
    HeadList<TElem>::push_back(node);
    do_ringlist();
}

template <typename TElem>
void RingHeadList<TElem>::insert_after(TNode<TElem>* Node, TElem val) {
    HeadList<TElem>::insert_after(Node, val);
    if (this->pCurr == this->pLast) {
        this->pLast = Node->pNext;
    }
    this->do_ringlist();
}

template <typename TElem>
void RingHeadList<TElem>::insert_before(TNode<TElem>* Node, TElem val) {
    HeadList<TElem>::insert_before(Node, val);
    if (Node == this->pFirst) {
        this->pFirst = Node->pNext;
    }
    this->do_ringlist();
}

template <typename TElem>
void RingHeadList<TElem>::remove(TElem val) {
    if (this->isEmpty()) {
        return;
    }
    bool wasFirst = (this->pFirst && this->pFirst->value == val);
    bool wasLast = (this->pLast && this->pLast->value == val);
    HeadList<TElem>::remove(val);
    if (wasFirst) {
        this->pHead->pNext = this->pFirst;
    }
    if (wasLast) {
        if (this->pLast) {
            this->pLast->pNext = this->pHead;
        }
    }
    this->do_ringlist();
}

template <typename TElem>
size_t RingHeadList<TElem>::size() const {
    if (this->isEmpty()) {
        return 0;
    }
    size_t count = 0;
    TNode<TElem>* current = this->pFirst;
    while (current != nullptr && current != this->pHead) {
        count++;
        current = current->pNext;
    }
    return count;
}

template <typename TElem>
bool RingHeadList<TElem>::operator==(const RingHeadList<TElem>& s) const {
    return HeadList<TElem>::operator==(s);
}

template <typename TElem>
bool RingHeadList<TElem>::operator!=(const RingHeadList<TElem>& rl) const {
    return !(*this == rl);
}
