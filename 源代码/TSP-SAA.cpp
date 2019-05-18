#include <stdlib.h>
#include <queue>
#include <stack>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include<math.h>
#include<iostream>
using namespace std;
/*

作者：孔凡豪
学号：161740130
时间：2019年5月1号
算法：启发式的模拟退火算法

算法过程：

1. 初始化城市信息，以及各个城市的距离矩阵
2. 随机产生一个解序列  eg: 12345 -->13245
3. 根据Metropolis法则判断是否接受新的解
4. 模拟退火过程
*/
#define max_vexNum 100
#define MAX_CITYNUM 150

const int LEGNTH_Mapkob = 500;
const double SPEED = 0.98;					// 退火速度
const double INITIAL_TEMPERATURE = 1000.0;	// 初始温度
const double MIN_TEMPERATURE = 0.001;		// 最低温度
const int MAX_INT = 99999999;

struct Node    //顶点信息
{
    int id;
    double x,y;
};

Node Array[max_vexNum];      				//存放坐标数据

typedef struct
{
	int vex_num, arc_num;					// 顶点数 边数
	int vexs[max_vexNum];					// 顶点向量  int
	double arcs[max_vexNum][max_vexNum];	// 邻接矩阵
}Graph;

typedef struct
{
	double length_path;
	int path[max_vexNum+1];
}TSP_solution;

void CreateGraph(Graph &G); //创建城市图

TSP_solution SA_TSP(Graph G); //用SAA解决TSP

TSP_solution FindNewSolution(Graph G, TSP_solution bestSolution);  //找出新的解

double CalculateLength(Graph G,TSP_solution newSolution); //计算一个方案的长度


void Display(Graph G,TSP_solution bestSoluion);  //输出最优方案


int main()
{
	cout<<"please wait..."<<endl;
	Graph G;
	CreateGraph(G);
	time_t T_begin = clock();
	TSP_solution bestSoluion = SA_TSP(G);
	Display(G, bestSoluion);
	time_t T_end = clock();
	double RunningTime = double(T_end - T_begin)/CLOCKS_PER_SEC;
	cout<<"程序运行时间 RunningTime = "<<RunningTime<<" s"<<endl;
	system("pause");
	return 0;
}

void CreateGraph(Graph &G)
{
	ifstream read_in;
	read_in.open("2.txt");
	if (!read_in.is_open())
	{
		cout<<"文件读取失败."<<endl;
		return;
	}
	G.vex_num = max_vexNum;

    //读取数据
    for(int i=0; i<max_vexNum; i++)
    {
        read_in>>Array[i].id>>Array[i].x>>Array[i].y;
    }

    double temp;
	for (int i = 0; i < G.vex_num;i++)
	{
		for (int j = i; j < G.vex_num; j++)
		{
            if(i == j)
                G.arcs[i][j] = -1;
            else
                {
                    temp = (Array[i].x-Array[j].x)*(Array[i].x-Array[j].x)+(Array[i].y-Array[j].y)*(Array[i].y-Array[j].y);
			        G.arcs[i][j] = G.arcs[j][i] = sqrt(temp);
                }
		}
	}
	/*cout<<G.vex_num;
	for (int i = 0; i < G.vex_num;i++)
	{
		for (int j = 0; j < G.vex_num; j++)
		{
			cout << std::left << setw(4) << G.arcs[i][j]<<" ";
		}
		cout<<endl;
	}
	*/
}

