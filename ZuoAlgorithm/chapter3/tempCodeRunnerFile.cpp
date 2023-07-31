#include<iostream>
// #include<string>
#include<unordered_map>
using namespace std;
int main(){
unordered_map<int,int> map{{1,2},{3,4},{5,6}};
for(auto it=map.begin();it!=map.end();it++){
    cout<<it->first<<" ,"<<it->second<<" "<<endl;

}
return 0;
}
