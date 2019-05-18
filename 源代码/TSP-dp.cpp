#include<iostream>
#include<algorithm>
#include<math.h>
#include<time.h>
using namespace std;
/*
���ߣ��׷���
ʱ�䣺2019��5��

������ע�����
���Բ�ͬ�ĵ㼯ʱ
Ҫ�ı���������
1.����number ��������ĸ���
2.�����ļ�����main�������freopen������һ������

*/


const int MAX_N = 32; //���ĳ��и���
const int INF = INT_MAX;
const int number = 10;  //������

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
		 cout<<"���еĸ�������"<<endl;
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
	
	//������������
	for(int i=0;i<n;i++)
	{
		cin>>Array[i].id>>Array[i].x>>Array[i].y;
	}
	for(int i=0;i<n;i++)
	{
		for(int j=i;j<n;j++) //�ɶԳ��Կ�֪��ֻ�������
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
	float dp[n][1<<(n-1)];  //ÿһ�д���һ�����ϡ�
	for(int i=1;i<n;i++)
	{
		dp[i][0] = Distance[i][0];  //��ʼ����һ�У�ÿ���㵽0�Ŷ���ľ���
	}
	
	for(int j=1;j < 1<<(n-1);j++)  //����n=4��0001��0111
	{
		for(int i=1;i<n;i++)
		{
			if((1<<(i-1) & j )== 0)  //i���ڵ�ǰ�ļ�������
			{
				float min = INT_MAX; //��ʼ��Ϊ���ֵ
				for(int k=1;k<n;k++)
				{
					if((1<<(k-1) & j) != 0) //k�ڵ�ǰ��������
					{
                        if(Distance[i][k] + dp[k][j-(1<<(k-1))] < min) //�ҵ���Сֵ
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
	
	//��������0��ʼ����n-1����ص�0����С����
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
	cout<<"·���ǣ�";
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
	
	cout<<"��̾���Ϊ��";
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
		cout<<"��ʱΪ: "<<duration<<endl;
	}
	
}
