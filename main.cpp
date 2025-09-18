#include <bits/stdc++.h>
//#include <bits/extc++.h>
//#define int long long
#define INLINE inline __attribute__((always_inline))
#define BreakPlus break
#define liuhengxi continue
#define __BEGIN_MULTITEST__ \
	signed T; \
	scanf("%d",&T);getchar(); \
	while(T--) \
	{
#define __END_MULTITEST__ }
struct node
{
	std::string P,G;
	bool right;
	int iid;
	node(const std::string &p,const std::string &g,const bool &r,const int &id) :
		P(p),G(g),right(r),iid(id) {}
	node() {}
};
using ll=long long;
using i128=__int128;
using vector_M=std::vector<node>;
using namespace std;
//using namespace __gnu_cxx;
//using namespace __gnu_pbds;
const int N=1005;
string s[N];
char endchar(const string &s) {return s[s.length()-1];}
bool is_be(const string &s) {return s=="am"||s=="is"||s=="are";}
string TPTN(const string &s) // Third Person To Normal 
{
	if(is_be(s))
		return "is";
	if(s=="does")
		return "do";
	if(s=="doesn't")
		return "don't";
	if(endchar(s)=='s')
		return s.substr(0,s.length()-1);
	return s;
}
string NTTP(const string &M,const string &s) // Normal To Third Person 
{
	if(M!="I"&&M!="you")
	{
		if(s=="do")
			return "does";
		if(s=="don't")
			return "doesn't";
		if(is_be(s))
			return "is";
		return s+'s';
	}
	if(is_be(s))
		return M=="I"?"am":"are";
	return s;
}
bool operator==(const node &x,const node &y) {return x.P==y.P&&x.G==y.G;}
int Dialog=0;
vector<string> vec;
vector_M wide;
string st;
bool abr=0;
map<string,vector_M> _Mp; // P and G to M
INLINE string _TransPerson(const string &s) {return s=="I"?"you":(s=="you"?"I":s);}
INLINE string _TransGuest(const string &s) {return s=="I"?"you":(s=="you"?"me":s);}
INLINE bool WideRange(const string &s) {return s=="everybody"||s=="nobody";}
INLINE void _Abroad(const node &nd,const vector<node> &v)
{
	for(auto i:v)
		if(i==nd&&i.right!=nd.right)
		{
			abr=1;
			BreakPlus;
		}
}
INLINE void _State(int iid)
{
	st=st.substr(0,st.length()-1);
	string M=vec[0];
	vec[1]=TPTN(vec[1]);
//	fprintf(stderr,"%s\n",P.c_str());
	bool right=1;
	right^=(M=="nobody")^(vec[1]=="don't");
//	fprintf(stderr,"%d\n",right);
	if(vec[1]=="don't")
	{
		vec[2]=TPTN(vec[2]);
//		fprintf(stderr,"%s\n",P.c_str());
	}
	string &P=vec[1]=="don't"?vec[2]:vec[1];
	string &G=P==vec[1]?vec[2]:vec[3];
	if(is_be(P))
		P="is";
//	fprintf(stderr,"%s %s %d %d\n",P.c_str(),G.c_str(),right,iid);
	node nd=node(P,G,right,iid);
	if(!WideRange(M))
	{
		_Mp[M].emplace_back(nd);
		_Abroad(nd,_Mp[M]);
		_Abroad(nd,wide);
	}
	else
	{
		wide.emplace_back(nd);
		for(auto i:_Mp)
			_Abroad(nd,i.second);
		_Abroad(nd,wide);
	}
}
INLINE void _Judge(const string &M,const node &nd,bool &jd,const vector<node> &v)
{
#define P nd.P
#define G nd.G
	if(jd)
		return;
	for(auto i:v)
		if(i==nd)
		{
			string ans=(i.right==nd.right?"yes":"no")+string(", ")+M+' '+(i.right==nd.right?NTTP(M,P):NTTP(M,"do")+"n't "+P)+(G==""?"":' '+G)+'.';
			printf("%s\n",ans.c_str());
			return jd=1,[]{}();
		}
#undef P
#undef G
}
INLINE void _Query(int iid)
{
	printf("%s\n",st.c_str());
	if(abr)
		return printf("I am abroad.\n"),[]{}();
	st=st.substr(0,st.length()-1);
	string Q=vec[0];
	if(Q=="do"||Q=="does")
	{
		string &M=vec[1];
		bool right=1;
		right^=(M=="nobody");
		string sl,sr,&P=vec[2],&G=vec[3];
		bool spl=0;
		for(int i=0;i<(int)P.length();i++)
		{
			if(!spl&&P[i]==' ')
			{
				sl=P.substr(0,i);
				spl=1;
				liuhengxi;
			}
			if(spl)
				sr+=P[i];
		}
		if(spl)
		{
			P=sl;
			G=sr;
		}
//		fprintf(stderr,"%s\n%s\n\n",P.c_str(),G.c_str());
		M=_TransPerson(M);
		Q=TPTN(Q);
		P=TPTN(P);
		bool jd=0;
		node nd=node(P,G,right,iid);
		_Judge(M,nd,jd,_Mp[M]);
		_Judge(M,nd,jd,wide);
		if(!jd)
			printf("maybe.\n");
		return;
	}
	if(Q=="who")
	{
		string &P=vec[1],&G=vec[2];
		P=TPTN(P);
		if(is_be(P))
			P="is";
		vector<node> ans;
		node tmp;
		string M;
		bool Wide=0;
		for(auto i:wide)
			if(i==node(P,G,"",iid))
			{
				M=i.right?"everybody":"nobody"; 
				Wide=1;
				BreakPlus;
			}
		if(Wide)
			return printf("%s %s.\n",M.c_str(),(NTTP(M,P)+(G==""?"":' '+G)).c_str()),[]{}();
		for(auto i:_Mp)
			for(auto j:i.second)
				if(j==node(P,G,Wide,iid)&&j.right)
				{
					ans.emplace_back(i.first,"",0,j.iid);
					BreakPlus;
				}
		sort(ans.begin(),ans.end(),[&](const node &x,const node &y){return x.iid<y.iid;});
		switch(ans.size())
		{
			case 0:
				printf("I don't know.\n");
				BreakPlus;
			case 1:
			{
				string &M=ans[0].P;
				M=_TransPerson(M);
//				fprintf(stderr,"[Debug] G=%s\n",G.c_str());
				printf("%s %s.\n",M.c_str(),(NTTP(M,P)+(G==""?"":' '+_TransGuest(G))).c_str());
				BreakPlus;
			}
			default:
			{
				for(int i=0;i<(int)ans.size();i++)
				{
					string &M=ans[i].P;
					M=_TransPerson(M);
					printf("%s",((i==(int)ans.size()-1?"and ":"")+M+(i>=(int)ans.size()-2?" ":", ")).c_str());
				}
				printf("%s.\n",(NTTP("you",P)+(G==""?"":' '+_TransGuest(G))).c_str());
				BreakPlus;	
			}
		}
		return;
	}
	if(Q=="what")
	{
		bool right=1;
		string &M=vec[2];
		for(int i=0;i<(int)M.length();i++)
			if(M[i]==' ')
			{
				M=M.substr(0,i);
				BreakPlus; 
			}
		right^=(M=="nobody");
		bool tp=(_TransPerson(M)==M);
		vector<node> ans;
//		fprintf(stderr,"%s\n",M.c_str());
//		fprintf(stderr,"%d\n",tp);
		for(auto i:_Mp[M])
			ans.emplace_back(i);
		M=_TransPerson(M);
		for(auto i:wide)
		{
			ans.emplace_back(i);
//			fprintf(stderr,"%s %s %d %d",i.P.c_str(),i.G.c_str(),i.right,i.iid);
		}
		sort(ans.begin(),ans.end(),[&](const node &x,const node &y){return x.iid<y.iid;});
		ans.erase(unique(ans.begin(),ans.end()),ans.end());
		switch(ans.size())
		{
			case 0:
				printf("I don't know.\n");
				BreakPlus;
			case 1:
			{
				string &P=ans[0].P,&G=ans[0].G;
				printf("%s %s.\n",M.c_str(),((ans[0].right^right?(tp?"doesn't ":"don't ")+TPTN(P):NTTP(M,P))+(G==""?"":' '+_TransGuest(G))).c_str());
				BreakPlus;
			}
			default:
			{
				printf("%s ",M.c_str()); 
				for(int i=0;i<(int)ans.size();i++)
				{
					string &P=ans[i].P,&G=ans[i].G;
					printf("%s",(string(i==(int)ans.size()-1?"and ":"")+(ans[i].right^right?(tp?"doesn't ":"don't ")+TPTN(P):NTTP(M,P))+(G==""?"":' '+_TransGuest(G))+(i==(int)ans.size()-1?".\n":", ")).c_str());
				}
				BreakPlus;
			}
		}
		return;
	}
	fprintf(stderr,"what's this?\n");
	return;
}
signed main()
{
	__BEGIN_MULTITEST__
	abr=0;
	_Mp.clear();
	wide.clear();
	printf("Dialogue #%d:\n",++Dialog);
	getline(cin,st);
	int iid=0;
	while(endchar(st)!='!')
	{
		if(st=="who are you?")
		{
			ifstream ifs("recall.txt");
			string S="";
			while(getline(ifs,S))
				printf("%s\n",S.c_str());
			getline(cin,st);
			liuhengxi;
		}
		vec.clear();
//		fprintf(stderr,"111\n");
		int b=1,c=0;
		string tmp;
		for(int i=0;i<(int)st.length();i++)
			if(st[i]==' '&&c<=b)
			{
				c++;
				vec.emplace_back(tmp);
				if(tmp=="don't"||tmp=="doesn't")
					b++;
				tmp="";
			}
			else
				tmp+=st[i];
		tmp=tmp.substr(0,tmp.length()-1);
		vec.emplace_back(tmp);
		vec.resize(max((int)vec.size(),4));
//		for(auto i:vec)
//			fprintf(stderr,"%s\n",i.c_str());
		if(endchar(st)=='.')
			_State(++iid);
		else
		{
			_Query(++iid);
			printf("\n");
		}
		getline(cin,st);
	}
	printf("%s\n\n",st.c_str());
	__END_MULTITEST__
	return 0;
}

