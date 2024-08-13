#include"arithmeticOfStdString.h"
#include<stack>

static int compareop(char op1,char op2);

std::string calculateStdStringExpression(std::string expression)
{
    std::stack<char> stackOfOps;
    std::stack<double> stackOfNumbers;

    //运算符和操作数分别出栈，结果存储在操作数栈顶
    auto lambdaf=[&]()
                {
                    double op2=stackOfNumbers.top();
                    stackOfNumbers.pop();//npop
                    switch(stackOfOps.top())
                    {
                    case '+':
                        stackOfNumbers.top()+=op2;
                        break;
                    case '-':
                        stackOfNumbers.top()-=op2;
                        break;
                    case '*':
                        stackOfNumbers.top()*=op2;
                        break;
                    case '/':
                        stackOfNumbers.top()/=op2;
                        break;
                    }
                    stackOfOps.pop();//opop
                };

    unsigned long j=0;
    for(unsigned long i=0;i<expression.size();i=j)
    {
        std::string temp="";

        //括号内的表达式可视为一个独立的子表达式，递归调用直到无括号为止
        bool is_number=false;
        if(expression[i]=='(')
        {
            std::string childExpression="";
            int c=1,k=i+1;
            while(c>0)
            {
                childExpression.push_back(expression[k]);
                ++k;
                if(*(childExpression.end()-1)=='(')
                    ++c;
                if(*(childExpression.end()-1)==')')
                    --c;
            }
            childExpression.erase(childExpression.end()-1);
            temp=calculateStdStringExpression(childExpression);
            i=k;
            is_number=true;
        }
        
        //读入字符串中的数字
        for(j=i;(expression[j]>='0'&&expression[j]<='9')||expression[j]=='.';j++)
        {
            temp+=expression[j];
            is_number=true;
        }

        //如果读入了至少一个数字,将读入的数字入栈，同时根据上次循环的结果确定-是否为单操作数运算符，如果是，则立即运算
        static bool shouldBeMinus=false;
        if(is_number)
        {
            if(shouldBeMinus==false)
                stackOfNumbers.push(strtod(temp.c_str(),nullptr));//npush
            else
            {
                stackOfNumbers.push(-strtod(temp.c_str(),nullptr));//npush
                shouldBeMinus=false;
            }
        }
        else//读入的是运算符
        {
            //判断-是否是单操作数运算符
            if(expression[i]=='-'&&i==0)
            {
                shouldBeMinus=true;
                goto a;
            }

            //优先级高的运算符（或栈空）直接入栈
            if(stackOfOps.empty()||compareop(expression[i],stackOfOps.top())>0)
            {
                stackOfOps.push(expression[i]);//opush
            }
            else//栈不空时，如果是优先级低的运算符，先运算上一个运算符，再入栈
            {
                if(!(stackOfOps.empty())&&compareop(expression[i],stackOfOps.top())<=0)
                {
                    lambdaf();
                    stackOfOps.push(expression[i]);//opush
                }
            }
            a:++j;
            is_number=false;
        }
    }

    //处理栈中的剩余内容
    while(!stackOfOps.empty())
    {
        lambdaf();
    }

    //double数据转换为字符串
    char szBuffer[1024];
    sprintf(szBuffer,"%lf",stackOfNumbers.top());
    std::string str=szBuffer;
    bool highIsZero=false;
    for(auto i=str.end()-1;;i--)
    {
        if(*i=='0'&&*(i-1)=='0')
        {
            str.erase(i);
            highIsZero=true;
        }
        else
        {
            break;
        }
    }
    if(highIsZero)
    {
        str.erase(str.end()-1);
        if(*(str.end()-1)=='.')
        {
            str.erase(str.end()-1);
        }
    }
    return str;
}

//return value's sign:- op1<op2 0 op1=op2 + op1>op2
int compareop(char op1,char op2)
{
    int intop1,intop2;
    switch(op1)
    {
    case '+':
    case '-':
        intop1=0;
        break;
    case '*':
    case '/':
        intop1=1;
        break;
    default:
        return 0x7FFFFFFF;
    }
    
    switch(op2)
    {
    case '+':
    case '-':
        intop2=0;
        break;
    case '*':
    case '/':
        intop2=1;
        break;
    default:
        return 0x7FFFFFFF;
    }
    return intop1-intop2;
}