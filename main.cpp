#include "game.h"
using namespace std;
const int N=1e5+5;
vector<int> eg[2][N],ln[N],num[N],line[50],dsr[50],dst;
int dis[2][N],vis[N];
void bfs(int s,int id){
	memset(dis[id],0,sizeof(dis[id]));
	memset(vis,0,sizeof(vis));
	queue<int> q;q.push(s);vis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:eg[id][u]){
			if(!vis[v])dis[id][v]=dis[id][u]+1,q.push(v),vis[v]=1;
		}
	}
}
#define in(vt,x) (lower_bound(vt.begin(),vt.end(),x)!=vt.end())
map<string,int> mp;
string city,name[N],distric[25],line_name[50];
int idx,line_num,Dnum;
int dnum[N][2],tim[N];
mt19937 rnd(time(0));
int rand_a_station(){
	srand(time(0));restart:
	int _way=((rand()%27)%9)%3;
	if(_way==0)return (rnd()+rnd()+rnd()+rnd()+rnd())%idx+1;
	if(_way==1){
		int x=(rnd()+rnd()+rnd()+rnd()+rnd())%line_num+1;
		if(!line[x].size())goto restart;
		vector<int> _ln(line[x]);
		shuffle(_ln.begin(),_ln.end(),rnd);
		reverse(_ln.begin(),_ln.end());
		shuffle(_ln.begin(),_ln.end(),rnd);
		reverse(_ln.begin(),_ln.end());
		shuffle(_ln.begin(),_ln.end(),rnd);
		int y=_ln[rnd()%_ln.size()];
		return y;
	}
	int x=dst[(rnd()+rnd()+rnd()+rnd()+rnd())%Dnum];
	vector<int> _ln(dsr[x]);
	shuffle(_ln.begin(),_ln.end(),rnd);
	reverse(_ln.begin(),_ln.end());
	shuffle(_ln.begin(),_ln.end(),rnd);
	reverse(_ln.begin(),_ln.end());
	shuffle(_ln.begin(),_ln.end(),rnd);
	int y=_ln[rnd()%_ln.size()];
	return y;
}
bool Guess(int ans=-1,int T=4,int tw=-1){
	Default;system("cls");Color(FLORALWHITE);
	if(!~ans)ans=rand_a_station();
	mp["放弃"]=mp["\\"]=ans;
	bfs(ans,0);bfs(ans,1);
	memset(vis,0,sizeof(vis));
//	cout<<ans<<" "<<name[ans]<<endl;
//	for(int i=1;i<=13;i++)cout<<vis[i]<<" ";cout<<endl;
	for(int v:ln[ans])vis[v]=1;
	cout<<"猜铁"<<city<<"      猜测次数：0 /"<<T;;if(~tw)cout<<"      连胜次数："<<tw;;cout<<"\n";
	cout<<"|        站名        |     区     |      线路      |  目标距离  |  目标换乘  |  投用时间  |\n";
	bool flag=0,gu=0;int nl=2;ShowCur();
	for(int t=0;t<=T;t++){
		Color(FLORALWHITE);gotoxy(24,0);cout<<t;if(t>=T)break;
		string s;gotoxy(0,nl);cin>>s;
		gotoxy(0,nl);for(int i=1;i<=(int)s.size();i++)cout<<"   ";
		if(mp.find(s)==mp.end()){
			Color(FIREBRICK);gotoxy(0,nl);cout<<"没有这个站！";t--;
			continue;
		}
		int u=mp[s];
		if(u==ans){
			Color(FLORALWHITE);gotoxy(24,0);cout<<t+1;
			gotoxy(0,nl);Color(LIMEGREEN);
			cout<<"|";Middle_Print(name[u],20);
			cout<<"|";Middle_Print(distric[dnum[u][0]],12);
			if(dnum[u][1])gotoxy(22,nl+1),Middle_Print(distric[dnum[u][1]],12),gotoxy(34,nl);
			cout<<"|";	
			for(int i=0;i<(int)ln[u].size();i++)gotoxy(35,nl+i),Middle_Print(line_name[ln[u][i]],16);
			gotoxy(51,nl);
			cout<<"|";Middle_Print(to_string(0),12);
			cout<<"|";Middle_Print(to_string(0),12);
			cout<<"|";Middle_Print(tim[u]<2100?to_string(tim[u]):"暂未开通",12);
			cout<<"|\n";flag=1;nl+=3;if(s=="放弃")gu=1;;break;
		}
		gotoxy(0,nl);Color(FLORALWHITE);cout<<"|";Middle_Print(name[u],20);cout<<"|";
		
		int x1=dnum[u][0],x2=dnum[u][1],y1=dnum[ans][0],y2=dnum[ans][1];
		if(x1==y1&&x2==y2)Color(LIMEGREEN);
		else if(x1==y1||x1==y2||(x2&&(x2==y1||x2==y2)))Color(BURLYWOOD);
		Middle_Print(distric[dnum[u][0]],12);
		if(dnum[u][1])gotoxy(22,nl+1),Middle_Print(distric[dnum[u][1]],12),gotoxy(34,nl);
		Color(FLORALWHITE);cout<<"|";
		
		bool f1=0;
		for(int v:ln[u])if(vis[v])f1=1;
		if(ln[u]==ln[ans])Color(LIMEGREEN);else if(f1)Color(BURLYWOOD);
		for(int i=0;i<(int)ln[u].size();i++)gotoxy(35,nl+i),Middle_Print(line_name[ln[u][i]],16);
		int d=dis[0][u],c=dis[1][u]/2-1;
		
		gotoxy(51,nl);
		Color(FLORALWHITE);cout<<"|";if(!d)Color(LIMEGREEN);
		Middle_Print(to_string(d),12);
		Color(FLORALWHITE);cout<<"|";if(!c)Color(LIMEGREEN);
		Middle_Print(to_string(c),12);
		Color(FLORALWHITE);cout<<"|";
		
		if(tim[u]==tim[ans]){
			Color(LIMEGREEN);
			Middle_Print(to_string(tim[u]),12);
			Color(FLORALWHITE);
		}
		else Middle_Print((tim[u]<2100?to_string(tim[u]):"暂未开通")+(tim[u]>tim[ans]?"v":"^"),12);
		cout<<"|\n";nl+=max((int)ln[u].size(),(bool)dnum[u][1]+1);
	}
	gotoxy(0,nl);
	if(flag){Color(LIMEGREEN),cout<<"恭喜你，你猜对了！";if(~tw)cout<<"\n连胜次数："<<tw+1;}
	else Color(FIREBRICK),cout<<"啊哦，你已经用完了猜测次数……\n答案："<<name[ans]<<endl;
	cout<<"\n";Color(FLORALWHITE);if(!~tw||!(flag&&!gu))system("pause");
	return flag&&!gu;
}
void Game(){
	Default;system("cls");Color(FLORALWHITE);HideCur();
	cout<<"猜铁"<<city<<"\n开始游戏[1]\n自定义[2]\n连胜[3]\n";
	char c;do c=Getc();while(c<49||c>51);
	if(c=='1')return Guess(),void();
	if(c=='2'){
		gotoxy(0,1);cout<<"导入[1]        \n导出[2]        \n                    ";
		do c=Getc();while(c!='1'&&c!='2');
		string s;gotoxy(0,1);
		cout<<"                    \n                    \n                    ";gotoxy(0,1);
		if(c=='1'){
			cout<<"请输入分享码：";
			cin>>s;s=decode(s);
			if(s=="-1"){cout<<"解码失败";Sleep(1000);return;}
			auto t=stois(s);
			if(t.size()!=2||t[0]>idx){cout<<"解码失败";Sleep(1000);return;}
			Guess(t[0],t[1]);
			return ;
		}
		cout<<"答案：";cin>>s;
		while(mp.find(s)==mp.end())gotoxy(6,1),Color(FIREBRICK),cout<<"没有这个站！",gotoxy(6,1),cin>>s;
		Color(FLORALWHITE);int t;cout<<"猜测次数：";cin>>t;
		string ss=to_string(mp[s])+'#'+to_string(t),tt=encode(ss);
		cout<<"分享码："<<tt<<"\n";
		WriteToClipboard(tt);cout<<"==已复制至剪贴板==\n";
		system("pause");return ;
	}
	gotoxy(0,1);cout<<"开始[1]        \n导入[2]        \n                    ";
	vector<int> sta(idx);
	do c=Getc();while(c!='1'&&c!='2');
	string s;gotoxy(0,1);int bgnum=0;
	cout<<"                    \n                    \n                    ";gotoxy(0,1);
	if(c=='2'){
		cout<<"请输入存档码：";
		cin>>s;s=decode(s);
		if(s=="-1"){cout<<"解码失败";Sleep(1000);return;}
		sta=stois(s);
		if((int)sta.size()!=idx+1){cout<<"解码失败";Sleep(1000);return;}
		bgnum=sta.back();
		sta.pop_back();
	}
	else{
		for(int i=0;i<idx;i++)sta[i]=idx-i;
		shuffle(sta.begin(),sta.end(),rnd);
	}
	for(int i=bgnum;i<=idx;i++){
		if(i==idx){
			system("cls");Color(LIMEGREEN);
			cout<<"你的成绩：全对（"<<idx<<"个）\n";
			break;
		}
		if(!Guess(sta[i],4,i)){
			system("cls");Color(FLORALWHITE);
			cout<<"你的成绩："<<i<<"个\n";
			break;
		}
		cout<<"请按任意键继续，按[Tab]键导出存档...\n";
		c=Getc();
		if(c==9){
			string t="";
			for(auto x:sta)t+=to_string(x)+'#';
			t+=to_string(i+1);
			t=encode(t);
			cout<<"分享码："<<t<<"\n";
			WriteToClipboard(t);
			cout<<"==已复制至剪贴板==\n";
			break;
		}
	}
	system("pause");
}
void init(){
	cout<<"猜糖2.3   by __yun__(luogu uid=749539)\n";
	cout<<"猜测时输入“放弃”即可直接显示答案\n";
	cout<<"猜铁天津：为保证连通，我们认为 Z4 线泰达站已开通，与北塘站距离为 1 站\n";
	string op,s;cout<<"选择城市（天津/青岛/济南）";cin>>city;
	ifstream fin;
	{op=city+"/distric.txt";
	fin.open(op.c_str(),ios::in);fin>>line_num;
	int y;fin>>Dnum;for(int i=1;i<=Dnum;i++)fin>>y>>s,distric[y]=s,dst.pb(y);
	fin.close();}
	for(int i=1;i<=line_num;i++){
		op=city+"/"+to_string(i)+".txt";
		fin.open(op.c_str(),ios::in);
		fin>>line_name[i];
		int x,lst=-1;fin>>x;
		while(x--){
			fin>>s;
			if(!mp.count(s))mp[s]=++idx,name[idx]=s;
			int u=mp[s];if(~lst)eg[0][u].pb(lst),eg[0][lst].pb(u);
			if(!in(ln[u],i))ln[u].pb(i),line[i].pb(u);
			lst=u;
		}
		fin.close();
	}
	op=city+"/station.txt";
	fin.open(op.c_str(),ios::in);
	for(int i=1;i<=idx;i++){
		fin>>s;int u=mp[s];
		if(s.find('(')){
			int x=s.find('(');
			mp[s.substr(0,x)]=u;
			mp[s.substr(x+1,s.size()-x-2)]=u;
		}
		fin>>tim[u]>>dnum[u][0];
		if(dnum[u][0]>100){
			dnum[u][1]=dnum[u][0]%100;
			dnum[u][0]=dnum[u][0]/100;
		}
		dsr[dnum[u][0]].pb(u);
		if(dnum[u][1])dsr[dnum[u][1]].pb(u);
	}
	fin.close();
	for(int i=1;i<=idx;i++){
		for(int u:ln[i])eg[1][u+idx].pb(i),eg[1][i].pb(u+idx);
	}
}
int main(){
	init();
	while(1){
		Game();
	}
	return 0;
}
