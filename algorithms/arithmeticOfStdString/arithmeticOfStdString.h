#ifndef arithmeticOfStdString_h_
#define arithmeticOfStdString_h_
#include<string>
#include<vector>

std::string calculateStdStringExpression(std::string expression);//expression：四则运算表达式；返回值：运算结果（字符串）
std::string replaceVariable(const std::string& expression,const std::vector<std::string>& values,const std::vector<char>& variables);//expression：任意字符串；values：要替换为的值，与variablesd中的元素一一对应；variables：变量名
//expression中的variables元素将被替换为values中的对应元素（在返回值中）
std::string cinReadStdStringFromStdString(std::string& source);//source：StdString输入流；返回值：输入字符串（模拟cin>>std::string行为），读入任意数量字符后遇空格字符停止输入；注意：source读入的字符（以及其前面的空格字符）会被抹除，在返回值中不保留空格字符
#endif