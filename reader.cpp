#include "reader.h"

/////////////////////////////////////////////////////////////////////
/// Initialization Functions

reader::reader() {
    wordCount = 0;
    syllableCount = 0;
    fleschScore = 0;
    paragraphIndex = 0;
}

reader::~reader() {
    deleteAll();
}

reader::reader(const reader &other) {
    copy(other);
}

reader &reader::operator=(const reader &other) {
    if(this != &other) {
        deleteAll();
        copy(other);
    }
    return *this;
}

/////////////////////////////////////////////////////////////////////
/// General Functions


void reader::setFilename(const std::string &str) {
    filename = str;
}

// Primary function to process text after the object is created
void reader::process() {
    std::ifstream fin(filename.c_str());
    std::string paragraph;
    while(!fin.eof()) {
        paragraph = getParagraph(fin);
        processParagraph(paragraph);
    }
    fin.close();
    std::cout << "Word Count : " << wordCount << std::endl;
    std::cout << "Syllable Count : " << syllableCount << std::endl;
}

// Returns a string containing a single paragraph of the text
std::string reader::getParagraph(std::ifstream &fin) {
    std::string output, line;
    while(getline(fin, line)) {
        if(line.empty()) break;
        else output += line + ' ';
    }

    if(output.length() != 0)
        output.erase(output.length() - 1);

    if(!output.empty())
        ++paragraphIndex;

    std::cout << " - - PARAGRAPH NUMBER " << paragraphIndex << std::endl;
    std::cout << "\t" << output << std::endl << std::endl;
    return output;
}

void reader::processParagraph(std::string &paragraph) {
    size_t lineCount = 1;
    std::string temp;
    std::stringstream ss(paragraph);
    while(ss >> temp) {

        // Removes non-alphabetical chars except ' and counts sentences
        for(size_t i = 0; i < temp.size(); ++i) {
            if((temp[i] == '.' || temp[i] == '!' || temp[i] == '?'))
                ++lineCount;
            if((isdigit(temp[i]) || ispunct(temp[i])) && temp[i] != '\'') {
                temp.erase(temp.begin() + i);
                --i;
            }
        }
        // Remove ending quotes after punctuations like "water?"
        if(temp[temp.size() - 1] == '\"' || temp[temp.size() - 1] == '\'')
            temp.pop_back();

        // Deletes words starting with quotes
        if(temp[0] == '\'' || temp[0] == '\"')
            temp.erase(temp.begin());

        // Capitalizes first char. before indexing
        temp[0] = toupper(temp[0]);

        if(isalpha(temp[0]))
            alphabetOrchardHeap[toupper(temp[0]) - 65].insert(temp, paragraphIndex, lineCount, 1);

        ++wordCount;
        countSyllable(temp);
    }

}

void reader::countSyllable(std::string input) {
    size_t tempCount = 0;
    size_t i = 0;

    // Ignores groups of vowels and consonants
    while (i < input.size()) {

        // Skips over non-vowels and ensures against buffer-overflow
        while(!isVowel(input[i]) && isValid(input[i]))
            ++i;

        // Does not do final increment if ends in consonants
        if(i >= input.size()) break;

        // Skips blocks of vowels before adding one
        while(isVowel(input[i])) ++i;

        ++tempCount;
    }

    // Ignores silent e at end (Most cases in English)
    if(input[input.size() - 1] == 'e' && tempCount != 1)
        --tempCount;

    syllableCount += tempCount;
}

bool reader::isVowel(char &ch) {
    char temp = tolower(ch);
    return temp == 'a' || temp == 'e' || temp == 'i' || temp == 'o' || temp == 'u' || temp == 'y';
}
bool reader::isValid(char &ch) {
    return (isalnum(ch) || ispunct(ch));
}

/////////////////////////////////////////////////////////////////////
/// Private Functions

void reader::copy(const reader &other) {
    wordCount = other.wordCount;
    syllableCount = other.syllableCount;
    fleschScore = other.fleschScore;
    paragraphIndex = other.paragraphIndex;
    filename = other.filename;
}
void reader::deleteAll() {
    wordCount = 0;
    syllableCount = 0;
    fleschScore = 0;
    paragraphIndex = 0;
    filename = std::string();
}
