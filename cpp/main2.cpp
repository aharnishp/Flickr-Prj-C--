#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<set>

#define fori(i,n) for(int i = 0; i < n; i++)

#if defined(__unix__) || defined(__APPLE__)
    #define is_OS_unix 1
    #include<unistd.h>
    #include<sys/types.h>
#elif defined(_WIN32) || defined(WIN32)
    #define is_OS_unix 0
    #include<windows.h>
#endif


using namespace std;


// Global variables
map<pair<long long, long long>, int> edge_map;
map<pair<long long, long long>, int> friend_map;
long max_edge_weight = 0;

// map storing union of friends and edges
map<pair<long long, long long>, int> union_map;

// map storing intersection of friends and edges
map<pair<long long, long long>, int> intersection_map;

// map storing the edge by weights
map<int,set<pair<long long,long long>>> edge_by_weight_map;

// int storing the number of common friends
int common_friends = 0;

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

// function to pre-process the file
int friend_processor(string fileSuffix) {

    string GROUP_SIZE = fileSuffix;

    #ifdef is_OS_unix
        string requiredOutputFilename = "../data-intermediate/checked-friends" + GROUP_SIZE + ".csv";
        string requiredInputFileName = "../friends" + GROUP_SIZE + ".csv";
    #else
        string requiredOutputFilename = "..\\data-intermediate\\checked-friends" + GROUP_SIZE + ".csv";
        string requiredInputFileName = "..\\friends" + GROUP_SIZE + ".csv";
    #endif

        // convert string to char array
    char *requiredOutputFilenameChar = new char[requiredOutputFilename.size() + 1];
    copy(requiredOutputFilename.begin(), requiredOutputFilename.end(), requiredOutputFilenameChar);
    requiredOutputFilenameChar[requiredOutputFilename.size()] = '\0';

    char *requiredInputFileNameChar = new char[requiredInputFileName.size() + 1];
    copy(requiredInputFileName.begin(), requiredInputFileName.end(), requiredInputFileNameChar);
    requiredInputFileNameChar[requiredInputFileName.size()] = '\0';


    // check if the required input file exists
    if(access(requiredInputFileNameChar, F_OK) == -1){
        cout << "Required input file does not exist" << endl;
        cout << "Filename: '" << requiredInputFileNameChar << "'" << endl;
        return -1;
    }

    
    // read file edges15.csv
    ifstream file(requiredInputFileNameChar);


    // write output to file data-intermediate/edges5.csv
    ofstream outfile(requiredOutputFilenameChar);

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
        if(friend_map.find({id1, id2}) != friend_map.end() or friend_map.find({id2, id1}) != friend_map.end()){
            cout << "Duplicate edge: " << id1 << " " << id2 << endl;
            // write to file
            outfile << id1 << "," << id2 << endl;
            common_friends++;
        }
        else{
            friend_map[{id1, id2}] = 1;
        } 
        
    }

    outfile.close();
    file.close();

    // destroy the char array
    delete[] requiredOutputFilenameChar;
    delete[] requiredInputFileNameChar;

    // remove all elements from the map with value 2
    for(auto it = friend_map.begin(); it != friend_map.end();){
        if(it->second == 2){
            it = friend_map.erase(it);
        }
        else{
            it++;
        }
    }

    return 1;
}



int read_friend(string fileSuffix){
    
    string GROUP_SIZE = fileSuffix;

    #ifdef is_OS_unix
        string requiredInputFileName = "../data-intermediate/checked-friends" + GROUP_SIZE + ".csv";
    #else
        string requiredInputFileName = "..\\data-intermediate\\checked-friends" + GROUP_SIZE + ".csv";
    #endif

    // convert string to char array
    char *requiredInputFileNameChar = new char[requiredInputFileName.size() + 1];
    copy(requiredInputFileName.begin(), requiredInputFileName.end(), requiredInputFileNameChar);
    requiredInputFileNameChar[requiredInputFileName.size()] = '\0';

    // open file
    ifstream file(requiredInputFileNameChar);

    string str;
    string str1, str2;
    while (getline(file, str)) {
        // split string into 2 by comma
        int pos = str.find(",");
        str1 = str.substr(0, pos);
        str2 = str.substr(pos+1, str.size());
        
        long long id1 = convert_id_to_int(str1);
        long long id2 = convert_id_to_int(str2);

        // as the file is already processed, we can directly add the edge to the map
        friend_map[{id1, id2}] = 1;
        common_friends++;
    }

    file.close();

    // destroy the char array
    delete[] requiredInputFileNameChar;

    return 1;
}

