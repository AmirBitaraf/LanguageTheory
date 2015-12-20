#ifndef RULE_H
#define RULE_H
#include <string>
#include <vector>
#include "ruleexception.h"
#include "Constants.h"

using namespace std;

class Rule
{
private:
    void init(string lhs,string rhs);
public:
    string lhs;
    vector<string> rhs;
    Rule(string rule);
    Rule(string lhs,string rhs);
    Rule(string lhs,vector<string> rhs);
    string getLeft();
    vector<string> getRight();
    string getRightText();
    QString getFormatted();
    bool isLambdaProduction();
    bool operator ==(Rule r);
};

#endif // RULE_H
