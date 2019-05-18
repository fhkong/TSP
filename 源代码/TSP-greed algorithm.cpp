#include<bits/stdc++.h>
using namespace std;

/*
作者：孔凡豪
时间：2019年5月

！！！注意事项：
测试不同的点集时
要改变两个参数
1.常量vexnum ，即城市的个数
2.数据文件，即main函数里的freopen函数第一个参数

*/


struct Node
{
	int id;
    int x;
    int y;
};

const int vexnum = 10;  //最大城市个数
Node Array[vexnum+1];  //0号单元未用，从1开始
float Dis[vexnum+1][vexnum+1];    

void ReadDate()
{
    for(int i=1;i<=vexnum;i++)
        cin>>Array[i].id>>Array[i].x>>Array[i].y;
}

void Distance()
{
    for(int i=1;i<=vexnum;i++)
    {
        for(int j=i;j<=vexnum;j++)  //计算出距离矩阵
        {
            Dis[i][j] = Dis[j][i] = sqrt((Array[i].x-Array[j].x)*(Array[i].x-Array[j].x)+(Array[i].y-Array[j].y)*(Array[i].y-Array[j].y));
        }
    }
}

void PrintDis()
{
    for(int i=1;i<=vexnum; i++)
    {
        for(int j=1;j<=vexnum;j++)
        cout<<Dis[i][j]<<" ";
        cout<<endl;
    }
}

void PrintData()
{
	for(int i=1;i<=vexnum;i++)
	{
		cout<<Array[i].id<<" "<<Array[i].x<<" "<<Array[i].y<<endl;
	}
}

float SoveTsp()
{
    bool visited[vexnum+1];
    float sum = 0;
    for(int i=1;i<=vexnum;i++)
      visited[i] = false;
    
    visited[1] = true;  //从1开始
    
    int mindistance; //
	int start = 1; //
    cout<<"1->";
    for(int i=1; i<=vexnum -1 ; i++) //循环n-1次
    {
        
        float min = INT_MAX;
        for(int j = 1; j<=vexnum; j++)
        {
            if(!visited[j] && Dis[start][j] < min)
            {
                min = Dis[start][j];
                mindistance = j;
            }
        }
       
        sum += min;
        //cout<<sum<<endl;
        visited[mindistance] = true;
        cout<<mindistance<<"->";
        start = mindistance;
    }
    cout<<"1"<<endl;
    sum += Dis[1][mindistance];
    //cout<<sum<<endl;
    return sum;

}


int main()
{
	clock_t start,finish;
	double duration;
	
    freopen("1.txt","r",stdin);
    ReadDate();
    Distance();
    PrintDis();
	//PrintData();
	start = clock();
	float Path = SoveTsp();
	cout<<"近似最短路径为："<<Path<<endl;
	finish = clock();
	duration = double(finish-start)/CLOCKS_PER_SEC;
	cout<<"时间消耗："<<duration<<endl;
        

}
