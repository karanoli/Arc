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
map<double,vector<node> >disrat;
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
			disrat[ds].push_back(node(name,nd));
		}
	}
	fin.close(); 
//	map<node,double>:: iterator it=rating.begin();
//	for(;it!=rating.end();++it){
//		cout<<"<"<<(*it).first.name<<"> <"<<(*it).first.nd<<"> <";
//		cout<<(*it).second<<">\n";
//	}
}
map<node,string>web;
inline void read_web(){
	fin.open("datas//website.txt",ios::in);
	while(getline(fin,s)){
		int n=s.size(),i=0;
		string name="",nd="" ,wz="";
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
			while(i<n&&s[i]!='>') wz+=s[i],i++;
		}
		web[node(name,nd)]=wz;
	}
	fin.close(); 
}
inline void init(){
	read_data();
	read_rating();
	read_web();
}
inline double get_rating(double rating,int x){
	if(x>=10000000) return rating+2.00;
	if(x>=9800000) return rating+1+(x-9800000)/200000.0;
	return max(0.0,rating+(x-9500000)/300000.0);
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
	string nd;int x;node xt;letagain:
	cout<<"song or song's rating ? or input @ to exit\n";
	getline(cin,s);
	if(s=="@")return;
	if((isdigit(s[0])&&isdigit(s[1])&&s[2]=='.')||(isdigit(s[0])&&s[1]=='.')){
		double ds=0.0; int i=0,n=s.size();
		while(i<n&&s[i]!='.')ds=ds*10+(s[i]^48),++i;
		++i;ds=ds+(s[i]^48)*0.1;
		if(ds<8.0||ds>12.0){cout<<"The rating is not found!!!\n";goto letagain;}
		vector<node>:: iterator it=disrat[ds].begin();
		for(i=0;it!=disrat[ds].end();++it){
			cout<<++i<<". "<<(*it).name<<" "<<(*it).nd<<"\n";
		}
		getline(cin,s);i=0;n=s.size();x=0;
		while(i<n&&s[i]!='.')x=x*10+(s[i]^48),++i;
		xt=disrat[ds][x-1];
	}else{
		cout<<"PST or PRS or FTR or BYD\n";
		getline(cin,nd);upper(nd);
		xt=node(s,nd);
		if(!rating[xt]){cout<<"The song is not found!!!\n";goto letagain;}
	}
	cout<<"Your score?\n";
	getline(cin,s);x=0;
	for(int i=0,sz=s.size();i<sz;++i)x=x*10+(s[i]^48);
	if(data[xt])data[xt]=max(data[xt],x);
	else data[xt]=x;
	printf("This song's rating is : %.2lf\nAnd your best score is : %d\n",get_rating(rating[xt],x),data[xt]);
} 
double ptt,best30,best10;
inline void arcb30(){
	cout<<"Your PTT : \n";
	ptt=0.0;int tot=0,i=0;
	getline(cin,s);int n=s.size();
	while(i<n&&s[i]!='.')ptt=ptt*10+(s[i]^48),++i;
	++i;ptt=ptt+(s[i]^48)*0.1+(i+1<n?(s[i+1]^48)*0.01:0);
	fout.open("!a b30.txt",ios::out|ios::trunc);
	map<node,int>:: iterator it=data.begin();
	for(;it!=data.end();++it)qp.push(b30((*it).first,(*it).second));
	b30 bi;
	best30=0.0,best10=0.0;
	if(qp.size()<=30){
		while(!qp.empty()){
			bi=qp.top();if(tot<9)best10+=get_rating(rating[bi.y],bi.x);
			fout<<"song : "<<bi.y.name<<" "<<bi.y.nd<<" "<<setprecision(1)<<fixed<<rating[bi.y]<<"\nscore : "<<bi.x<<"\nrating : "<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x)<<"\n\n";
			best30+=get_rating(rating[bi.y],bi.x);qp.pop();++tot;
		}
	}else{
		for(int i=0;i<30;i++){
			bi=qp.top();if(tot<10)best10+=get_rating(rating[bi.y],bi.x);
			fout<<"song : "<<bi.y.name<<" "<<bi.y.nd<<" "<<setprecision(1)<<fixed<<rating[bi.y]<<"\nscore : "<<bi.x<<"\nrating : "<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x)<<"\n\n";
			best30+=get_rating(rating[bi.y],bi.x);qp.pop();++tot;
		}
		if(!qp.empty()){
			if(qp.size()<=10){
				cout<<"_______________\n\n";
				fout<<"_______________\n\n";
				while(!qp.empty()){
					bi=qp.top();qp.pop();
					fout<<"song : "<<bi.y.name<<" "<<bi.y.nd<<" "<<setprecision(1)<<fixed<<rating[bi.y]<<"\nscore : "<<bi.x<<"\nrating : "<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x)<<"\n\n";
				}
			}else{
				cout<<"_______________\n\n";
				fout<<"_______________\n\n";
				for(int i=0;i<10;i++){
					bi=qp.top();
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
inline string nd_change(string nd,double rating){
	string s="";char a,b,c;
	if(rating>=10){
		a=((((int)(rating/10))%10)+'0');//if(a=='0')a='\0';
		b=((((int)(rating))%10)+'0');c=((((int)(rating*10))%10+'0'));
		s=s+a+b+'.'+c;
	}else{
		b=((((int)(rating))%10)+'0');c=((((int)(rating*10))%10+'0'));
		s=s+b+'.'+c;
	}
	if(nd=="BYD")return "${\\color{red}"+s+"}$";
	else if(nd=="FTR") return "${\\color{purple}"+s+"}$";
	else return "${\\color{green}"+s+"}$";
}
inline void get_md(){
	int tot=0;
	fout.open("!a b30.md",ios::out|ios::trunc);
	while(!qp.empty())qp.pop();
	map<node,int>:: iterator it=data.begin();
	for(;it!=data.end();++it)qp.push(b30((*it).first,(*it).second));
	b30 bi;
	double r10=(ptt*40-best30)/10.0;
	fout<<"|ptt|b30|r10|pttmax|\n|:-:|:-:|:-:|:-:|\n"<<"|"<<setprecision(2)<<fixed<<ptt<<"|";
	fout<<setprecision(2)<<fixed<<best30/30<<"|";
	fout<<setprecision(2)<<fixed<<r10<<"|";
	fout<<setprecision(2)<<fixed<<(best30+best10)/40<<"|\n\n";
	fout<<"|song|score|song|score|song|score|song|score|\n|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|\n";
	if(qp.size()<=30){
		while(!qp.empty()){
			bi=qp.top();++tot;
			fout<<"|${\\color{blue}"<<tot<<"}$ "<<bi.y.name.substr(0,7)+(bi.y.name.size()<7?" ":"...")<<"<br>![]("<<web[bi.y]<<")<br>";
			fout<<nd_change(bi.y.nd,rating[bi.y])<<"|"<<bi.x<<"<br>"<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x);
			qp.pop();if(tot%4==0)fout<<"|\n";
		}
	}else{
		for(int i=0;i<30;i++){
			bi=qp.top();++tot;
			fout<<"|${\\color{blue}"<<tot<<"}$ "<<bi.y.name.substr(0,7)+(bi.y.name.size()<7?" ":"...")<<"<br>![]("<<web[bi.y]<<")<br>";
			fout<<nd_change(bi.y.nd,rating[bi.y])<<"|"<<bi.x<<"<br>"<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x);
			qp.pop();if(tot%4==0)fout<<"|\n";
		}
		if(!qp.empty()){
			//cout<<qp.size()<<endl;
			if(qp.size()<=10){
				while(!qp.empty()){
					bi=qp.top();++tot;
					fout<<"|${\\color{blue}"<<tot<<"}$ "<<bi.y.name.substr(0,7)+(bi.y.name.size()<7?" ":"...")<<"<br>![]("<<web[bi.y]<<")<br>";
					fout<<nd_change(bi.y.nd,rating[bi.y])<<"|"<<bi.x<<"<br>"<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x);
					qp.pop();if(tot%4==0)fout<<"|\n";
				}
			}else{
				for(int i=0;i<10;i++){
					bi=qp.top();++tot;
					fout<<"|${\\color{blue}"<<tot<<"}$ "<<bi.y.name.substr(0,7)+(bi.y.name.size()<7?" ":"...")<<"<br>![]("<<web[bi.y]<<")<br>";
					fout<<nd_change(bi.y.nd,rating[bi.y])<<"|"<<bi.x<<"<br>"<<setprecision(2)<<fixed<<get_rating(rating[bi.y],bi.x);
					qp.pop();if(tot%4==0)fout<<"|\n";
				}
			}
		}
	}			
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
			for(;it!=data.end();++it){fout<<"<"<<(*it).first.name<<"> <"<<(*it).first.nd<<"> <";fout<<(*it).second<<">\n";}
			fout.close();
		}
		if(s=="2"){
			arcb30();
			get_md();
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


