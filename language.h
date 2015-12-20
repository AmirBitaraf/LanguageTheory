#ifndef LANGUAGE_H
#define LANGUAGE_H
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include "rule.h"

using namespace std;

class Language
{
public:
    Language();
    vector<Rule> rules;
    void addRule(Rule rule);
    void loadRules(istream & ss);
    void clearRules();
    void removeRule(int index);
    void removeLambdaProduction();
    void removeUnitProduction();
    void removeUselessVariables();
    void processLanguage();
    vector<Rule> setOfRules(string s);
    void convertCNF();
private:
    bool f(string var);
    map<string,bool> isOK;
    vector<string> checkup;
};

#endif // LANGUAGE_H
