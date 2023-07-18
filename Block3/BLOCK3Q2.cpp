#include <iostream>

template<size_t n>
class permutation{
public:
    permutation(){
        for (int i=0;i<=n;++i){
            arr[i]=i;
        }

    }
    permutation(const unsigned *array){
        for (int i=0;i<n;++i){
            arr[i]=array[i];
        }
    }
    permutation(const permutation& other){
        for (int i=0;i<n;++i){
            arr[i]=other.arr[i];
        }
    }
    permutation& operator=(const permutation& other){
        for (int i=0;i<n;++i){
            arr[i]=other.arr[i];
        }
        return *this;
    }
    unsigned int& operator[] (const size_t i) { return arr[i] ; }
    unsigned const int& operator[] (const size_t i) const {return arr[i]; }

    permutation& operator*=(const permutation& other){
        unsigned val[n];
        for (int i=0;i<n;++i){
            val[i]=arr[i];
        }
        for (int i=0;i<n;++i){
            arr[i]=val[other[i]];
        }
        return *this ;
    }

    void operator() (unsigned* values) const{
        unsigned val[n];
        for (int i=0;i<n;++i){
            val[i]=values[i];
        }
        for (int i=0;i<n;++i){
            for (int f=0;f<n;++f){
                if(arr[f]==val[i]-1){
                    values[i]=(f+1);
                    break;
                }
            }
        }
    }

    permutation inverse() const {
        unsigned int obj[n];
        for (int i=0;i<n;++i){
            obj[arr[i]]=i;
        }
        return (permutation(obj));
    }

    permutation prev() const {
        int ival=-1;
        int jval=0;
        unsigned int oval[n];
        for (int i=1;i<n;++i){
                oval[i]=arr[i];
                if (arr[i]<arr[i-1]){
                    ival=i;
                }
        }
        oval[0]=arr[0];
        if (ival!=-1){
            for (int j=ival;j<n;++j){
                if (arr[j]<arr[ival-1]){
                    jval=j;
                }
            }
        }
        if (ival!=-1){
            std::swap(oval[ival-1],oval[jval]);
            int epoint=n-1;
            for (int f=ival;f<epoint;++f){
                std::swap(oval[f],oval[epoint]);
                --epoint;
            }
        }
        else{
            for (int f=0;f<n;++f){
                oval[f]=n-1-f;
            }
        }
       return permutation(oval);
    }
    permutation next() const {
        int ival=-1;
        int jval=0;
        unsigned int oval[n];
        for (int i=1;i<n;++i){
            oval[i]=arr[i];
            if (arr[i]>arr[i-1]){
                ival=i;
            }
        }
        oval[0]=arr[0];
        if (ival!=-1){
            for (int j=ival;j<n;++j){
                if (arr[j]>arr[ival-1]){
                    jval=j;
                }
            }
        }
        if (ival!=-1){
            std::swap(oval[ival-1],oval[jval]);
            int epoint=n-1;
            for (int f=ival;f<epoint;++f){
                std::swap(oval[f],oval[epoint]);
                --epoint;
            }
        }
        else{
            for (int f=0;f<n;++f){
                oval[f]=f;
            }
        }

        return permutation(oval);
    }
    const permutation operator++ (int){
        permutation temp(*this);
        ++*this;
        return temp;
    }
    const permutation operator-- (int){
        permutation temp(*this);
        --*this;
        return temp;
    }
     permutation& operator++ (){
        *this = next();
        return *this;
    }
     permutation& operator-- (){
         *this = prev();
         return *this;
    }

private:
    unsigned int arr[n];
};

template<size_t n>
bool operator==(const permutation<n> obj1, const permutation<n> obj2){
    bool l=1;
    for (int i=0;i<n;++i){
        if (obj1[i]==obj2[i]){
            continue;
        }
        l=0;
    }
    return l;
}

template<size_t n>
bool operator!=(const permutation<n> obj1, const permutation<n> obj2){
    return (!(obj1==obj2));

}
template<size_t n>
bool operator< (const permutation<n> obj1, const permutation<n> obj2){
    bool l=0;
    if (obj1!=obj2) {
        for (int i = 0; i < n; ++i) {
            if (obj1[i]!=obj2[i]) {
                l = obj1[i] < obj2[i];
                break;
            }
        }
    }
    return l;
}
template<size_t n>
bool operator> (const permutation<n> obj1, const permutation<n> obj2){return (obj1==obj2) ? 0 : !(obj1<obj2);}

template<size_t n>
bool operator<= (const permutation<n> obj1, const permutation<n> obj2) {
    bool l = 0;
    if (obj1 == obj2) {
        l=1;
    }
    else {
        for (int i = 0; i < n; ++i) {
            if (obj1[i] != obj2[i]) {
                l = obj1[i] < obj2[i];
                break;
            }
        }
    }
    return l;

}
template<size_t n>
bool operator>= (const permutation<n> obj1, const permutation<n> obj2){ return (obj1==obj2) ? 1 : !(obj1<=obj2); }

template<size_t n>
permutation<n> operator* (const permutation<n> obj1, const permutation<n> obj2){return permutation<n>(obj1) *=obj2; }

int main(){
    const unsigned a[19] = {10, 5, 15, 3, 8, 17, 12, 1, 11, 18, 0, 7, 6, 16, 2, 13, 14, 9, 4};
    permutation<19>perm(a);

    const unsigned b[19] = {10, 5, 15, 3, 8, 17, 12, 1, 11, 18, 0, 7, 6, 16, 2, 13, 14, 9, 4};
    permutation<19>prm(b);

    perm++;
    ++prm;



}