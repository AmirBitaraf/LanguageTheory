
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <map>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define PSS pair<string,string>

vector<string> Rules;
string Terminals,Variables,Rule,String;
vector<PSS> RuleData;

/*
QImage img(mywidget.size());
QPainter painter(&img);
mywidget.render(&painter);
img.save("/some/file.jpg");

*/



void input()
{
    printf("Enter Terminals: ");
    cin>>Terminals;
    printf("Enter Variables: ");
    cin>>Variables;
    printf("Enter String to Evaluate: ");
    cin>>String;
    printf("Enter Rules (one per each line):\n");
    getline(cin,Rule);
    while(getline(cin,Rule) && Rule[0])
        Rules.push_back(Rule);
}


void parse()
{
    for(int i = 0;String[i];i++)
    {
        if(Terminals.find(String[i]) == Terminals.npos)
        {
            printf("Invalid Sentence: There is a character %c which is not a terminal! So this sentence is not belonged to this Language!",String[i]);
            exit(0);
        }
    }
    for(int i = 0;Terminals[i];i++)
    {
        for(int j = 0;Variables[j];j++)
        {
            if(Terminals[i]==Variables[j]){
                printf("Parse Error: Found a character %c which is a terminal and a variable!",Terminals[i]);
                exit(0);
            }
        }
    }
    for(int i = 0;i < Rules.size();i++)
    {
        string k="",v="";
        int flag = false,is=false;
        for(int j = 0; j < Rules[i].size();j++)
        {
            if(!isalpha(Rules[i][j])) flag=true;
            else if(flag) v+= Rules[i][j];
            else k+= Rules[i][j];
        }
        RuleData.push_back(make_pair(k,v));
        if(v.empty())
        {
            printf("Invalid Rule: No Right Value!");
            exit(0);
        }
        if(k.size() != 1){
            printf("Invalid Rule Entered!");
            exit(0);
        }
    }
}


map<string,bool> isOK;

vector<string> checkup;
bool f(string var)
{
    if(isOK.find(var) != isOK.end()) return isOK[var];
    bool res = false;
    for(int i = 0;i < RuleData.size();i++)
    {
        if(RuleData[i].first == var)
        {
            vector<string> vars;
            bool flag = true;
            for(int j = 0;j < checkup.size();j++)
            {
                if(RuleData[i].second.find(checkup[j]) != string::npos)
                {
                    flag = false;
                    break;
                }
            }
            if(!flag) continue;

            bool isOnlyTerminal = true;
            for(int j = 0;j < RuleData[i].second.size();j++){
                if(Variables.find(RuleData[i].second[j]) != string::npos){
                    isOnlyTerminal = false;
                    vars.push_back(RuleData[i].second.substr(j,1));
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

void cleanup_rules()
{
    f("S");
    for(int i = 0;i < RuleData.size();i++)
    {
        if(!isOK[RuleData[i].first])
        {
            cout<<"Erased Rule "<<RuleData[i].first<<" -> "<<RuleData[i].second<<" due to non-usability."<<endl;
            RuleData.erase(RuleData.begin()+i);
            i--;
        }
    }
}


vector<string> S;
int flag = false;
int backtrack(string & str,int indent)
{
    if(flag) return false;
    if(str.size()>String.size()) return false;//because we don't have lambda!
    if(String == str)
    {
        flag=true;
        return true;
    }
    for(int i = 0;i<str.size();i++)
    {
        if(Variables.find(str[i])!=string::npos)
        {
            int j,k;
            for(j = 0;j < RuleData.size();j++)
            {
                if(RuleData[j].first[0] == str[i])
                {
                    string newString = "";
                    for(k = 0;k < i;k++) newString += str[k];
                    for(k = 0;k < RuleData[j].second.size();k++) newString += RuleData[j].second[k];
                    for(k = i+1;k < str.size();k++) newString += str[k];

                    for(k=0;k<indent-1;k++) cout<<"  ";
                    if(indent) cout<<"--";
                    cout<<newString<<endl;
                    if(!flag) S.push_back(newString);
                    backtrack(newString,indent+1);
                    if(!flag) S.pop_back();
                }
            }
        }
    }
}


/*
int main()
{
    input();
    parse();
    cleanup_rules();
    S.push_back("S");
    cout<<"S"<<endl;
    string start = "S";
    backtrack(start,1);
    if(flag)
    {
        printf("Sentence is a member of this Language with this path:\n");
        for(int i = 0;i < S.size();i++)
        {
            cout<<S[i];
            if(i!=S.size()-1) cout<<" -> ";
        }
        cout<<endl;
    }
    else
    {
        printf("Sentence is not a member of this Language!\n");
    }
}
*/
