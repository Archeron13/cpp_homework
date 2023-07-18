
class square: public rectangle{
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