#include "heap.h"

/////////////////////////////////////////////////////////////////////
/// Initialization Functions

heap::heap() {
    tree.push_back(node());
}
heap::~heap() {
    deleteAll();
}
heap::heap(const heap &other) {
    copy(other);
}
heap &heap::operator=(const heap &other) {
    if(this != &other) {
        deleteAll();
        copy(other);
    }
    return *this;
}

/////////////////////////////////////////////////////////////////////
/// General Functions

bool heap::empty() const {
    return tree.size() <= 1;
}

size_t heap::size() const {
    return tree.size() - 1;
}
const std::string heap::peek() const {
    if(empty()) throw EMPTY_HEAP;
    return tree[1].word;
}

/* Generates a node based off parameters, then inserts into heap and heapifies up */
void heap::insert(const std::string &w, const size_t &pIdx, const size_t &lIdx, const size_t &count) {

    // Puts node at end of heap vector
    tree.push_back(node(w, pIdx, lIdx, count));

    // Ignores heapify process it first insert
    if(tree.size() != 2)
        heapify();
    /////// ******** DEBUG OUTPUT  use https://www.cs.usfca.edu/~galles/visualization/Heap.html
//    for(int i = 0; i < tree.size(); ++i) {
//        std::cout << "(" << tree[i].word << ")";
//    }
//    std::cout << std::endl;
}

/* Removes and returns minimum node and heapifies down */
node heap::pop() {

    if(empty()) throw EMPTY_HEAP;

    node temp = tree[1];
    if(tree.size() != 2)
        tree[1] = tree[tree.size() - 1];
    tree.pop_back();

    heapifyDown();

    /////// ******** DEBUG OUTPUT  use https://www.cs.usfca.edu/~galles/visualization/Heap.html
//    for(int i = 0; i < tree.size(); ++i) {
//        std::cout << "(" << tree[i].word << ")";
//    }
//    std::cout << std::endl;

    return temp;
}

/////////////////////////////////////////////////////////////////////
/// Private Functions

void heap::clear() {
    deleteAll();
}

void heap::copy(const heap &other) {
    tree = other.tree;
}
void heap::deleteAll() {
    tree.clear();
}

/* Simple function to swap two node values on the heap */
void heap::swap(const size_t &x, const size_t &y) {
    node temp = tree[x];
    tree[x] = tree[y];
    tree[y] = temp;
}

/* Starting from the last inserted node, swaps the smaller value up the tree */
void heap::heapify() {
    size_t idx = tree.size() - 1;
    size_t parent;

    // Swaps value with parent if smaller up tree until not possible
    do {
        parent = idx / 2;
        if(tree[idx] < tree[parent])
            swap(idx, parent);
        idx = parent;
    } while(parent != 1);
}

/* Compares root value with children and moves node downwards */
void heap::heapifyDown() {
    size_t idx = 1;
    size_t leftIdx = idx * 2;
    size_t rightIdx;
    size_t nextNodeIndex;

    // Starts from root and swaps with the smaller of the children while possible
    while(leftIdx < tree.size()) {

        rightIdx = leftIdx + 1;

        // Gets index of next comparison, and the smaller of the children if both exist
        nextNodeIndex = (rightIdx < tree.size()) ? getSmaller(leftIdx, rightIdx) : leftIdx;
        if(tree[idx] > tree[nextNodeIndex])
            swap(idx, nextNodeIndex);
        idx = nextNodeIndex;
        leftIdx = idx * 2;
    }
}

/* Simple helper to get the index of the smaller of two nodes */
size_t heap::getSmaller(const size_t &x, const size_t &y) {
    return (tree[x] < tree[y]) ? x : y;
}
