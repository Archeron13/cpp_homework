
class circle : public shape{
    vector center_;
    double radius_;
public:

    ~circle() override = default;
    circle(vector a,double radius): center_(a),radius_(radius) {}
    circle()=default;

    double radius() const { return radius_; }
    vector center() const override {return center_; }
    double perimeter() const override{ return M_PI*2*radius_;}
    double area() const override{ return M_PI*radius_*radius_;}

    bool operator==( const shape& obj) const override{
        const circle* b=dynamic_cast<const circle*>(&obj);
        bool val = (b== nullptr) ? false : eq(center_.x,b->center_.x) and eq(center_.y,b->center_.y);
        return val;
    }
    bool operator!=(const shape& obj) const override{return !(*this==obj) ;}
    bool congruent_to(const shape& obj) const override{
        const circle* b=dynamic_cast<const circle*>(&obj);
        bool val = (b== nullptr) ? false : eq(radius_,b->radius_);
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