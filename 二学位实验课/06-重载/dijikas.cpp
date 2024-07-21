#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Node {
    int index, dist, prev;
    Node(int _index, int _dist, int _prev) : index(_index), dist(_dist), prev(_prev) {}
    bool operator<(const Node& rhs) const {
        return dist > rhs.dist;
    }
};


void Dijkstra(const int N, const int M, const char* maze){
    std::unordered_map<int, std::pair<int, int>> dist; // <index, <distance, previous index>>
    std::priority_queue<Node> pq;
    
    int dx[4] = {0, -1, 1, 0};
    int dy[4] = {1, 0, 0, -1};

    pq.push(Node(0, 0, -1));

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        if (dist.count(node.index) && dist[node.index].first < node.dist) {
            continue;
        }

        dist[node.index] = {node.dist, node.prev};

        for (int i = 0; i < 4; ++i) {
            int nx = node.index / M + dx[i];
            int ny = node.index % M + dy[i];
            int nindex = nx * M + ny;

            if (nx >= 0 && nx < N && ny >= 0 && ny < M && maze[nx*M+ny] != 'X') {
                int ndist = node.dist + 1;
                if ( maze[nx*M+ny] >= '1' && maze[nx*M+ny] <= '9') {
                    ndist += maze[nx*M+ny] - '0';
                }
                pq.push(Node(nindex, ndist, node.index));
            }
        }
    }

    std::vector<int> path;
    int cur = (N - 1) * M + M - 1; // index of the destination
    int max_steps = dist[cur].first;
    if (max_steps == 0) {
        std::cout << "-1" << std::endl;
        return;
    }
    while (cur != -1) {
        path.push_back(cur);
        cur = dist[cur].second; // move to the previous cell
    }
    std::reverse(path.begin(), path.end()); // reverse the path to start from the source

    std::cout<<"到达目标位置需要"<<max_steps<<"步，具体路径为"<<std::endl;
    int steps=1;
    // print the path
    for (int k=0; k<path.size();k++) {
        int index = path[k];
        
        // int x = index / M;
        // int y = index % M;
        char value = maze[index];
        if (value >= '1' && value <= '9') {
            for (int i = 0; i < value - '0'; ++i) {
                std::cout << steps<<":FIGHT AT (" << index/M << "," << index%M << ")" << std::endl;
                steps+=1;
            }
            // std::cout << "(" << x << "," << y << "," << value << ")" << std::endl;
        }

        if (k+1 == path.size() ) {
            break;
        }
        int next_index = path[k+1];
        std::cout << steps<<":(" << index/M << "," << index%M << ")->"<< "(" << next_index/M << "," << next_index%M << ")"<< std::endl;
        steps+=1;
    }

}

int main() {
    int N, M;
    std::cin >> N >> M;
    char* maze = new char [N*M];
    for (int i = 0; i < N*M; ++i) {
        std::cin >> maze[i];
    }
    // Now, 'maze' is a 2D array representing the grid.
    Dijkstra(N,M,maze);
    return 0;
}