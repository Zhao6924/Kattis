// Meysam Aghighi

#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

const int N = 20010;

bool marked[N];
int comp[N], comps;
int t,n,m,u,v;
stack<int> s;
vector<int> g[N],gi[N];

void dfs(int v){
	if (marked[v]) return;
//	cout << v << " ";
	marked[v] = true;
	for (vector<int>::iterator u=g[v].begin();u!=g[v].end();++u) dfs(*u);
	s.push(v);
}

void dfs2(int v, int c){
	if (marked[v]) return;
//	cout << v << " ";
	marked[v] = true;
	comp[v] = c;
	for (vector<int>::iterator u=gi[v].begin();u!=gi[v].end();++u) dfs2(*u,c);
}

int main(){
	cin >> t;
	while (t--){
		cin >> n >> m;
		for (int i=0;i<n;i++){
			g[i].clear();
			gi[i].clear();
		}
		for (int i=0;i<m;i++){ // make graph
			cin >> u >> v;
			u--, v--;
			g[u].push_back(v);
			gi[v].push_back(u);
		}
		// DFS
		memset(marked,false,sizeof(marked));
		for (int i=0;i<n;i++) dfs(i);
//		cout << endl;
		// DFS 2
		memset(marked,false,sizeof(marked));
		comps = 0;
		while (!s.empty()){
			int v = s.top(); s.pop();
			if (!marked[v]) dfs2(v, comps++);
		}
//		cout << endl;
		// Total in-degree & out-degree
		bool in[comps], out[comps];
		memset(in,false,sizeof(in));
		memset(out,false,sizeof(out));
		for (int i=0;i<n;i++){
			for (int j=0;j<g[i].size();j++){
				u = i, v = g[i][j];
				if (comp[u] != comp[v]) out[comp[u]]=true, in[comp[v]]=true;
			}
		}
		int need_in = 0, need_out = 0;
		for (int i=0;i<comps;i++){
			if (!in[i]) need_in++;
			if (!out[i]) need_out++;
		}
//		cout << comps << endl;
		if (comps == 1) cout << 0 << endl;
		else cout << max(need_in, need_out) << endl;
	}
	return 0;
}
