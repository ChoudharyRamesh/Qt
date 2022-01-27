#include<iostream>
#include <sstream>

using namespace std;

int main()
{
    string s = "12345";
    stringstream geek(s);

    int x = 0;
    geek >> x;



    return 0;
}
