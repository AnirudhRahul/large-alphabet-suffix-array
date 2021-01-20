
#include "karkkainen_sanders.hpp"
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // int s[] = {2,1,4,4,1,4,4,1,3,3,1,0,0};
    // int n = 11;
    // int k = 4;
    // int s[] = {3,3,2,1,5,5,4,0,0,0};
    // int n = 7;
    // int k = 5;
    int n = 70000000;
    int k = 70000000;
    int* s = new int[n+3];
    for(int i=0; i<n; ++i){
      // if(i>n/2)
      //   s[i]=i;
      // else
        s[i]=k-i;
    }

    // int s[] = {2,2,2,2,2,0,0,0};
    // int n = 5;
    // int k = 2;
    int* sa = karkkainen_sanders_sa(s, n, k);


    delete[] s;
    for (int i = n-100; i < n; ++i)
        cout << sa[i] << " ";
    cout << endl;
    delete[] sa;
    cout<<"DONE"<<endl;
}
