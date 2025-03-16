#pragma once
#include "list.h"

template <typename TElem> class HeadList : public TList<TElem> {
protected:
    TNode<TElem>* pHead;
public:
    HeadList() : TList<TElem>() {
        pHead = new TNode<TElem>(TElem());
        this->pPrev = pHead;
    }
    HeadList(const TNode<TElem>& Node) : TList<TElem>(Node) {
        pHead = new TNode<TElem>(TElem(), this->pFirst);
        this->pPrev = pHead;
    }
    HeadList(const TElem& elem) : TList<TElem>(elem) {
        pHead = new TNode<TElem>(TElem(), this->pFirst);
        this->pPrev = pHead;
    }
    HeadList(const TList<TElem>& list) : TList<TElem>(list) {
        pHead = new TNode<TElem>(TElem(), this->pFirst);
        this->pPrev = pHead;
    }
    HeadList(const HeadList<TElem>& list) : TList<TElem>(list) {
        pHead = new TNode<TElem>(TElem(), this->pFirst);
        this->pPrev = pHead;
    }
    ~HeadList() {
        clear();
        delete pHead;
    }

    void clear() {
        while (!this->isEmpty()) {
            TNode<TElem>* node = this->pFirst;
            this->pFirst = this->pFirst->pNext;
            delete node;
        }
        this->pLast = nullptr;
        this->pCurr = nullptr;
        this->pPrev = pHead;
        if (pHead) {
            pHead->pNext = nullptr;
        }
    }

    TNode<TElem>* get_pHead() const { return pHead; }

    HeadList<TElem>& operator=(const HeadList<TElem>& list) {
        if (this == &list) {
            return *this;
        }
        clear();
        delete pHead;
        TList<TElem>::operator=(list);
        pHead = new TNode<TElem>(TElem(), this->pFirst);
        this->pPrev = pHead;
        return *this;
    }

    void push_front(TNode<TElem>* Node) {
        if (Node == nullptr) {
            throw "Node cannot be nullptr.";
        }
        TList<TElem>::push_front(Node);
        this->pPrev = pHead;
        if (pHead) {
            pHead->pNext = Node;
        }
    }

    void push_back(TNode<TElem>* Node) {
        if (Node == nullptr) {
            throw "Trying to insert Node, that is nullptr.";
        }
        if (this->isEmpty()) {
            this->pFirst = Node;
            this->pLast = Node;
            this->pCurr = Node;
            this->pPrev = pHead;
            pHead->pNext = Node;
        }
        else {
            this->pLast->pNext = Node;
            this->pLast = Node;
        }
    }

    void insert_after(TNode<TElem>* Node, TElem key) {
        if (Node == nullptr) {
            throw "Node cannot be nullptr.";
        }
        this->reset();
        while (!this->isEnded()) {
            if (this->current() == key) {
                Node->pNext = this->pCurr->pNext;
                if (this->pCurr->pNext == nullptr) {
                    this->pLast = Node;
                }
                this->pCurr->pNext = Node;
                return;
            }
            this->next();
        }
        throw "There's no node with entered value.";
    }

    void insert_before(TNode<TElem>* Node, TElem key) {
        if (Node == nullptr) {
            throw "Node cannot be nullptr.";
        }
        this->reset();
        while (!this->isEnded()) {
            if (this->current() == key) {
                if (this->pCurr == this->pFirst) {
                    this->push_front(Node);
                }
                else {
                    Node->pNext = this->pCurr;
                    this->pPrev->pNext = Node;
                }
                return;
            }
            this->next();
        }
        throw "There's no node with entered value.";
    }

    void remove(TElem key) {
        if (this->isEmpty()) {
            return;
        }
        this->reset();
        while (!this->isEnded()) {
            if (this->current() == key) {
                if (this->pCurr == this->pFirst) {
                    this->pFirst = this->pFirst->pNext;
                    delete this->pCurr;
                    pHead->pNext = this->pFirst;
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
        return TList<TElem>::size();
    }

    bool operator==(const HeadList<TElem>& s) const {
        return TList<TElem>::operator==(s);
    }

    bool operator!=(const HeadList<TElem>& list) const {
        return !(*this == list);
    }
};