TSP_solution SA_TSP(Graph G)
{
	srand ( unsigned ( time(0) ) );

	// 当前温度
	double Current_Temperature = INITIAL_TEMPERATURE;

	// 最优解
	TSP_solution Best_solution;
	Best_solution.length_path = MAX_INT;  //初始化最优解长度为无穷大

	// 初始路径
	for (int i = 0;i < G.vex_num; i++)
	{
		Best_solution.path[i] = i;
	}

	random_shuffle(Best_solution.path + 1, Best_solution.path + G.vex_num);  //打乱元素排列顺序

    //for(int i=0;i<G.vex_num;i++)
     //   cout<<Best_solution.path[i]<<" ";
    //cout<<endl;

	// 当前解, 与最优解进行比较
	TSP_solution Current_solution;

	// 模拟退火过程
	while(MIN_TEMPERATURE < Current_Temperature)
    {
		// 满足迭代次数
		for (int i = 0; i < LEGNTH_Mapkob; i++)
		{
			Current_solution = FindNewSolution(G, Best_solution);
			if (Current_solution.length_path <= Best_solution.length_path)	// 接受新解
			{
				Best_solution = Current_solution;
			}
			else
            {	// 按 Metropolis 判断是否接受
				if ((int)exp((Best_solution.length_path - Current_solution.length_path) / Current_Temperature)*100 > (rand()*101))
				{
					Best_solution = Current_solution;
				}
			}
		}
		Current_Temperature *= SPEED;  // 按 SPEED 速率退火

	} // while

	return Best_solution;
}


TSP_solution FindNewSolution(Graph G, TSP_solution bestSolution){
	// 产生新的解
	TSP_solution newSolution;

	// 起始城市固定为A, 终点也要返回A, 即需要关注起点A和终点A之间的所有城市
	int i = rand() % (G.vex_num - 1) + 1;	// % 取余 -> 即将随机数控制在[1, G.vex_num - 1]
	int j = rand() % (G.vex_num - 1) + 1;


   //保证 j > i
	if (i > j)
	{
		int temp = i;
		i = j;
		j = temp;
	}
	else if (i == j)
	{	// 表示产生的随机数没有改变的作用, 将此路程设置为最大并结束该函数

		newSolution = bestSolution;
		return newSolution;
	}

	/* way 2 */
	int choose = rand() % 3;
	
	if (choose == 0)
	{	// 随机交换任意两个城市的位置
		int temp = bestSolution.path[i];
		bestSolution.path[i] = bestSolution.path[j];
		bestSolution.path[j] = temp;
	}
	
    else if (choose == 1)
	{	// 随机逆置城市的位置
		reverse(bestSolution.path + i, bestSolution.path + j);  //要求j > i
	}
	
	else
    {	// 随机移位城市的位置
		if (j+1 == G.vex_num) //边界处不处理
		{
			newSolution = bestSolution;
			return newSolution;
		}
		rotate(bestSolution.path + i, bestSolution.path + j, bestSolution.path + j + 1);
	}
	
	newSolution = bestSolution;
	newSolution.path[G.vex_num] = newSolution.path[0];   // 终点与起始点相同
	newSolution.length_path = CalculateLength(G, newSolution);

	return newSolution;
}

double CalculateLength(Graph G,TSP_solution newSolution)
{
	double _length = 0;

	for (int i = 0; i < G.vex_num - 1; i++)
	{
		int _startCity = (int)newSolution.path[i];
		int _endCity = (int)newSolution.path[i+1];
		if (G.arcs[_startCity][_endCity] == -1)
		{
			return MAX_INT;
		}
		else
        {
			_length += G.arcs[_startCity][_endCity];
		}
	}

	// 判断该路径是否能回到起始城市
	if (G.arcs[newSolution.path[G.vex_num-1]][newSolution.path[0]] == -1)
	{
		return MAX_INT;
	}
	else
    {
		_length += G.arcs[newSolution.path[G.vex_num - 1]][newSolution.path[0]];

		return _length;
	}
}

void Display(Graph G,TSP_solution bestSoluion)
{
	
	cout<<"用SAA算法求解的近似最优路径为："<<endl;

	for (int i = 0; i < G.vex_num; i++)
	{
		cout<<bestSoluion.path[i]<<"-->";
	}

	cout<<bestSoluion.path[G.vex_num]<<endl;

	cout<<"近似最优路径的值为："<<bestSoluion.length_path<<endl;;

}

