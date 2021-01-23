#include <iostream>
using namespace std;

#define max_vertices 100
#define INF 1000000

typedef struct GraphType
{
	int n; // 정점의 개수
	int weight[max_vertices][max_vertices];
} GraphType;

int graph[max_vertices][max_vertices];

// 출력 함수
void print_graph(GraphType *g)
{
	int i, j;
	cout << "------------------------\n";
	for (i = 0; i < g->n; i++)
	{
		for (j = 0; j < g->n; j++)
		{
			// 연결되지 않는 노드는 무한이므로 * 출력
			if (graph[i][j] == INF)
				cout << " * ";
			// 연결된 노드는 INF 아니므로 배열 내의 가중치 출력
			else
				cout << graph[i][j] << " ";
		}
		cout << '\n';
	}
	cout << "------------------------\n";
}

void floyd(GraphType *g)
{
	int i, j, k;
	// 자신 노드와 연결된 노드의 가중치만 저장
	for (i = 0; i < g->n; i++)
	{
		for (j = 0; j < g->n; j++)
		{
			graph[i][j] = g->weight[i][j];
		}
	}
	print_graph(g);

	// k 노드와 거쳐서 목표 노드를 갈 때 원래 가중치 값 보다 적으면 갱신
	for (k = 0; k < g->n; k++)
	{
		for (i = 0; i < g->n; i++)
		{
			for (j = 0; j < g->n; j++)
			{
				if (graph[i][k] + graph[k][j] < graph[i][j])
					graph[i][j] = graph[i][k] + graph[k][j];
			}
		}
		print_graph(g);
	}
}

int main()
{
	ios_base ::sync_with_stdio(false);
	cin.tie(NULL);

	GraphType g = {7, // GraphType에 선언된 n
										// GraphType에 선언된 weight[][]
								 {{0, 7, INF, INF, 3, 10, INF},
									{7, 0, 4, 10, 2, 6, INF},
									{INF, 4, 0, 2, INF, INF, INF},
									{INF, 10, 2, 0, 11, 9, 4},
									{3, 2, INF, 11, 0, INF, 5},
									{10, 6, INF, 9, INF, 0, INF},
									{INF, INF, INF, 4, 5, INF, 0}}};
	floyd(&g);
	return 0;
}