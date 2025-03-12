#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
using namespace std;

map<string, vector<string> > graph;

void initializeGraph() {
    graph["Tom_Hanks"].push_back("Forrest_Gump");
    graph["Tom_Hanks"].push_back("Saving_Private_Ryan");
    graph["Tom_Hanks"].push_back("Cast_Away");

    graph["Forrest_Gump"].push_back("Tom_Hanks");
    graph["Forrest_Gump"].push_back("Robin_Wright");

    graph["Saving_Private_Ryan"].push_back("Tom_Hanks");
    graph["Saving_Private_Ryan"].push_back("Matt_Damon");
    graph["Saving_Private_Ryan"].push_back("Vin_Diesel");

    graph["Cast_Away"].push_back("Tom_Hanks");

    graph["Robin_Wright"].push_back("Forrest_Gump");

    graph["Matt_Damon"].push_back("Saving_Private_Ryan");

    graph["Vin_Diesel"].push_back("Saving_Private_Ryan");
}

vector<string> bfs(const string& start, int depth) {
    queue<pair<string, int> > q;
    vector<string> visited;

    q.push(make_pair(start, 0));
    visited.push_back(start);

    while (!q.empty()) {
        pair<string, int> front = q.front();
        string current = front.first;
        int level = front.second;
        q.pop();

        if (level >= depth) continue;

        vector<string> neighbors = graph[current];
        for (size_t i = 0; i < neighbors.size(); i++) {
            string neighbor = neighbors[i];

            if (find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                visited.push_back(neighbor);
                q.push(make_pair(neighbor, level + 1));
            }
        }
    }
    return visited;
}

int main() {
    initializeGraph();
    string start = "Tom_Hanks";
    int depth = 2;

    vector<string> result = bfs(start, depth);
    cout << "Nodes found within " << depth << ":" << endl;
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }
    return 0;
}