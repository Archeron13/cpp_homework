
class rectangle : public polygon{
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