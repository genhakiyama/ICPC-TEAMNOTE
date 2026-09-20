class Ford_fulkerson{
public:
    vector<vector<int>> f , cap , adj;
    vector<int> trace , dist;    
    int n;

    void init(int num_node){
        dist.assign(num_node + 1 , -1);
        f.assign(num_node + 1 , vector<int>(num_node + 1 , 0));
        cap.assign(num_node + 1 , vector<int>(num_node + 1 , 0));
        adj.assign(num_node + 1 , vector<int>());
        trace.assign(num_node + 1 , 0);
        return;
    }

    void add_edge(int u , int v , int cost){
        adj[u].push_back(v);
        adj[v].push_back(u); // augmenting path
        cap[u][v] = cost;
        return;
    }

    bool bfs(int source , int sink){
        fill(dist.begin() , dist.end() , -1);
        dist[source] = 0;
        queue<int> q;
        
        q.push(source);
        while (q.size()){
            int u = q.front(); q.pop();
            for(int v : adj[u]){
                if (dist[v] == -1 && f[u][v] < cap[u][v]){
                    dist[v] = dist[u] + 1;
                    trace[v] = u;
                    q.push(v);
                }
            }
        }

        return dist[sink] != -1;
    }

    int dfs(int source , int sink){
        int ans = inf;
        int temp = sink;
    
        while (temp != source){
            int v = trace[temp];
            ans = min(ans , cap[v][temp] - f[v][temp]);
            temp = v;
        }

        while (sink != source){
            int v = trace[sink];
            f[v][sink] += ans , f[sink][v] -= ans;
            sink = v;
        }

        return ans;
    }

    int ford_fulkerson(int source , int sink){
        int cnt = 0;
        while (bfs(source , sink)){
            cnt += dfs(source , sink);
        }
        return cnt;
    }
} flow;
