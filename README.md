
## Requirements

* g++, make 
* yaml-cpp: https://github.com/jbeder/yaml-cpp/blob/master/install.txt

## Build and Run

Follow the steps below to build the application:

```bash
git clone https://github.com/alvyC/HikingSimulator
cd HikingSimulator
make
```

To run the application, you can create your own input yaml file and pass it as command line argument with `-f` option:
```bash
./bin/hiking_simulator -f input.yaml.
```
## Strategies
A strategy interface has been provided which supports automatic registration of new implemented strategies. So far, the application supports two strategies: greedy-strategy and slowest-first-strategy. 
There is no one optimal strategy which will work for all different inputs. However, the following strategies were developed based on some heuristics that can work well in certain cases.

### Greedy-Strategy
In the greedy approach we pick the fastest hiker and use him as a torch bearer to help cross all other hikers. The goal is to have the lowest return time and torch idle time.
Time complexity of the strategy is O(n) and space complexity is O(1), where n is the number of hikers.

### Slowest-First-Strategy
The logic behind this strategy is that by moving the slowest hikers first, the faster hikers can maximize their speed in subsequent crossings. We pick two slower hiker to cross and then pick the fastest hiker who already crossed to come back with the torch.
Time complexity of the strategy is O(nlogn) and space compexity is O(n), where n is the number of hikers.
