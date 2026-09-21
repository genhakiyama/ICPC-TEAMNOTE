const int inf = (int)1e9 + 7;

struct Edge{
    int u , v;
    int flow , cap;

    Edge(){
        u = v = flow = cap = 0;
    }

    Edge(int u , int v , int cap , int flow) : u(u) , v(v) , cap(cap) , flow(flow) {};
};

class Edmons_karp{
    public:
        vector<Edge> edg;
        vector<vector<int>> adj;
        vector<int> level , index;

        void init(int num_node){
            adj.assign(num_node + 1 , vector<int>());
            level.assign(num_node + 1 , -1);
            index.assign(num_node + 1 , 0);
            return;
        }

        void add_edge(int u , int v , int cap){
            edg.push_back(Edge(u , v , cap , 0));
            edg.push_back(Edge(v , u , 0 , 0));

            adj[u].push_back(edg.size() - 2);
            adj[v].push_back(edg.size() - 1);
            return;
        }

        bool bfs(int source , int sink){
            fill(level.begin() , level.end() , -1);
            level[source] = 0;
            queue<int> q;
            q.push(source);
            while (q.size()){
                int u = q.front(); q.pop();
    
                for(int id : adj[u]){
                    int v = edg[id].u ^ edg[id].v ^ u;
                    if (level[v] != -1) continue;
                    if (edg[id].flow >= edg[id].cap) continue;

                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }

            return level[sink] != -1;
        }

        int dfs(int u , int sink , int cost){
            if (u == sink) return cost;
            for(; index[u] < adj[u].size(); ++index[u]){
                int id = adj[u][index[u]];
                int v = u ^ edg[id].u ^ edg[id].v;
                if (level[v] != level[u] + 1 || edg[id].cap - edg[id].flow == 0) continue;
                int t = dfs(v , sink , min(cost , edg[id].cap - edg[id].flow));
                if (t != 0) {
                    edg[id].flow += t , edg[id ^ 1].flow -= t;
                    return t;
                }
            }
            return 0;
        }

        int edmons_karp(int source , int sink){
            int ans = 0;
            while (bfs(source , sink)){
                fill(index.begin() , index.end() , 0);
                ans += dfs(source , sink , inf);
            }
            return ans;
        }
} flow;
