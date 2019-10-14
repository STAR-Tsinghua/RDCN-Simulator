#pragma once
#include "header.h"

class Link {
public:
	int id; // link id
	int src; // source node
	int dst; // destination node
	int flowNumThrIt; // how many flows transfer through it
	bool isWireless; // 1: wireless 0: wired
	bool isAvailable; // 1: active 0 : inactive 
	double src_x, src_y, dst_x, dst_y; // postions of src and dst
	double weight;
	double totalBandwidth;
	double unusedBandwidth;
	double averageBandwidth;
	double tmpUsedBandwidth;
	double curLinkLoad;
	vector<double> totalRate;// record the acutal transmission rate
	vector<Link*> intfLinks; // set of interference links
	vector<Link*> inNeighborLinks;
	vector<Link*> outNeighborLinks;
	Link(int s, int d, bool iswireless, double ratio = 1.0); // constructor
};

class Path {
public:
	int len; // hop number
	bool isHybrid; // 1: wirelss link included; 0: wireless link not included
	bool isAvailable; 
	bool isSelectedPath;
	double weight;
	vector<int> nodes; // nodes on the path
	vector<Link*> links; // links on the path 
	Path(); // constructor
};

class MultiPath {
public:
	int src; // source node
	int dst; // destination node
	int pathNumber; // how many paths
	bool isAvailable; 
	vector<Path*> paths; // set of paths
	MultiPath();
};

class Flow {
public:
	int id; // flowID
	int src; // start from ...
	int dst; // to ...
	int pathNumber; //the number of selected path
	int arrivalTime; // arrival time 
	int finishTime; // complete time
	bool isLargeFlow; 
	bool isSlowStart; // transfer state
	bool isFirstVisted; // transfer state
	double rate; //bps
	double totalSize; 
	double currentSize; // remaining size
	Path* prepath; // previous routing path
	vector<double> rates; //flow rate
	vector<Path*> paths;
	Flow(int s, int d, double size, int arr);
};

class IndependentSet
{
public:
	vector<Link*> linkSet; // set of links that are not conflicted with each other
	bool isSelected;
	double weight;
	IndependentSet();
};
