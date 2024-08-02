#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <yaml-cpp/yaml.h>

struct Hiker {
    std::string name;
    double speed; // in feet per minute
};

struct Bridge {
    int length; // in feet
    std::vector<Hiker> hikers;
};

double time_to_cross(const Bridge& bridge, const Hiker& hiker1, const Hiker& hiker2) {
    double slower_speed = std::min(hiker1.speed, hiker2.speed);
    return bridge.length / slower_speed;
}

double cross_bridge(Bridge& bridge) {
    // Sort hikers by their speed in ascending order
    std::sort(bridge.hikers.begin(), bridge.hikers.end(), [](const Hiker& a, const Hiker& b) {
        return a.speed < b.speed;
    });

    double total_time = 0.0;
    while (bridge.hikers.size() > 1) {
        if (bridge.hikers.size() == 2) {
            total_time += time_to_cross(bridge, bridge.hikers[0], bridge.hikers[1]);
            bridge.hikers.clear(); // All hikers have crossed the bridge
        } else {
            // Two strategies to cross the bridge:
            // 1. Slowest two cross first and fastest returns.
            // 2. Fastest two cross first and the second fastest returns.
            double strategy1 = 2 * time_to_cross(bridge, bridge.hikers[0], bridge.hikers[1]) + 
                               time_to_cross(bridge, bridge.hikers.back(), bridge.hikers[bridge.hikers.size() - 2]);
            double strategy2 = 2 * time_to_cross(bridge, bridge.hikers[0], bridge.hikers.back()) + 
                               time_to_cross(bridge, bridge.hikers[1], bridge.hikers[bridge.hikers.size() - 2]);

            // Choose the faster strategy
            total_time += std::min(strategy1, strategy2);

            // Two slowest hikers have crossed the bridge
            bridge.hikers.pop_back();
            bridge.hikers.pop_back();
        }
    }

    // If there's one hiker left, they can cross alone
    if (!bridge.hikers.empty()) {
        total_time += bridge.length / bridge.hikers[0].speed;
        bridge.hikers.clear();
    }

    return total_time;
}

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

    YAML::Node config = YAML::LoadFile("input.yaml");

    std::vector<Bridge> bridges;
    for (const auto& bridgeNode : config["bridges"]) {
        Bridge bridge;
        bridge.length = bridgeNode["length"].as<int>();

        for (const auto& hikerNode : bridgeNode["hikers"]) {
            Hiker hiker;
            hiker.name = hikerNode["name"].as<std::string>();
            hiker.speed = hikerNode["speed"].as<double>();
            bridge.hikers.push_back(hiker);
        }

        bridges.push_back(bridge);
    }

    double total_time = 0.0;
    for (auto& bridge : bridges) {
        double bridge_time = cross_bridge(bridge);
        std::cout << "Time to cross bridge of length " << bridge.length << " feet: " << bridge_time << " minutes\n";
        total_time += bridge_time;
    }

    std::cout << "Total time to cross all bridges: " << total_time << " minutes\n";
    } catch (const YAML::Exception& e) {
    	std::cerr << "Error loading YAML file: " << e.what() << std::endl;
	return 1;
    }

    return 0;
}
