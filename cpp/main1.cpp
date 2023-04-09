#include<iostream>
#include<fstream>

#define fori(i,n) for(int i = 0; i < n; i++)

using namespace std;

#define GROUP_SIZE 5


long long convert_id_to_int(string &str){
    // remove characters from the string
    int strlen = str.size();

    string newstr = "";
    fori(i,strlen){
        if(str[i] >= 48 && str[i] <= 57){
            newstr += str[i];
        }
    }

    long long id_int = stoll(newstr);
    return(id_int);
}


int main(){
    // read file edges15.csv
    ifstream file("../edges15.csv");


    // write output to file data-intermediate/edges5.csv
    ofstream outfile("../data-intermediate/edges15.csv");

    string str;
    string str1, str2;
    while (getline(file, str))
    {
        // detect and ignore header
        if(str[0] == 'S' or str[0] == 's'){
            continue;
        }
        // split string into 2 by comma
        int pos = str.find(",");
        str1 = str.substr(0, pos);
        str2 = str.substr(pos+1, str.size());



        // cout << convert_id_to_int(str1) << "," << convert_id_to_int(str2) << endl;


        // write to file
        outfile << convert_id_to_int(str1) << "," << convert_id_to_int(str2) << endl;
    }

    return 0;
}