#ifndef RULEEXCEPTION_H
#define RULEEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

class RuleException : public std::exception
{
    string message;
public:
    RuleException(QString);
    virtual ~RuleException() throw() {}
    virtual const char *what() const throw() {
        return this->message.c_str();
    }
};

#endif // RULEEXCEPTION_H
