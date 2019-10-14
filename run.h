#pragma once
#include "header.h"
#include "classes.h"
#include "topology.h"
#include "link.h"
#include "flow.h"
#include "SP.h"
#include "routing.h"
#include "schedule.h"

class ALGORITHM
{
public:
	int topo[SWITCH_NUM][SWITCH_NUM];
	string algName;
	vector<Flow*> flowSet;
	vector<Flow*> largeFlows;
	vector<Flow*> smallFlows;
	vector<Link*> wiredLinks;
	vector<Link*> wirelessLinks;
	vector<Link*> allLinks;
	vector<Link*> selectedWirelessLinks;
	MultiPath multiPath[NODE_NUM][NODE_NUM];
	MultiPath multiPath_wire[NODE_NUM][NODE_NUM];
	void set();
	void run();
};