int read_edge(string fileSuffix){
    
    string GROUP_SIZE = fileSuffix;

    #ifdef is_OS_unix
        string requiredInputFileName = "../data-intermediate/weighted-edges" + GROUP_SIZE + ".csv";
    #else
        string requiredInputFileName = "..\\data-intermediate\\weighted-edges" + GROUP_SIZE + ".csv";
    #endif

    // convert string to char array
    char *requiredInputFileNameChar = new char[requiredInputFileName.size() + 1];
    copy(requiredInputFileName.begin(), requiredInputFileName.end(), requiredInputFileNameChar);
    requiredInputFileNameChar[requiredInputFileName.size()] = '\0';

    // open file
    ifstream file(requiredInputFileNameChar);

    string str;
    string str1, str2,str3;
    while (getline(file, str)) {
        // format of edge file = id1,id2,weight
        // split string into 3 by comma
        int pos1 = str.find(",");
        int pos2 = str.find(",", pos1+1);
        str1 = str.substr(0, pos1);
        str2 = str.substr(pos1+1, pos2-pos1-1);
        str3 = str.substr(pos2+1, str.size());

        long long id1 = convert_id_to_int(str1);
        long long id2 = convert_id_to_int(str2);
        long long weight = convert_id_to_int(str3);

        // as the file is already processed, we can directly insert the edge to the map
        edge_map[{id1, id2}] = weight;
        if(weight > max_edge_weight){
            max_edge_weight = weight;
        }

        edge_by_weight[weight].push_back({id1, id2});
    }

    file.close();

    // destroy the char array
    delete[] requiredInputFileNameChar;

    return 1;
}


int edge_processor(string fileSuffix){

    string GROUP_SIZE = fileSuffix;

    // for windows file support
#ifdef is_OS_unix
    string requiredOutputFilename = "../data-intermediate/weighted-edges" + GROUP_SIZE + ".csv";
    string outputMaxWeightFilename = "../data-intermediate/max-edge-weight"+ GROUP_SIZE + ".csv";
    string requiredInputFileName = "../edges" + GROUP_SIZE + ".csv";
#else
    string requiredOutputFilename = "..\\data-intermediate\\weighted-edges" + GROUP_SIZE + ".csv";
    string outputMaxWeightFilename = "..\\data-intermediate\\max-edge-weight"+ GROUP_SIZE + ".csv";
    string requiredInputFileName = "..\\edges" + GROUP_SIZE + ".csv";
#endif

    // convert string to char array
    char *requiredOutputFilenameChar = new char[requiredOutputFilename.size() + 1];
    copy(requiredOutputFilename.begin(), requiredOutputFilename.end(), requiredOutputFilenameChar);
    requiredOutputFilenameChar[requiredOutputFilename.size()] = '\0';

    char *outputMaxWeightFilenameChar = new char[outputMaxWeightFilename.size() + 1];
    copy(outputMaxWeightFilename.begin(), outputMaxWeightFilename.end(), outputMaxWeightFilenameChar);
    outputMaxWeightFilenameChar[outputMaxWeightFilename.size()] = '\0';

    char *requiredInputFileNameChar = new char[requiredInputFileName.size() + 1];
    copy(requiredInputFileName.begin(), requiredInputFileName.end(), requiredInputFileNameChar);
    requiredInputFileNameChar[requiredInputFileName.size()] = '\0';


    // check if the required input file exists
    if(access(requiredInputFileNameChar, F_OK) == -1){
        cout << "Required input file does not exist" << endl;
        cout << "Filename: '" << requiredInputFileNameChar << "'" << endl;
        return 0;
    }
    cout << "Pre-processing file..." << endl;

    

    // read file edges15.csv
    ifstream file(requiredInputFileNameChar);


    // write output to file data-intermediate/edges5.csv
    ofstream outfile(requiredOutputFilenameChar);

    ofstream maxCount_file(outputMaxWeightFilenameChar);

    long maxWeight = 0;

    string str;
    string str1, str2;
    while (getline(file, str)) {
        // detect and ignore header
        if(str[0] == 'S' or str[0] == 's'){
            continue;
        }
        // split string into 2 by comma
        int pos = str.find(",");
        str1 = str.substr(0, pos);
        str2 = str.substr(pos+1, str.size());

        // convert string to int
        long long id1 = convert_id_to_int(str1);
        long long id2 = convert_id_to_int(str2);

        // search pair in map
        auto it = edge_map.find(make_pair(id1, id2));

        // find inverse edge
        if(it == edge_map.end()){
            // pair not found
            it = edge_map.find(make_pair(id2, id1));
        }

        // add weight
        if(it != edge_map.end()){
            // pair found
            it->second += 1;
            if(it->second > maxWeight){
                maxWeight = it->second;
            }
        }else{
            // pair not found
            edge_map.insert(make_pair(make_pair(id1, id2), 1));
        }

        // // write to file
        // outfile << convert_id_to_int(str1) << "," << convert_id_to_int(str2) << "," <<  << endl;
    }

    cout << "Edges Weight Calculated." << endl;
    cout << "Writing to file..." << endl;

    // write the map pair with weights
    for(auto it = edge_map.begin(); it != edge_map.end(); it++){
        outfile << it->first.first << "," << it->first.second << "," << it->second << endl;
    } 

    // write maxWeight to file
    maxCount_file << maxWeight << endl;
    max_edge_weight = maxWeight;

    cout << "Written to Edges with weights to file" << endl;


    // close file
    outfile.close();
    file.close();

    // destroy the char array
    delete[] requiredOutputFilenameChar;
    delete[] requiredInputFileNameChar;

    return 1;
}


