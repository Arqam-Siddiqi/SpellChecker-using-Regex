#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <QDebug>
using namespace std;

class SpellChecker
{
public:
    string reg_exp;
    string text;

    SpellChecker(string dict, string passage);
    vector<string> splitString(const string& str);
    vector<string> checkSpelling();
    bool compareStrings(string s1, string s2);

};

#endif // SPELLCHECKER_H
