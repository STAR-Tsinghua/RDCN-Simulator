#include "topology.h"

void GenerateWiredTopology(int topo[][SWITCH_NUM])
{
	memset(topo, 0, SWITCH_NUM * SWITCH_NUM * sizeof(int));// initialize topology
														   // from tor to core
	int num = AGGR_NUM;
	for (int i = num; i < num * 2; i++)
	{
		int sort = i % (K / 2);
		sort = -sort;
		for (int j = 0; j < (K / 2); j++) {
			topo[i][i - num + sort + j] = 1;
			topo[i - num + sort + j][i] = 1;
		}
	}
	int core = CORE_NUM;
	for (int i = num * 2; i < num * 2 + core; i++) {
		int part = (i - 2 * num) / (K / 2);
		for (int j = 0; j < K; j++) {
			topo[i][num + j*K / 2 + part] = 1;
			topo[num + j*K / 2 + part][i] = 1;
		}
	}
	cout << "GenerateWiredTopology() succeeds !!!" << endl;
}

void GetHybridTopology(int topo[][SWITCH_NUM], vector<Link*>& selectedWirelessLinks)
{
	for (int i = 0; i < selectedWirelessLinks.size(); i++)
	{
		Link* link = selectedWirelessLinks[i];
		topo[link->src][link->dst] = 1;
	}
	cout << "GetHybridTopology() succeeds !!!" << endl;
}