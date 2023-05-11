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
struct b30{
	node y;
	int x;
	b30(){y=node("","");x=0;}
	b30(node b,int c){y=b,x=c;}
	bool operator<(const b30 &b)const{
		return get_rating(rating[y],x)<get_rating(rating[b.y],b.x);
	}
};
priority_queue<b30>qp;
inline void upper(string &sx){
	for(int i=0,sz=sx.size();i<sz;++i)
		if(sx[i]>='a'&&sx[i]<='z')
			sx[i]-=32;
}
inline void input(){
	fout.open("datas//playdata.txt",ios::out|ios::trunc);
	string nd;int x;letagain:
	cout<<"song? or input @ to exit\n";
	getline(cin,s);
	if(s=="@")return;
	if(nickname[s]!="")s=nickname[s];
	cout<<"PST or PRS or FTR or BYD\n";
	getline(cin,nd);upper(nd);
	node xt=node(s,nd);
	if(!rating[xt]){cout<<"The song is not found!!!\n";goto letagain;}
	cout<<"Your score?\n";
	getline(cin,s);x=0;
	for(int i=0,sz=s.size();i<sz;++i)x=x*10+(s[i]^48);
	if(data[xt])data[xt]=max(data[xt],x);
	else data[xt]=x;
	printf("This song's rating is : %.2lf\nAnd your best score is : %d\n",get_rating(rating[xt],x),data[xt]);
} 
inline void arcb30(){
	cout<<"Your PTT : \n";
	double ptt;int tot=0,i=0;
	getline(cin,s);int n=s.size();
	while(i<n&&s[i]!='.')ptt=ptt*10+(s[i]^48),++i;
	++i;ptt=ptt+(s[i]^48)*0.1+(i+1<n?(s[i+1]^48)*0.01:0);
	init();
	fout.open("!a b30.txt",ios::out|ios::trunc);
	map<node,int>:: iterator it=data.begin();
	for(;it!=data.end();++it)qp.push(b30((*it).first,(*it).second));
	b30 bi;
	double best30=0.0,best10=0.0;
	if(qp.size()<=30){
		while(!qp.empty()){
			bi=qp.top();if(tot<9)best10+=get_rating(rating[bi.y],bi.x);
			cout<<"song : "<<bi.y.name<<" "<<bi.y.nd<<" "<<setprecision(1)<<fixed<<rating[bi.y]<<"\nscore : "<<bi.x<<"\nrating : "<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x)<<"\n\n";
			fout<<"song : "<<bi.y.name<<" "<<bi.y.nd<<" "<<setprecision(1)<<fixed<<rating[bi.y]<<"\nscore : "<<bi.x<<"\nrating : "<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x)<<"\n\n";
			best30+=get_rating(rating[bi.y],bi.x);qp.pop();++tot;
		}
	}else{
		for(int i=0;i<30;i++){
			bi=qp.top();if(tot<10)best10+=get_rating(rating[bi.y],bi.x);
			cout<<"song : "<<bi.y.name<<" "<<bi.y.nd<<" "<<setprecision(1)<<fixed<<rating[bi.y]<<"\nscore : "<<bi.x<<"\nrating : "<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x)<<"\n\n";
			fout<<"song : "<<bi.y.name<<" "<<bi.y.nd<<" "<<setprecision(1)<<fixed<<rating[bi.y]<<"\nscore : "<<bi.x<<"\nrating : "<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x)<<"\n\n";
			best30+=get_rating(rating[bi.y],bi.x);qp.pop();++tot;
		}
		if(!qp.empty()){
			if(qp.size()<=10){
				cout<<"_______________\n\n";
				fout<<"_______________\n\n";
				while(!qp.empty()){
					bi=qp.top();qp.pop();
					cout<<"song : "<<bi.y.name<<" "<<bi.y.nd<<" "<<setprecision(1)<<fixed<<rating[bi.y]<<"\nscore : "<<bi.x<<"\nrating : "<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x)<<"\n\n";
					fout<<"song : "<<bi.y.name<<" "<<bi.y.nd<<" "<<setprecision(1)<<fixed<<rating[bi.y]<<"\nscore : "<<bi.x<<"\nrating : "<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x)<<"\n\n";
				}
			}else{
				cout<<"_______________\n\n";
				fout<<"_______________\n\n";
				for(int i=0;i<10;i++){
					bi=qp.top();
					cout<<"song : "<<bi.y.name<<" "<<bi.y.nd<<" "<<setprecision(1)<<fixed<<rating[bi.y]<<"\nscore : "<<bi.x<<"\nrating : "<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x)<<"\n\n";
					fout<<"song : "<<bi.y.name<<" "<<bi.y.nd<<" "<<setprecision(1)<<fixed<<rating[bi.y]<<"\nscore : "<<bi.x<<"\nrating : "<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x)<<"\n\n";
					qp.pop();
				}
			}
		}
	}
	double r10=(ptt*40-best30)/10.0;
	cout<<"b30 : "<<setprecision(2)<<fixed<<best30/30<<"\n";
	cout<<"r10 : "<<setprecision(2)<<fixed<<r10<<"\n";
	cout<<"ptt : "<<setprecision(2)<<fixed<<ptt<<"\n";
	cout<<"ptt_max : "<<setprecision(2)<<fixed<<(best30+best10)/40<<"\n";
	fout<<"b30 : "<<setprecision(2)<<fixed<<best30/30<<"\n";
	fout<<"r10 : "<<setprecision(2)<<fixed<<r10<<"\n";
	fout<<"ptt : "<<setprecision(2)<<fixed<<ptt<<"\n";
	fout<<"ptt_max : "<<setprecision(2)<<fixed<<(best30+best10)/40<<"\n";			
	fout.close();
}
signed main(){
	init();
	while(1){
		cout<<"1.input \n2.!a b30 \n3.exit \n";
		getline(cin,s);
		if(s=="3")break;
		if(s=="1"){
			input();
			map<node,int>:: iterator it=data.begin();
			for(;it!=data.end();++it){
				fout<<"<"<<(*it).first.name<<"> <"<<(*it).first.nd<<"> <";
				fout<<(*it).second<<">\n";
			}
			fout.close();
		}
		if(s=="2"){
			arcb30();
			break;
		}
	}
	fout.open("datas//playdata.txt",ios::out|ios::trunc);
	map<node,int>:: iterator it=data.begin();
	for(;it!=data.end();++it){
		fout<<"<"<<(*it).first.name<<"> <"<<(*it).first.nd<<"> <";
		fout<<(*it).second<<">\n";
	}
	fin.close();fout.close();
    return 0;
}


