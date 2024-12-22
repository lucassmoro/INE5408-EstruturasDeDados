// Copyright [2024] <Autor>

#include <algorithm>
#include "./array_list.h"


namespace structures {

template<typename T>
class AVLTree {
 public:
    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

 private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
            left = nullptr;
            right = nullptr;
            height_ = 0;
        }

        T data;
        Node* left;
        Node* right;
        int height_;

        ~Node() {
            delete left;
            delete right;
        }


        void updateHeight() {
            int left_height = (left == nullptr) ? -1 : left->height_;
            int right_height = (right == nullptr) ? -1 : right->height_;
            height_ = 1 + std::max(left_height, right_height);
        }

        Node* balance() {
            updateHeight();
            int bf = balanceFactor();


            if (bf > 1) {
                if (left != nullptr && left->balanceFactor() < 0) {
                    left = left->simpleLeft();
                }
                return simpleRight();
            }
            if (bf < -1) {
                if (right != nullptr && right->balanceFactor() > 0) {
                    right = right->simpleRight();
                }
                return simpleLeft();
            }

            return this;
        }

        int balanceFactor() const {
            int left_height = (left == nullptr) ? -1 : left->height_;
            int right_height = (right == nullptr) ? -1 : right->height_;
            return left_height - right_height;
        }

        Node* insert(const T& data_) {
            if (data_ < data) {
                if (left == nullptr) {
                    left = new Node(data_);
                } else {
                    left = left->insert(data_);
                }
            } else {
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right = right->insert(data_);
                }
            }
            return balance();
        }

        bool remove(Node*& p, const T& data) {
            Node* tmp;
            if (p == nullptr) {
                return false;
            } else if (data < p->data) {
                return remove(p->left, data);
            } else if (data > p->data) {
                return remove(p->right, data);
            } else {  // achamos o nó
                if (p->left != nullptr && p->right != nullptr) {
                tmp = p->right;
                while (tmp->left != nullptr) {
                    tmp = tmp->left;
                }
                p->data = tmp->data;
                return remove(p->right, tmp->data);
            } else {
                tmp = p;
                p = (p->left != nullptr) ? p->left : p->right;
                tmp->left = tmp->right = nullptr;
                delete tmp;
                return true;
            }
        }
    }
        bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ < data) {
                if (left != nullptr) {
                    return left->contains(data_);
                } else {
                    return false;
                }
            } else {  // data_ > data
                if (right != nullptr) {
                    return right->contains(data_);
                } else {
                    return false;
                }
            }
        }
        Node* simpleLeft() {
            Node* new_root = right;
            right = new_root->left;
            new_root->left = this;
            updateHeight();
            new_root->updateHeight();
            return new_root;
        }

        Node* simpleRight() {
            Node* new_root = left;
            left = new_root->right;
            new_root->right = this;
            updateHeight();
            new_root->updateHeight();
            return new_root;
        }

        Node* doubleLeft() {
            if (right != nullptr) {
                right = right->simpleRight();
            }
            return simpleLeft();
        }

        Node* doubleRight() {
            if (left != nullptr) {
                left = left->simpleLeft();
            }
            return simpleRight();
        }

        void pre_order(ArrayList<T>& v) const {
            // COLOQUE SEU CÓDIGO AQUI...
            v.push_back(data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            // COLOQUE SEU CÓDIGO AQUI...
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            // COLOQUE SEU CÓDIGO AQUI...
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }

        int height() {
            return height_;
        }
    };

    Node* root;
    std::size_t size_;
};

template<typename T>
AVLTree<T>::~AVLTree() {
    delete root;
}

template<typename T>
void AVLTree<T>::insert(const T& data) {
    if (root == nullptr) {
        root = new Node(data);
    } else {
        root = root->insert(data);
    }
    size_++;
}

template<typename T>
void AVLTree<T>::remove(const T& data) {
    if (root != nullptr && root->remove(root, data)) {
        size_--;
    }
}

template<typename T>
bool AVLTree<T>::contains(const T& data) const {
    return (root != nullptr) && root->contains(data);
}

template<typename T>
bool AVLTree<T>::empty() const {
    return root == nullptr;
}

template<typename T>
std::size_t AVLTree<T>::size() const {
    return size_;
}

template<typename T>
int structures::AVLTree<T>::height() const {
    return root->height();
}

template<typename T>
ArrayList<T> AVLTree<T>::pre_order() const {
    ArrayList<T> result;
    if (root != nullptr) {
        root->pre_order(result);
    }
    return result;
}

template<typename T>
ArrayList<T> AVLTree<T>::in_order() const {
    ArrayList<T> result;
    if (root != nullptr) {
        root->in_order(result);
    }
    return result;
}

template<typename T>
ArrayList<T> AVLTree<T>::post_order() const {
    ArrayList<T> result;
    if (root != nullptr) {
        root->post_order(result);
    }
    return result;
}

}  //  namespace structures

// -----


