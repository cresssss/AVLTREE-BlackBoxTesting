
// AVLTree.h
#pragma once
#include <iostream>

namespace CustomDB {

    struct EmployeeInfo {
        int salary;
        int age;
        int emplNumber;
        int sin; // search by social insurance number
    };

    struct Node {
        EmployeeInfo empl;
        Node* left;
        Node* right;
        int height;
    };

    class AVL {
        Node* root;

        void makeEmpty(Node* t);
        int max(int a, int b);
        Node* insert(EmployeeInfo empl, Node* t);
        Node* remove(int sin, Node* t);
        Node* singleRightRotate(Node*& t);
        Node* singleLeftRotate(Node*& t);
        Node* doubleLeftRotate(Node*& t);
        Node* doubleRightRotate(Node*& t);
        Node* findMin(Node* t);
        Node* findMax(Node* t);
        int height(Node* t) const;
        int getBalance(Node* t) const;
        void inorder(Node* t, std::ostream& os) const;
        Node* Find(Node* node, int sin) const;

    public:
        AVL();
        ~AVL();
        void insert(EmployeeInfo empl);
        void remove(int sin);
        void display(std::ostream& os = std::cout) const;
        Node* GetRoot() const;
        Node* Find(int sin) const;
    };

} // namespace CustomDB
