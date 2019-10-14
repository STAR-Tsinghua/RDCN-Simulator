#pragma once
#include "header.h"

class K_Shortest_Path {
public:
	//
	//Yen_k-shortest-path
	//
	vector<vector<unsigned int>> run(
		const unsigned int kPath,					// K Path
		const vector<vector<unsigned int>>& NW,		// network
		const unsigned int src,						// source node
		const unsigned int dst);					// destination node
};

//
// store the shortest path and path length
//
class DijPath
{
public:
	vector<unsigned int> onePath;
	int cost;

	bool operator <(const DijPath &n2);

	//whether two paths are equal
	bool operator ==(const DijPath &n2);
};