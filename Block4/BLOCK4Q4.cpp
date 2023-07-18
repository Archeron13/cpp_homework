#include <forward_list>

template<typename vt>
class reverse_forward_list{
public:
    static void reverse(std::forward_list<vt>& lis){
        int size=0;
        for (auto l=lis.begin();l!=lis.end();++l) {
            if (l == lis.begin()) {
                size+=1;
                continue;
            }
            int pop=0;
            pop= *l;
            lis.push_front(pop);
            size+=1;
        }
        lis.resize(size);
    }
};

int main(){
    std::forward_list<int>  a = {1,2,3,4,5,6};
    reverse_forward_list<int> b;
    b.reverse(a);
}