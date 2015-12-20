#include "rule.h"
#include <QTextCodec>

void Rule::init(string lhs, string rhs)
{
    if(rhs.empty())
    {
        throw RuleException("Invalid Rule: No Right-Side Value!");
    }
    int cnt = 0;
    for(int i = 0;i < lhs.size();i++)
    {
        if(!isupper(lhs[i]) && !isdigit(lhs[i])) throw RuleException("Invalid Rule: Terminal at Left-Side!");
        cnt += isupper(lhs[i]);
    }
    if(cnt != 1){
        throw RuleException("Invalid Rule: Context-Free Grammars have only one Left-Side Variable");
    }
    this->lhs = lhs;
    for(int i = 0;i < rhs.size();i++)
    {
        int j = i;
        string s = "";
        s += rhs[j++];
        while(j < rhs.size() && !isalpha(rhs[j]) && rhs[j] != '~') s += rhs[j++];
        this->rhs.push_back(s);
        i=j-1;
    }
}


Rule::Rule(string rule)
{
    string k="",v="";
    int flag = false;
    for(int j = 0; j < rule.size();j++)
    {
        if(!isalnum(rule[j]) && rule[j] != '~') flag=true;
        else if(flag) v+= rule[j];
        else k+= rule[j];
    }
    this->init(k,v);
}

Rule::Rule(string k,string v)
{
    this->init(k,v);
}

string Rule::getLeft()
{
    return this->lhs;
}

vector<string> Rule::getRight()
{
    return rhs;
}

QString subs(string & s)
{
    QString ret = "";
    for(int i = 0;i < s.size();i++)
    {
        if(isdigit(s[i])) ret += "<sub>"+QString::number(s[i]-'0')+"</sub>";
        else ret += QString(s[i]);
    }
    return ret;
}

QString Rule::getFormatted()
{
    QString ret = subs(this->lhs);
    ret += " -> ";
    for(int i = 0;i < this->rhs.size();i++)
    {
        ret += subs(this->rhs[i]);
    }
    return ret.replace('~',"&lambda;");
}


