#ifndef NODE_H
#define NODE_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct node {
    std::string word;
    size_t count;
    int balance;
    int height;
    std::vector<size_t> paragraphIndex;
    std::vector<size_t> lineIndex;

    node(const std::string &w = std::string(), const size_t &pIdx = 0, const size_t &lIdx = 0, size_t c = 1) {
        word = w;
        count = c;
        height = 0;
        paragraphIndex.push_back(pIdx);
        lineIndex.push_back(lIdx);
    }
    ~node() {
        word = std::string();
        count = 0;
        height = 0;
        paragraphIndex.clear();
        lineIndex.clear();
    }
    node(const node &other) {
        word = other.word;
        count = other.count;
        height = other.height;
        paragraphIndex = other.paragraphIndex;
        lineIndex = other.lineIndex;
    }
    node &operator=(const node &other) {
        if(this != &other) {
            word = other.word;
            count = other.count;
            height = other.height;
            paragraphIndex = other.paragraphIndex;
            lineIndex = other.lineIndex;
        }
        return *this;
    }

    friend
    std::ostream &operator<<(std::ostream &out, const node &n);
    friend
    std::istream &operator>>(std::istream &in, node *&n);
    friend
    bool operator==(const node &a, const node &b);
    friend
    bool operator<(const node &a, const node &b);
    friend
    bool operator>(const node &a, const node &b);

    node &operator++();
    node operator++(int);
    node &operator--();
    node operator--(int);
};



#endif // NODE_H


