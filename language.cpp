#include "language.h"

Language::Language()
{

}

void Language::addRule(Rule rule)
{
    this->rules.push_back(rule);
}

void Language::loadRules(istream &ss)
{
    string rule;
    while(getline(ss,rule) && rule[0])
        this->addRule(Rule(rule));
}

void Language::clearRules()
{
    this->rules.clear();
}

void Language::removeRule(int index)
{
    this->rules.erase(rules.begin()+index);
}
