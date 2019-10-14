#pragma once
#include "classes.h"

void GetFlowFromFile(vector<Flow*> &flowSet);

void SplitFlows(vector<Flow*> &flowSet, vector<Flow*> &largeFlows, vector<Flow*> &smallFlows); // classify all flows into small flows and large flows 

void UpdateFlows(vector<Flow*> &largeFlows, vector<Flow*> &smallFlows); // simulate hotspot flow