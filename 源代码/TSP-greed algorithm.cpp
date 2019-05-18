#include<bits/stdc++.h>
using namespace std;

/*
���ߣ��׷���
ʱ�䣺2019��5��

������ע�����
���Բ�ͬ�ĵ㼯ʱ
Ҫ�ı���������
1.����vexnum �������еĸ���
2.�����ļ�����main�������freopen������һ������

*/


struct Node
{
	int id;
    int x;
    int y;
};

const int vexnum = 10;  //�����и���
Node Array[vexnum+1];  //0�ŵ�Ԫδ�ã���1��ʼ
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
        for(int j=i;j<=vexnum;j++)  //������������
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
    
    visited[1] = true;  //��1��ʼ
    
    int mindistance; //
	int start = 1; //
    cout<<"1->";
    for(int i=1; i<=vexnum -1 ; i++) //ѭ��n-1��
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
	cout<<"�������·��Ϊ��"<<Path<<endl;
	finish = clock();
	duration = double(finish-start)/CLOCKS_PER_SEC;
	cout<<"ʱ�����ģ�"<<duration<<endl;
        

}
