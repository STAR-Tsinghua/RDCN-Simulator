#pragma once
#include "header.h"
#include "classes.h"
void OpenFile(int code);

void CloseFile();

void ComputeShortestPath(int topo[][NODE_NUM], MultiPath multiPath[][NODE_NUM]);

void GetShortestPath(int topo[][NODE_NUM], MultiPath multiPath[][NODE_NUM], vector<Link*> *AllLinks, int code);

void ComputeShortestPath(int src, int dest, int topo[][NODE_NUM]);

void ComputeMultiPath(vector<Flow*> &flows, int topo[][NODE_NUM]);

Link* findLink(int src, int dest, vector<Link*> *AllLinks);
