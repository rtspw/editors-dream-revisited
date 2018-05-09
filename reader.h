#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>
#include "heap.h"

enum readerErrors {BAD_CALCULATION, INVALID_SCORE};

class reader {

public:

    reader();
    ~reader();
    reader(const reader &other);
    reader &operator=(const reader &other);

    void process();
    void setFilename(const std::string &str);
    std::string getParagraph(std::ifstream &fin);
    void processParagraph(std::string &paragraph);

    void countSyllable(std::string input);

private:

    std::string filename;
    size_t wordCount;
    size_t syllableCount;
    size_t sentenceCount;

    size_t fleschScore;
    size_t paragraphIndex;

    heap alphabetOrchardHeap[26];

    void copy(const reader &other);
    void deleteAll();

    bool isVowel(char &ch);
    bool isValid(char &ch);

    double getFleschScore();
    std::string translateScore(const double &score);

};

#endif // READER_H
