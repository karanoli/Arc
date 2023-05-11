#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
ifstream fin;
ofstream fout;
signed main(){
	fin.open("cache.txt",ios::in);
	fout.open("playdata.txt",ios::out|ios::trunc);
	while(getline(fin,s)){
		fout<<s<<endl;
	}
    return 0;
}


