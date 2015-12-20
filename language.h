#ifndef LANGUAGE_H
#define LANGUAGE_H
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include "rule.h"
#include <QStandardItemModel>;
#include <QLabel>
#include <QStandardItem>
#include <QTreeView>

using namespace std;

class Language
{
public:
    Language();
    vector<Rule> rules;
    bool *** P;
    map<int,string> IND;
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
    void performCYK(string s);
    void performESP(string s,QStandardItemModel * model);
    QString beautify(QString rule)
    {
        QString ret = "";
        for(int i = 0;i < rule.size();i++)
        {
            if(rule[i].isDigit()) ret += "<sub>"+rule[i]+"</sub>";
            else ret += QString(rule[i]);
        }
        return ret;
    }
    QTreeView * tree;
    int flag;

private:
    bool f(string var);
    map<string,bool> isOK;
    vector<string> checkup;
    int backtrack(vector<string> & str,QStandardItem * item);
    vector<string> S;
    string String;
};

#endif // LANGUAGE_H
