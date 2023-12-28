#include<iostream>
#include<fstream>
#include<filesystem>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

vector<string> read_file(string file_name) {
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

vector<string> split_str_by_space(string str_in) {
    vector<string> str_out;
    istringstream iss(str_in);
    for (string word; iss>>word;){
        str_out.push_back(word);
    }
    return str_out;
}

class ATOM {
    public:
        string element;
        int atomic_num;
        double atomic_mass;
        double cart_coor[3];

        void print_atom() {
            cout<< "element:\t"<<element <<endl;
            cout<< "atomic number:\t"<<atomic_num <<endl;
            cout<< "atomic mass:\t"<<atomic_mass <<endl;
            cout<< "cartesian coordinate:"<<endl;
            cout<< "x="<<cart_coor[0] <<"\t";
            cout<< "y="<<cart_coor[1] <<"\t";
            cout<< "z="<<cart_coor[2] <<endl<<endl;
        }
};

void store_input(){   
    // deal with the cartesian coordinates
    vector<string> structure_str = read_file("structure.xyz");
    ATOM atom[structure_str.size()]; 
    for (int i=0; i<structure_str.size(); i++) {
        vector<string> structure_split_str = split_str_by_space(structure_str[i]);
        atom[i].element = structure_split_str[0];
        for (int j=0; j<3; j++) {
            atom[i].cart_coor[j] = stod(structure_split_str[j+1]);
        }
        // for convenience, only H and O here
        if(atom[i].element == "H") {
            atom[i].atomic_num=1;
            atom[i].atomic_mass=1.00797;
        } else {
            atom[i].atomic_num=8;
            atom[i].atomic_mass=15.9994;
        }
    }    
    for (int i=0; i<3; i++) atom[i].print_atom();// for checking

    // deal with the basis set (cc-pVTZ of H2O here)
    vector<string> basis_str = read_file("basis");
    vector<string> basis_split_str;
    for (string str_line : basis_str){
        vector<string> str_word= split_str_by_space(str_line);
        for (int i=0; i<str_word.size(); i++){
            basis_split_str.push_back(str_word[i]);
        }
        if (str_line=="****") continue;
    }
}

int main()
{
    store_input();
    return 0;
}
