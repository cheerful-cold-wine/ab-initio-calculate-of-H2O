#include<iostream>
#include<fstream>
#include<sstream>
#include<filesystem>
#include<string>
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

struct ATOM_INFO {
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

struct BASIS_INFO {
    string element;
    int atomic_num;
    int max_l;//max_l + 1 = number of shell

    void print_basis() {
        cout<< "element:\t"<<element <<endl;
        cout<< "atomic number:\t"<<atomic_num <<endl;
        cout<< "max angular momentum: \t"<< max_l<<endl;
    }
};

struct SHELL_INFO {
    string sign;
    int ang_mom; 
    int num_pGTO;// primitive GTO
    int num_cGTO;// contraction GTO
    double* exp_pGTO;
    double* coef_LC;// linear combination

    void check_angmom() {
        cout << "angular momentum :";
        if     (sign=="S" and ang_mom==0) cout<< "S"<<endl;
        else if(sign=="P" and ang_mom==1) cout<< "P"<<endl;
        else if(sign=="D" and ang_mom==2) cout<< "D"<<endl;
        else if(sign=="F" and ang_mom==3) cout<< "F"<<endl;
        else cout<< "unknown"<<endl;
    }
};

void store_input(){   
    // deal with the cartesian coordinates
    vector<string> structure_str = read_file("structure.xyz");
    ATOM_INFO atom[structure_str.size()]; 
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
    //for (int i=0; i<3; i++) atom[i].print_atom();// for checking

    // deal with the basis set (cc-pVTZ of H2O here)
    vector<string> basis_str = read_file("basis");
    vector<string> basis_split_str;
    for (string str_line : basis_str){
        vector<string> str_word= split_str_by_space(str_line);
        for (int i=0; i<str_word.size(); i++){
            basis_split_str.push_back(str_word[i]);
        }
    }

    vector<int> star_position;// the start and end of one basis 
    for (int i=0; i<basis_split_str.size(); i++){
        if(basis_split_str[i]=="****") {
            star_position.push_back(i);
        }
    }

    BASIS_INFO diff_basis[star_position.size()-1];
    for (int i=0; i<star_position.size()-1; i++){
        int i_start = star_position[i]+1;
        //int i_end = star_position[i+1]-1;
        diff_basis[i].element    = basis_split_str[i_start];
        diff_basis[i].atomic_num = stoi(basis_split_str[i_start+1]);
        diff_basis[i].max_l      = stoi(basis_split_str[i_start+2]);
        // 
        int j_start = i_start +3;
        vector<SHELL_INFO> diff_shell;
        for (int j=0; j<diff_basis[i].max_l+1; j++){
            SHELL_INFO one_shell;
            // one_shell.sign = basis_split_str[j_start];
            one_shell.ang_mom = j;
            // one_shell.check_angmom();
            one_shell.num_pGTO = stoi(basis_split_str[j_start+1]);
            one_shell.num_cGTO = stoi(basis_split_str[j_start+2]);
            one_shell.exp_pGTO = new double[one_shell.num_pGTO];
            one_shell.coef_LC  = new double[one_shell.num_pGTO*one_shell.num_cGTO];
            for (int k=0; k<one_shell.num_pGTO; k++){
                one_shell.exp_pGTO[k] = stod(basis_split_str[j_start +3 +k]);
                //cout<< one_shell.exp_pGTO[k]<<endl;
            }
            for (int l=0; l<one_shell.num_pGTO*one_shell.num_cGTO; l++){
                one_shell.coef_LC[l] = stod(basis_split_str[j_start +3 +one_shell.num_pGTO +l]);
                //cout<< one_shell.coef_LC[l]<<endl;
            }
            //
            diff_shell.push_back(one_shell);
            j_start = j_start +3 +one_shell.num_pGTO*(one_shell.num_cGTO +1);
        }
    }
    
    /* check
    for (int i=0; i<2;i++){
        diff_basis[i].print_basis();
    }
    */
}

int main()
{
    store_input();
    return 0;
}
