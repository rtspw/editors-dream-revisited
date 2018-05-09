#ifndef HEAP_H
#define HEAP_H
#include <cstdlib>
#include <vector>
#include <string>
#include "node.h"

enum HEAP_ERRORS {EMPTY_HEAP};
class heap {

public:

    heap();
    ~heap();
    heap(const heap &other);
    heap &operator=(const heap &other);

    bool empty() const;
    size_t size() const;
    const std::string peek() const;

    void insert(const std::string &w, const size_t &pIdx, const size_t &lIdx, const size_t &count = 1);
    node pop();
    void clear();

private:

    std::vector<node> tree;

    void copy(const heap &other);
    void deleteAll();
    void swap(const size_t &x, const size_t &y);
    void heapify();
    void heapifyDown();
    size_t getSmaller(const size_t &x, const size_t &y);

};

#endif // HEAP_H
