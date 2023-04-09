#include<iostream>
#include<fstream>
#include<vector>
#include<map>

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

// map to store the edges
map<pair<long long, long long>, int> edge_map;


int main(){
    // read file edges15.csv
    ifstream file("../../friends15.csv");


    // write output to file data-intermediate/edges5.csv
    ofstream outfile("../../data-intermediate/checked-friends15.csv");

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
        
        long long id1 = convert_id_to_int(str1);
        long long id2 = convert_id_to_int(str2);

        // check if the edge is already present
        if(edge_map.find({id1, id2}) != edge_map.end() or edge_map.find({id2, id1}) != edge_map.end()){
            cout << "Duplicate edge: " << id1 << " " << id2 << endl;
            // write to file
            outfile << id1 << "," << id2 << endl;
        }
        else{
            edge_map[{id1, id2}] = 1;
        } 

        // write to file
    }

    return 0;
}