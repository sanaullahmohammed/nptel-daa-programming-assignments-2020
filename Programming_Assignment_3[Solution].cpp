#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int DFS(/* in */ const int n,
        /* in */ const int src,
		/* in */ const vector< vector <int> > &graph, // adjacency list
		/* in */ const vector <int> &museums, // cost factor
		/* inout */ vector <bool> &visited)
{
	if (visited[src] == true)
		return 0;
	int sum = museums[src];
	visited[src] = true;
	const vector<int> & adj1 = graph[src];
	for (vector<int>::const_iterator ci = adj1.begin(); ci != adj1.end(); ci++)
	{
		int next = *ci;
		if (visited[next] == false)
			sum += DFS(n, next, graph, museums, visited);
	}
	return sum;
}

int main(void)
{
	
		int N, M, K;
		cin >> N >> M >> K;
		
		vector< vector <int> > graph;
		graph.reserve(N);
		for (int n = 0; n < N; n++)
		{
			// adjacency list
			vector<int>  node;
			graph.push_back(node);
		}
		
		for (int m = 0; m < M; m++)
		{
			int s,d;
			cin >> s >> d;
			d--; s--; // convert 1-based to 0-based

			vector<int> & adj1 = graph[s];
			adj1.push_back(d);  // add link s->d

			vector<int> & adj2 = graph[d];
			adj2.push_back(s);  // add link d->s
		}
		
		vector <int> museums;
		vector <bool> visited;
		for (int n = 0; n < N; n++)
		{
			int c;
			cin >> c;
			museums.push_back(c);
			visited.push_back(false);
		}
		
		// BFS
		vector<int> trips;
		for (int n = 0; n < N; n++)
		{
			if (visited[n] == false)
			{
				int total = DFS(n, n, graph, museums, visited);
				trips.push_back(total);
			}
		}

		
		sort(trips.begin(), trips.end(), greater<int>());
		
		int total = 0;
		int l = 0, r = trips.size() - 1;
		for (int i = 0; i < K && l <= r; i++)
		{
			if (i % 2 == 0)
				total += trips[l++];
			else
				total += trips[r--];
		}
  		if (trips.size() < K)
		{
			// no solution available
			cout << -1 << endl;
			
		}
		else
		cout << total << endl;
	
	
	return 0;
}
