#include "avlbst.h"

/////////////////////////////////////////////////////////////////////
/// Initialization Functions

avlBST::avlBST() {}

avlBST::~avlBST() {
    deleteAll();
}

avlBST::avlBST(const avlBST &other) {
    copy(other);
}

avlBST &avlBST::operator=(const avlBST &other) {
    if(this != &other) {
        deleteAll();
        copy(other);
    }
    return *this;
}

/////////////////////////////////////////////////////////////////////
/// General Functions

bool avlBST::empty() const {
    return !tree.size();
}

size_t avlBST::size() {
    return tree.size();
}

 // Concerns : vector.push_back creates copy
void avlBST::insert(const std::string &w, const size_t &pIdx, const size_t &lIdx, const size_t count) {
    node temp(w, pIdx, lIdx, count);
    if(empty()) {
        insertRoot(temp);
    }
    else {
        bool notBreak = true;
        int index = 0;

        /* Iterates down the tree, along with changing the balance of the nodes accordingly */
        while(notBreak) {

            /* Case 1: Add to word count if character already exists
             * Also ignores balance value changes as no new nodes are added */
            if(temp.word == tree[index].word) {
                ++tree[index];
                tree[index].paragraphIndex.push_back(pIdx);
                tree[index].lineIndex.push_back(lIdx);
                notBreak = false;
            }

            /* Case 2: Makes left children, which goes down until there is a -1 index */
            else if(temp.word < tree[index].word) {
                if(leftIdxs[index] == -1) {
                    insertLeft(temp, index);
                    notBreak = false;
                }
                    index = leftIdxs[index];
            }

            /* Case 3: Opposite of case 2 */
            else {
                if(rightIdxs[index] == -1) {
                    insertRight(temp, index);
                    notBreak = false;
                }
                    index = rightIdxs[index];
            }
         }

        /* Starts from added node and modifies height values up to the root */
        while(index != -1) {
            tree[index].height = 1 + getBigger(getHeight(leftIdxs[index]), getHeight(rightIdxs[index]));
            index = parentIdxs[index];
        }

        /* Uses last entered node and finds and fixes imbalances */
        rebalance();
    }


    for(size_t i = 0; i < tree.size(); ++i) {
        std::cout << i << "| (" << tree[i].word << "," << tree[i].count << ")\t";
        std::cout << leftIdxs[i] << "\t";
        std::cout << rightIdxs[i] << "\t";
        std::cout << parentIdxs[i];
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;

}

node getMin() {

}

void avlBST::insertRoot(node &temp) {
    tree.push_back(temp);
    leftIdxs.push_back(-1);
    rightIdxs.push_back(-1);
    parentIdxs.push_back(-1);
}

void avlBST::insertLeft(node &temp, const int &index) {
    leftIdxs[index] = (tree.size()); // size refers to index of the inserted node
    leftIdxs.push_back(-1);
    rightIdxs.push_back(-1);
    parentIdxs.push_back(index);
    tree.push_back(temp);
}

void avlBST::insertRight(node &temp, const int &index) {
    rightIdxs[index] = (tree.size());
    leftIdxs.push_back(-1);
    rightIdxs.push_back(-1);
    parentIdxs.push_back(index);
    tree.push_back(temp);
}

/* When an imbalance is found, the subtree is rotated based on four cases */
void avlBST::rebalance() {
    int risingIndex = tree.size() - 1;
    do {
        risingIndex = parentIdxs[risingIndex];
        int balanceOfNode = getBalance(risingIndex);
        if(balanceOfNode <= -2 && getBalance(leftIdxs[risingIndex]) == -1) {
            rotateRight(risingIndex);
        }
        else if(balanceOfNode <= -2 && getBalance(leftIdxs[risingIndex]) == 1) {
            rotateLeft(leftIdxs[risingIndex]);
            rotateRight(risingIndex);
        }
        else if(balanceOfNode >= 2 && getBalance(rightIdxs[risingIndex]) == -1) {
            rotateRight(rightIdxs[risingIndex]);
            rotateLeft(risingIndex);

        }
        else if(balanceOfNode >= 2 && getBalance(rightIdxs[risingIndex]) == 1) {
            rotateLeft(risingIndex);
        }
    } while(parentIdxs[risingIndex] != -1);
}

/* rotateRight's variables:
 *      y       x
 *     /      /  \
 *    x   -> a   y
 *   / \        /
 *  a  b       b
 */
void avlBST::rotateRight(int index) {

    // Updates nodes above pivot if exists
    if(parentIdxs[index] != -1) {
        if(leftIdxs[parentIdxs[index]] == index)
            leftIdxs[parentIdxs[index]] = leftIdxs[index];
        else
            rightIdxs[parentIdxs[index]] = leftIdxs[index];
    }

    // Stores index of b before other indexes are modified
    int bIdx = rightIdxs[leftIdxs[index]];

    // Sets parent of x as parent of y
    parentIdxs[leftIdxs[index]] = parentIdxs[index];
    // Sets parent of y as x
    parentIdxs[index] = leftIdxs[index];
    // Sets right child of x as y
    rightIdxs[leftIdxs[index]] = index;

    // If b exists, sets parent of b as y
    if(bIdx != -1) {
        parentIdxs[bIdx] = index;
        leftIdxs[index] = bIdx;
    }
    else
        leftIdxs[index] = -1;

    /* Starts from added node and modifies height values up to the root */
    while(index != -1) {
        tree[index].height = 1 + getBigger(getHeight(leftIdxs[index]), getHeight(rightIdxs[index]));
        index = parentIdxs[index];
    }
}

/* rotateLeft's variables:
 *      y         x
 *      \        /\
 *      x   ->  y  a
 *     /\       \
 *    b a        b
 */
void avlBST::rotateLeft(int index) {

    // Stores index of b before other indexes are modified
    int bIdx = leftIdxs[rightIdxs[index]];

    // Updates nodes above pivot if exists
    if(parentIdxs[index] != -1) {
        if(leftIdxs[parentIdxs[index]] == index)
            leftIdxs[parentIdxs[index]] = rightIdxs[index];
        else
            rightIdxs[parentIdxs[index]] = rightIdxs[index];
    }

    // Sets parent of x as parent of y
    parentIdxs[rightIdxs[index]] = parentIdxs[index];
    // Sets parent of y as x
    parentIdxs[index] = rightIdxs[index];
    // Sets left child of x as y
    leftIdxs[rightIdxs[index]] = index;


    // If b exists, sets parent of b as y
    if(bIdx != -1) {
        parentIdxs[bIdx] = index;
        rightIdxs[index] = bIdx;
    }
    else
        rightIdxs[index] = -1;

    /* Starts from added node and modifies height values up to the root */
    while(index != -1) {
        tree[index].height = 1 + getBigger(getHeight(leftIdxs[index]), getHeight(rightIdxs[index]));
        index = parentIdxs[index];
    }
}

void avlBST::clear() {
    deleteAll();
}


// Gets the larger of two numbers
int avlBST::getBigger(const int &x, const int &y) {
    return (x > y) ? x : y;
}

// Get height insures we can get the height even when the node does not exist
int avlBST::getHeight(const int &indexOfNode) {
    return (indexOfNode == -1) ? 0 : tree[indexOfNode].height;
}

// Calculates balance factor of node
int avlBST::getBalance(const int &indexOfNode) {
    return (indexOfNode == -1) ? 0 : getHeight(rightIdxs[indexOfNode])  - getHeight(leftIdxs[indexOfNode]);
}

void avlBST::copy(const avlBST &other) {
    tree = other.tree;
    leftIdxs = other.leftIdxs;
    rightIdxs = other.rightIdxs;
    parentIdxs = other.parentIdxs;
}

void avlBST::deleteAll() {
    tree.clear();
    leftIdxs.clear();
    rightIdxs.clear();
    parentIdxs.clear();
}
