#include<iostream>
#include<fstream>
#include<vector>
#include<map>

#include <sys/types.h>
#include <unistd.h>

#define fori(i,n) for(int i = 0; i < n; i++)

using namespace std;

// #define GROUP_SIZE "5"


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


int main(int argc, char *argv[]) {

    string GROUP_SIZE = "5";

    // get group size from arguments
    if(argc > 1){
        GROUP_SIZE = argv[1];
    }


    string requiredEdgeFilename = "../data-intermediate/edges" + GROUP_SIZE + ".csv";
    string requiredFriendFilename = "../data-intermediate/checked-friends" + GROUP_SIZE + ".csv";

    // convert string to char array
    char *requiredEdgeFilenameChar = new char[requiredEdgeFilename.size() + 1];
    copy(requiredEdgeFilename.begin(), requiredEdgeFilename.end(), requiredEdgeFilenameChar);
    requiredEdgeFilenameChar[requiredEdgeFilename.size()] = '\0';

    char *requiredFriendFilenameChar = new char[requiredFriendFilename.size() + 1];
    copy(requiredFriendFilename.begin(), requiredFriendFilename.end(), requiredFriendFilenameChar);
    requiredFriendFilenameChar[requiredFriendFilename.size()] = '\0';



    // check if the following file exists: data-intermediate/edges5.csv or data-intermediate/edges10.csv or data-intermediate/edges15.csv
    if(access(requiredEdgeFilenameChar, F_OK) != -1){
        // file exists
        cout << "File exists" << endl;
    }
    else{
        // file doesn't exist
        cout << "Pre-processed file doesn't exist" << endl;
        cout << "Running edges pre-processor..." << endl;
        // run the pre-processor
        system("g++ ./pre-processors/edges.cpp -o ./pre-processors/edges");
        system("./pre-processors/edges " + GROUP_SIZE);
    }

    // check if the following file exists: data-intermediate/checked-friends5.csv or data-intermediate/checked-friends10.csv or data-intermediate/checked-friends15.csv
    if(access(requiredFriendFilenameChar, F_OK) != -1){
        // file exists
        cout << "File exists" << endl;
    }
    else{
        // file doesn't exist   
        cout << "File doesn't exist" << endl;
        cout << "Running friend pre-processor..." << endl;
        // run the pre-processor
        system("g++ ./pre-processors/friend-finder.cpp -o ./pre-processors/friend-finder");
        system("./pre-processors/friend-finder");
    }

    // read file edges15.csv
    ifstream file(requiredEdgeFilename);


    // write output to file data-intermediate/edges5.csv
    ofstream outfile("../data-intermediate/edges15.csv");

    string str;
    string str1, str2;


    return 0;
}