#include<iostream>
#include<fstream>
#include<filesystem>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

vector<string> read_file(string file_name){
    vector<string> file_str;
    string pwd = filesystem::current_path();
    ifstream file;
    file.open(pwd+"/input/"+file_name,ios::in);
    if(file.is_open()){
        string line;
        while(getline(file,line)){
            file_str.push_back(line);
        }
        file.close();
    } else {
        cerr<< "unable to open file "<< file_name << endl;
    }
    return file_str;
}

vector<string> split_str_by_space(string str){
    vector<string> result;
    istringstream iss(str);
    for (string word; iss>>word;){
        result.push_back(word);
    }
    return result;
}

int main()
{   
    vector<string> basis_str = read_file("basis");
    for (string str : basis_str){
        if (str=="****") continue;
        vector<string> str_= split_str_by_space(str);
        for (int i=0; i<str_.size(); i++){
            cout<< str_[i]<<endl;
        }
    }
    vector<string> structure_str = read_file("structure.xyz");
/*    
    for(const auto& str : basis_str){
        cout<< str<<endl;
    }
    for(const auto& str : structure_str) {
        cout<< str <<endl;
    }
*/
    return 0;
}
