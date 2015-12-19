#ifndef LANGUAGE_H
#define LANGUAGE_H
#include <vector>
#include <iostream>
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
};

#endif // LANGUAGE_H
