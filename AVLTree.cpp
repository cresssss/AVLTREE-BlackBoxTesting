// AVLTree.cpp
#include "AVLTree.h"
#include <algorithm>

using namespace CustomDB;

AVL::AVL() : root(nullptr) {}

AVL::~AVL() {
    makeEmpty(root);
}

void AVL::makeEmpty(Node* t) {
    if (!t) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

int AVL::max(int a, int b) {
    return (a > b) ? a : b;
}

int AVL::height(Node* t) const {
    return t ? t->height : -1;
}

int AVL::getBalance(Node* t) const {
    return t ? height(t->left) - height(t->right) : 0;
}

Node* AVL::insert(EmployeeInfo empl, Node* t) {
    if (!t) {
        t = new Node{empl, nullptr, nullptr, 0};
    } else if (empl.sin < t->empl.sin) {
        t->left = insert(empl, t->left);
        if (height(t->left) - height(t->right) == 2) {
            if (empl.sin < t->left->empl.sin)
                t = singleRightRotate(t);
            else
                t = doubleRightRotate(t);
        }
    } else if (empl.sin > t->empl.sin) {
        t->right = insert(empl, t->right);
        if (height(t->right) - height(t->left) == 2) {
            if (empl.sin > t->right->empl.sin)
                t = singleLeftRotate(t);
            else
                t = doubleLeftRotate(t);
        }
    }
    t->height = max(height(t->left), height(t->right)) + 1;
    return t;
}

Node* AVL::singleRightRotate(Node*& t) {
    Node* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(u->left), t->height) + 1;
    return u;
}

Node* AVL::singleLeftRotate(Node*& t) {
    Node* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(u->right), t->height) + 1;
    return u;
}

Node* AVL::doubleLeftRotate(Node*& t) {
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}

Node* AVL::doubleRightRotate(Node*& t) {
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

Node* AVL::findMin(Node* t) {
    if (!t) return nullptr;
    return t->left ? findMin(t->left) : t;
}

Node* AVL::findMax(Node* t) {
    if (!t) return nullptr;
    return t->right ? findMax(t->right) : t;
}

Node* AVL::remove(int sin, Node* t) {
    if (!t) return nullptr;
    if (sin < t->empl.sin) {
        t->left = remove(sin, t->left);
    } else if (sin > t->empl.sin) {
        t->right = remove(sin, t->right);
    } else {
        if (t->left && t->right) {
            Node* temp = findMin(t->right);
            t->empl = temp->empl;
            t->right = remove(temp->empl.sin, t->right);
        } else {
            Node* temp = t;
            t = (t->left) ? t->left : t->right;
            delete temp;
        }
    }
    if (!t) return t;
    t->height = max(height(t->left), height(t->right)) + 1;
    if (height(t->left) - height(t->right) == 2) {
        if (height(t->left->left) >= height(t->left->right))
            return singleRightRotate(t);
        else
            return doubleRightRotate(t);
    } else if (height(t->right) - height(t->left) == 2) {
        if (height(t->right->right) >= height(t->right->left))
            return singleLeftRotate(t);
        else
            return doubleLeftRotate(t);
    }
    return t;
}

void AVL::insert(EmployeeInfo empl) {
    root = insert(empl, root);
}

void AVL::remove(int sin) {
    root = remove(sin, root);
}

Node* AVL::GetRoot() const {
    return root;
}

void AVL::display(std::ostream& os) const {
    inorder(root, os);
}

void AVL::inorder(Node* t, std::ostream& os) const {
    if (!t) return;
    inorder(t->left, os);
    os << " height:" << t->height
       << " sin:" << t->empl.sin
       << " employee number:" << t->empl.emplNumber
       << " salary:" << t->empl.salary
       << " age:" << t->empl.age << '\n';
    inorder(t->right, os);
}

Node* AVL::Find(Node* node, int sin) const {
    if (!node) return nullptr;
    if (sin < node->empl.sin) return Find(node->left, sin);
    else if (sin > node->empl.sin) return Find(node->right, sin);
    return node;
}

Node* AVL::Find(int sin) const {
    return Find(root, sin);
}
