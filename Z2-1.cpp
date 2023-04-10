#include <iostream>
#include <queue>
using namespace std;
int a,b,k,cnt[200005];
bool vis[200005];
queue<int> q;
void bfsPart(int nx, int f)
{
	q.push(nx);
	vis[nx]=true;
	cnt[nx]=cnt[f]+1;
}
bool check(int nx)
{
	return nx>0&&nx<=2e5&&!vis[nx];
}
int main()
{
	cin>>a>>b>>k;
	q.push(a);
	vis[a]=true;
	cnt[a]=0;
	while (!q.empty())
	{
		int first=q.front();
		q.pop();
		if (first==b)
		{
			cout<<cnt[b]<<endl;
			break;
		}
		int nowX;
		nowX=first-1;
		if (check(nowX)) bfsPart(nowX, first);
		for (int i=2;i<=k;i++)
        {
            nowX=first-first%i;
            if (check(nowX)) bfsPart(nowX, first);
        }
	}
	return 0;
}