#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <cstdlib>
#include "AVLTree.h"
#include "timer.h"
#include <new>
#include <random>

using namespace std;
using namespace CustomDB;

const int TEST_SIZE = 100000;

EmployeeInfo createEmployee(int id) {
    EmployeeInfo e;
    e.emplNumber = id;
    e.salary = 50000 + (id * 23) % 40000;
    e.age = 20 + (id * 7) % 45;
    e.sin = 100000000 + id;
    return e;
}

vector<int> getShuffledIndices(int size) {
    vector<int> indices(size);
    for (int i = 0; i < size; ++i)
        indices[i] = i;

    // Custom Fisher–Yates shuffle
    for (int i = size - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(indices[i], indices[j]);
    }

    return indices;
}



void testCorrectnessInsertionAVL() {
    cout << "[AVL] Test 1: Correctness of Insertion" << endl;
    AVL tree;
    tree.insert(createEmployee(10));
    tree.insert(createEmployee(5));
    tree.insert(createEmployee(15));
    tree.display();
    cout << "\nExpected: Sins in order - 100000005, 100000010, 100000015\n\n";
}

void testCorrectnessDeletionAVL() {
    cout << "[AVL] Test 2: Correctness of Deletion" << endl;
    AVL tree;
    tree.insert(createEmployee(10));
    tree.insert(createEmployee(5));
    tree.insert(createEmployee(15));
    tree.remove(100000005);
    tree.display();
    cout << "\nExpected: Sins in order - 100000010, 100000015\n\n";
}

void testMaxSizeAVL() {
    cout << "[AVL] Test 3: Max Size" << endl;
    AVL tree;
    try {
        int i = 0;
        for (; i < INT32_MAX; ++i) {
            tree.insert(createEmployee(i));
            if (i % 100000 == 0) cout << "." << flush;
        }
    } catch (bad_alloc&) {
        cout << "\nReached memory limit after inserting nodes.\n";
    }
}

void testLoadAVL() {
    cout << "[AVL] Test 4: Load Test (Insertion x " << TEST_SIZE << ")" << endl;
    AVL tree;
    Timer timer;
    timer.start();
    for (int i = 0; i < TEST_SIZE; ++i)
        tree.insert(createEmployee(i));
    timer.stop();
    cout << "Elapsed Time: " << timer.currtime() << " seconds\n\n";
}

void testSpeedWorstCaseSearchAVL() {
    cout << "[AVL] Test 6: Worst Case Search" << endl;
    AVL tree;
    for (int i = 0; i < TEST_SIZE; ++i)
        tree.insert(createEmployee(i));
    Timer timer;
    timer.start();
    Node* result = tree.Find(100000000 + TEST_SIZE - 1);
    timer.stop();
    cout << "Searched for SIN: " << (100000000 + TEST_SIZE - 1) << ", Found: " << (result != nullptr) << endl;
    cout << "Elapsed Time: " << timer.currtime() << " seconds\n\n";
}

// std::map equivalents
void testLoadStdMap() {
    cout << "[std::map] Test 4: Load Test (Insertion x " << TEST_SIZE << ")" << endl;
    map<int, EmployeeInfo> db;
    Timer timer;
    timer.start();
    for (int i = 0; i < TEST_SIZE; ++i) {
        auto e = createEmployee(i);
        db[e.sin] = e;
    }
    timer.stop();
    cout << "Elapsed Time: " << timer.currtime() << " seconds\n\n";
}

void testSpeedWorstCaseSearchStdMap() {
    cout << "[std::map] Test 6: Worst Case Search" << endl;
    map<int, EmployeeInfo> db;
    for (int i = 0; i < TEST_SIZE; ++i) {
        auto e = createEmployee(i);
        db[e.sin] = e;
    }
    Timer timer;
    timer.start();
    auto it = db.find(100000000 + TEST_SIZE - 1);
    timer.stop();
    cout << "Searched for SIN: " << (100000000 + TEST_SIZE - 1) << ", Found: " << (it != db.end()) << endl;
    cout << "Elapsed Time: " << timer.currtime() << " seconds\n\n";
}

int main() {
    testCorrectnessInsertionAVL();
    system("pause");

    testCorrectnessDeletionAVL();
    system("pause");

    // testMaxSizeAVL(); // Uncomment if you want to test max size (can crash)
    // system("pause");

    testLoadStdMap();
    testSpeedWorstCaseSearchStdMap();
    system("pause");

    testLoadAVL();
    testSpeedWorstCaseSearchAVL();
    system("pause");

    cout << "All tests done.\n";
    return 0;
}