#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
#define ll long long
#define debug(x) cout << "Debug " #x << ": " << x << endl;
#define pb push_back
#define present cout << "PRESENT" << endl;
#define space " "
#define rep(i, a, n) for (int i = a; i < n; i++)
const long long MOD = 1e9 + 7;
int const size = (1e6)+1;
ll const tot = 1e7+1;
 #define printlist(x) for(auto it : x) cout<<it<<" ";cout<<endl;

vector<bool> prime(tot, 1);
vector<int> pri;

long long power(long long x,long long y){

    long long res = 1;
    x = x%MOD;
    if(x==0) return 0;
    while(y>0){
        if(y&1)
        res =(res)*x % MOD;
        y = y>>1;
        x = (x*x) % MOD;
    }
    return res;
}

bool isSquare(ll n){
    ll root = sqrt(n);
    if(root*root == n)return true;
    else return false;
}



unordered_map<ll,ll> fact(ll n){
    unordered_map<ll,ll> freq;
    for(int i=0;(ll)pri[i]*pri[i]<=n;i++){
    if(n%pri[i]==0){
    int cnt = 0;
    while(n%pri[i]==0){
        cnt++;
        n /= pri[i];
    }
    freq[pri[i]] = cnt;
    }
    }
    if(n!=1)freq[n] = 1;
    return freq;
}

   
#define V 12
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not
    // visited
    bool visited[V];
    memset(visited, 0, sizeof(visited));
 
    // Create a queue, enqueue source vertex and mark source
    // vertex as visited
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();
 
        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                // If we find a connection to the sink node,
                // then there is no point in BFS anymore We
                // just have to set its parent and can return
                // true
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    // We didn't reach sink in BFS starting from source, so
    // return false
    return false;
}

int fordFulkerson(int graph[V][V], int s, int t)
{
    int u, v;
 
    // Create a residual graph and fill the residual graph
    // with given capacities in the original graph as
    // residual capacities in residual graph
    int rGraph[V]
              [V]; // Residual graph where rGraph[i][j]
                   // indicates residual capacity of edge
                   // from i to j (if there is an edge. If
                   // rGraph[i][j] is 0, then there is not)
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];
 
    int parent[V]; // This array is filled by BFS and to
                   // store path
 
    int max_flow = 0; // There is no flow initially
 
    // Augment the flow while there is path from source to
    // sink
    while (bfs(rGraph, s, t, parent)) {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
    }
 
    // Return the overall flow
    return max_flow;
}
 
 
        
void RED(){
   
    int graph[V][V];
    int N = 4;
    int Edges[5][5] = {  {1,2}, {2,3}, {3,4}};
          
          for(int i=0;i<V;i++){
              for(int j=0;j<V;j++){
                  graph[i][j] = 0;
              }
          }
          
          for(int i=1;i<=N;i++){
              if(i&1) graph[0][i] = 1;
              else graph[i][V-1] =1;
          }
          
          for(auto it : Edges){
              graph[it[0]*2][it[1]*2-1]=1;
              graph[it[1]*2-1][it[0]*2] = 1;
          }

          for(int i=0;i<=N;i++){
            if(i&1) graph[i][10] = 1;
            else graph[9][i]=1;
          }

          graph[9][0]=1;
          graph[V-1][10]=1;
          
          int flow = fordFulkerson(graph, 9, 10);
          cout<< (flow)<<endl;

}

int main()
{
    

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);

// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
    int t;
    int k;
    for (int p = 2; p * p < tot; p++)
    {

        if (prime[p] == true)
        {

            for (int i = p * p; i < tot; i += p)
                prime[i] = false;
        }
    }

    for (int i = 2; i < tot; i++)
    {
        if (prime[i])
            pri.pb(i);
    }

    t = 1;
 cin >> t;

    k = t;
    while (t--)
    {

        // cout<<"Case #"<<k-t<<": ";
        RED();
    }
}

