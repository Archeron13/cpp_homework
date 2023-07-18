#include <iostream>
#include <vector>

class layered_matrix {
public:
    layered_matrix() = delete; // Default constructor
    layered_matrix(size_t n) { //Constructor
        size = n;
        _a = new int *[size];
        for (int b = 0; b < n; ++b) {
            _a[b] = new int[n];
        }
        for (int i = 0; i < n; ++i) {
            for (int f = 0; f < n; ++f) {
                if (f >= i) {
                    _a[i][f] = f - i;
                } else if (f < i) {
                    _a[i][f] = i - f;
                }
            }
        }
    }

    ~layered_matrix() { //Destructor
        for (size_t i = 0; i < size; i++) {
            delete _a[i];
        }
        delete _a;
    }
    layered_matrix& operator=(const layered_matrix& obj ){
        size = obj.size;
        _a = new int *[size];
        for (int b = 0; b < size; ++b) {
            _a[b] = new int[size];
        }
        for (int i = 0; i < size; ++i) {
            for (int f = 0; f < size; ++f) {
                if (f >= i) {
                    _a[i][f] = f - i;
                } else if (f < i) {
                    _a[i][f] = i - f;
                }
            }
        }
        return *this;
    }
    int get_sum(size_t x1, size_t y1, size_t x2, size_t y2) const{
        size_t xmin,xmax,ymin,ymax,sum=0;
        xmin=std::min(x1,x2);
        xmax=std::max(x1,x2);
        ymin=std::min(y1,y2);
        ymax=std::max(y1,y2);
        for (int i=0;i<size;++i){
            for (int j=0;j<size;++j){
                if ((j==xmin) or (j==xmax)){
                    if((i>=ymin) and (i<=ymax)){
                        sum+=_a[i][j];
                    }
                }
                else if ((i==ymin) or (i==ymax)){
                    if((j>=xmin) and (j<=xmax)){
                        sum+=_a[i][j];
                    }
                }
            }
        }
        return sum;
    }
    layered_matrix(const layered_matrix& obj ){
        size = obj.size;
        _a = new int *[size];
        for (int b = 0; b < size; ++b) {
            _a[b] = new int[size];
        }
        for (int i = 0; i < size; ++i) {
            for (int f = 0; f < size; ++f) {
                if (f >= i) {
                    _a[i][f] = f - i;
                } else if (f < i) {
                    _a[i][f] = i - f;
                }
            }
        }
    }



private:
    int **_a;
    size_t size;
};

int main(){
    layered_matrix obj(5);
    std::cout << obj.get_sum(0,1,3,1);

}