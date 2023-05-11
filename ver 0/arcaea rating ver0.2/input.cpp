#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
ifstream fin;
ofstream fout;
struct node{
	string name,nd;
	node(){name=nd="";}
	node(string x,string y){name=x,nd=y;}
	bool operator<(const node& b)const{
		return name==b.name?nd<b.nd:name<b.name;
	}
};
map<node,int>data;
inline void read_data(){
	fin.open("datas//playdata.txt",ios::in);data.clear(); 
	while(getline(fin,s)){
		int n=s.size(),i=0,x=0;
		string name="",nd="";
		if(s[i]=='<'){
			++i;
			while(i<n&&s[i]!='>') name+=s[i],i++;
		}
		while(s[i]!='<'&&i<n)++i;
		if(s[i]=='<'){
			++i;
			while(i<n&&s[i]!='>') nd+=s[i],i++;
		}
		while(s[i]!='<'&&i<n)++i;
		if(s[i]=='<'){
			++i;
			while(i<n&&s[i]!='>') x=x*10+(48^s[i]),i++;
		}
		data[node(name,nd)]=x;
	}
	fin.close(); 
}
map<node,double>rating;
inline void read_rating(){
	fin.open("datas//rating.txt",ios::in);
	double ds=0.0;int n;
	while(getline(fin,s)){
		n=s.size();int i=0;
		string nd="",name="";
		if(isdigit(s[0])){
			ds=0.0; 
			while(i<n&&s[i]!='.')ds=ds*10+(s[i]^48),++i;
			++i;ds=ds+(s[i]^48)*0.1;
		}else if(s[0]=='['){
			++i;name=nd="";
			while(i<n&&s[i]!=']')nd+=s[i],i++;
			++i;
			while(i<n){
				if(!(i==n-1&&s[i]==' '))name+=s[i];
				i++;
			}
			rating[node(name,nd)]=ds;
		}
	}
	fin.close(); 
//	map<node,double>:: iterator it=rating.begin();
//	for(;it!=rating.end();++it){
//		cout<<"<"<<(*it).first.name<<"> <"<<(*it).first.nd<<"> <";
//		cout<<(*it).second<<">\n";
//	}
}
map<string,string>nickname; 
inline void read_nickname(){
	fin.open("datas//nickname.txt",ios::in);
	while(getline(fin,s)){
		int n=s.size(),i=0;
		string name="",wh="";
		while(s[i]!='<'&&i<n)++i;
		++i;
		while(s[i]!='>'&&i<n)name+=s[i],i++;
		while(i<n){
			if(wh!=""&&s[i]==' ')nickname[wh]=name,wh="",i++;
			else if(s[i]!=' ')wh+=s[i],++i;
		}
		if(wh!="")nickname[wh]=name;
	}
	fin.close(); 
	map<string,string>:: iterator it=nickname.begin();
	for(;it!=nickname.end();++it){
		cout<<"<"<<(*it).first<<"> <";
		cout<<(*it).second<<">\n";
	}
}
inline void init(){
	read_data();
	read_rating();
//	read_nickname();
}
inline double get_rating(double rating,int x){
	if(x>=10000000) return rating+2.00;
	if(x>=9800000) return rating+1+((int)(x-9800000)/2000)/100.0;
	return max(0.0,rating+((int)(x-9500000)/3000)/100.0);
}
inline void upper(string &sx){
	for(int i=0,sz=sx.size();i<sz;++i)
		if(sx[i]>='a'&&sx[i]<='z')
			sx[i]-=32;
}
signed main(){
	init();
	fout.open("datas//cache.txt",ios::out|ios::trunc);
	string nd;int x;
	while(1){
		cout<<"song? or input @ to exit\n";
		getline(cin,s);
		if(s=="@")break;
		if(nickname[s]!="")s=nickname[s];
		cout<<"PST or PRS or FTR or BYD\n";
		getline(cin,nd);upper(nd);
		node xt=node(s,nd);
		if(!rating[xt]){cout<<"The song is not found!!!\n";continue;}
		cout<<"Your score?\n";
		getline(cin,s);x=0;
		for(int i=0,sz=s.size();i<sz;++i)x=x*10+(s[i]^48);
		if(data[xt])data[xt]=max(data[xt],x);
		else data[xt]=x;
		printf("This song's rating is : %.2lf\nAnd your best score is : %d\n",get_rating(rating[xt],x),data[xt]);
	}
	map<node,int>:: iterator it=data.begin();
	for(;it!=data.end();++it){
		fout<<"<"<<(*it).first.name<<"> <"<<(*it).first.nd<<"> <";
		fout<<(*it).second<<">\n";
	}
	fout.close();
	fin.open("datas//cache.txt",ios::in);
	fout.open("datas//playdata.txt",ios::out|ios::trunc);
	while(getline(fin,s)){
		fout<<s<<endl;
	}
    return 0;
}


