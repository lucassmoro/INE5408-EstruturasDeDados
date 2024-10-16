namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}
        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }
        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }
        void prev(Node* node) {
            prev_ = node;
        }
        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    head = nullptr;
    size_ = 0;
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    Node* p = new Node(data);
    if (p != nullptr) {
        if (empty()) {
            head = p;
            p->next(p);
            p->prev(p);
        } else {
            p->prev(head->prev());
            head->prev()->next(p);
            head->prev(p);
            p->next(head);
        }
        size_++;
    } else {
        throw std::out_of_range("memória insuficiente");
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node* p = new Node(data);
    if (p != nullptr) {
        Node* t = head;
        head = p;
        if (empty()) {
            p->next(p);
            p->prev(p);
        } else {
            p->prev(t->prev());
            t->prev()->next(p);
            p->next(t);
            t->prev(p);
        }
        size_++;
    } else {
        throw std::out_of_range("memória insuficiente");
    }
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return size() == 0;
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    Node* p = head;
    for (size_t i = 0; i < size_; i++) {
        if (p->data() == data) {
            return true;
        }
        p = p->next();
    }
    return false;
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (index < size_) {
        Node* p = head;
        for (size_t i = 0; i < index; i++) {
            p = p->next();
        }
        return p->data();
    }
    throw std::out_of_range("indice inexistente");
}

template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    if (index < size_) {
        Node* p = head;
        for (size_t i = 0; i < index; i++) {
            p = p->next();
        }
        return p->data();
    }
    throw std::out_of_range("indice inexistente");
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    Node* p = head;
    for (size_t i = 0; i < size_; i++) {
        if (p->data() == data) {
            return i;
        }
        p = p->next();
    }
    return size();
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    Node* p = head;
    while (p != nullptr && p->data() != data) {
        p = p->next();
    }
    if (p != nullptr) {
        if (p->prev() == nullptr) {
            pop_front();
        } else {
            Node* ant = p->prev();
            ant->next(p->next());
            if (p->next() != nullptr) {
                p->next()->prev(ant);
            }
            delete p;
            size_--;
        }
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty() || data <= head->data()) {
        push_front(data);
    } else if (data >= head->prev()->data()) {
        push_back(data);
    } else {
        Node* current = head;
        size_t index = 0;
        while (current->next() != head && data > current->data()) {
            current = current->next();
            index++;
        }
        insert(data, index);
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("Index invalido");
    }
    if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        Node* p = head;
        for (size_t i = 0; i < index; i++) {
                p = p->next();
        }
        Node* novo = new Node(data, p->prev(), p);
        if (novo != nullptr) {
            p->prev()->next(novo);
            p->prev(novo);
            size_++;
        } else {
            throw std::out_of_range("Sem espaço");
        }
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index invalido");
    }
    if (index == 0) {
        return pop_front();
    } else if (index == size_ - 1) {
        return pop_back();
    } else {
        Node* p = head;
        for (size_t i = 0; i < index; i++) {
            p = p->next();
        }
        T data = p->data();

        p->next()->prev(p->prev());
        p->prev()->next(p->next());

        delete p;
        size_--;
        return data;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    Node* saiu = head->prev();
    T data = saiu->data();
    if (size() == 1) {
        head = nullptr;
    } else {
        head->prev(saiu->prev());
        saiu->prev()->next(head);
    }
    delete saiu;
    size_--;
    return data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    Node* saiu = head;
    T volta = saiu->data();
    if (size() == 1) {
        head = nullptr;
    } else {
        head = head->next();
        head->prev(saiu->prev());
        saiu->prev()->next(head);
    }
    delete saiu;
    size_--;
    return volta;
}
