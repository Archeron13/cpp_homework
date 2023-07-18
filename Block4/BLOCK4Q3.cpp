#include <iostream>
#include <stack>
#include <string>

int main() {
    std::string val;
    std::cin >> val;
    std::stack<char> stk;
    for (int i=0;i<val.size();++i){
        if (stk.size()==0){
            stk.push(val[i]);
        }
        else{
            if (val[i]==']' and stk.top()=='['){
                stk.pop();
            }
            else if (val[i]==')' and stk.top()=='('){
                stk.pop();
            }
            else {
                stk.push(val[i]);
            }
        }
    }
    val = (stk.size() ) ? "NO" : "YES";
    std::cout << val;

}
