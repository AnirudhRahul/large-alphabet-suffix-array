
#include "karkkainen_sanders.hpp"
#include <iostream>
#include <cmath>

using namespace std;
#include <cstring>

int main() {
    // int s[] = {2,1,4,4,1,4,4,1,3,3,1,0,0};
    // int n = 11;
    // int k = 4;
    // int s[] = {3,3,2,1,5,5,4,0,0,0};
    // int n = 7;
    // int k = 5;
    int n = 70000000;
    int k = 1;
    int* s = new int[n+3];
    s[n]=s[n+1]=s[n+2]=0;
    for(int i=0; i<n; ++i){
      // if(i>n/2)
      //   s[i]=i;
      // else
        s[i]=1;
    }
    int* sa = karkkainen_sanders_sa(s, n, k);

    for (int i = max(0,n-100); i < n; ++i)
          cout << sa[i] << " ";

    cout << endl;
    delete[] sa;

    cout<<"DONE"<<endl;
}
