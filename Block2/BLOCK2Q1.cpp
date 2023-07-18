#include <iostream>
#include <cmath>

double dot_product(double x1,double y1, double x2, double y2){
    double ans;
    ans=(x1*x2) + (y1*y2);
    return ans;

}
double cross_product(double x1, double y1, double x2, double y2){
    double ans;
    ans= (x1*y2)-(y1*x2);
    return ans;
}

double perimeter(size_t n,const double* x,const double* y){
    double dist=0.0;
    for(size_t b=0;b<n;++b){
        if (b==0){
            continue;
        }
        else if (b==n-1){
            dist += std::sqrt(std::pow((x[b] - x[b - 1]), 2.0) + std::pow((y[b] - y[b - 1]), 2.0));
            dist+=std::sqrt(std::pow((x[n-1]-x[0]),2.0)+std::pow((y[n-1]-y[0]),2.0));
        }
        else {
            dist += std::sqrt(std::pow((x[b] - x[b - 1]), 2.0) + std::pow((y[b] - y[b - 1]), 2.0));
        }
    }
    return dist;
}
double area(size_t n,const double* x,const double* y){
    double area=0;
    for (size_t b=0;b<n;++b){
        if (b==0){
            continue;
        }
        else if (b==n-1){
            area+=cross_product(x[0],y[0],x[n-1],y[n-1]);
            area+=cross_product(x[b],y[b],x[b-1],y[b-1]);
        }
        else{
            area+=cross_product(x[b],y[b],x[b-1],y[b-1]);
        }
    }
    area=std::fabs(area/(2.0));
    return area;
}

