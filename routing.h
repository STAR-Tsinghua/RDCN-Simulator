#pragma once
#include "header.h"
#include "classes.h"
#include "gurobi_c++.h"

void BuildPath(int k, int src, int dst, double** X, vector<Link*> &allLinks, Path* path, vector<int> &store);

void SelectRoutingPathForLargeFlows(vector<Flow*> &flowSet, vector<Link*> &allLinks, int code = 1);

void SelectRoutingPathForSmallFlows(vector<Flow*> &flowSet, MultiPath multiPath[][NODE_NUM]);

void ECMP(vector<Flow*>& flowSet, MultiPath multiPath[][NODE_NUM]); 

void GFF(vector<Flow*>& flowSet, vector<Link*> &allLinks, MultiPath multiPath[][NODE_NUM], MultiPath multiPath_wire[][NODE_NUM]);