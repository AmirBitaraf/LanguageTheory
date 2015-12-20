#include "language.h"
#include <QDebug>

Language::Language()
{

}

void Language::addRule(Rule rule)
{
    qDebug() << rule.lhs.c_str() << rule.getRightText().c_str();
    for(int i = 0;i < rules.size();i++)
        if(rule == rules[i])
            return;
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

void Language::processLanguage()
{
    this->removeLambdaProduction();
    this->removeUnitProduction();
    this->removeUselessVariables();
}


bool isIn(vector<string> & V,string s)
{
    for(int j = 0;j < V.size();j++)
        if(V[j]==s)
            return true;
    return false;
}


void Language::removeLambdaProduction()
{
    vector<string> Vn;
    for(int i = 0;i < rules.size();i++)
        if(rules[i].isLambdaProduction()){
            if(!isIn(Vn,rules[i].getLeft()))
                Vn.push_back(rules[i].getLeft());
            rules.erase(rules.begin()+i);
            i--;
        }
    bool flag = true;
    while(flag)
    {
        flag = false;
        for(int i = 0;i < rules.size();i++)
        {
            bool isNullable = true;
            for(int j = 0;j < rules[i].rhs.size();j++)
            {
                if(!isIn(Vn,rules[i].rhs[j])) isNullable=false;
            }
            if(isNullable)
            {
                if(!isIn(Vn,rules[i].getLeft()))
                    Vn.push_back(rules[i].getLeft());
                rules.erase(rules.begin()+i);
                i--;
                flag=true;
            }
        }
    }

    vector<Rule> newRules;
    for(int i = 0;i < rules.size();i++)
    {
        int count = 0;
        for(int j = 0;j < rules[i].rhs.size();j++)
        {
            if(isIn(Vn,rules[i].rhs[j]))
                count++;
        }
        for(int mask = 0;mask < (1<<count);mask++)
        {
            vector<string> newrhs;
            int k = 0;
            for(int j = 0;j < rules[i].rhs.size();j++)
            {
                if(isIn(Vn,rules[i].rhs[j]))
                {
                    if(mask & (1<<k))
                        newrhs.push_back(rules[i].rhs[j]);
                    k++;
                }
                else newrhs.push_back(rules[i].rhs[j]);
            }
            if(newrhs.size())
            {
                newRules.push_back(Rule(rules[i].lhs,newrhs));
            }
        }
    }

    for(int i = 0;i < newRules.size();i++)
    {
        this->addRule(newRules[i]);
    }
}

vector<Rule> Language::setOfRules(string s)
{
    vector<Rule> ret;
    for(int i = 0;i < rules.size();i++)
        if(rules[i].lhs == s)
            ret.push_back(rules[i]);
    return ret;
}


#define PSS pair<string,string>

vector<PSS> processUnits(vector<PSS> V)
{
    bool flag = true;
    set<PSS> S(V.begin(),V.end());
    while(flag)
    {
        int sz = S.size();
        for(int i = 0;i < V.size();i++)
        {
            for(int j = 0;j < V.size();j++)
            {
                if(i==j) continue;
                if(V[i].second==V[j].first && V[i].first != V[j].second)
                {
                    S.insert(PSS(V[i].first,V[j].second));
                }
            }
        }
        flag = (sz != S.size());
    }
    return vector<PSS>(S.begin(),S.end());
}

void Language::removeUnitProduction()
{
    vector<Rule> newRules;
    vector<PSS> V;
    for(int i = 0;i < rules.size();i++)
    {
        if(rules[i].rhs.size() == 1 && isupper(rules[i].rhs[0][0]))
            V.push_back(PSS(rules[i].lhs,rules[i].rhs[0]));
        else
            newRules.push_back(rules[i]);
    }
    V = processUnits(V);
    this->rules.clear();
    for(int i = 0;i < newRules.size();i++)
        this->addRule(newRules[i]);
    for(int i = 0;i < V.size();i++)
    {
        vector<Rule> SV = this->setOfRules(V[i].second);
        for(int j = 0;j < SV.size();j++)
        {
            this->addRule(Rule(V[i].first,SV[j].rhs));
        }
    }
}

bool Language::f(string var)
{
    if(isOK.find(var) != isOK.end()) return isOK[var];
    bool res = false;
    for(int i = 0;i < rules.size();i++)
    {
        if(rules[i].lhs == var)
        {
            vector<string> vars;
            bool flag = true;
            for(int j = 0;j < checkup.size();j++)
            {
                if(rules[i].getRightText().find(checkup[j]) != string::npos)
                {
                    flag = false;
                    break;
                }
            }
            if(!flag) continue;

            bool isOnlyTerminal = true;
            for(int j = 0;j < rules[i].rhs.size();j++){
                if(isupper(rules[i].rhs[j][0])){
                    isOnlyTerminal = false;
                    vars.push_back(rules[i].rhs[j]);
                }
            }
            if(isOnlyTerminal) return isOK[var]=true;
            checkup.push_back(var);

            bool ans = true;
            for(int j = 0;j < vars.size();j++)
            {
                ans = f(vars[j]) && ans;
            }
            res = res || ans;
            checkup.pop_back();
        }
    }
    return isOK[var]=res;
}

void Language::removeUselessVariables()
{
    isOK.clear();
    checkup.clear();
    f("S");
    for(int i = 0;i < rules.size();i++)
    {
        if(!isOK[rules[i].lhs])
        {
            qDebug() << rules[i].lhs.c_str();
            rules.erase(rules.begin()+i);
            i--;
        }
    }
}

void Language::convertCNF()
{
    for(int i = 0;i < rules.size();i++)
    {
        if(rules[i].lhs == "S") rules[i].lhs = "S0";
        for(int j = 0;j < rules[i].rhs.size();j++)
            if(rules[i].rhs[j]=="S") rules[i].rhs[j]="S0";
    }
    this->addRule(Rule("S","S0"));
    vector<Rule> newRules;
    for(int i = 0;i < rules.size();i++)
    {
        for(int j = 0;j < rules[i].rhs.size();j++)
        {
            if(rules[i].rhs[j].size()==1 && islower(rules[i].rhs[j][0]))
            {
                string lh = ("T"+QString::number(rules[i].rhs[j][0]-'a')).toStdString();
                newRules.push_back(Rule(lh,QString(rules[i].rhs[j][0]).toStdString()));
                rules[i].rhs[j] = lh;
            }
        }
    }
    for(int i = 0,rind = 0;i < rules.size();i++,rind++)
    {
        if(rules[i].rhs.size()>2)
        {
            int sz = rules[i].rhs.size();
            for(int j = 0;j < sz-2;j++)
            {
                vector<string> rh;
                string vname = ("V"+QString::number(rind)+QString::number(j)).toStdString();
                rh.push_back(rules[i].rhs[j]);
                rh.push_back(vname);
                if(j==0){
                    newRules.push_back(Rule(rules[i].lhs,rh));
                }
                else
                {
                    string cname = ("V"+QString::number(rind)+QString::number(j-1)).toStdString();
                    newRules.push_back(Rule(cname,rh));
                }
            }
            vector<string> rh;
            rh.push_back(rules[i].rhs[sz-2]);
            rh.push_back(rules[i].rhs[sz-1]);
            string cname = ("V"+QString::number(rind)+QString::number(sz-3)).toStdString();
            newRules.push_back(Rule(cname,rh));
            rules.erase(rules.begin()+i);
            i--;
        }
    }
    for(int i = 0;i < newRules.size();i++)
        this->addRule(newRules[i]);
    this->removeUnitProduction();
    this->removeUselessVariables();
}


bool *** alloc3d(int x,int y,int z)
{
    x+=10;
    y+=10;
    z+=10;
    bool *** arr;
    arr = new bool**[x];
    for(int i = 0; i < x; i++)
    {
    arr[i] = new bool*[y];
        for(int j = 0; j < y; j++)
        {
            arr[i][j] = new bool[z];
            for(int k = 0;k < z;k++) arr[i][j][k]=false;
        }
    }
    return arr;
}



void Language::performCYK(string s)
{
    int ind = 0;
    map<string,int> I;
    IND.clear();
    for(int i = 0;i < rules.size();i++)
    {
        if(I.find(rules[i].lhs)==I.end()){
            I[rules[i].lhs] = ind;
            IND[ind] = rules[i].lhs;
            ind++;
        }
    }
    int n = s.size();
    s = " "+s;
    P = alloc3d(s.size(),s.size(),ind);
    for(int k = 1;k < s.size();k++)
    {
        for(int i = 0;i < rules.size();i++)
        {
            if(rules[i].rhs.size()==1 && islower(rules[i].rhs[0][0]) && s[k]==rules[i].rhs[0][0])
            {
                P[1][k][I[rules[i].lhs]] = true;
            }
        }
    }
    for(int i = 2;i <= n;i++)
    {
        for(int j = 1;j <= n-i+1;j++)
        {
            for(int k = 1;k < i;k++)
            {
                for(int r = 0;r < rules.size();r++)
                {
                    string A = rules[r].lhs;
                    if(!(rules[r].rhs.size()==1 && islower(rules[r].rhs[0][0])))
                    {
                        string B = rules[r].rhs[0];
                        string C = rules[r].rhs[1];
                        if(P[k][j][I[B]] && P[i-k][j+k][I[C]])
                            P[i][j][I[A]]=true;
                    }
                }
            }
        }
    }
}

void Language::performESP(string s, QStandardItemModel *model)
{
    QStandardItem * item = new QStandardItem(QString("S"));
    model->setItem(0,0,item);
    S.clear();
    flag = false;
    String = s;
    vector<string> R;
    R.push_back("S");
    this->backtrack(R,item);

}

bool isEqual(vector<string> & String,string s)
{
    if(String.size()!=s.size()) return false;
    for(int i = 0;i < String.size();i++)
    {
        if(String[i][0] != s[i]) return false;
    }
    return true;
}


int Language::backtrack(vector<string> & str,QStandardItem * item)
{
    if(flag) return false;
    if(str.size()>String.size()) return false;//because we don't have lambda!
    if(isEqual(str,String))
    {
        item->setBackground(Qt::green);
        flag=true;
        return true;
    }
    for(int i = 0;i<str.size();i++)
    {
        if(isupper(str[i][0]))
        {
            int j,k;
            for(j = 0;j < rules.size();j++)
            {
                if(rules[j].lhs == str[i])
                {
                    vector<string> newString;
                    string newStr = "";
                    for(k = 0;k < i;k++) newString.push_back(str[k]);
                    for(k = 0;k < rules[j].rhs.size();k++) newString.push_back(rules[j].rhs[k]);
                    for(k = i+1;k < str.size();k++) newString.push_back(str[k]);
                    for(int u = 0;u < newString.size();u++) newStr += newString[u];

                    QStandardItem * child = new QStandardItem(QString(newStr.c_str()));
                    item->appendRow(child);

                    if(!flag) S.push_back(newStr);
                    backtrack(newString,child);
                    if(flag){
                        item->setBackground(Qt::green);
                    }
                    if(!flag) S.pop_back();
                }
            }
        }
    }
}


