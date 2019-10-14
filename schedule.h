#pragma once
#include "run.h"
#include "KSP.h"
#include "header.h"
#include "classes.h"
#include "routing.h"
#include "gurobi_c++.h"

void ScheduleFlows(vector<Flow*> &flowSet, vector<Link*> &allLinks, string algName);

void OFS(vector<Flow*> &unfinishedFlows, vector<Flow*> &arrivalFlows, vector<Link*> &allLinks);