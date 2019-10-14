#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <memory.h>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <limits.h>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <Windows.h>

//Basic settings
#define K 8 // K-port switches
#define THRESHOLD_LARGE_FLOW 800000// b
#define CORE_NUM (K*K/4) // core switch number
#define AGGR_NUM (K*K/2) // aggregation switch number
#define EDGE_NUM (K*K/2) // edge/tor switch number
#define RACK_NUM EDGE_NUM // rack number should be equal to or less than edge switch number
#define SWITCH_NUM (5*K*K/4) // total switch number
#define NODE_NUM SWITCH_NUM
#define WIRED_BW 10000000000 // bps
#define WIRELESS_BW 6000000000  // bps
#define MIN_WIRELESS_BW 1000000000 // bps
#define RUSH_WIRELESS_BW 1000000000 // bps
#define WIRELESS_DIS 10 //m
#define START_RATE 100000 //bps
#define TICK 0.001 // second
#define ROW_DIS 2.4 //m
#define COL_DIS 3 //m
#define RACK_LENGTH 0.6 //m
#define RACK_WIDTH 1.2 //m
#define CLUSTER_NUM_IN_A_ROW 4
#define RACK_NUM_IN_A_CLUSTER 4
#define LARGE_FLOW_NUMBER 100
#define SMALL_FLOW_NUMBER 1000
#define FLOW_NUM (LARGE_FLOW_NUMBER + SMALL_FLOW_NUMBER)
#define HOTSPOT_X 1 // {1, 5}
#define HOTSPOT_Y 0 // {0.1, 0.2, 0.3, 0.4, 0.5}

//OFS settings
#define KPATH 5 // Top-K shortest path {1, 2, 5, 10}
#define OMEGA 0 // trade-off parameter, load balancing vs. reconfiguration, {0, 1, 10, 100, 1000}

using namespace std;