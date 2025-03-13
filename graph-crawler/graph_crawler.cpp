#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <algorithm>
#include <curl/curl.h>
#include <rapidjson/document.h>
using namespace std;
using namespace rapidjson;

size_t my_write_data(char* ptr, size_t size, size_t nmemb, void* userdata) {
    size_t total_size = size * nmemb;
    string* mystring = static_cast<string*>(userdata);
    mystring->append(ptr, total_size);
    return total_size;
}

string encode_spaces(const string& str) {
    string encoded;
    for (char c : str) {
        if (c == ' ')
            encoded += "%20";
        else
            encoded += c;
    }
    return encoded;
}

vector<string> get_neighbors(const string& node) {
    CURL* curl = curl_easy_init();
    string response;

    if (!curl) {
        cerr << "Failed to initialize curl\n";
        return {};
    }
    
    string encoded_node = encode_spaces(node);
    string url = "http://hollywood-graph-crawler.bridgesuncc.org/neighbors/" + encoded_node;
    
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&response);
    

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
        curl_easy_cleanup(curl);
        return {};
    }

    curl_easy_cleanup(curl);

    // Parse JSON using RapidJSON
    vector<string> neighbors;
    Document doc;
    
    if (doc.Parse(response.c_str()).HasParseError()) {
        cerr << "JSON parse error\n";
        return {};
    }

    if (doc.HasMember("neighbors") && doc["neighbors"].IsArray()) {
    for (const auto& val : doc["neighbors"].GetArray()) {
        if (val.IsString()) {
            neighbors.push_back(val.GetString());
        }
    }
}
    return neighbors;
}

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
        cerr << "Usage: " << argv[0] << " <start_node (may have spaces)> <depth>" << endl;
        return 1;
    }

    // Combine all arguments except the last one into the name
    string start;
    for (int i = 1; i < argc - 1; ++i) {
        start += argv[i];
        if (i != argc - 2) start += " ";  // add space between words
    }

    int depth = stoi(argv[argc - 1]);

    vector<string> result = bfs(start, depth);
    cout << "Nodes found within depth " << depth << " from " << start << ":" << endl;
    for (const string& node : result) {
        cout << node << endl;
    }

    return 0;
}