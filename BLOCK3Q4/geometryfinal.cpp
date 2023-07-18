#include <cmath>
#include <vector>
#include <iostream>



bool eq(double x,double y){
    const double val=1e-6;
    return std::fabs(x-y) < val;
}
bool cmp(double x, double y){
    const double val=1e-6;
    return x-y>val;
}

struct vector {
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

bool operator==(const vector& obj1,const vector& obj2){return (eq(obj2.x,obj1.x) and eq(obj2.y,obj1.y));}
bool operator !=(const vector& obj1,const vector& obj2){ return !(obj1==obj2); }

vector operator+(const vector& obj1,const vector& obj2){ return vector(obj1)+=obj2; }
vector operator-(const vector& obj1,const vector& obj2){ return vector(obj1)-=obj2; }
vector operator*(const vector& obj1,const double obj2){ return vector(obj1)*=obj2; }
vector operator*(const double obj2,const vector& obj1){ return vector(obj1)*=obj2; }
vector operator/(const vector& obj1,const double obj2){ return vector(obj1)/=obj2; }

double dot_product (const vector& obj1, const vector& obj2){ return ((obj1.x*obj2.x) + (obj1.y*obj2.y)); }
double angle(const vector& obj1, const vector& obj2 ){
    return std::acos((dot_product(obj1,obj2)/(obj1.length()*obj2.length())));
}
double cross_product (const vector& obj1, const vector& obj2){return ((obj1.x*obj2.y)-(obj2.x*obj1.y)); }
bool collinear(const vector& obj1, const vector& obj2) { return (eq(cross_product(obj1, obj2), 0));}

class shape {
public:
    shape()= default;
    virtual ~shape() =default;

    virtual vector center() const= 0;

    virtual double perimeter() const= 0;
    virtual double area() const= 0;

    virtual bool operator==(const shape& obj) const= 0;
    virtual bool operator!=(const shape& obj) const = 0;
    virtual bool congruent_to(const shape& obj) const = 0;

    virtual void rotate(double angle) = 0;
    virtual void scale(double coefficient) = 0;
    virtual void translate(vector transform) = 0;
};


class circle : public shape{
    vector center_;
    double radius_;
public:

    ~circle() override = default;
    circle(vector center,double radius): center_(center),radius_(radius) {}
    circle()=default;

    double radius() const { return radius_; }
    vector center() const override {return center_; }
    double perimeter() const override{ return M_PI*2*radius_;}
    double area() const override{ return M_PI*radius_*radius_;}

    bool operator==(const shape& obj) const override{
        const circle* cast_check=dynamic_cast<const circle*>(&obj);
        bool val = (cast_check== nullptr) ? false :
                                            eq(center_.x,cast_check->center_.x) and eq(center_.y,cast_check->center_.y);
        return val;
    }
    bool operator!=(const shape& obj) const override{return !(*this==obj) ;}
    bool congruent_to(const shape& obj) const override{
        const circle* cast_check=dynamic_cast<const circle*>(&obj);
        bool val = (cast_check== nullptr) ? false : eq(radius_,cast_check->radius_);
        return val;
    }

    void rotate(double angle) override {}
    void scale (double coefficient) override{
        radius_*=std::fabs(coefficient);
    }
    void translate(vector transform) override{
        center_.x+=transform.x;
        center_.y+=transform.y;
    }

};


class polygon: public shape {
    std::vector<vector> vertices_;
public:

    ~polygon() override = default;
    polygon& operator=(const polygon& obj){
        vertices_=obj.vertices_;
        return *this;
    }
    polygon(const polygon& obj): vertices_(obj.vertices_){}
    polygon() = default;
    explicit polygon (std::vector<vector> _vertices_){
        vertices_=_vertices_;
        double area=0.0;
        size_t n=vertices_.size();
        for (size_t i=1;i<n;++i){
            if (i==n-1){
                area+=cross_product(vertices_[0],vertices_[i]);
                area+=cross_product(vertices_[i],vertices_[i-1]);
            }
            else{
                area+=cross_product(vertices_[i],vertices_[i-1]);
            }
        }
        if (area>0){
            std::vector<vector> copy_of_vertices;
            copy_of_vertices=vertices_;
            vertices_.clear();
            for (int i=copy_of_vertices.size()-1;i>=0;--i){
                vertices_.push_back(copy_of_vertices[i]);
            }
        }

    }

    const std::vector<vector>& get_vertices() const { return (vertices_); }
    int vertices_count()  { return vertices_.size() ;}
    double perimeter() const override {
        long double dist=0.0;
        int n=vertices_.size();
        for(size_t b=1;b<n;++b){
            if (b==n-1){
                dist += std::sqrt(std::pow((vertices_[b].x - vertices_[b-1].x), 2.0) +
                                  std::pow((vertices_[b].y - vertices_[b-1].y), 2.0));
                dist+=std::sqrt(std::pow((vertices_[n-1].x - vertices_[0].x),2.0)+
                                std::pow((vertices_[n-1].y - vertices_[0].y),2.0));
            }
            else {
                dist += std::sqrt(std::pow((vertices_[b].x - vertices_[b-1].x), 2.0) +
                                  std::pow((vertices_[b].y - vertices_[b-1].y), 2.0));
            }
        }
        return dist;
    }
    double area() const override {
        double area=0;
        size_t n=vertices_.size();
        for (size_t b=1;b<n;++b){
            if (b==n-1){
                area+=cross_product(vertices_[0],vertices_[n-1]);
                area+=cross_product(vertices_[b],vertices_[b-1]);
            }
            else{
                area+=cross_product(vertices_[b],vertices_[b-1]);
            }
        }
        area=std::fabs(area/(2.0));
        return area;
    }

