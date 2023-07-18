

#include <iostream>
#include <array>

#ifndef RUBIKS_CUBE_SRC_RUBIKS_CUBE_H
#define RUBIKS_CUBE_SRC_RUBIKS_CUBE_H


class rubiks_cube {

public:
    enum color {
        e_white, e_red, e_green, e_orange, e_blue, e_yellow
    };
    enum side {
        e_top, e_front, e_left, e_back, e_right, e_bottom
    };
    enum direction {
        e_middle, e_equator, e_standing
    };

    rubiks_cube() {
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    if (i == 0) {
                        cube[i][j][k] = e_white;
                    } else if (i == 1) {
                        cube[i][j][k] = e_red;
                    } else if (i == 2) {
                        cube[i][j][k] = e_green;
                    } else if (i == 3) {
                        cube[i][j][k] = e_orange;
                    } else if (i == 4) {
                        cube[i][j][k] = e_blue;
                    } else if (i == 5) {
                        cube[i][j][k] = e_yellow;
                    }
                }
            }
        }

    };

    rubiks_cube(const rubiks_cube &other) = default;

    rubiks_cube &operator=(const rubiks_cube &other) = default;

    ~rubiks_cube() = default;



    void rotate_side(rubiks_cube::side side_to_rotate, int count) {
        int l=count;
        for (int f = 0; f < l; ++f) {
            color val[6];
            if (side_to_rotate == 0) {
                // e_top
                side s1 = e_front;
                side s2 = e_left;
                side s3 = e_back;
                side s4 = e_right;
                for (int i = 0; i < 4; ++i) {
                    if (i == 0) {
                        val[0] = cube[s1][0][0];
                        val[1] = cube[s1][0][1];
                        cube[s1][0][0] = cube[s4][0][0];
                        cube[s1][0][1] = cube[s4][0][1];
                    } else if (i == 1) {
                        val[2] = cube[s2][0][0];
                        val[3] = cube[s2][0][1];
                        cube[s2][0][0] = val[0];
                        cube[s2][0][1] = val[1];
                    } else if (i == 2) {
                        val[4] = cube[s3][0][0];
                        val[5] = cube[s3][0][1];
                        cube[s3][0][0] = val[2];
                        cube[s3][0][1] = val[3];
                    } else if (i == 3) {
                        cube[s4][0][0] = val[4];
                        cube[s4][0][1] = val[5];
                    }
                }
            } else if (side_to_rotate == 1) {
                // e_front
                side s1 = e_top;
                side s2 = e_right;
                side s3 = e_bottom;
                side s4 = e_left;
                for (int i = 0; i < 4; ++i) {
                    if (i == 0) {
                        val[0] = cube[s1][1][0];
                        val[1] = cube[s1][1][1];
                        cube[s1][1][0] = cube[s4][0][1];
                        cube[s1][1][1] = cube[s4][1][1];
                    } else if (i == 1) {
                        val[2] = cube[s2][0][0];
                        val[3] = cube[s2][1][0];
                        cube[s2][0][0] = val[0];
                        cube[s2][1][0] = val[1];
                    } else if (i == 2) {
                        val[4] = cube[s3][0][0];
                        val[5] = cube[s3][0][1];
                        cube[s3][0][0] = val[3];
                        cube[s3][0][1] = val[2];
                    } else if (i == 3) {
                        cube[s4][0][1] = val[4];
                        cube[s4][1][1] = val[5];
                    }
                }
            } else if (side_to_rotate == 2) {
                // e_left
                side s1 = e_top;
                side s2 = e_front;
                side s3 = e_bottom;
                side s4 = e_back;
                for (int i = 0; i < 4; ++i) {
                    if (i == 0) {
                        val[0] = cube[s1][0][0];
                        val[1] = cube[s1][1][0];
                        cube[s1][0][0] = cube[s4][0][1];
                        cube[s1][1][0] = cube[s4][1][1];
                    } else if (i == 1) {
                        val[2] = cube[s2][0][0];
                        val[3] = cube[s2][1][0];
                        cube[s2][0][0] = val[0];
                        cube[s2][1][0] = val[1];
                    } else if (i == 2) {
                        val[4] = cube[s3][0][0];
                        val[5] = cube[s3][1][0];
                        cube[s3][0][0] = val[2];
                        cube[s3][1][0] = val[3];
                    } else if (i == 3) {
                        cube[s4][0][1] = val[5];
                        cube[s4][1][1] = val[4];
                    }
                }
            } else if (side_to_rotate == 3) {
                //e_back
                side s1 = e_top;
                side s2 = e_left;
                side s3 = e_bottom;
                side s4 = e_right;
                for (int i = 0; i < 4; ++i) {
                    if (i == 0) {
                        val[0] = cube[s1][0][0];
                        val[1] = cube[s1][0][1];
                        cube[s1][0][0] = cube[s4][0][1];
                        cube[s1][0][1] = cube[s4][1][1];
                    }
                    else if (i == 1) {
                        val[2] = cube[s2][0][0];
                        val[3] = cube[s2][1][0];
                        cube[s2][0][0] = val[1];
                        cube[s2][1][0] = val[0];
                    }
                    else if (i == 2) {
                        val[4] = cube[s3][1][0];
                        val[5] = cube[s3][1][1];
                        cube[s3][1][0] = val[2];
                        cube[s3][1][1] = val[3];
                    }
                    else if (i == 3) {
                        cube[s4][0][1] = val[5];
                        cube[s4][1][1] = val[4];
                    }
                }
            } else if (side_to_rotate == 4) {
                //e_right
                side s1 = e_front;
                side s2 = e_top;
                side s3 = e_back;
                side s4 = e_bottom;
                for (int i = 0; i < 4; ++i) {
                    if (i == 0) {
                        val[0] = cube[s1][0][1];
                        val[1] = cube[s1][1][1];
                        cube[s1][0][1] = cube[s4][0][1];
                        cube[s1][1][1] = cube[s4][1][1];
                    } else if (i == 1) {
                        val[2] = cube[s2][0][1];
                        val[3] = cube[s2][1][1];
                        cube[s2][0][1] = val[0];
                        cube[s2][1][1] = val[1];
                    } else if (i == 2) {
                        val[4] = cube[s3][0][0];
                        val[5] = cube[s3][1][0];
                        cube[s3][0][0] = val[3];
                        cube[s3][1][0] = val[2];
                    } else if (i == 3) {
                        cube[s4][0][1] = val[5];
                        cube[s4][1][1] = val[4];
                    }
                }
            } else if (side_to_rotate == 5) {
                //e_bottom
                side s1 = e_front;
                side s2 = e_right;
                side s3 = e_back;
                side s4 = e_left;
                for (int i = 0; i < 4; ++i) {
                    if (i == 0) {
                        val[0] = cube[s1][1][0];
                        val[1] = cube[s1][1][1];
                        cube[s1][1][0] = cube[s4][1][0];
                        cube[s1][1][1] = cube[s4][1][1];
                    } else if (i == 1) {
                        val[2] = cube[s2][1][0];
                        val[3] = cube[s2][1][1];
                        cube[s2][1][0] = val[0];
                        cube[s2][1][1] = val[1];
                    } else if (i == 2) {
                        val[4] = cube[s3][1][0];
                        val[5] = cube[s3][1][1];
                        cube[s3][1][0] = val[2];
                        cube[s3][1][1] = val[3];
                    } else if (i == 3) {
                        cube[s4][1][0] = val[4];
                        cube[s4][1][1] = val[5];
                    }
                }
            }
        }
    }

    void rotate_cube(direction direction_to_rotate, int count) {
        for (int n=0;n<count;++n){
            if (direction_to_rotate==0){
                std::cout << "CALLED";
                rotate_side(e_left,3);
                rotate_side(e_right,1);
            }
            else if(direction_to_rotate==1){
                std::cout << "STANDINGCALLED";
                rotate_side(e_top,1);
                rotate_side(e_bottom,3);;
            }
            else if (direction_to_rotate==2){
                std::cout << "2 G CALLED";
                rotate_side(e_front,1);
                rotate_side(e_back,3);
            }
        }

        }
    const std::array<color, 4> &get_side(const rubiks_cube::side side_to_get) const {
        std::array<color, 4> *val = new std::array<color, 4>;
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                if (k == 0 and j == 0) {
                    (*val)[0] = cube[side_to_get][j][k];
                } else if (k == 1 and j == 0) {
                    (*val)[1] = cube[side_to_get][j][k];
                } else if (k == 0 and j == 1) {
                    (*val)[2] = cube[side_to_get][j][k];
                } else if (k == 1 and j == 1) {
                    (*val)[3] = cube[side_to_get][j][k];
                }
            }
        }
        return *val;
    }
