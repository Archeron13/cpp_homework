#include <iostream>

int main() {
    int n=0,f=1;
    std::cin >> n;
    int arr[n];
    for (int i=n;i>=1;--i) {
        arr[f] = i;
        ++f;
    }
    //for (int  x=1;x<=n;++x)
      //  std::cout << arr[x] ;
    for (int y=1;y<=n;++y){
        if (y==1){

        }
        else {
            for (int c = 1; c <= n; ++c) {
                if (y>c){
                    arr[c]-=1;
                }
                else if (y<=c){
                    arr[c]+=1;
                }
            }
        }



        for (int  x=1;x<=n;++x){
            std::cout << arr[x] << " " ;
        }
        std::cout << std::endl;
    }

}
