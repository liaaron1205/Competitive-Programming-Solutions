//IOI 2014 P2 - Wall
#include <bits/stdc++.h>
using namespace std;
#define mid (seg[rt].l+seg[rt].r)/2
struct Node{ int l, r, mx, mn;
bool lazymx, lazymn; };
int n, k, op[2000005], l[2000005], r[2000005], height[2000005], finalHeight[2000005];
Node seg[8000000];

void build (int l, int r, int rt){
    //cout<<l<<" "<<r<<" "<<rt<<endl;
    seg[rt].l = l;
    seg[rt].r = r;
    if (l==r) return;
    build (l, mid, 2*rt);
    build (mid+1, r, 2*rt+1);
}
void pushup (int rt){
    seg[rt].mx = max(seg[2*rt].mx, seg[2*rt+1].mx);
    seg[rt].mn = min(seg[2*rt].mn, seg[2*rt+1].mn);
}
void lazy (int rt){
    if (seg[rt].lazymn){
        seg[2*rt].mn = max(seg[2*rt].mn, seg[rt].mn);
        seg[2*rt].mx = max(seg[2*rt].mx, seg[2*rt].mn);
        seg[2*rt+1].mn = max(seg[2*rt+1].mn, seg[rt].mn);
        seg[2*rt+1].mx = max(seg[2*rt+1].mx, seg[2*rt+1].mn);
        seg[2*rt].lazymn=true;
        seg[2*rt+1].lazymn=true;
        seg[rt].lazymn=false;
    }
    if (seg[rt].lazymx){
        seg[2*rt].mx = min(seg[2*rt].mx, seg[rt].mx);
        seg[2*rt].mn = min(seg[2*rt].mx, seg[2*rt].mn);
        seg[2*rt+1].mx = min(seg[2*rt+1].mx, seg[rt].mx);
        seg[2*rt+1].mn = min(seg[2*rt+1].mx, seg[2*rt+1].mn);
        seg[2*rt].lazymx=true;
        seg[2*rt+1].lazymx=true;
        seg[rt].lazymx=false;
    }
}
void add (int l, int r, int v, int rt){
    if (seg[rt].l==l&&seg[rt].r==r){
        seg[rt].mn = max(seg[rt].mn, v);
        seg[rt].mx = max(seg[rt].mx, seg[rt].mn);
        seg[rt].lazymn = true;
        return;
    }
    if(seg[rt].lazymn||seg[rt].lazymx) lazy(rt);
    if (r<=mid) add (l, r, v, 2*rt);
    else if (l>mid) add(l, r, v, 2*rt+1);
    else{
        add (l, mid, v, 2*rt);
        add (mid+1, r, v, 2*rt+1);
    }
    pushup(rt);
}
void rem (int l, int r, int v, int rt){
    if (seg[rt].l==l&&seg[rt].r==r){
        seg[rt].mx = min(seg[rt].mx, v);
        seg[rt].mn = min(seg[rt].mx, seg[rt].mn);
        seg[rt].lazymx = true;
        return;
    }
    if(seg[rt].lazymn||seg[rt].lazymx) lazy(rt);
    if (r<=mid) rem(l, r, v, 2*rt);
    else if (l>mid) rem(l, r, v, 2*rt+1);
    else{
        rem (l, mid, v, 2*rt);
        rem (mid+1, r, v, 2*rt+1);
    }
    pushup(rt);
}
void print (int rt){
    cout<<seg[rt].l<<" "<<seg[rt].r<<" "<<seg[rt].mx<<" "<<seg[rt].mn<<" "<<seg[rt].lazymx<<" "<<seg[rt].lazymn<<endl;
    if (seg[rt].l==seg[rt].r) return;
    print(2*rt); print(2*rt+1);
}
void dfs (int rt, int ar[]){
    if (seg[rt].lazymn||seg[rt].lazymx) lazy(rt);
    if (seg[rt].l==seg[rt].r){
        ar[seg[rt].l] = seg[rt].mn;
        return;
    }
    dfs (2*rt, ar); dfs (2*rt+1, ar);
}
void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
    build (0, n-1, 1);
    for (int i = 0; i<k; i++){
        if (op[i]==1){
            add(left[i], right[i], height[i], 1);
        }
        else{
            rem(left[i], right[i], height[i], 1);
        }
        //print(1);
        //cout<<endl;
        /*dfs(1, finalHeight);
        for (int i = 0; i<n; i++){
            cout<<finalHeight[i]<<" ";
        }
        cout<<endl;*/
    }
    dfs (1, finalHeight);
    /*for (int i = 0; i<n; i++){
        cout<<finalHeight[i]<<" ";
    }
    cout<<endl;*/
}
/*
int main()
{
    cin>>n>>k;
    for (int i = 0; i<k; i++){
        cin>>op[i]>>l[i]>>r[i]>>height[i];
    }
    buildWall(n, k, op, l, r, height, finalHeight);
}*/
