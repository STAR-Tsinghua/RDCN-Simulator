#pragma once
#include "header.h"
#include "classes.h"
#include "gurobi_c++.h"

void GetWiredLinks(int topo[SWITCH_NUM][SWITCH_NUM], vector<Link*> & wiredLinks, int code = 0);// code = 0: generate; code = 1: read file

void GetWirelessLinks(vector<Link*> & wirelessLinks, int code = 0); // code = 0: generate; code = 1: read file

void GetInterferenceLinks(vector<Link*> & wirelessLinks, string algName = "");

void GetSelectedWirelessLinks(vector<Flow*> & largeFlows, vector<Link*> & wiredLinks, vector<Link*> & wirelessLinks, vector<Link*> & selectedWirelessLinks, string algName);

void GetAllLinks(vector<Link*> &wiredLinks, vector<Link*> &wirelessLinks, vector<Link*> &allLinks);

void GetFailedLinks(vector<Link*> &wiredLinks, vector<Link*> &wirelessLinks, int topo[SWITCH_NUM][SWITCH_NUM], double failureRate = FAILURE_RATE);