#include "flow.h"
#include "header.h"
#define PATH0 "../../Share/flow.txt"

void GetFlowFromFile(vector<Flow*>& flowSet)
{
	ifstream in(PATH0);
	while (!in.eof())
	{
		int src = -1, dst, arrivalTime;
		double size;
		in >> src >> dst >> size >> arrivalTime;
		if (src >= 0)
		{
			Flow* flow = new Flow(src, dst, size, arrivalTime);
			flowSet.push_back(flow);
		}
	}
	in.close();
	cout << "GetFlowFromFile() succeeds !!!" << endl;
}

void SplitFlows(vector<Flow*>& flowSet, vector<Flow*>& largeFlows, vector<Flow*>& smallFlows) 
{
	for (int i = 0; i < flowSet.size(); i++)
	{
		Flow* flow = flowSet[i];
		if (flow->isLargeFlow == true)
		{
			largeFlows.push_back(flow);
		}
		else
		{
			smallFlows.push_back(flow);
		}
	}
	cout << "SplitFlows() succeeds !!!" << endl;
}

void UpdateFlows(vector<Flow*>& largeFlows, vector<Flow*>& smallFlows) 
{
	for (vector<Flow*>::iterator flowIt = largeFlows.begin(); flowIt != largeFlows.end(); flowIt ++)
	{
		(*flowIt)->totalSize *= HOTSPOT_X;
		(*flowIt)->currentSize *= HOTSPOT_X;
	}

	int num = (int)(largeFlows.size() * HOTSPOT_Y);
	for (int i = 0; i < num; i++)
	{
		largeFlows[i]->totalSize *= 10;
		largeFlows[i]->currentSize *= 10;
	}
	cout << "UpdateFlows() succeeds !!!" << endl;
}
