//IOI 2016 P5 - Unscrambling a Messy Bug
#include <bits/stdc++.h>
using namespace std;
int ans[128], N;
vector<int> solved [128][128];
void generatePermutations(int l, int r){
    //cout<<l<<" "<<r<<endl;
    if (l==r) return;
    string S  = string(r-l+1, '0');
    int mid = (l+r)/2;
    string prefix = string(l, '1'), suffix = string (N-1-r, '1');
    for (int i = 0; i<=(mid-l); i++){
        S[i] = '1';
        add_element (prefix+S+suffix);
        S[i] = '0';
    }
    generatePermutations (l, mid);
    generatePermutations (mid+1, r);
}
void checkPermutations (int l, int r){
    if (l==r) return;
    string S =  string(N, '0');
    int l1 = 0, r1 = N-1;
    while (l1!=l){
        int t = l1 + (1<<(int)log2(l-l1+1)) - 1;
        for (int i: solved[l1][t]) S[i] = '1';
        l1 = t+1;
    }
    while (r1!=r){
        int t = r1 - (1<<(int)log2(r1-r+1)) + 1;
        for (int i: solved[t][r1]) S[i] = '1';
        r1 = t-1;
    }
    int mid = (l+r)/2;
    for (int i = 0; i<N; i++){
        if (S[i]=='1') continue;
        S[i] = '1';
        if (check_element(S)) solved[l][mid].push_back(i);
        else solved[mid+1][r].push_back(i);
        S[i] = '0';
    }
    //for (int i: solved[l][mid]) cout<<i<<" ";
    //for (int i: solved[mid+1][r]) cout<<i<<" ";
    checkPermutations (l, mid);
    checkPermutations (mid+1, r);
}
int* restore_permutation(int n, int w, int r){
    N=n;
    generatePermutations(0, N-1);
    compile_set();
    checkPermutations(0, N-1);
    for (int i = 0; i<N; i++) ans[solved[i][i][0]] = i;
    return ans;
}
