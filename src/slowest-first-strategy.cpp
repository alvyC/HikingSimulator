#include <algorithm>
#include <queue>

#include "strategy.hpp"

class SlowestFirstStrategy : public Strategy {
public:
    double crossBridge(const Bridge& bridge) override {
    	auto cmp = [](const Hiker& a, const Hiker& b) { return a.getSpeed() > b.getSpeed(); };

	std::priority_queue<Hiker, std::vector<Hiker>, decltype(cmp)> slowestFirst(cmp);
	
	for (auto hiker : bridge.getHikers()) {
		slowestFirst.push(hiker);
	}

        double totalTime = 0.0;
  	if (slowestFirst.size() == 1)
		return bridge.timeToCross(slowestFirst.top(), slowestFirst.top());
		
	while (slowestFirst.size() > 1) {
		Hiker slowest1 = slowestFirst.top(); slowestFirst.pop();
		Hiker slowest2 = slowestFirst.top();

		totalTime += bridge.timeToCross(slowest1, slowest2);
		
		if (slowestFirst.size() != 1) // if this is not the last trip, faster of the slowest two will come back
			totalTime += bridge.timeToCross(slowest2, slowest2);
	}
	
        return totalTime;
    }
};

// Autoregistration
static StrategyRegistrar<SlowestFirstStrategy> registrar("slowest-first-strategy");