    vector center() const override {
        double area=0.0;
        double weight;
        vector centroid(0,0);
        size_t n=vertices_.size();
        for (size_t b=1;b<n;++b){
            if (b==n-1){
                weight=cross_product(vertices_[b],vertices_[b-1]);
                area+=weight;
                centroid.x+=(vertices_[b].x+vertices_[b-1].x)*weight;
                centroid.y+=(vertices_[b].y+vertices_[b-1].y)*weight;
                weight=cross_product(vertices_[0],vertices_[n-1]);
                area+=weight;
                centroid.x+=(vertices_[0].x+vertices_[n-1].x)*weight;
                centroid.y+=(vertices_[0].y+vertices_[n-1].y)*weight;
            }
            else{
                weight=cross_product(vertices_[b],vertices_[b-1]);
                area+=weight;
                centroid.x+=(vertices_[b].x+vertices_[b-1].x)*weight;
                centroid.y+=(vertices_[b].y+vertices_[b-1].y)*weight;
            }
        }
        area*=0.5;
        centroid.x /= (6.0*area);
        centroid.y /= (6.0)*area;
        return centroid;
    }

    void rotate(double angle) override{
        vector centroid=center();
        for (auto & point : vertices_){
            point.x-=centroid.x;
            point.y-=centroid.y;
            double temp=point.x;
            point.x= std::cos(angle)*point.x - std::sin(angle)*point.y +centroid.x;
            point.y= std::cos(angle)*point.y + std::sin(angle)*temp +centroid.y;
        }
    }
    void scale(double coefficient) override{
        vector centroid=center();
        for (auto & point : vertices_){
            point.x-=centroid.x;
            point.y-=centroid.y;

            point.x=point.x*coefficient+centroid.x;
            point.y=point.y*coefficient+centroid.y;
        }
    }
    void translate(vector transform) override{
        for (auto & point : vertices_){
            point.x+=transform.x;
            point.y+=transform.y;
        }
    }

   ь
    bool operator==(const shape& obj) const override{
        const polygon* cast_check=dynamic_cast<const polygon*>(&obj);
        bool val= (cast_check== nullptr) ? false : (this->center()==cast_check->center());
        return val;
    }
    bool operator!=(const shape& obj) const override{ return !(*this==obj); }

};


class rectangle : public polygon {
    vector center_;
    double height_;
    double width_;
public:
    ~rectangle() override = default;
    rectangle()=default;
    rectangle(const vector& center,const double& height,const double& width ):
            center_(center),
            height_(height),
            width_(width),
            polygon (std::vector<vector>
                     {vector(center.x+width/2,center.y-height/2),
                      vector(center.x-width/2,center.y-height/2),
                      vector(center.x-width/2,center.y+height/2),
                      vector(center.x+width/2,center.y+height/2)}) {
    }

    double height() const {return height_ ;}
    double width() const {return width_ ;}


};


class square: public rectangle {
    vector center_;
    double side_;
public:
    ~square() override = default;
    square(vector center,double side): center_(center),side_(side),rectangle(center,side,side){}
    square()=default;

    double side() const { return  side_ ; }

    circle inscribed_circle() const { return circle(center_,side_/2) ; }
    circle circumscribed_circle() const { return circle(center_,(side_/std::sqrt(2.))); }
};

class triangle: public polygon {
    vector side_one_;
    vector side_two_;
    vector side_three_;
public:

    ~triangle() override = default;
    triangle(vector side_one,vector side_two,vector side_three):
                                          polygon (std::vector<vector>{side_one,side_two,side_three} ) ,
                                          side_one_(side_one) ,
                                          side_two_(side_two) ,
                                          side_three_(side_three) {}
    triangle() = default;

    circle circumscribed_circle() const{
        double product_length= (side_one_-side_two_).length() *
                               (side_two_-side_three_).length() * (side_three_-side_one_).length();
        double radius=product_length/(4*(this->area()));
        vector center(0,0);
        double denominator=2*(side_one_.x-side_two_.x)*(side_one_.y-side_three_.y)
                           -2*(side_one_.x-side_three_.x)*(side_one_.y-side_two_.y);
        center.x=( (side_one_.y-side_three_.y)* ( (side_one_.x*side_one_.x) + (side_one_.y*side_one_.y)
                                                  - (side_two_.x*side_two_.x) - (side_two_.y*side_two_.y) )
                   - (side_one_.y-side_two_.y)*( (side_one_.x*side_one_.x) + (side_one_.y*side_one_.y)
                   - (side_three_.x*side_three_.x) - (side_three_.y*side_three_.y) ) )/denominator;
        center.y=( (side_one_.x-side_two_.x)*( (side_one_.x*side_one_.x) +
                (side_one_.y*side_one_.y) - (side_three_.x*side_three_.x)
                - (side_three_.y*side_three_.y) ) - (side_one_.x-side_three_.x)*
                        ( (side_one_.x*side_one_.x) + (side_one_.y*side_one_.y) - (side_two_.x*side_two_.x) -
                        (side_two_.y*side_two_.y) ) )/denominator;
        return circle(center,radius);
    }

    circle inscribed_circle() const {
        double x1=(side_one_-side_two_).length()*side_three_.x;
        double x2=(side_two_-side_three_).length()*side_one_.x;
        double x3=(side_three_-side_one_).length()*side_two_.x;
        double y1=(side_one_-side_two_).length()*side_three_.y;
        double y2=(side_two_-side_three_).length()*side_one_.y;
        double y3=(side_three_-side_one_).length()*side_two_.y;
        vector center(0,0);
        double perimeter=this->perimeter();
        center.x=(x1+x2+x3)/(perimeter);
        center.y=(y1+y2+y3)/(perimeter);
        double radius= (2*(this->area()))/(perimeter);
        return (circle(center,radius));
    }
};
