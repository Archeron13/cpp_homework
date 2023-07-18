
class triangle: public polygon{
    vector side_one_;
    vector side_two_;
    vector side_three_;
public:

    ~triangle() override = default;
    triangle(vector a,vector b,vector c): polygon (std::vector<vector>{a,b,c} ) , side_one_(a) , side_two_(b) , side_three_(c) {}
    triangle() = default;

    circle circumscribed_circle() const{
        double product_length= (side_one_-side_two_).length() * (side_two_-side_three_).length() * (side_three_-side_one_).length();
        double radius=product_length/(4*(this->area()));
        vector center(0,0);
        double denominator=2*(side_one_.x-side_two_.x)*(side_one_.y-side_three_.y)
                                    -2*(side_one_.x-side_three_.x)*(side_one_.y-side_two_.y);
        center.x=( (side_one_.y-side_three_.y)* ( (side_one_.x*side_one_.x) + (side_one_.y*side_one_.y)
                - (side_two_.x*side_two_.x) - (side_two_.y*side_two_.y) )
                - (side_one_.y-side_two_.y)*( (side_one_.x*side_one_.x) + (side_one_.y*side_one_.y)
                - (side_three_.x*side_three_.x) - (side_three_.y*side_three_.y) ) )/denominator;
        center.y=( (side_one_.x-side_two_.x)*( (side_one_.x*side_one_.x) + (side_one_.y*side_one_.y) - (side_three_.x*side_three_.x)
                - (side_three_.y*side_three_.y) ) - (side_one_.x-side_three_.x)*( (side_one_.x*side_one_.x) + (side_one_.y*side_one_.y)
                - (side_two_.x*side_two_.x) - (side_two_.y*side_two_.y) ) )/denominator;
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