int 


int check_pre_process_cache_exists(string fileSuffix){
    string GROUP_SIZE = fileSuffix;

    int edges_processed = 0;
    int friends_processed = 0;

#ifdef is_OS_unix
    string requiredEdgeFilename = "../data-intermediate/weighted-edges" + GROUP_SIZE + ".csv";
    string requiredFriendFilename = "../data-intermediate/checked-friends" + GROUP_SIZE + ".csv";
#else
    string requiredEdgeFilename = "..\\data-intermediate\\weighted-edges" + GROUP_SIZE + ".csv";
    string requiredFriendFilename = "..\\data-intermediate\\checked-friends" + GROUP_SIZE + ".csv";
#endif

    // convert string to char array
    char *requiredEdgeFilenameChar = new char[requiredEdgeFilename.size() + 1];
    copy(requiredEdgeFilename.begin(), requiredEdgeFilename.end(), requiredEdgeFilenameChar);
    requiredEdgeFilenameChar[requiredEdgeFilename.size()] = '\0';

    char *requiredFriendFilenameChar = new char[requiredFriendFilename.size() + 1];
    copy(requiredFriendFilename.begin(), requiredFriendFilename.end(), requiredFriendFilenameChar);
    requiredFriendFilenameChar[requiredFriendFilename.size()] = '\0';

    // group size to char array
    char *GROUP_SIZE_char = new char[GROUP_SIZE.size() + 1];
    copy(GROUP_SIZE.begin(), GROUP_SIZE.end(), GROUP_SIZE_char);
    GROUP_SIZE_char[GROUP_SIZE.size()] = '\0';


    // check if the following file exists: data-intermediate/edges5.csv or data-intermediate/edges10.csv or data-intermediate/edges15.csv
    if(access(requiredEdgeFilenameChar, F_OK) != -1){
        // file exists
        cout << "Edge intermediate is processed." << endl;
        edges_processed = 1;
        read_edge(GROUP_SIZE_char);
    }
    else{
        // file doesn't exist
        cout << "Pre-processed edge file doesn't exist" << endl;
        edges_processed = edge_processor(GROUP_SIZE);
    }

    // check if the following file exists: data-intermediate/checked-friends5.csv or data-intermediate/checked-friends10.csv or data-intermediate/checked-friends15.csv
    if(access(requiredFriendFilenameChar, F_OK) != -1){
        // file exists
        cout << "Friends intermediate is processed. " << endl;
        friends_processed = 1;
        read_friend(GROUP_SIZE_char);
    }
    else{
        // file doesn't exist   
        cout << "File doesn't exist" << endl;
        friends_processed = friend_processor(GROUP_SIZE);
    }

    if(friends_processed && edges_processed){
        return 1;
    }

}



int main(int argc, char *argv[]) {
    string GROUP_SIZE = "15";

    // get group size from arguments
    if(argc > 1){
        GROUP_SIZE = argv[1];
    }else{
        cout << "To define input files, use: ./main1 ${Group Count}" << endl;
        cout << "Example: ./main 15" << endl;
        cout << "will use files 'edges15.csv' as input" << endl;
    }

    // check if the pre-processed files exist
    if(check_pre_process_cache_exists(GROUP_SIZE)){
        cout << "Pre-processed files exist." << endl;
        cout << "Reading from pre-processed files..." << endl;
    }else{
        return -1;
    }

    // print the size of the edgemap
    cout << "Size of edge map: " << edge_map.size() << endl;
    cout << "Size of friend map: " << friend_map.size() << endl;

    // calculate the union

    

    return 0;

}