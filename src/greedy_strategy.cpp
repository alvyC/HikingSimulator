#include <algorithm>

#include "strategy.hpp"

class FastestFirstStrategy : public Strategy {
public:
    double crossBridge(const Bridge& bridge) override {
    	// Sort hikers by their speed in ascending order
	std::vector<Hiker> hikers = bridge.getHikers();
	std::sort(hikers.begin(), hikers.end(), [](const Hiker& a, const Hiker& b) {
        	return a.getSpeed() < b.getSpeed();
    	});
   	
    	double totalTime = 0.0;
	
	if (hikers.size() == 0 ) {
		return totalTime;
	}


	if (hikers.size() == 1) {
		return bridge.timeToCross(hikers.back(), hikers.back());
	}

    	Hiker fastestHiker = hikers.back();
    	for (const auto& hiker : hikers ) {
    		if (hiker.getName() == fastestHiker.getName())
			continue;

		double time = bridge.timeToCross(hiker, fastestHiker);
  		totalTime += time;
    	}

    	double fastestHikerTime = bridge.timeToCross(fastestHiker, fastestHiker);
    	totalTime += (fastestHikerTime * (hikers.size()-2));
        
   	return totalTime;
    }
};

// Autoregistration
static StrategyRegistrar<FastestFirstStrategy> registrar("greedy-strategy");
