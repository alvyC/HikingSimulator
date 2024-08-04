#include "strategy.hpp"

class SlowestFirstStrategy : public Strategy {
public:
    double crossBridge(const Bridge& bridge) override {
        // Implementation of the slowest-first strategy
        double totalTime = 0.0;
        auto hikers = bridge.getHikers();
	auto n = bridge.getHikers().size();

        while (n > 1) {
            double time = bridge.timeToCross(hikers[0], hikers[n-1]);
            totalTime += time;
            n -= 1;
        }
        if (n == 1) {
            totalTime += bridge.timeToCross(hikers[0], hikers[0]);
        }

        return totalTime;
    }
};

// Autoregistration
static StrategyRegistrar<SlowestFirstStrategy> registrar("slowest-first-strategy");
