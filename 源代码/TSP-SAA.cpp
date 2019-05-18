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

���ߣ��׷���
ѧ�ţ�161740130
ʱ�䣺2019��5��1��
�㷨������ʽ��ģ���˻��㷨

�㷨���̣�

1. ��ʼ��������Ϣ���Լ��������еľ������
2. �������һ��������  eg: 12345 -->13245
3. ����Metropolis�����ж��Ƿ�����µĽ�
4. ģ���˻����
*/
#define max_vexNum 100
#define MAX_CITYNUM 150

const int LEGNTH_Mapkob = 500;
const double SPEED = 0.98;					// �˻��ٶ�
const double INITIAL_TEMPERATURE = 1000.0;	// ��ʼ�¶�
const double MIN_TEMPERATURE = 0.001;		// ����¶�
const int MAX_INT = 99999999;

struct Node    //������Ϣ
{
    int id;
    double x,y;
};

Node Array[max_vexNum];      				//�����������

typedef struct
{
	int vex_num, arc_num;					// ������ ����
	int vexs[max_vexNum];					// ��������  int
	double arcs[max_vexNum][max_vexNum];	// �ڽӾ���
}Graph;

typedef struct
{
	double length_path;
	int path[max_vexNum+1];
}TSP_solution;

void CreateGraph(Graph &G); //��������ͼ

TSP_solution SA_TSP(Graph G); //��SAA���TSP

TSP_solution FindNewSolution(Graph G, TSP_solution bestSolution);  //�ҳ��µĽ�

double CalculateLength(Graph G,TSP_solution newSolution); //����һ�������ĳ���


void Display(Graph G,TSP_solution bestSoluion);  //������ŷ���


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
	cout<<"��������ʱ�� RunningTime = "<<RunningTime<<" s"<<endl;
	system("pause");
	return 0;
}

void CreateGraph(Graph &G)
{
	ifstream read_in;
	read_in.open("2.txt");
	if (!read_in.is_open())
	{
		cout<<"�ļ���ȡʧ��."<<endl;
		return;
	}
	G.vex_num = max_vexNum;

    //��ȡ����
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

	// ��ǰ�¶�
	double Current_Temperature = INITIAL_TEMPERATURE;

	// ���Ž�
	TSP_solution Best_solution;
	Best_solution.length_path = MAX_INT;  //��ʼ�����Žⳤ��Ϊ�����

	// ��ʼ·��
	for (int i = 0;i < G.vex_num; i++)
	{
		Best_solution.path[i] = i;
	}

	random_shuffle(Best_solution.path + 1, Best_solution.path + G.vex_num);  //����Ԫ������˳��

    //for(int i=0;i<G.vex_num;i++)
     //   cout<<Best_solution.path[i]<<" ";
    //cout<<endl;

	// ��ǰ��, �����Ž���бȽ�
	TSP_solution Current_solution;

	// ģ���˻����
	while(MIN_TEMPERATURE < Current_Temperature)
    {
		// �����������
		for (int i = 0; i < LEGNTH_Mapkob; i++)
		{
			Current_solution = FindNewSolution(G, Best_solution);
			if (Current_solution.length_path <= Best_solution.length_path)	// �����½�
			{
				Best_solution = Current_solution;
			}
			else
            {	// �� Metropolis �ж��Ƿ����
				if ((int)exp((Best_solution.length_path - Current_solution.length_path) / Current_Temperature)*100 > (rand()*101))
				{
					Best_solution = Current_solution;
				}
			}
		}
		Current_Temperature *= SPEED;  // �� SPEED �����˻�

	} // while

	return Best_solution;
}


TSP_solution FindNewSolution(Graph G, TSP_solution bestSolution){
	// �����µĽ�
	TSP_solution newSolution;

	// ��ʼ���й̶�ΪA, �յ�ҲҪ����A, ����Ҫ��ע���A���յ�A֮������г���
	int i = rand() % (G.vex_num - 1) + 1;	// % ȡ�� -> ���������������[1, G.vex_num - 1]
	int j = rand() % (G.vex_num - 1) + 1;


   //��֤ j > i
	if (i > j)
	{
		int temp = i;
		i = j;
		j = temp;
	}
	else if (i == j)
	{	// ��ʾ�����������û�иı������, ����·������Ϊ��󲢽����ú���

		newSolution = bestSolution;
		return newSolution;
	}

	/* way 2 */
	int choose = rand() % 3;
	
	if (choose == 0)
	{	// ������������������е�λ��
		int temp = bestSolution.path[i];
		bestSolution.path[i] = bestSolution.path[j];
		bestSolution.path[j] = temp;
	}
	
    else if (choose == 1)
	{	// ������ó��е�λ��
		reverse(bestSolution.path + i, bestSolution.path + j);  //Ҫ��j > i
	}
	
	else
    {	// �����λ���е�λ��
		if (j+1 == G.vex_num) //�߽紦������
		{
			newSolution = bestSolution;
			return newSolution;
		}
		rotate(bestSolution.path + i, bestSolution.path + j, bestSolution.path + j + 1);
	}
	
	newSolution = bestSolution;
	newSolution.path[G.vex_num] = newSolution.path[0];   // �յ�����ʼ����ͬ
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

	// �жϸ�·���Ƿ��ܻص���ʼ����
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
	
	cout<<"��SAA�㷨���Ľ�������·��Ϊ��"<<endl;

	for (int i = 0; i < G.vex_num; i++)
	{
		cout<<bestSoluion.path[i]<<"-->";
	}

	cout<<bestSoluion.path[G.vex_num]<<endl;

	cout<<"��������·����ֵΪ��"<<bestSoluion.length_path<<endl;;

}

