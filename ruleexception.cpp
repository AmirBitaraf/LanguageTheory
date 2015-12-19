#include "ruleexception.h"

RuleException::RuleException(QString Message)
{
    this->message = Message.toStdString();
}
