#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class bigint{
    bool sign;
    std::vector<int> arr;
public:
    bigint(long long int num){
        sign = (num >= 0);
        num=std::abs(num);
        if (num==0) {
            arr.push_back(0);
        }
        while (num>0){
            arr.push_back(num%10);
            num /= 10;
        }
    }
    bigint(){
        sign=true;
        arr.push_back(0);
    }

    bigint& operator= (const bigint& other){
        sign=other.sign;
        int a=other.arr.size()-1;
        arr.clear();
        for(int i=0;i<=a;++i){
            arr.push_back(other.arr[i]);
        }
        return *this;
    }

    friend std::istream& operator>>(std::istream& inst,bigint& num);
    friend std::ostream& operator<<(std::ostream& inst,const bigint& num);
    std::string to_string() const;
    friend bool operator==(const bigint& obj1,const bigint& obj2);
    friend bool operator>(const bigint& obj1,const bigint& obj2);
    explicit operator bool() const{
        return ((arr.size()>1) or (arr.size()==1 and arr[0]!=0));
    }
    bigint operator+(){
        return *this;
    }
    bigint operator-(){
        sign=!sign;
        return *this;
    }

    bigint(const bigint& obj){
        sign=obj.sign;
        int a=obj.arr.size();
        for(int i=0;i<a;++i){
            arr.push_back(obj.arr[i]);
        }
    }
    bigint& operator+=(const bigint& obj1){
        size_t a = std::min(obj1.arr.size(),arr.size());
        bigint temp=*this;
        int carry=0;
        int remainder=0;
        if (obj1.sign!=sign){
            bigint temp=obj1;
            temp.sign=!temp.sign;
            return (*this-=temp);

        }
        int sum=0;
        for (int i=0; i<=a-1;++i){
            sum= obj1.arr[i] + temp.arr[i]+carry;
            if (sum>=10){
                carry=sum/10;
                arr[i]=(sum%10);
            }
            else{
                carry=0;
                arr[i]=(sum);
            }
        }

        if (arr.size()<obj1.arr.size()){
            for (int i=a;i<obj1.arr.size();++i){
                arr.push_back(obj1.arr[i]);
            }
        }
        else if (arr.size()==obj1.arr.size()){
            while (carry>0){
                if (carry>=10){
                    arr.push_back(carry%10);
                    carry=carry/10;
                }
                else{
                    arr.push_back(carry);
                    carry=0;
                }
            }
            return *this;
        }
        int j=a;
        while (carry>0){
            if (j>=arr.size()){
                sum=carry;
            }
            else{
                sum=arr[j]+carry;
            }
            if (sum>=10){
                carry=sum/10;
                sum=sum%10;
            }
            else{
                carry=0;
            }
            if (j>=arr.size()){
                arr.push_back(sum);
            }
            else{
                arr[j]=sum;
            }
            ++j;
        }
        return *this;

    }
    bigint& operator-=(const bigint& obj1){
        if (obj1.sign!=sign){
            bigint temp;
            temp=obj1;
            temp.sign=!obj1.sign;
            return(*this+=temp);
        }
        size_t a=std::min(arr.size(),obj1.arr.size());
        int carry=0;
        int remainder=0;
        bigint temp=*this;
        bigint temp1=obj1;
        temp.sign=temp1.sign=true;
        if (!( temp>temp1)){
            if (obj1==*this){
                return *this=bigint(0);
            }
            for (int i=0;i<=a-1;++i){
                remainder=obj1.arr[i]-arr[i]-carry;
                carry=0;
                while (remainder<0){
                    carry+=1;
                    remainder+=10;
                }
                arr[i]=remainder;
            }

            for (int i=a;i<obj1.arr.size();++i){
                remainder=obj1.arr[i]-carry;
                carry=0;
                while (remainder<0){
                    carry+=1;
                    remainder+=10;
                }
                arr.push_back(remainder);
            }
            sign=!sign;
        }
        else{
            for (int i=0;i<=a-1;++i){
                remainder=arr[i]-obj1.arr[i]-carry;
                carry=0;
                while (remainder<0){
                    carry+=1;
                    remainder+=10;
                }
                arr[i]=remainder;
            }

            int j=a;
            while (carry>0){
                int remainder=arr[j]-carry;
                carry=0;
                while (remainder<0){
                    carry+=1;
                    remainder+=10;
                }
                arr[j]=remainder;

                ++j;
            }
        }

        for (int i=arr.size()-1;i>=0;++i){
            if (arr[i]!=0){
                break;
            }
            else {
                arr.pop_back();
            }
        }
        return *this;

    }
    bigint& operator++(){
        *this+=1;
        return *this;
    }
    bigint& operator--(){
        *this-=1;
        return *this;
    }

    const bigint operator++(int){
        bigint temp(*this);
        ++*this;
        return temp;
    }
    const bigint operator--(int){
        bigint temp=*this;
        --*this;
        return temp;
    }
    friend  bigint multiply(const bigint& obj1,const bigint& obj2);
    bigint& operator*=(const bigint& obj1){
        bigint a=*this;
        if (a.arr.size()>=obj1.arr.size()){
            a = multiply(a,obj1);
        }
        else{
            a= multiply(obj1,a);
        }
        if (sign!=obj1.sign){
            a.sign=false;
        }
        else{
            a.sign=true;
        }
        *this=a;
        return *this;
    }


};

