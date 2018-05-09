#ifndef AVLBST_H
#define AVLBST_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "node.h"

enum AVLBST_ERRORS {BST_EMPTY, BST_FULL, BST_NO_PARENT};

class avlBST {

public:

    avlBST();
    ~avlBST();
    avlBST(const avlBST &other);
    avlBST &operator=(const avlBST &other);

    bool empty() const;
    bool full() const;
    size_t size();

    void insert(const std::string &w, const size_t &pIdx, const size_t &lIdx, const size_t count = 1);
    node getMin();
    void clear();

private:

    std::vector<node> tree;
    std::vector<int> leftIdxs;
    std::vector<int> rightIdxs;
    std::vector<int> parentIdxs;

    void copy(const avlBST &other);
    void deleteAll();

    int getBigger(const int &x, const int &y);
    int getHeight(const int &indexOfNode);
    int getBalance(const int &indexOfNode);

    void insertRoot(node &temp);
    void insertLeft(node &temp, const int &index);
    void insertRight(node &temp, const int &index);

    void rotateRight(int index);
    void rotateLeft(int index);

    void rebalance();
};

#endif // AVLBST_H
