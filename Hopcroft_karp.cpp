const int inf = (int)1e9;
class Hopcroft_karp{
    public:
        vector<int> match , dist;
        vector<vector<int>> adj;
 
        int n , m ;
 
        void init(int _n , int _m){
            n = _n , m = _m;
            match.assign(n + m + 1 , 0) ;
            dist.assign(n + m + 1 , inf);
            adj.assign(n + m + 1 , vector<int>());
        }
 
        void add_edge(int i , int j){
            adj[i].push_back(j + n);
            adj[j + n].push_back(i);
            return;
        }
 
        bool bfs(){
            queue<int> q;
            for(int i = 1; i <= n; ++i) {
                if (!match[i]){
                    dist[i] = 0;
                    q.push(i);
                }
                else dist[i] = inf;
            }
            dist[0] = inf;
 
            while (q.size()){
                int u = q.front(); q.pop();
                if (dist[u] >= dist[0]) continue;
 
                for(int v : adj[u]){
                    if (dist[match[v]] == inf){
                        dist[match[v]] = dist[u] + 1;
                        q.push(match[v]);
                    }
                }
            }
 
            return dist[0] != inf;
        }
 
        bool dfs(int u){
            if (u == 0) return true;
            for(int v : adj[u]){
                if (dist[match[v]] == dist[u] + 1 && dfs(match[v])) {
                    match[v] = u , 
                    match[u] = v;
                    return true;
                }
            }
            dist[u] = inf;
            return false;
        }
 
        int hopcroft_karp(void){
            int cnt = 0 ;
            while (bfs()){
                for(int i = 1; i <= n; ++i) if (!match[i] && dfs(i)) ++cnt;
            }
            return cnt;
        }
} flow;
