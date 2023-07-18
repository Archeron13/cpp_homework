
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
        for (size_t b=1;b<n;++b){
            if (b==n-1){
                area+=cross_product(vertices_[0],vertices_[b]);
                area+=cross_product(vertices_[b],vertices_[b-1]);
            }
            else{
                area+=cross_product(vertices_[b],vertices_[b-1]);
            }
        }
        if (area>0){
            std::vector<vector> b;
            b=vertices_;
            vertices_.clear();
            for (int i=b.size()-1;i>=0;--i){
                vertices_.push_back(b[i]);
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
                dist += std::sqrt(std::pow((vertices_[b].x - vertices_[b-1].x), 2.0) + std::pow((vertices_[b].y - vertices_[b-1].y), 2.0));
                dist+=std::sqrt(std::pow((vertices_[n-1].x - vertices_[0].x),2.0)+std::pow((vertices_[n-1].y - vertices_[0].y),2.0));
            }
            else {
                dist += std::sqrt(std::pow((vertices_[b].x - vertices_[b-1].x), 2.0) + std::pow((vertices_[b].y - vertices_[b-1].y), 2.0));
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
        vector a=center();
        for (auto & point : vertices_){
            point.x-=a.x;
            point.y-=a.y;
            double temp=point.x;
            point.x= std::cos(angle)*point.x - std::sin(angle)*point.y +a.x;
            point.y= std::cos(angle)*point.y + std::sin(angle)*temp +a.y;
        }
    }
    void scale(double coefficient) override{
        vector a=center();
        for (auto & point : vertices_){
            point.x-=a.x;
            point.y-=a.y;

            point.x=point.x*coefficient+a.x;
            point.y=point.y*coefficient+a.y;
        }
    }
    void translate(vector transform) override{
        for (auto & point : vertices_){
            point.x+=transform.x;
            point.y+=transform.y;
        }
    }

    bool ccheck(const polygon& obj){
        polygon b=obj;
        polygon a=*this;
        size_t n=b.vertices_.size();
        std::vector<int> ival;
        vector bs1=b.vertices_[1]-b.vertices_[0];
        vector bs2=b.vertices_[2]-b.vertices_[1];
        vector bs3=b.vertices_[0]-b.vertices_[n-1];
        double angbs1=angle(bs1,bs2);
        double angbs2=angle(bs1,bs3);
        for (size_t i=1;i<n;++i) {
            if (i != n - 1) {
                if (eq(bs1.length(),(a.vertices_[i] - a.vertices_[i - 1]).length())) {
                    ival.push_back(i);
                }
            }
            else{
                if (eq(bs1.length(),(a.vertices_[i] - a.vertices_[i - 1]).length())) {
                    ival.push_back(i);
                }
                if (eq(bs1.length(),(a.vertices_[0] - a.vertices_[i]).length())) {
                    ival.push_back(0);
                }
            }
        }
        for (auto i: ival ){
            vector as=a.vertices_[i%n] - a.vertices_[(i-1+n)%n];
            vector asR=a.vertices_[(i+1)%n]-a.vertices_[(i+n)%n];
            double angR=angle(as,asR);
            double mangR=std::fmod((2*M_PI -angR),(2*M_PI));
            if (eq(angbs1,angR) or eq(angbs1,mangR) or eq(std::fabs(angbs1),std::fabs(angR))){
                for (size_t l=1;l<b.vertices_.size();++l){
                    vector sb =(b.vertices_[l]-b.vertices_[l-1]);
                    vector sa=(a.vertices_[(i+l-1)%n]-a.vertices_[(i+l-2+n)%n]);
                    double asb=angle(b.vertices_[l]-b.vertices_[l-1],b.vertices_[(l+1)%n]-b.vertices_[l]);
                    double asa=angle(a.vertices_[(i+l-1)%n]-a.vertices_[(i+l-2+n)%n],a.vertices_[(i+l)%n]-a.vertices_[(i+l-1)%n]);
                    double masa=std::fmod((2*M_PI - asa),(2*M_PI));
                    if (!eq(sb.length(),sa.length())){
                        break;
                    }
                    if (!(eq(asb,asa) or eq(asb,masa))){
                        break;
                    }
                    if (l==b.vertices_.size()-1){
                        vector sb =(b.vertices_[0]-b.vertices_[l]);
                        vector sa=(a.vertices_[(i+l)%n]-a.vertices_[(i+l-1)%n]);
                        if (!eq(sb.length(),sa.length())){
                            break;
                        }
                        return true;
                    }
                }
            }
            else if ( (eq(angbs2,angR) or eq(angbs2,mangR) or eq(std::fabs(angbs2),std::fabs(angR)))){
                for (size_t l=1;l<n;l++){
                    vector sb =(b.vertices_[l]-b.vertices_[l-1]);
                    vector sa=(a.vertices_[(i-l+1+n)%n]-a.vertices_[(i-l+n)%n]);
                    double asb=angle(b.vertices_[l]-b.vertices_[l-1],b.vertices_[(l+1)%n]-b.vertices_[l]);
                    double asa=angle(a.vertices_[(i-l+1+n)%n]-a.vertices_[(i-l+n)%n],a.vertices_[(i-l+n)%n]-a.vertices_[(i-l+n-1)%n]);
                    double masa=std::fmod((2*M_PI - asa),(2*M_PI));
                    if (!eq(sb.length(),sa.length())){
                        break;
                    }
                    if (!(eq(asb,asa) or eq(asb,masa) or eq(std::fabs(asb),std::fabs(asa)) )){
                        break;
                    }
                    if (l==b.vertices_.size()-1){
                        vector sb =(b.vertices_[0]-b.vertices_[l]);
                        vector sa=(a.vertices_[(i-l+n)%n]-a.vertices_[(i-l+n-1)%n]);
                        if (!eq(sb.length(),sa.length())){
                            break;
                        }
                        return true;
                    }
                }
            }
        }
        return false;
    }
    bool congruent_to(const shape& obj) const override{
        const polygon* b=dynamic_cast<const polygon*>(&obj);
        polygon c=dynamic_cast<const polygon&>(obj);
        polygon a=*this;
        bool val= (b== nullptr) ? false : (c.ccheck(a));
        return (val);
    }
    bool operator==(const shape& obj) const override{
        const polygon* b=dynamic_cast<const polygon*>(&obj);
        bool val= (b== nullptr) ? false : (this->center()==b->center());
        return val;
    }
    bool operator!=(const shape& obj) const override{ return !(*this==obj); }

};

