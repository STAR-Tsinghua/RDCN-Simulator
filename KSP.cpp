#include "KSP.h"

static const unsigned int INF(INT_MAX);
static const unsigned undefined = INF;

bool DijPath::operator <(const DijPath &n2)
{
	return cost < n2.cost;
}

bool DijPath::operator ==(const DijPath &n2)
{
	if (onePath.size() == n2.onePath.size())
	{
		for (unsigned int i = 0; i < onePath.size(); i++)
		{
			if (onePath[i] != n2.onePath[i])
				return false;
		}

		return true;
	}

	return false;
}
//
//×ûShortest path algorithm
//
DijPath dijkstra(
	const vector<vector<unsigned int>> &NW,
	const int src,
	const int dst
)
{
	// node number
	unsigned int sizeNW = NW.size();

	// whether a node is visited
	vector<bool> visited(sizeNW);

	vector<unsigned int> prev(sizeNW);

	int minPos = 0;

	// record the length of each node to source node
	// when len[dst]=INF, src and dst are unreachable
	// set cost to INF first 
	vector<unsigned int> len(sizeNW);

	for (unsigned int i = 0; i < NW.size(); i++) // initialize
	{
		visited[i] = false;  // set visited status as false
		len[i] = NW[src][i];
		prev[i] = INF;
	}

	// set src as visited
	visited[src] = true;

	for (unsigned int i = 0; i < sizeNW; ++i)
	{
		unsigned int min = INF; 

		for (unsigned int j = 0; j < sizeNW; ++j)
		{
			if (!visited[j] && min > len[j])
			{
				minPos = j;   // find next node
				min = len[j];
			}
		}

		visited[minPos] = true;

		for (unsigned int j = 0; j < sizeNW; ++j)
		{
			// update if j node has not been visited and find shorter paths to other nodes through j
			if (!visited[j] && len[j] >(len[minPos] + NW[minPos][j]))
			{
				prev[j] = minPos;
				len[j] = len[minPos] + NW[minPos][j];
			}
		}
	}


	unsigned int beforeVertex = dst;
	
	stack<unsigned int> st;
	while (prev[beforeVertex] != INF)
	{
		st.push(beforeVertex);
		beforeVertex = prev[beforeVertex];
	}
	st.push(beforeVertex);

	DijPath oneDijPath;
	oneDijPath.onePath.resize(st.size() + 1);
	oneDijPath.onePath[0] = src;
	for (unsigned int i = 1; !st.empty(); i++)
	{
		oneDijPath.onePath[i] = st.top();
		st.pop();
	}
	oneDijPath.cost = len[dst];  //return the value of shortest path, if not reachable, set as INF
	return oneDijPath;
}


// cut the edges and return a new graph
vector<vector<unsigned int>> cutEdge(
	const vector<vector<unsigned int>>& NW,
	vector< DijPath> kSPCost,
	unsigned int root)
{
	vector<vector<unsigned int>>NWCopy = NW;
	for (unsigned int i = 0; i < kSPCost.size(); i++)
	{
		for (unsigned int j = 0; j < kSPCost[i].onePath.size(); j++)
		{
			if (kSPCost[i].onePath[j] == root)
			{
				unsigned int nextVertex = kSPCost[i].onePath[j + 1];
				if (j >= 1)
				{
					unsigned int beforeVertex = kSPCost[i].onePath[j - 1];
					NWCopy[root][beforeVertex] = INF;
				}
				NWCopy[root][nextVertex] = INF;  // set as unreachable
				break;
			}
		}
	}

	return NWCopy;
}

vector<vector<unsigned int>> K_Shortest_Path::run(
	const unsigned int kPath,					// K Path
	const vector<vector<unsigned int>>& NW,		// network
	const unsigned int src,						// source node
	const unsigned int dst)						// destination node

{
	vector<vector<unsigned int>>NWCopy = NW;
	vector< DijPath> kSPCost(1);  
	vector< DijPath>B;    
	DijPath newPath = dijkstra(NW, src, dst);  
	vector<vector<unsigned int>> kSP;   
	if (newPath.cost == INF) 
	{
		kSP.resize(0);
		return kSP;
	}


	kSPCost[0] = newPath; // store paths
	vector<unsigned int>forwardPath; 
	int nowCost; 

	for (unsigned int k = 1; k < kPath; k++)  //find kPath
	{
		nowCost = 0;

		bool flag = false;

		for (unsigned int i = 0; i < B.size() && kSPCost.size() < kPath&&kSPCost.size() >= k - 1; i++)
		{

			kSPCost.push_back(B[i]);

			flag = true;

		}

		if (flag) 
		{
			B.resize(0);
		}


		//return if no path found
		if (kSPCost.size() < k)
		{
			sort(kSPCost.begin(), kSPCost.end());
			for (unsigned int i = 0; i < kSPCost.size(); i++)
			{
				kSP.push_back(kSPCost[i].onePath);
			}
			return kSP;
		}

		forwardPath.resize(0);

		for (unsigned int i = 0; i < kSPCost[k - 1].onePath.size() - 1; i++) 
		{
			forwardPath.push_back(kSPCost[k - 1].onePath[i]);
			if (i != 0)

			{
				unsigned int forwardVertex = kSPCost[k - 1].onePath[i];
				unsigned int nextVertex = kSPCost[k - 1].onePath[i - 1];
				nowCost += NW[forwardVertex][nextVertex];
			}

			NWCopy = cutEdge(NW, kSPCost, kSPCost[k - 1].onePath[i]);

			DijPath secondPath = dijkstra(NWCopy, kSPCost[k - 1].onePath[i], dst);
			if (secondPath.cost > 100000) // judge whether two nodes are attachable
			{
				continue;
			}

			// find new path
			newPath.onePath = forwardPath;
			for (unsigned int j = 1; j < secondPath.onePath.size(); j++)
			{

				newPath.onePath.push_back(secondPath.onePath[j]);

			}

			newPath.cost = secondPath.cost + nowCost;


			// judge whether newPath is exist

			secondPath.onePath.resize(0);

			DijPath tmp;

			tmp.cost = newPath.cost;

			bool flag = true;

			for (unsigned int j = 0; j < kSPCost.size(); j++)
			{

				tmp.onePath = kSPCost[j].onePath;
				if (tmp == newPath)
				{
					flag = false;  
					break;
				}

			}

			if (flag)  //if not exist, add to new path
			{
				B.push_back(newPath);
			}

			if (kSPCost.size() >= kPath)
			{
				sort(kSPCost.begin(), kSPCost.end());
				for (unsigned int i = 0; i < kSPCost.size(); i++)
				{
					kSP.push_back(kSPCost[i].onePath);
				}
				return kSP;
			}
		}

	}
	sort(kSPCost.begin(), kSPCost.end());
	for (unsigned int i = 0; i < kSPCost.size(); i++)
	{
		kSP.push_back(kSPCost[i].onePath);
	}
	return kSP;
}