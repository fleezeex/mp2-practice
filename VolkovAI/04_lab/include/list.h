#pragma once
template <typename TElem> struct TNode {
    TElem value;
    TNode* pNext;
    TNode() : value(TElem()), pNext(nullptr) {}
    TNode(const TElem& elem) : value(TElem(elem)), pNext(nullptr) {}
    TNode(const TElem& elem, TNode* next) : value(TElem(elem)), pNext(next) {}
    const TNode<TElem>& operator= (const TNode<TElem>& node) noexcept {
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
    TNode<TElem>* pCurr, * pPrev;
    TNode<TElem>* pStop;
public:
    TList();
    TList(const TElem& elem);
    TList(const TList<TElem>& list);
    ~TList();

    void clear();
    bool isEmpty() const;
    size_t size() const;

    virtual void push_front(TNode<TElem>* node);
    virtual void push_back(TNode<TElem>* node);
    virtual void insert_before(TNode<TElem>* node, TElem val);
    virtual void insert_after(TNode<TElem>* node, TElem val);
    virtual void remove(const TElem& val);

    TNode<TElem>* search(const TElem& value);

    void reset();
    TElem current() const;
    void next();
    bool isEnded() const;

    const TList<TElem>& operator=(const TList<TElem>& list) noexcept;
    bool operator==(const TList<TElem>& list) const;
    bool operator!=(const TList<TElem>& list) const;
};

template <typename TElem>
TList<TElem>::TList() {
    pFirst = nullptr;
    pLast = nullptr;
    pCurr = pFirst;
    pPrev = nullptr;
    pStop = nullptr;
}

template <typename TElem>
TList<TElem>::TList(const TElem& elem) {
    pFirst = new TNode<TElem>(elem);
    pLast = pFirst;
    pCurr = pFirst;
    pPrev = nullptr;
    pStop = nullptr;
}

template <typename TElem>
TList<TElem>::TList(const TList<TElem>& list) : TList() {
    if (list.pFirst == nullptr) {
        return;
    }

    pFirst = new TNode<TElem>(list.pFirst->value);
    pCurr = pFirst;
    pPrev = nullptr;
    pStop = nullptr;

    TNode<TElem>* srcCurr = list.pFirst->pNext;
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

template <typename TElem>
TList<TElem>::~TList() {
    clear();
}

template <typename TElem>
void TList<TElem>::clear() {
    while (!isEmpty()) {
        TNode<TElem>* curr = pFirst;
        pFirst = pFirst->pNext;
        delete curr;
    }
    pLast = nullptr;
    pCurr = nullptr;
    pPrev = nullptr;
}

template <typename TElem>
bool TList<TElem>::isEmpty() const {
    return pFirst == nullptr;
}

template <typename TElem>
void TList<TElem>::push_front(TNode<TElem>* node) {
    if (node == nullptr) {
        throw "Trying to insert node that is nullptr";
    }
    if (isEmpty()) {
        pFirst = node;
        pCurr = pFirst;
        pPrev = nullptr;
        pLast = pFirst;
        return;
    }
    node->pNext = pFirst;
    pFirst = node;
    pCurr = pFirst;
    pPrev = nullptr;
}

template <typename TElem>
void TList<TElem>::push_back(TNode<TElem>* node) {
    if (node == nullptr) {
        throw "Trying to insert node that is nullptr";
    }
    if (isEmpty()) {
        push_front(node);
        return;
    }
    pLast->pNext = node;
    pLast = pLast->pNext;
}

template <typename TElem>
TNode<TElem>* TList<TElem>::search(const TElem& value) {
    reset();
    while (!isEnded()) {
        if (current() == value) {
            return pCurr;
        }
        next();
    }
    return nullptr;
}

template <typename TElem>
void TList<TElem>::insert_before(TNode<TElem>* node, TElem val) {
    search(val);
    if (pCurr == pStop) {
        throw "Element not found";
    }
    if (pCurr == pFirst) {
        push_front(node);
    }
    else {
        node->pNext = pCurr;
        pPrev->pNext = node;
    }
}

template <typename TElem>
void TList<TElem>::insert_after(TNode<TElem>* node, TElem val) {
    search(val);
    if (pCurr == pStop) {
        throw "Element not found";
    }
    node->pNext = pCurr->pNext;
    if (pCurr->pNext == nullptr) {
        pLast = node;
    }
    pCurr->pNext = node;
}

template <typename TElem>
void TList<TElem>::remove(const TElem& val) {
    search(val);
    if (pCurr == nullptr) {
        throw "Element not found";
    }
    if (pCurr == pFirst) {
        pFirst = pFirst->pNext;
        if (pFirst == nullptr) {
            pLast = nullptr;
        }
        delete pCurr;
    }
    else if (pCurr->pNext == nullptr) {
        pLast = pPrev;
        pPrev->pNext = nullptr;
        delete pCurr;
    }
    else {
        pPrev->pNext = pCurr->pNext;
        delete pCurr;
    }
    reset();
}

template <typename TElem>
size_t TList<TElem>::size() const {
    size_t count = 0;
    TNode<TElem>* current = pFirst;
    while (current != nullptr) {
        count++;
        current = current->pNext;
    }
    return count;
}

template <typename TElem>
const TList<TElem>& TList<TElem>::operator=(const TList<TElem>& list) noexcept {
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
    pLast = currentThis; //
    return *this;
}

template <typename TElem>
bool TList<TElem>::operator==(const TList<TElem>& list) const {
    TNode<TElem>* curr1 = pFirst;
    TNode<TElem>* curr2 = list.pFirst;
    while (curr1 != pStop && curr2 != list.pStop) {
        if (curr1->value != curr2->value) {
            return false;
        }
        curr1 = curr1->pNext;
        curr2 = curr2->pNext;
    }
    return curr1 == pStop && curr2 == list.pStop;
}

template <typename TElem>
bool TList<TElem>::operator!=(const TList<TElem>& list) const {
    return !(*this == list);
}

template <typename TElem>
void TList<TElem>::reset() {
    pCurr = pFirst;
    pPrev = pStop;
}

template <typename TElem>
TElem TList<TElem>::current() const {
    if (pCurr == nullptr) {
        throw "Current pointer is nullptr";
    }
    return pCurr->value;
}

template <typename TElem>
void TList<TElem>::next() {
    if (pCurr == nullptr) {
        throw "Current pointer is nullptr";
    }
    pPrev = pCurr;
    pCurr = pCurr->pNext;
}

template <typename TElem>
bool TList<TElem>::isEnded() const {
    return pCurr == pStop;
}
