#pragma once
#include "head_list.h"

template <typename TElem>
class RingHeadList : public HeadList<TElem> {
public:
    RingHeadList() : HeadList<TElem>() {
        do_ringlist();
    }

    RingHeadList(const TElem& val) : HeadList<TElem>(val) {
        do_ringlist();
    }

    RingHeadList(const TNode<TElem>* Node) : HeadList<TElem>(Node) {
        do_ringlist();
    }

    RingHeadList(const HeadList<TElem>& list) : HeadList<TElem>(list) {
        do_ringlist();
    }

    RingHeadList(const RingHeadList<TElem>& list) : HeadList<TElem>(list) {
        do_ringlist();
    }
    ~RingHeadList() {
        clear();
    }
    void clear() {
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
        if (this->pHead) {
            this->pHead->pNext = this->pHead;
        }
    }
    RingHeadList<TElem>& operator=(const RingHeadList<TElem>& list) {
        if (this == &list) {
            return *this;
        }
        this->clear();
        if (list.isEmpty()) {
            this->pFirst = nullptr;
            this->pLast = nullptr;
            this->pCurr = nullptr;
            this->pPrev = this->pHead;
            this->pHead->pNext = this->pHead;
            return *this;
        }
        this->pFirst = new TNode<TElem>(list.pFirst->value);
        TNode<TElem>* currentThis = this->pFirst;
        TNode<TElem>* currentList = list.pFirst->pNext;
        while (currentList != list.get_pHead()) {
            currentThis->pNext = new TNode<TElem>(currentList->value);
            currentThis = currentThis->pNext;
            currentList = currentList->pNext;
        }
        currentThis->pNext = this->pHead;
        this->pLast = currentThis;
        return *this;
    }
    void do_ringlist() {
        if (this->get_pHead() == nullptr) {
            return;
        }
        this->pStop = this->get_pHead();
        if (this->pFirst == nullptr) {
            this->get_pHead()->pNext = this->get_pHead();
            this->pLast = this->get_pHead();
        }
        else {
            if (this->pLast) {
                this->pLast->pNext = this->get_pHead();
            }
        }
    }

    void push_front(TElem val) {
        TNode<TElem>* node = new TNode<TElem>(val);
        if (node == nullptr) {
            throw std::bad_alloc();
        }
        HeadList<TElem>::push_front(node);
        if (this->pLast) {
            this->pLast->pNext = this->get_pHead();
        }
        this->pStop = this->get_pHead();
    }

    void push_front(TNode<TElem>* Node) {
        if (Node == nullptr) {
            throw ("Node cannot be nullptr.");
        }
        HeadList<TElem>::push_front(Node);
        if (this->pLast) {
            this->pLast->pNext = this->get_pHead();
        }
        this->pStop = this->get_pHead();
    }
    void insert_after(TNode<TElem>* Node, TElem val) {
        if (Node == nullptr) {
            throw ("Node cannot be nullptr.");
        }
        this->reset();
        while (!this->isEnded()) {
            if (this->pCurr == Node) {
                TNode<TElem>* newNode = new TNode<TElem>(val);
                newNode->pNext = this->pCurr->pNext;
                this->pCurr->pNext = newNode;
                if (this->pCurr == this->pLast) {
                    this->pLast = newNode;
                }
                return;
            }
            this->next();
        }
        throw "Node not found in the list.";
    }
    void insert_before(TNode<TElem>* Node, TElem val) {
        if (Node == nullptr) {
            throw("Node cannot be nullptr.");
        }
        this->reset();
        while (!this->isEnded()) {
            if (this->pCurr == Node) {
                if (this->pCurr == this->pFirst) {
                    this->push_front(val);
                }
                else {
                    TNode<TElem>* newNode = new TNode<TElem>(val);
                    newNode->pNext = this->pCurr;
                    this->pPrev->pNext = newNode;
                }
                return;
            }
            this->next();
        }
        throw "Node not found in the list.";
    }
    void push_back(TElem val) {
        TNode<TElem>* node = new TNode<TElem>(val);
        if (node == nullptr) {
            throw std::bad_alloc();
        }
        HeadList<TElem>::push_back(node);
        do_ringlist();
    }

    void push_back(TNode<TElem>* Node) {
        if (Node == nullptr) {
            throw ("Node cannot be nullptr.");
        }
        HeadList<TElem>::push_back(Node);
        do_ringlist();
    }
    void remove(TElem val) {
        if (this->isEmpty()) {
            return;
        }

        this->reset();
        while (!this->isEnded()) {
            if (this->current() == val) {
                if (this->pCurr == this->pFirst) {
                    this->pFirst = this->pFirst->pNext;
                    delete this->pCurr;
                    this->pHead->pNext = this->pFirst;
                    if (this->pFirst == nullptr) {
                        this->pLast = nullptr;
                    }
                }
                else {
                    this->pPrev->pNext = this->pCurr->pNext;
                    delete this->pCurr;
                }
                return;
            }
            this->next();
        }
    }
    size_t size() const {
        if (this->isEmpty()) {
            return 0;
        }

        size_t count = 0;
        TNode<TElem>* current = this->pFirst; 
        while (current != this->pStop) { 
            count++;
            current = current->pNext;         
        }
        return count;
    }
    bool operator==(const RingHeadList<TElem>& s) const {
        return HeadList<TElem>::operator==(s);
    }

    bool operator!=(const RingHeadList<TElem>& rl) const {
        return !(*this == rl);
    }
};