#include "node.h"

std::ostream &operator<<(std::ostream &out, const node &n) {
    out << "("<< n.word << "|" << n.count << ")";
    return out;
}

bool operator==(const node &a, const node &b) {
    return a.word == b.word;
}

bool operator<(const node &a, const node &b) {
    return a.word < b.word;
}

bool operator>(const node &a, const node &b) {
    return a.word > b.word;
}

node &node::operator++() {
    ++count;
    return *this;
}
node node::operator++(int) {
    node temp = *this;
    ++*this;
    return temp;
}
node &node::operator--() {
    --count;
    return *this;
}
node node::operator--(int) {
    node temp = *this;
    --*this;
    return temp;
}