private:
    color cube[6][2][2];


};

#endif /// RUBIKS_CUBE_SRC_RUBIKS_CUBE_H.



int main() {
    /*
    rubiks_cube obj;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                    std::cout << obj.cube[i][j][k] <<" ";
            }

        }
    }
    std::cout << std::endl;
    */

    rubiks_cube obj;
    std::array<rubiks_cube::color,4> abc;
    obj.rotate_side(rubiks_cube::side::e_top,3);
    for (int i=0;i<6;++i) {
        if (i==0){
            abc= obj.get_side(rubiks_cube::side::e_front);
        }
        else if(i==1){
            abc= obj.get_side(rubiks_cube::side::e_left);
        }
        else if (i==2){
            abc= obj.get_side(rubiks_cube::side::e_back);;
        }
        else if (i==3){
            abc= obj.get_side(rubiks_cube::side::e_right);
        }
        else if (i==4){
            abc=obj.get_side(rubiks_cube::side::e_top);
        }
        else if (i==5){
            abc=obj.get_side(rubiks_cube::side::e_bottom);
        }
          for (int f=0;f<4;++f){
              if (abc[f]==0){
                  std::cout << "w " ;
              }
              else if (abc[f]==1){
                  std::cout << "r ";
              }
              else if (abc[f]==2){
                  std::cout << "g ";
              }else if (abc[f]==3){
                  std::cout << "o ";
              }
              else if (abc[f]==4){
                  std::cout << "b ";
              }
              else if (abc[f]==5){
                  std::cout << "y ";
              }
          }
        std::cout << std::endl;
    }

}