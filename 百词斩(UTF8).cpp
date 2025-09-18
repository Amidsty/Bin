#include <bits/stdc++.h>
//#include <bits/extc++.h>
//#define int long long
using namespace std;
//using namespace __gnu_cxx;
//using namespace __gnu_pbds;
string E[100005]; 
string C[100005];
int vis[100005];
int cntE=0,cntC=0,tot=0,wrong=0,correct=0,comb=0;
string st;
mt19937 mt(time(0)*rand()*998244353);
signed main()
{
	ifstream ifs("word.txt");
	while(getline(ifs,E[++cntE]))
	{
		if(E[cntE]==" "||E[cntE]=="\r"||E[cntE]=="\n"||E[cntE]=="::"||E[cntE]=="")
		{
			if(E[cntE]=="::")
			{
				cntE--;
				break;
			}
			cntE--;
		}
		fflush(stdin);
	}
	while(getline(ifs,C[++cntC]))
		fflush(stdin);
	printf("review for a few minutes, please enter the time(ms): \n");
	unsigned t;
	scanf("%u",&t);
	for(int i=1;i<=cntE;i++)
		printf("————————————\n%s\n%s\n",E[i].c_str(),C[i].c_str());
	_sleep(t);
	system("cls");
	fflush(stdin);
	printf("choose mode [1: CH to EN, 2: EN to CH (recommended)]:");
	int op;
	scanf("%d",&op);
	if(op==1)
	{
		while(1)
		{
			if(!cntE)
			{
				system("pause");
				return 0;
			}
			int tmp=mt()%cntE+1;
			printf("%s\n",E[tmp].c_str());
			fflush(stdin);
			getline(cin,st);
			if(st=="END")
			{
				system("pause");
				return 0;
			}
			printf("Right Answer: %s\n",C[tmp].c_str());
			fflush(stdin);
			E[tmp]=C[tmp]="";
			for(int i=tmp+1;i<=cntE;i++)
			{
				E[i-1]=E[i];
				C[i-1]=C[i];
			}
			cntE--;
		}
	}
	else
	{
		while(1)
		{
			if(!cntE)
			{
				printf("————————————————\nCorrect: %d/%d %.3lf%%\nMaximum Consecutive Correct Ones: %d\n",tot-wrong,tot,100.0*(tot-wrong)/tot,comb);
				system("pause");
				return 0;
			}
			int tmp=mt()%cntE+1;
			printf("%s\n",C[tmp].c_str());
			fflush(stdin);
			getline(cin,st);
			if(st=="END")
			{
				printf("————————————————\nCorrect: %d/%d %.3lf%%\nMaximum Consecutive Correct Ones: %d\n",tot-wrong,tot,100.0*(tot-wrong)/tot,comb);
				system("pause");
				return 0;
			}
			tot++;
			if(st==E[tmp])
			{
				correct++;
				if(correct>4)
					printf("Correct! %d Consecutive Correct Ones!\n",correct);
				else
				{
					switch(correct)
					{
						case 1:
							printf("Correct!\n");
							break;
						case 2:
							printf("Doubly Correct!\n");
							break;
						case 3:
							printf("Triply Correct!\n");
							break;
						default:
							printf("Quadruply Correct!\n");
							break;
					}
				}
			}
			else
			{
				wrong++;
				comb=max(comb,correct);
				correct=0;
				printf("Wrong! The Right Answer is \"%s\".\n",E[tmp].c_str());
			}
			E[tmp]=C[tmp]="";
			for(int i=tmp+1;i<=cntE;i++)
			{
				E[i-1]=E[i];
				C[i-1]=C[i];
			}
			cntE--;
		}
	}
	return 0;
}

