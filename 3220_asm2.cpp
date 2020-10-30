#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

char idx2nuc[] = "$ACGT";
inline int nuc2idx(char nuc){
	switch (nuc){
		case '$':return 0;
		case 'A':return 1;
		case 'C':return 2;
		case 'G':return 3;
		case 'T':return 4;
	}
	
	return -1;
	
}

struct TrieNode{
	int par;
	int nxt[5];
	
	bool isLeaf;
	int leftmost;
	
	int suffix_tree_par, lt, rt;
	
	TrieNode(){
		par = -1;
		memset(nxt, -1, sizeof(nxt));
		isLeaf = false;
		leftmost = 0x3f3f3f3f;
	}
};

static const int MAXN = 10005;
TrieNode pool[MAXN];
int pool_cur = 1;
int trie_root = 0;

void trie_insert(string str, int offset){
	int cur_node = trie_root;
	for(int i = 0; i < str.size();i++){
		int nxt_idx = nuc2idx(str[i]);
		if(pool[cur_node].nxt[nxt_idx] == -1){
			pool[cur_node].nxt[nxt_idx] = pool_cur;
			pool[pool_cur].par = cur_node;
			pool_cur++;
			
		}
		
		cur_node = pool[cur_node].nxt[nxt_idx];
		pool[cur_node].leftmost = min(pool[cur_node].leftmost, i+offset);
		
	}
	
	pool[cur_node].isLeaf = true;
	
}

int child_cnt[MAXN];
void compress(){
	for(int i = 0; i<pool_cur;i++){
		child_cnt[i] = 0;
		for(int j = 0; j<5; j++){
			if(pool[i].nxt[j] != -1){
				child_cnt[i]++;
				
			}
			
		}
		
	}
	
	for(int i = 0; i < pool_cur; i++){
		if(pool[i].isLeaf){
			int cur_node = i;
			int lt = -1;
			int rt = pool[i].leftmost;
			while(child_cnt[cur_node] <= 1){
				lt = pool[cur_node].leftmost;
				cur_node = pool[cur_node].par;
				
			}
			pool[i].suffix_tree_par = cur_node;
			pool[i].lt = lt;
			pool[i].rt = rt;
 			
		}
		
	}
	
}

void dfs(int cur_node){
	if(pool[cur_node].isLeaf){
		cout<<pool[cur_node].lt << '-' << pool[cur_node].rt << endl;
		
	}
	for(int i = 0; i < 5; i++){
		if(pool[cur_node].nxt[i] != -1){
			dfs(pool[cur_node].nxt[i]);
		}
		
	}
	
}

int main(){
	string str;
	cin >> str;
	for(int i = 0; i < str.size(); i++){
		cout << str.substr(i) << endl;
		trie_insert(str.substr(i), i+1);
		
	}
	compress();
	dfs(trie_root);
	
	return 0;
	
}


























