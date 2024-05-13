#include "SpellChecker.h"

SpellChecker::SpellChecker(string dict, string passage) {

    std::istringstream ss(dict);
    std::string token;

    while (std::getline(ss, token)) {
        reg_exp += token + "('s)?" + "(s)?" + "[.?!,]?" + "|";
    }

    if(!reg_exp.empty()){
        reg_exp.pop_back();
    }

    text = passage;

}

vector<string> SpellChecker::splitString(const string& str) {

    vector<string> tokens;
    istringstream iss(str);
    string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

bool SpellChecker::compareStrings(string s1, string s2){

    for(char& c : s1)
        c = tolower(c);

    for(char& c : s2)
        c = tolower(c);

    if(s1 == s2){
        return true;
    }

    return false;
}

vector<string> SpellChecker::checkSpelling() {

    vector<string> misspellings;
    vector<string> words = splitString(text);

    qDebug() << "The Regular Expression for this Dictionary is:\n" << reg_exp << "\n\n";
    for(string word : words){

        bool flag = false;
        string check;
        bool openRoundBracket = false;   // tells us if "(" has been previously spotted.
        bool openSquareBracket = false;  // tells us if "[" has been previously spotted.
        bool keepPushing = true;    // decides whether we keep pushing characters into string check.

        int prev;

        for(int i = 0; i<reg_exp.size(); i++){

            if(reg_exp[i] == '|'){    // if a new word in the reg_exp is being searched, clear the check buffer and give permission to push.
                check.clear();
                keepPushing = true;
                i++;
            }

            if(!isalpha(reg_exp[i])){     // if a non-alphabetic character is found, deny permission to push.
                keepPushing = false;
            }

            if(reg_exp[i] == '('){
                if(compareStrings(check, word)){
                    flag = true;
                    break;
                }
                openRoundBracket = true;
                prev = i;   // store index of '('
            }
            else if(reg_exp[i] == ')' && openRoundBracket && reg_exp[i+1] == '?'){
                openRoundBracket = false;
                string str = reg_exp.substr(prev+1, i-prev-1);    // extract the string between '(' and ')'

                if(compareStrings(check + str, word)){
                    flag = true;
                    break;
                }
            }
            else if(reg_exp[i] == '['){
                if(compareStrings(check, word)){
                    flag = true;
                    break;
                }
                openSquareBracket = true;
                prev = i;   // store index of '['
            }
            else if(reg_exp[i] == ']' && openSquareBracket && reg_exp[i+1] == '?'){
                openSquareBracket = false;
                string str = reg_exp.substr(prev+1, i-prev-1);    // extract the string between '[' and ']'

                // check each character inside the extracted string and append it to check for comparision
                for(int j = 0; j<str.length(); j++){
                    if(compareStrings(check + str[j], word)){
                        flag = true;
                        break;
                    }
                }

            }

            if(keepPushing){    // if permission to push, then push characters into check
                check.push_back(reg_exp[i]);
            }

        }


        if(!flag){     // if word is found to be incorrect, push it into the misspellings list
            misspellings.push_back(word);
        }

    }

    return misspellings;
}
