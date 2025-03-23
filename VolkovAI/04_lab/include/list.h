#ifndef LIST_H
#define LIST_H

#pragma once
template <typename TElem> struct TNode {
    TElem value;
    TNode* pNext;
    TNode() : value(TElem()), pNext(nullptr) {}
    TNode(const TElem& elem) : value(TElem(elem)), pNext(nullptr) {}
    TNode(const TElem& elem, TNode* next) : value(TElem(elem)), pNext(next) {}
    TNode<TElem>& operator= (const TNode<TElem>& node) noexcept {
        if (this == &node) {
            return *this;
        }
        value = node.value;
        pNext = node.pNext;
        return *this;
    }
};

template <typename TElem> class TList {
protected:
    TNode<TElem>* pFirst, * pLast;
    mutable TNode<TElem>* pCurr, * pPrev;
    TNode<TElem>* pStop;
public:
    TList() {
        pFirst = nullptr;
        pLast = nullptr;
        pCurr = pFirst;
        pPrev = nullptr;
        pStop = nullptr;
    }
    TList(const TElem& elem) {
        pFirst = new TNode<TElem>(elem);
        pLast = pFirst;
        pCurr = pFirst;
        pPrev = nullptr;
        pStop = nullptr;
    }
    TList(const TList<TElem>& list) : TList() {
        if (list.pFirst == nullptr) {
            return;
        }
        pFirst = new TNode<TElem>(list.pFirst->value);
        pCurr = pFirst;
        pPrev = nullptr;
        pStop = nullptr;

        TNode<TElem>* srcCurr = list.pFirst->pNext;
        if (srcCurr == list.pStop) {
            pLast = pFirst;
            return;
        }
        while (srcCurr != list.pStop) {
            pCurr->pNext = new TNode<TElem>(srcCurr->value);
            pPrev = pCurr;
            pCurr = pCurr->pNext;
            srcCurr = srcCurr->pNext;
        }
        pLast = pCurr;
        if (pPrev != nullptr) {
            pPrev->pNext = pCurr;
        }
        pCurr = pFirst;
        pPrev = pStop;
    }

    ~TList() {
        clear();
    }

    void clear() {
        while (!isEmpty()) {
            TNode<TElem>* curr = pFirst;
            pFirst = pFirst->pNext;
            delete curr;
        }
        pLast = nullptr;
        pCurr = nullptr;
        pPrev = nullptr;
    }

    bool isEmpty() const {
        return pFirst == nullptr;
    }

    TElem first_value() const {
        if (pFirst == nullptr) {
            throw "PFirst is nullptr.";
        }
        return pFirst->value;
    }

    void push_front(TNode<TElem>* Node) {
        if (Node == nullptr) {
            throw "Trying to insert Node, that is nullptr.";
        }
        if (isEmpty()) {
            pFirst = Node;
            pCurr = pFirst;
            pPrev = pStop;
            pLast = pFirst;
            return;
        }
        Node->pNext = pFirst;
        pFirst = Node;
        pCurr = pFirst;
        pPrev = pStop;
    }

    void push_back(TNode<TElem>* Node) {
        if (Node == nullptr) {
            throw "Trying to insert Node, that is nullptr.";
        }
        if (isEmpty()) {
            this->push_front(Node);
            return;
        }
        pLast->pNext = Node;
        pLast = pLast->pNext;
    }

    TNode<TElem>* search(TElem value) {
        reset();
        while (!isEnded()) {
            if (current() == value) {
                return pCurr;
            }
            next();
        }
        throw ("There's no node with entered value.");
    }

    void insert_before(TNode<TElem>* Node, TElem val) {
        reset();
        while (!isEnded()) {
            if (current() == val) {
                if (pCurr == pFirst) {
                    push_front(Node);
                }
                else {
                    Node->pNext = pCurr;
                    pPrev->pNext = Node;
                }
                return;
            }
            next();
        }
        throw ("There's no node with entered value.");
    }

    void insert_after(TNode<TElem>* Node, TElem val) {
        reset();
        while (!isEnded()) {
            if (current() == val) {
                Node->pNext = pCurr->pNext;
                if (pCurr->pNext == nullptr) {
                    pLast = Node;
                }
                pCurr->pNext = Node;
                return;
            }
            next();
        }
        throw ("There's no node with entered value.");
    }

    void remove(TElem val) {
        reset();
        while (!isEnded()) {
            if (current() == val) {
                if (pCurr == pFirst) {
                    pFirst = pFirst->pNext;
                    delete pCurr;
                }
                else {
                    pPrev->pNext = pCurr->pNext;
                    delete pCurr;
                }
                return;
            }
            next();
        }
    }

    size_t size() const {
        size_t count = 0;
        TNode<TElem>* current = this->pFirst;
        while (current != nullptr) {
            count++;
            current = current->pNext;
        }
        return count;
    }

    TList<TElem>& operator= (const TList<TElem>& list) noexcept {
        if (this == &list) {
            return *this;
        }

        clear();

        if (list.isEmpty()) {
            pFirst = nullptr;
            return *this;
        }

        pFirst = new TNode<TElem>(list.pFirst->value);
        TNode<TElem>* currentThis = pFirst;
        TNode<TElem>* currentList = list.pFirst->pNext;

        while (currentList != nullptr) {
            currentThis->pNext = new TNode<TElem>(currentList->value);
            currentThis = currentThis->pNext;
            currentList = currentList->pNext;
        }

        return *this;
    }

    bool operator==(const TList<TElem>& s) const {
        TNode<TElem>* curr1 = pFirst, * curr2 = s.pFirst;
        while (curr1 != pStop && curr2 != s.pStop) {
            if (curr1->value != curr2->value) {
                return 0;
            }
            curr1 = curr1->pNext;
            curr2 = curr2->pNext;
        }
        return curr1 == pStop && curr2 == s.pStop;
    }

    bool operator!= (const TList<TElem>& list) const {
        return !(*this == list);
    }
    void reset() const {
        pCurr = pFirst;
        pPrev = pStop;
    }
    TElem current() const {
        if (pCurr == nullptr) {
            throw "Current pointer is nullptr.";
        }
        return pCurr->value;
    }
    void next() const {
        if (pCurr == nullptr) {
            throw "Current pointer is nullptr.";
        }
        pPrev = pCurr;
        pCurr = pCurr->pNext;
    }
    bool isEnded() const {
        return pCurr == pStop;
    }
};
#endif //LIST_H