#include <algorithm>
#include <queue>

#include "strategy.hpp"

class SlowestFirstStrategy : public Strategy {
public:
    double crossBridge(const Bridge& bridge) override {
    	auto cmp_min = [](const Hiker& a, const Hiker& b) { return a.getSpeed() > b.getSpeed(); };
    	auto cmp_max = [](const Hiker& a, const Hiker& b) { return a.getSpeed() < b.getSpeed(); };

	std::priority_queue<Hiker, std::vector<Hiker>, decltype(cmp_min)> slowestFirst(cmp_min);
	std::priority_queue<Hiker, std::vector<Hiker>, decltype(cmp_max)> fastestFirst(cmp_max);
	
	for (auto hiker : bridge.getHikers()) {
		slowestFirst.push(hiker);
	}

        double totalTime = 0.0;
  	if (slowestFirst.size() == 1)
		return bridge.timeToCross(slowestFirst.top(), slowestFirst.top());
		
	while (slowestFirst.size() > 1) {
		// Calculate time it takes for the hiker to cross; pick two slowest ones
		Hiker slowest1 = slowestFirst.top(); slowestFirst.pop();
		Hiker slowest2 = slowestFirst.top(); slowestFirst.pop();
		totalTime += bridge.timeToCross(slowest1, slowest2);
		
		fastestFirst.push(slowest1);
		fastestFirst.push(slowest2);

		// Calculate the time it takes for the fastest hiker on the other side to come back
		Hiker fastest = fastestFirst.top(); fastestFirst.pop();
		if (slowestFirst.size() != 1) // if this is not the last trip, faster of the slowest two will come back
			totalTime += bridge.timeToCross(fastest, fastest);
	}

        return totalTime;
    }
};

// Autoregistration
static StrategyRegistrar<SlowestFirstStrategy> registrar("slowest-first-strategy");
