#pragma once
#include "header.h"
#include "classes.h"

void GenerateWiredTopology(int topo[][SWITCH_NUM]); // generate fat-tree topology

void GetHybridTopology(int topo[][SWITCH_NUM], vector<Link*> &selectedWirelessLinks); // construct hybrid topology