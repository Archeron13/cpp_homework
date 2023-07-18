#include <vector>

struct no_such_move: std::exception{
    const char * what () const throw ()
    {
        return "Move not valid";
    }
};

bool find(std::vector<std::pair<int,int> > vec, std::pair<int,int> a){
    bool val=false;
    for (auto x: vec){
        if (x==a){
            val=true;
        }
    }
    return val;
}

class figure {
public:
    std::pair<int,int> pos;

    figure(): pos(0,0)  {}
    figure (const std::pair<int,int> a ) : pos(a) {}
    ~figure() = default;

    figure(const figure& obj) = default;
    figure& operator=(const figure& obj) = default;

    const std::pair<int, int>& get_coordinates () const { return pos; }

    virtual std::vector<std::pair<int, int> > get_possible_moves () const = 0;
    virtual void make_move(const std::pair<int, int>& move)  = 0;


};

class warrior : public figure {
public:
    warrior() : figure() {}
    warrior(const std::pair<int,int> a) : figure(a) {}

    std::vector<std::pair<int, int> > get_possible_moves () const {
        std::vector<std::pair<int,int> > moves;
        int x = this->pos.first;
        int y = this->pos.second;
        moves.push_back( std::pair<int,int>(x+1,y) );
        moves.push_back( std::pair<int,int>(x-1,y) );
        moves.push_back( std::pair<int,int>(x,y+1));
        moves.push_back( std::pair<int,int>(x,y-1));
        moves.push_back( std::pair<int,int>(x+1,y+1) ) ;
        moves.push_back( std::pair<int,int>(x-1,y-1));
        moves.push_back( std::pair<int,int>(x+1,y-1));
        moves.push_back( std::pair<int,int>(x-1,y+1));
        return moves;
    }
    void make_move(const std::pair<int, int>& move) {
        std::vector<std::pair<int,int> > moves = this->get_possible_moves();
        if (find(moves,move)) {
            this->pos.first=move.first;
            this->pos.second=move.second;
            return ;
        }
       throw (no_such_move());
    }
};

class witch : public figure{
public:
    witch() : figure() {}
    witch(const std::pair<int,int> a) : figure(a) {}

    std::vector<std::pair<int, int> > get_possible_moves () const {
        std::vector<std::pair<int,int> > moves;
        int x = this->pos.first;
        int y = this->pos.second;
        moves.push_back( std::pair<int,int>(x+2,y) );
        moves.push_back( std::pair<int,int>(x+1,y) );
        moves.push_back( std::pair<int,int>(x,y+2) );
        moves.push_back( std::pair<int,int>(x,y+1) );
        moves.push_back( std::pair<int,int>(x-2,y) ) ;
        moves.push_back( std::pair<int,int>(x-1,y) );
        moves.push_back( std::pair<int,int>(x,y-2) );
        moves.push_back( std::pair<int,int>(x,y-1) );
        return moves;

    }
    void make_move(const std::pair<int, int>& move) {
        std::vector<std::pair<int,int> > moves = this->get_possible_moves();
        if (find(moves,move)){
            this->pos.first=move.first;
            this->pos.second=move.second;
            return ;

        }
        throw (no_such_move());
    }
};

class jumper : public figure{
public:
    jumper() : figure() {}
    jumper(const std::pair<int,int> a) : figure(a) {}

    std::vector<std::pair<int, int> > get_possible_moves () const {
        std::vector<std::pair<int,int> > moves;
        int x = this->pos.first;
        int y = this->pos.second;
        moves.push_back( std::pair<int,int>(x+1,y+2) );
        moves.push_back( std::pair<int,int>(x+2,y+1) );
        moves.push_back( std::pair<int,int>(x+2,y-1) );
        moves.push_back( std::pair<int,int>(x+1,y-2) );
        moves.push_back( std::pair<int,int>(x-1,y-2) ) ;
        moves.push_back( std::pair<int,int>(x-2,y-1 ) );
        moves.push_back( std::pair<int,int>(x-2,y+1) );
        moves.push_back( std::pair<int,int>(x-1,y + 2) );
        return moves;

    }

    void make_move(const std::pair<int, int>& move) {
        std::vector<std::pair<int,int> > moves = this->get_possible_moves();
        if (find(moves,move)){
            this->pos.first=move.first;
            this->pos.second=move.second;
            return ;

        }
        throw (no_such_move());
    }
};