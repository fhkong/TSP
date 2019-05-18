#include<iostream>
#include<algorithm>
#include<math.h>
#include<time.h>
using namespace std;
/*
作者：孔凡豪
时间：2019年5月

！！！注意事项：
测试不同的点集时
要改变两个参数
1.常量number ，即顶点的个数
2.数据文件，即main函数里的freopen函数第一个参数

*/


const int MAX_N = 32; //最大的城市个数
const int INF = INT_MAX;
const int number = 10;  //顶点数

struct Node
{
	int id;
	float x,y;
};

bool ReadFiles(int &n)
{
	n = number;
	if(n > MAX_N)
	   {
		 cout<<"城市的个数过大"<<endl;
		 return false;
  	   }
	return true;
}

bool CalculateDistance(float ** &Distance,Node *&Array,int n)
{
	Distance = new float*[n];
	for(int i=0;i<n;i++)
	{
		Distance[i] = new float[n];
	}

	Array = new Node[n];
	
	//读入坐标数据
	for(int i=0;i<n;i++)
	{
		cin>>Array[i].id>>Array[i].x>>Array[i].y;
	}
	for(int i=0;i<n;i++)
	{
		for(int j=i;j<n;j++) //由对称性可知，只算半三角
		{
			if(i == j)
			Distance[i][j] = INF;
			else
			{
				float temp1 = (Array[i].x-Array[j].x)*(Array[i].x-Array[j].x);
				float temp2 = (Array[i].y-Array[j].y)*(Array[i].y-Array[j].y);
				Distance[i][j] = Distance[j][i] = sqrt(temp1+temp2);
			}
		}
	}
	return true;
}

void DisplayDistance(float **Distance,int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<Distance[i][j]<<" ";
		}
		cout<<endl;
	}
}

float DP(float **Distance,int n)
{
	float dp[n][1<<(n-1)];  //每一列代表一个集合。
	for(int i=1;i<n;i++)
	{
		dp[i][0] = Distance[i][0];  //初始化第一列，每个点到0号顶点的距离
	}
	
	for(int j=1;j < 1<<(n-1);j++)  //例如n=4从0001到0111
	{
		for(int i=1;i<n;i++)
		{
			if((1<<(i-1) & j )== 0)  //i不在当前的集合里面
			{
				float min = INT_MAX; //初始化为最大值
				for(int k=1;k<n;k++)
				{
					if((1<<(k-1) & j) != 0) //k在当前集合里面
					{
                        if(Distance[i][k] + dp[k][j-(1<<(k-1))] < min) //找到最小值
						{
							min = Distance[i][k] + dp[k][j-(1<<(k-1))];
						}
					}
			    }
				dp[i][j] = min;
				//cout<<i<<"->"<<j<<": "<<dp[i][j]<<endl;
			}
		}
	}
	
	//下面计算从0开始经过n-1个点回到0的最小距离
	float min = INT_MAX;
	int flag = 0;
	for(int k=1;k<n;k++)
	{
		if(Distance[0][k]+dp[k][(1<<(n-1))-1 - (1<<(k-1))] < min)
		{
		  min = Distance[0][k] + dp[k][(1<<(n-1)) - 1 - (1<<(k-1))];
		  flag = k;
		}
	}
	cout<<"路径是：";
	cout<<"0->"<<flag;
	int	j = (1<<(n-1))-1-(1<<(flag-1));
	int t;
	while(j)
	{
		float min = INT_MAX;
		for(int k = 1;k<n;k++)
		{
			if((1<<(k-1) & j) != 0)
			{
				float temp = Distance[flag][k]+dp[k][j-(1<<(k-1))];
				if(temp<min)
				{
					min = temp;
					t = k;
				}
			}
		}
		flag = t;
		cout<<"->"<<flag;
		j = j-(1<<(flag-1));
	}
	cout<<"->0"<<endl;
	
	cout<<"最短距离为：";
	return min;
}
int main()
{
	clock_t start,finish;
	double duration;
	int n;
	freopen("2.txt","r",stdin);
	//freopen("w.txt","w",stdout);
	if(ReadFiles(n))
	{
	    float **Distance;
		Node *Array;
		CalculateDistance(Distance,Array,n);
		//DisplayDistance(Distance,n);
		start = clock();
		cout<<DP(Distance,n)<<endl;
		finish = clock();
		duration = (double)(finish - start)/CLOCKS_PER_SEC;
		cout<<"耗时为: "<<duration<<endl;
	}
	
}
