#include <cstdio>
#include <climits>
#include <algorithm>
#include <map>

using namespace std;

struct bus
{
	int U,V;
	long S,E;
	long maxWaitTime;
};

long getBusPathTime(bus current, multimap<int, bus> busMap, int N, long T)
{
	if(current.maxWaitTime != LONG_MIN)
	{
		return current.maxWaitTime;
	}
	
	if(current.E > T)
	{
		current.maxWaitTime = -1;
		return current.maxWaitTime;
	}
		
	if(current.V == N)
	{
		current.maxWaitTime = 0;
		return current.maxWaitTime;
	}
	
	pair<multimap<int, bus>::iterator, multimap<int, bus>::iterator> nextBuses; 
	nextBuses = busMap.equal_range(current.V);
	long minWait = LONG_MAX;
	for(map<int, bus>::iterator it = nextBuses.first; it != nextBuses.second; ++it)
	{
		long waitTimeWithThisBus = it->second.S - current.E;
		if(waitTimeWithThisBus >= 0)
		{
			long maxWaitTimeInternal = getBusPathTime(it->second, busMap, N, T);
			if(maxWaitTimeInternal >= 0)
			{
				long maxWaitTimeWithBus = max(waitTimeWithThisBus, maxWaitTimeInternal);
				minWait = min(minWait, maxWaitTimeWithBus);
			}
		}
	}
	
	current.maxWaitTime = minWait == LONG_MAX ? -1l : minWait; 
	return current.maxWaitTime;
}

int main()
{
	int N, M;
	long T;
	scanf("%d %ld %d", &N, &T, &M);
	multimap<int, bus> busMap;
	for(int i = 0; i < M; ++i)
	{
		bus b;
		scanf("%d %d %ld %ld", &b.U, &b.V, &b.S, &b.E);
		b.maxWaitTime = LONG_MIN;
		busMap.insert(pair<int, bus>(b.U, b));
	}

	// Get all buses which start at 1.
	pair<multimap<int, bus>::iterator, multimap<int, bus>::iterator> startBuses;
	startBuses = busMap.equal_range(1);
	long minWait = LONG_MAX;
	for(multimap<int, bus>::iterator it = startBuses.first; it != startBuses.second; ++it)
	{
		long maxWaitTimeInternal = getBusPathTime(it->second, busMap, N, T);
		if(maxWaitTimeInternal >= 0)
		{
			long maxWaitTimeWithBus = max(it->second.S, maxWaitTimeInternal);
			minWait = min(minWait, maxWaitTimeWithBus);
		}
	}
	
	if(minWait == LONG_MAX)
		printf("%ld", -1l);
	else
		printf("%ld", minWait);
	return 0;
}