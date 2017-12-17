#pragma once

struct Edge
{
	int toNode;
	int weight;
	int colour; // 0 = white, 1 = grey, 2 = black
	Edge(int toNodeIn, int weightIn)
	{
		toNode = toNodeIn; weight = weightIn;
		colour = 0;
	}
};


