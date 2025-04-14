#include <iostream>

using namespace std;



int main(){

int a = 2;

//a = (a = (a = 2 * a + 1) + 2) * 3 + a;
int temp1 = 2 * a + 1;
int temp2 = temp1 + 2;
int temp3 = temp2 * 3;
a = temp3 + temp2;
cout<<a<<endl;

}