#include <iostream>

using namespace std;

int main()

{

     int radius;

     cout<<"Please enter the radius!\n";

     cin>>radius;//断点1

     cout<<"The radius is:"<<radius<<'\n';    

     cout<<"PI is:"<<3.14<<'\n';

     cout<<"Please enter a different radius!\n"; 

     cin>>radius;//断点2

     cout<<"Now the radius is changed to:"<<radius<<'\n';

     return 0;

}