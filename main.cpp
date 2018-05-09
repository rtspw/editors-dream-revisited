#include <iostream>
#include "node.h"
#include "avlbst.h"
#include "heap.h"
#include "reader.h"
using namespace std;

void readText(ifstream &fin, string &line);
bool getFileName(string &fileName);
bool checkIfFileExists(const string &filename);

int main() {
    string filename;
    try {
        if(getFileName(filename)) {
            cout << "opened " << filename << endl;
            reader textProcessor;
            textProcessor.setFilename(filename);
            textProcessor.process();
        }
    }
    catch (...) {
        cout << "Unknown error occured." << endl;
    }
    return 0;
}

bool getFileName(string &filename) {
    cout<<"Enter name of text file: " ;
    getline(cin, filename);
    while(checkIfFileExists(filename)) {
        if(filename == "") return false;
      cout<<"Invalid text file, try again: ";
      cin.clear();
      getline(cin,filename);
    }
    return true;
}

bool checkIfFileExists(const string &filename) {
    ifstream fin(filename.c_str());
    fin.close();
    return !fin.good();
}

//    avlBST aa;
//    heap bb;

//    aa.insert("apple",2,1,1);
//    aa.insert("app",1,3,1);
//    aa.insert("ape",4,1,1);
//    aa.insert("alice",5,1,1);
//    aa.insert("alchemy",1,1,1);
//    aa.insert("allen",1,1,1);
//    aa.insert("arson",155,1,1);
//    aa.insert("boy",1,1,1);
//    aa.insert("bee",1,1,1);
//    aa.insert("be",1,1,1);
//    aa.insert("ain't",1,1,1);
//    aa.insert("hi",1,1,1);
//    aa.insert("h",1,1,1);

//    // HEAP TEST
//    bb.insert("apple",1,1,1);
//    bb.insert("abba",1,1,1);
//    bb.insert("appl",1,1,1);
//    bb.insert("appla",1,1,1);
//    bb.insert("apricot",1,1,1);
//    bb.insert("alice",1,1,1);
//    bb.insert("a",1,1,1);
//    bb.insert("an",1,1,1);
//    bb.insert("answer",1,1,1);
//    bb.insert("babbple",1,1,1);
//    bb.insert("c",1,1,1);
//    bb.insert("d",1,1,1);

//    while(!bb.empty()) {
//        cout << bb.pop().word << endl;
//