bigint multiply(const bigint& obj1,const bigint& obj2){
    bigint sum=0;
    bigint num=0;
    std::vector<int> arr;
    for (int i=0;i<obj2.arr.size();++i){
        int mul=0;
        int carry=0;
        for (int j=0;j<obj1.arr.size();++j){
            mul=obj1.arr[j]*obj2.arr[i]+carry;
            if (mul>=10){
                carry=mul/10;
                mul=mul%10;
            }
            else{
                carry=0;
            }
            arr.push_back(mul);
        }
        if (carry>=10){
           while (carry>=10){
               arr.push_back(carry%10);
               carry/=10;
           }
        }
        if (carry>0){
            arr.push_back(carry);
            carry=0;
        }
        sum=0;
        sum.arr=arr;
        arr.clear();
        for (int k=i;k>0;--k){
            sum.arr.insert(sum.arr.begin(),0);
        }
        num+=bigint(sum);

    }
    return num;

}

std::istream& operator>>(std::istream& inst,bigint& num){
    std::string temp;
    inst >> temp;
    int s=temp.size();
    num.sign=true;
    for (int i=s-1;i>=0;--i) {
        if (temp[i] == '-') {
            num.sign = false;
            continue;
        }
        num.arr.push_back(temp[i] - '0');
    }
    num.arr.erase(num.arr.begin());
    return inst;
}

std::ostream& operator<<(std::ostream& inst,const bigint& num){
    if (num.sign==0){
        inst << "-";
    }
    int a =num.arr.size()-1;
    for (int i=a;i>=0;--i){
        inst << num.arr[i];
    }
    return inst;

}

std::string bigint::to_string() const {
    std::stringstream string;
    string << *this;
    return string.str();
}

bool operator==(const bigint& obj1,const bigint& obj2){
    if (obj1.arr==obj2.arr and (obj1.sign==obj2.sign)){
        return true;
    }
    return false;
}
bool operator!=(const bigint& obj1,const bigint& obj2){
    return !(obj1==obj2);
}
bool operator>(const bigint& obj1,const bigint& obj2){
    if (obj1==obj2){
        return false;
    }
    else if (obj1.sign!=obj2.sign){
        return obj1.sign;
    }
    else if(obj1.arr.size()!=obj2.arr.size()){
        if (obj1.sign==true){
            return obj1.arr.size()>obj2.arr.size();
        }
        else{
            return obj1.arr.size()<obj2.arr.size();
        }
    }
    else if(obj1.sign== true){
        bool l=0;
        for (int i=obj1.arr.size()-1;i>=0;--i){
            if (obj1.arr[i]>obj2.arr[i]){
                l=1;
                break;
            }
            else if (obj1.arr[i]==obj2.arr[i]){
                continue;
            }
            else{
                break;
            }
        }
        return l;
    }
    else{
        bool l=1;
        for (int i=obj1.arr.size()-1;i>=0;--i){
            if (obj1.arr[i]>obj2.arr[i]){
                l=0;
                break;
            }
            else if (obj1.arr[i]==obj2.arr[i]){
                continue;
            }
            else{
                break;
            }

        }
        return l;
    }

}
bool operator>=(const bigint&obj1,const bigint& obj2){
    if (obj1==obj2){
        return true;
    }
    else{
        return (obj1>obj2);
    }
}

bool operator<(const bigint& obj1,const bigint& obj2){ return !(obj1>=obj2); }
bool operator<=(const bigint& obj1,const bigint& obj2){ return !(obj1>obj2); }

bigint operator+(const bigint& obj1, const bigint& obj2){ return bigint(obj1)+=obj2 ; }
bigint operator-(const bigint& obj1,const bigint& obj2){ return bigint(obj1)-=obj2 ;}
bigint operator*(const bigint& obj1,const bigint& obj2){return bigint(obj1)*=obj2 ;}






int main(){
    std::cout <<  ( bigint(-376018) * bigint(-461470454670946) );
}