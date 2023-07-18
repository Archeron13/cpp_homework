#include <iostream>
#include <vector>
#include <unordered_set>

int main(){
    std::vector<int> ara;
    std::vector<int> arb;
    int siza,sizb,c;
    std::cin >> siza;
    for (int i=0;i<siza;++i){
        int pback=0;
        std::cin >> pback;
        ara.push_back(pback);
    }
    std::cin >> sizb;
    for (int i=0;i<sizb;++i){
        int pback=0;
        std::cin >> pback;
        arb.push_back(pback);
    }
    std::cin >> c;
    std::unordered_set<int> uset;
    for (auto i=ara.begin();i!=ara.end();++i){
        uset.insert(uset.begin(),c-*i);
    }
    int count=0;
    for (auto i=arb.begin();i!=arb.end();++i){
        if (uset.count(*i)==1){ count+=1 ;}
    }
    std::cout << count;



}