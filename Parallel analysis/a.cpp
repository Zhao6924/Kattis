// Meysam Aghighi
// Finding the Longest path - Scheduling (last write is important! -> Mahder found it!)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int t,n,m;
long long temp;
map<long long,int> mapp;
int map_size;

// Key of the map
int key(long long value){
    if (!mapp.count(value))
        mapp[value] = map_size++;
    return mapp[value];
}

// Binary Search
int bs(vector<int> &s, int size, int v){
	if (size == 0) return -1;
	int lo = 0, hi = size-1, mid;
	while (lo != hi){
		mid = (lo+hi+1)/2;
		if (s[mid] < v)
			lo = mid;
		else
			hi = --mid;
	}
	if (s[lo] < v)
		return s[lo];
	return -1;
}

int main(){
	scanf("%d",&t);
    for(int ii=0;ii<t;ii++){
        scanf("%d",&n);
        vector<int> g[n];
        vector<int> iin[25*n], oout[25*n];
        mapp.clear();
        map_size = 0;
        for (int i=0;i<n;i++){
            scanf("%d",&m);
            for (int j=0;j<m-1;j++){
                scanf("%lld",&temp);
                iin[key(temp)].push_back(i);
            }
            scanf("%lld",&temp);
            oout[key(temp)].push_back(i);
        }
        // Building the Graph
        int u, v;
        for (int i=0;i<map_size;i++){
        	sort(iin[i].begin(),iin[i].end());
        	sort(oout[i].begin(),oout[i].end());
            for (int j=0;j<iin[i].size();j++){
                v = iin[i][j];
        		u = bs(oout[i],oout[i].size(),v);
        		if (u != -1)
        			g[u].push_back(v);
            }
        }
        int maxx = 1;
        vector<int> answer(n,1);
        for (int i=n-2;i>=0;i--){
            for (int j=0;j<g[i].size();j++){
                v = g[i][j];
                answer[i] = max(answer[i],answer[v]+1);
                maxx = max(maxx,answer[i]);
            }
        }
        printf("%d  %d\n",ii+1,maxx);
    }
    return 0;
}
