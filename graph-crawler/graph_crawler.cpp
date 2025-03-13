#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <curl/curl.h>
#include <rapidjson/document.h>
#include <chrono>
using namespace std;
using namespace rapidjson;
using namespace chrono;

//store HTTP response in string
size_t my_write_data(char* ptr, size_t size, size_t nmemb, void* userdata) {
    size_t total_size = size * nmemb;
    string* mystring = static_cast<string*>(userdata);
    mystring->append(ptr, total_size);
    return total_size;
}

//encode spaces in string for URL format
string encode_spaces(const string& mystring) {
    string newstring;
    for (char c : mystring) {
        if (c == ' ')
            newstring += "%20";
        else
            newstring += c;
    }
    return newstring;
}

//fetch neighbors of given node using web api
vector<string> get_neighbors(const string& node) {
    CURL* curl = curl_easy_init();
    string response;

    string encoded_node = encode_spaces(node);
    string url = "http://hollywood-graph-crawler.bridgesuncc.org/neighbors/" + encoded_node;
    
    //set curl options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&response);
    
    //perform GET request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
        curl_easy_cleanup(curl);
        return {};
    }

    curl_easy_cleanup(curl);

    vector<string> neighbors;
    Document doc;
    
    if (doc.Parse(response.c_str()).HasParseError()) {
        cerr << "JSON parse error\n";
        return {};
    }

    //extract neighbors
    if (doc.HasMember("neighbors") && doc["neighbors"].IsArray()) {
    for (const auto& val : doc["neighbors"].GetArray()) {
        if (val.IsString()) {
            neighbors.push_back(val.GetString());
        }
    }
}
    return neighbors;
}

//breadth first search to the given depth, returns reachable nodes
vector<string> bfs(const string& start, int depth) {
    queue<pair<string, int>> q;
    vector<string> visited;

    q.push({start, 0});
    visited.push_back(start);

    while (!q.empty()) {
        pair<std::string, int> front = q.front();
        string current = front.first;
        int level = front.second;
        q.pop();

        if (level >= depth) continue;

        vector<string> neighbors = get_neighbors(current);
        for (const string& neighbor : neighbors) {
            if (find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                visited.push_back(neighbor);
                q.push({neighbor, level + 1});
            }
        }
    }
    return visited;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Make sure to include all arguments: " << argv[0] << " <start_node (may have spaces)> <depth>" << endl;
        return 1;
    }

    string start;
    if (argc == 3) {
        start = argv[1];
    } else if (argc == 4) {
        start = string(argv[1]) + " " + argv[2];
    }

    int depth = stoi(argv[argc - 1]);

    auto begin = high_resolution_clock::now();

    vector<string> result = bfs(start, depth);

    auto end = high_resolution_clock::now();
    chrono::duration<double> elapsed = end - begin;

    cout << "Nodes found within depth " << depth << " from " << start << ":" << endl;
    for (const string& node : result) {
        cout << node << endl;
    }

    cout << "Execution time: " << elapsed.count() << " seconds" << endl;

    return 0;
}