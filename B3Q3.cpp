#include <iostream>
#include <stdexcept>
#include <string>

template<typename vt,size_t height, size_t width>
class matrix{
private:
    vt arr[height][width];
public:
    typedef matrix<vt, std::max<size_t>(height - 1, 1), std::max<size_t>(width - 1, 1)> matrix_minor;
    matrix(){
        for (int i=0;i<height;++i){
            for(int f=0;f<width;++f){
                arr[i][f]=0;

            }
        }
    }
    matrix(const vt& num){
        for (int i=0;i<height;++i){
            for(int f=0;f<width;++f){
                arr[i][f]=num;

            }
        }
    }
    matrix(const matrix& other){
        for (int i=0;i<height;++i){
            for(int f=0;f<width;++f){
                arr[i][f]=other.arr[i][f];
            }
        }
    }

    matrix& operator=(const matrix& other){
        if (*this!=other){
            for (int i=0;i<height;++i){
                for(int f=0;f<width;++f){
                    arr[i][f]=other.arr[i][f];
                }
            }
        }
        return *this;
    }

    vt& at(const size_t& i, const size_t& j)  {
        vt& a= arr[i][j];
        return a;
    }
    const vt& at(const size_t& i, const size_t& j) const {
        const vt& a= arr[i][j];
        return a;
    }
    matrix& operator*=(const matrix<vt,width,height> other){
        matrix<vt,height,width> m;
        m=*this;
        for (int i=0;i<height;++i){
            for (int j=0;j<width;++j){
                int sum=0;
                for (int k=0;k<width;++k){
                    sum+=(m.at(i,k)*other.at(k,j));
                }
                arr[i][j]=sum;
            }
        }
        return *this;
    }
    matrix& operator*=(const size_t obj){
        for (int i=0;i<height;++i){
            for (int j=0;j<width;++j){
                arr[i][j]*=obj;
            }
        }
        return *this;
    }
    matrix& operator+=(const matrix& other){
        for (int i=0;i<height;++i){
            for(int f=0;f<width;++f){
                arr[i][f]+=other.arr[i][f];
            }
        }
        return *this;
    }
    matrix& operator-=(const matrix& other){
        for (int i=0;i<height;++i){
            for(int f=0;f<width;++f){
                arr[i][f]-=other.arr[i][f];
            }
        }
        return *this;
    }
    matrix& operator-=(const size_t other){
        for (int i=0;i<height;++i){
            for(int f=0;f<width;++f){
                arr[i][f]-=other;
            }
        }
        return *this;
    }
    matrix& operator+=(const size_t other){
        for (int i=0;i<height;++i){
            for(int f=0;f<width;++f){
                arr[i][f]+=other;
            }
        }
        return *this;
    }
    const matrix operator- () const {
        matrix temp(*this);
        temp*=-1;
        return temp;
    }
    const matrix operator+ () const {
        matrix temp(*this);
        return temp;
    }
    matrix<vt,width,height> transposed() const{
        matrix<vt,width,height> mal(0);
        for (int i=0;i<height;++i){
            for (int f=0;f<width;++f){
                mal.at(f,i)=arr[i][f];
            }
        }
        return mal;
    }
    const vt trace() const {
        vt a=0;
        for (int i=0;i<height;++i){
            a+=arr[i][i];
        }
        return a;
    }
    const vt det() const{
        size_t det=0;
        if (height==1){
            return arr[0][0];
        }
        else if (height==2){
            return (arr[0][0]*arr[1][1]-arr[0][1]*arr[1][0]);
        }
        else{
            matrix_minor sm;
            int sign=1;
            for (int i=0;i<height;++i){
                int sm_r=0;
                for (int m_r=1;m_r<height;++m_r){
                    int sm_c=0;
                    for (int m_c=0;m_c<height;++m_c) {
                        if (m_c != i) {
                            sm.at(sm_r, sm_c) = arr[m_r][m_c];
                            sm_c += 1;
                        }
                    }
                    sm_r+=1;
                }
                det=det+(sign*arr[0][i]*sm.det());
                sign*=-1;
            }

        }
        return det;
    }

};

template<typename vt,size_t height, size_t width>
bool operator==(const matrix<vt,height,width> obj,const matrix<vt,height,width> obj2) {
    bool l = 1;
    for (int i = 0; i < height; ++i) {
        for (int f = 0; f < width; ++f) {
            if (obj.at(i,f)!= obj2.at(i,f)) {
                l = 0;
                break;
            }
        }
    }
    return l;
}

template<typename vt,size_t height, size_t width>
bool operator!=(const matrix<vt,height,width> obj,const matrix<vt,height,width> obj2){ return !(obj==obj2); }

template<typename vt,size_t height, size_t width>
matrix<vt,height,width> operator+(const matrix<vt,height,width> obj,const matrix<vt,height,width> obj2){
    return matrix<vt,height,width>(obj)+=obj2;
}

template<typename vt,size_t height, size_t width>
matrix<vt,height,width> operator-(const matrix<vt,height,width> obj,const matrix<vt,height,width> obj2){
    return matrix<vt,height,width>(obj)-=obj2;
}

template<typename vt,size_t height, size_t width>
matrix<vt,height,width> operator+(const matrix<vt,height,width> obj,const size_t obj2){
    return matrix<vt,height,width>(obj)+=obj2;
}

template<typename vt,size_t height, size_t width>
matrix<vt,height,width> operator-(const matrix<vt,height,width> obj,const size_t obj2){
    return matrix<vt,height,width>(obj)-=obj2;
}

template<typename vt,size_t height, size_t width>
matrix<vt,height,width> operator+(const size_t obj2,const matrix<vt,height,width> obj){
    return matrix<vt,height,width>(obj)+=obj2;
}

template<typename vt,size_t height, size_t width>
matrix<vt,height,width> operator-(const size_t obj2,const matrix<vt,height,width> obj){
    matrix<vt,height,width> m =obj;
    m=-m;
    return m+=obj2;
}
template<typename vt,size_t height, size_t width>
matrix<vt,height,width> operator*(const matrix<vt,height,width> obj,const size_t obj2){
    return matrix<vt,height,width>(obj)*=obj2;
}
template<typename vt,size_t height, size_t width>
matrix<vt,height,width> operator*(size_t obj2,const matrix<vt,height,width> obj){
    return matrix<vt,height,width>(obj)*=obj2;
}
template<typename vt,size_t height, size_t width,size_t h>
matrix<vt,height,h> operator*(const matrix<vt,height,width> obj1,const matrix<vt,width,h> obj2) {
    matrix<vt,height,h> m;
    for (int i=0;i<height;++i){
        for (int j=0;j<h;++j){
            int sum=0;
            for (int k=0;k<width;++k){
                sum+=(obj1.at(i,k)*obj2.at(k,j));
            }
            m.at(i,j)=sum;
        }
    }
    return m;
}
