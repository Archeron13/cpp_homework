
#include <iostream>
#include <cmath>

bool double_cmp(const double d1, const double d2){
    return std::fabs(d1-d2)<1e-6;
}
bool double_grt(const double d1, const double d2){
    return (d1-d2) > 1e-6;
}
bool double_grteq(const double d1, const double d2){
    return (d1-d2) >= -1e-6;
}


int main() {
    double x,y,r,a,b,c,distx,disty,distp,sumr,delta;
    double z=2;
    std::cin >> x >> y >> r;
    std::cin >> a >> b >> c;
    sumr=r+c;
    distx= std::pow(x-a,z);
    disty=std::pow(y-b,z);
    distp=std::sqrt(distx+disty);
    delta=std::fabs(r-c);

    if (double_cmp(r,0) and double_cmp(c,0)){
        if (double_cmp(distp,0)){
            std::cout << 1;
        }
        else {
            std::cout << 0;
        }
    }
    else if (double_cmp(x,a) and double_cmp(y,b)){
        if (double_cmp(r,c)){
            std::cout << "infinity";
        }
        else{
            std::cout << 0;
        }
    }
    else if (double_grt(distp,sumr)){
        std::cout << 0;
    }
    else if (double_cmp(sumr,distp)){
        std::cout << 1;
    }
    else if (double_grteq(sumr,distp)){
        if (double_grt(distp,delta)){
            std::cout << 2;
        }
        else if (double_cmp(delta,distp)){
            std::cout << 1;
        }
        else{
            std::cout << 0;
        }
    }


}
