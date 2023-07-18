

bool eq(double x,double y){
    const double val=1e-6;
    return std::fabs(x-y) < val;
}
bool cmp(double x, double y){
    const double val=1e-6;
    return x-y>val;
}

struct vector{
    double x;
    double y;

    vector(double x1, double y1): x(x1),y(y1){}
    vector()=default;

    vector& operator*=(const double scal){
        x*=scal;
        y*=scal;
        return *this;
    }
    vector& operator/=(const double scal){
        x/=scal;
        y/=scal;
        return *this;
    }
    vector operator-()const { return vector(-x,-y); }
    vector operator+()const { return vector(x,y);}

    vector& operator+=(const vector& obj1){
        x+=obj1.x;
        y+=obj1.y;
        return *this;
    }
    vector& operator-=(const vector& obj1){
        x-=obj1.x;
        y-=obj1.y;
        return *this;
    }

    double length () const{ return std::sqrt(std::pow((x),2.0)+std::pow((y),2.0)); }

};

bool operator==(const vector& obj1,const vector& obj2){ return (eq(obj2.x,obj1.x) and eq(obj2.y,obj1.y)); }
bool operator !=(const vector& obj1,const vector& obj2){ return !(obj1==obj2); }

vector operator+(const vector& obj1,const vector& obj2){ return vector(obj1)+=obj2; }
vector operator-(const vector& obj1,const vector& obj2){ return vector(obj1)-=obj2; }
vector operator*(const vector& obj1,const double obj2){ return vector(obj1)*=obj2; }
vector operator*(const double obj2,const vector& obj1){ return vector(obj1)*=obj2; }
vector operator/(const vector& obj1,const double obj2){ return vector(obj1)/=obj2; }

double dot_product (const vector& obj1, const vector& obj2){ return ((obj1.x*obj2.x) + (obj1.y*obj2.y)); }
double angle(const vector& obj1, const vector& obj2 ){ return std::acos((dot_product(obj1,obj2)/(obj1.length()*obj2.length()))); }
double cross_product (const vector& obj1, const vector& obj2){ return ((obj1.x*obj2.y)-(obj2.x*obj1.y)); }
bool collinear(const vector& obj1, const vector& obj2) { return (eq(cross_product(obj1, obj2), 0)); }
