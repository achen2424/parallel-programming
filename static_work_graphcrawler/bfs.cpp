#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <vector>
#include <thread>
#include <mutex>
#include <curl/curl.h>
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

const string MAIN_URL = "http://hollywood-graph-crawler.bridgesuncc.org/neighbors/";
mutex mtx;  //synchronize shared data

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

string encode_spaces(const string& node) {
    string encoded;
    for (char c : node) {
        if (c == ' ') encoded += "%20";
        else encoded += c;
    }
    return encoded;
}

string fetch_neighbors(CURL* curl, const string& node) {
    string url = MAIN_URL + encode_spaces(node);
    string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "User-Agent: C++-Client/1.0");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);

    return (res == CURLE_OK) ? response : "{}";
}

vector<string> get_neighbors(const string& json_str) {
    vector<string> neighbors;
    Document doc;
    doc.Parse(json_str.c_str());

    if (doc.HasMember("neighbors") && doc["neighbors"].IsArray()) {
        for (const auto& neighbor : doc["neighbors"].GetArray()) {
            neighbors.push_back(neighbor.GetString());
        }
    }
    return neighbors;
}

void process_node(const string& node, unordered_set<string>& visited, vector<string>& next_level) {
    CURL* curl = curl_easy_init();
    if (!curl) return;
    
    string response = fetch_neighbors(curl, node);
    vector<string> neighbors = get_neighbors(response);
    
    lock_guard<mutex> lock(mtx);
    for (const auto& neighbor : neighbors) {
        if (visited.insert(neighbor).second) {
            next_level.push_back(neighbor);
        }
    }
    
    curl_easy_cleanup(curl);
}

vector<vector<string>> parallel_bfs(const string& start, int depth) {
    vector<vector<string>> levels;
    unordered_set<string> visited;
    
    levels.push_back({start});
    visited.insert(start);

    for (int d = 0; d < depth; d++) {
        vector<string> next_level;
        vector<thread> threads;

        for (const auto& node : levels[d]) {
            threads.emplace_back(
                process_node, 
                node, 
                ref(visited), 
                ref(next_level)
            );
        }

        for (auto& t : threads) t.join();

        if (next_level.empty()) break;
        levels.push_back(next_level);
    }

    return levels;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <node_name> <depth>\n";
        return 1;
    }

    string start_node = argv[1];
    int depth = stoi(argv[2]);

    auto start = chrono::steady_clock::now();
    auto levels = parallel_bfs(start_node, depth);
    auto end = chrono::steady_clock::now();

    for (const auto& level : levels) {
        for (const auto& node : level) {
            cout << node << " ";
        }
        cout << "\n";
    }

    chrono::duration<double> elapsed = end - start;
    cout << "Time taken: " << elapsed.count() << " seconds\n";
    return 0;
}
