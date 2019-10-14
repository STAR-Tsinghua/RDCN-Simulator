#include "classes.h"

Link::Link(int s, int d, bool iswireless, double ratio)
{
	src = s;
	dst = d;
	weight = 0.0;
	flowNumThrIt = 0;
	averageBandwidth = 0;
	isWireless = iswireless;
	isAvailable = true;
	totalRate.clear();
	intfLinks.clear();
	inNeighborLinks.clear();
	if (isWireless == false)
	{
		totalBandwidth = unusedBandwidth = WIRED_BW;
	}
	else
	{
		totalBandwidth = unusedBandwidth = WIRELESS_BW * ratio;
	}
}

Path::Path()
{
	len = 0;
	weight = 0.0;
	isHybrid = false;
	isSelectedPath = false;
	links.clear();
}

MultiPath::MultiPath()
{
	pathNumber = 0;
	isAvailable = false;
	paths.clear();
}

Flow::Flow(int s, int d, double size, int arr)
{
	id = -1;
	src = s;
	dst = d;
	prepath = NULL;
	pathNumber = 0;
	arrivalTime = arr;
	totalSize = currentSize = size;
	if (size > THRESHOLD_LARGE_FLOW)
	{
		isLargeFlow = true;
	}
	else
	{
		isLargeFlow = false;
	}
	rate = 0;
	isFirstVisted = true;
	isSlowStart = true;
}

IndependentSet::IndependentSet()
{
	linkSet.clear();
	isSelected = false;
}

