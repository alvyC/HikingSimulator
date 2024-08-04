#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include <vector>
#include <map>
#include <functional>

#include "bridge.hpp"

// Strategy interface
class Strategy {
public:
    virtual ~Strategy() {}
    virtual double crossBridge(const Bridge& bridge) = 0;
};

// Strategy factory registry
class StrategyFactory {
public:
    static StrategyFactory& instance() {
        static StrategyFactory factory;
        return factory;
    }

    void registerStrategy(const std::string& name, std::function<Strategy*()> creator) {
        strategies[name] = creator;
    }

    Strategy* createStrategy(const std::string& name) {
        if (strategies.find(name) != strategies.end()) {
            return strategies[name]();
        }
        return nullptr;
    }


    bool isValidStrategy(const std::string& name) {
	return strategies.find(name) != strategies.end();
    }

private:
    std::map<std::string, std::function<Strategy*()>> strategies;
};

// Registration helper
template <typename T>
class StrategyRegistrar {
public:
    StrategyRegistrar(const std::string& name) {
        StrategyFactory::instance().registerStrategy(name, []() { return new T(); });
    }
};

#endif // STRATEGY_H
