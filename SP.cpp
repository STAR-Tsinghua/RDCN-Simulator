#include "SP.h"
#define PATH_SP "Tmp/shortestPath.txt"
#define PATH_SP_WIRE "Tmp/shortestPath_wire.txt"
ofstream out_SP;
const int maxnum = NODE_NUM;
const int maxint = INT_MAX;

int dist[maxnum];     	// path length from current node to source node
int c[maxnum][maxnum];  // record path length
int n = maxnum;            

						// n -- n nodes
						// v -- the source node
						// dist[] -- the distance from the ith node to the source node
						// prev[] -- the previous node of the ith node
						// c[][] -- every two nodes' distance

void OpenFile(int code)
{
	if(code == 0)
		out_SP.open(PATH_SP);
	if(code == 1)
		out_SP.open(PATH_SP_WIRE);
}

void CloseFile()
{
	out_SP.close();
}

void Dijkstra(int n, int v, int *dist, vector<int> *prev, int c[maxnum][maxnum])
{
	bool s[maxnum];   
	for (int i = 0; i < n; ++i)
	{
		dist[i] = c[v][i];
		s[i] = 0;     // initialize
		if (dist[i] < maxint)
			prev[i].push_back(v);
	}
	dist[v] = 0;
	s[v] = 1;

	// once nodes in V are included in S, dist record all SP from src to others
	// start from second node, src is first node
	for (int i = 1; i < n; ++i)
	{
		int tmp = maxint;
		int u = v;
		// find j
		for (int j = 0; j < n; ++j)
		{
			if ((!s[j]) && dist[j] < tmp)
			{
				u = j;              
				tmp = dist[j];
			}
		}
		s[u] = 1;    // u has been added to S

					 // update dist
		for (int j = 0; j < n; ++j)
			if ((!s[j]) && c[u][j]<maxint)
			{
				int newdist = dist[u] + c[u][j];
				if (newdist <= dist[j])//// store only one path
				{
					if (newdist < dist[j]) {
						prev[j].clear();
						dist[j] = newdist;
					}
					prev[j].push_back(u);
				}
			}
	}
}
// find path from v to u and output
void searchPath(vector<int> *prev, int v, int u, int sta[], int len)
{
	if (u == v)
	{
		out_SP << v;
		return;
	}
	sta[len] = u;
	for (int i = 0; i < prev[u].size(); ++i)
	{
		if (i > 0)
		{
			for (int j = len - 1; j >= 0; --j)
			{
				out_SP << " " << sta[j];
			}
			out_SP << endl;
		}
		searchPath(prev, v, prev[u][i], sta, len + 1);
		out_SP << " " << u;
	}
}

void ComputeShortestPath(int topo[][NODE_NUM], MultiPath multiPath[][NODE_NUM])
{
	vector<int> prev[maxnum];
	for (int i = 0; i < maxnum; i++)
	{
		for (int j = 0; j < maxnum; j++)
		{
			if (topo[i][j] == 0)
				c[i][j] = maxint;
			else
				c[i][j] = topo[i][j];
		}
	}

	for (int k = 0; k < RACK_NUM; k++)
	{
		//cout << k << endl;
		for (int i = 0; i < maxnum; i++)
			prev[i].clear();
		// initialize the path length
		for (int i = 0; i < n; ++i)
			dist[i] = maxint;

		Dijkstra(n, k, dist, prev, c);

		for (int j = 0; j < RACK_NUM; j++)
		{
			multiPath[k][j].src = k;
			multiPath[k][j].dst = j;

			int sta[maxnum];
			if (k != j)
			{
				searchPath(prev, multiPath[k][j].src, multiPath[k][j].dst, sta, 0);
				out_SP << endl;
			}
		}
	}
}

void ComputeShortestPath(int src, int dest, int topo[][NODE_NUM])
{
	vector<int> prev[maxnum];
							 
	for (int i = 0; i < maxnum; i++)
	{
		for (int j = 0; j < maxnum; j++)
		{
			if (topo[i][j] == 0)
				c[i][j] = maxint;
			else
				c[i][j] = topo[i][j];
		}
	}

	for (int i = 0; i < maxnum; i++)
		prev[i].clear();
	for (int i = 0; i < n; ++i)
		dist[i] = maxint;
	Dijkstra(n, src, dist, prev, c);

	if (src != dest)
	{
		int sta[maxnum];
		searchPath(prev, src, dest, sta, 0);
		out_SP << endl;
	}
}

void buildPath(string tmp, MultiPath multiPath[][NODE_NUM], vector<Link*> *AllLinks)
{
	vector<int> v;//store nodes on path
	v.clear();
	int sLen = tmp.size();
	int number = 0;
	for (int i = 0; i < sLen; i++)
	{
		if (tmp[i] >= '0' && tmp[i] <= '9')
		{
			number = number * 10 + (tmp[i] - '0');
		}
		else
		{
			v.push_back(number);
			number = 0;
		}
	};
	v.push_back(number);
	int vLen = v.size();// get node number
	int src = v[0];// get head node
	int dest = v[vLen - 1];// get tail node

	Path *p = new Path();
	p->len = vLen - 1;
	p->nodes = v;// record nodes on path

				 //Link h;
	for (int i = 1; i < vLen; i++)
	{
		int src = v[i - 1];
		int dest = v[i];
		Link *link = findLink(src, dest, AllLinks);
		p->links.push_back(link);
	}

	for (int i = 0; i < p->links.size(); i++)
	{
		Link* link = p->links[i];
		if (link->isWireless == true)
			p->isHybrid = true;
	}
	//add path to multiPath
	multiPath[src][dest].src = src;
	multiPath[src][dest].dst = dest;
	multiPath[src][dest].pathNumber++;
	multiPath[src][dest].paths.push_back(p);
}

void GetShortestPath(int topo[][NODE_NUM], MultiPath multiPath[][NODE_NUM], vector<Link*> *AllLinks, int code)
{
	ifstream read;
	if (code == 0)
		read.open(PATH_SP);
	else
		read.open(PATH_SP_WIRE);

	if (!read)
	{
		cout << "read file error" << endl;
	}
	string tmp;
	int count = 0;
	while (getline(read, tmp))
	{
		buildPath(tmp, multiPath, AllLinks);
	}
	read.close();
}

Link* findLink(int src, int dest, vector<Link*> *AllLinks)
{
	for (int i = 0; i < AllLinks->size(); i++)
	{
		Link *link = (*AllLinks)[i];
		if (link->src == src && link->dst == dest)
			return link;
	}
}

void ComputeMultiPath(vector<Flow*> &flows, int topo[][NODE_NUM])
{
	// avoid calculating the path for one node pair many times
	for (int i = 0; i < flows.size(); i++)
	{
		Flow* flow = flows[i];
		int src = flow->src;
		int dst = flow->dst;
		bool flag = false;
		for (int j = 0; j < i; j++)
		{
			if (src == flows[j]->src && dst == flows[j]->dst)
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			ComputeShortestPath(src, dst, topo);
		}
	}
}