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
    string lhs;
    vector<string> rhs;
    void init(string & lhs,string & rhs);
public:
    Rule(string & rule);
    Rule(string & lhs,string & rhs);
    string getLeft();
    vector<string> getRight();
    QString getFormatted();
};

#endif // RULE_H
