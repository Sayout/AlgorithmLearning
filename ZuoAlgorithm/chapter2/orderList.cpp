
#include <iostream>
#include<unordered_map>
#include<unordered_set>
#include<bits/stdc++.h>
#include<map>
#include<set>
using namespace std;
int main(){
    //哈希表
    unordered_map<int,int> un_map{{1,2},{2,3},{3,4},{4,5}};
    un_map[5]=6;
    un_map.insert({6,7});
    for(auto it=un_map.begin();it!=un_map.end();it++){
        cout<<it->first<<"  :  "<<it->second<<endl;
    }

    unordered_set<int> un_set{1,2,3,4,5,6};
    un_set.insert(7);
    for(auto it=un_set.begin();it!=un_set.end();it++){
        cout<<*it<<endl;
    }
    cout<<endl;
    //有序表
    set <int,greater<int>> order_set{3,4,5,6};
    order_set.insert(1);
    order_set.insert(2);
    for(auto it=order_set.begin();it!=order_set.end();it++){
        cout<<*it<<endl;
    }

    map<int,int,greater<int>>order_map{{1,2},{2,3},{3,4},{4,5}};
     for(auto it=order_map.begin();it!=order_map.end();it++){
        cout<<it->first<<"  :  "<<it->second<<endl;
    }
    return 0;
}