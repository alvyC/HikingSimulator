#include <iostream>
#include <vector>
#include <unistd.h>
#include <yaml-cpp/yaml.h>

#include "strategy.hpp"

static void usage(std::ostream& os, const std::string& prog_name) {
	os << "Usage: " << prog_name << " -f <yaml_file>\n" << std::endl;
}

int main(int argc, char** argv) {
    std::string prog_name(argv[0]);
    std::string yaml_file;
    int opt;

    while ((opt = getopt(argc, argv, "hf:")) != -1 ) {
    	switch (opt) {
		case 'h':
			usage(std::cout, prog_name);
			return 0;
			
		case 'f':
			std::cout << "Config file" << std::endl;
			yaml_file = optarg;
			break;
		default:
			usage(std::cerr, prog_name);
			return 2;
	}
    }
    
    std::cout << yaml_file << std::endl;
    if (yaml_file.empty()) {
    	usage(std::cerr, prog_name);
	return 1;
    }
    
    try {

    	YAML::Node config = YAML::LoadFile(yaml_file);

    	std::vector<Bridge> bridges;
    	for (const auto& bridgeNode : config["bridges"]) {
        	Bridge bridge(bridgeNode["length"].as<int>());

        	for (const auto& hikerNode : bridgeNode["hikers"]) {
			std::string name = hikerNode["name"].as<std::string>();
            		double speed = hikerNode["speed"].as<double>();
            		Hiker hiker(name, speed);
			bridge.addHiker(hiker);
        	}

        	bridges.push_back(bridge);
    	}

    	double totalTime = 0.0;
    	auto strategyName = config["strategy"]["name"].as<std::string>();
	
	if (!StrategyFactory::instance().isValidStrategy(strategyName)) {
		std::cerr << "Error: Unknown strategy '" << strategyName << "' provided in input.\n";
        	return 1; // Exit the program with an error code
	}
	
	std::cout << "Using "  << strategyName << " to cross bridge." << std::endl;
	Strategy* strategy = StrategyFactory::instance().createStrategy(strategyName);
	for (auto& bridge : bridges) {
        	double bridgeTime = 0;
		bridgeTime = strategy->crossBridge(bridge);

		std::cout << "Time to cross bridge of length " << bridge.getLength() << " feet: " << bridgeTime << " minutes\n";
        	totalTime += bridgeTime;
    	}

    	std::cout << "Total time to cross all bridges: " << totalTime << " minutes\n";

    } catch (const YAML::Exception& e) {
    	std::cerr << "Error loading YAML file: " << e.what() << std::endl;
	return 1;
    }

    return 0;
}
