
class interface{
public:
    int x;
    int y;

    interface(): x(0), y(0)  {}
    interface (&std::pair(int,int) a): x(a.first), y(a.second()) {}
    ~interface() = default;


};

class warrior : interface {


};

class witch : interface{

};

class jumper : interface{

};