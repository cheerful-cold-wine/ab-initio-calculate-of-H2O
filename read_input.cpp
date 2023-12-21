#include<iostream>
#include<fstream>
#include<filesystem>
#include<string>
using namespace std;

int main()
{
    string pwd = filesystem::current_path();
    ifstream basis;
    basis.open(pwd+"/input/basis",ios::in);
    if(basis.is_open()){
        
    }
    return 0;
}
