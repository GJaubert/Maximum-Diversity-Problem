#include "../lib/mdp.hpp"
#include "../lib/strategy.hpp"
#include "../lib/greedy.hpp"
#include "../lib/grasp.hpp"
#include <memory>
#include <chrono>
#include <fstream>
using namespace std::chrono;

int main(int args, char* argv[]) {
  try {
    std::ofstream file;
    file.open("tables/grasp-tables.md", std::ofstream::app);
    std::vector<std::string> sizes = {"15", "20", "30"};
    file << "| ID | n | k | m | Max_iter | LRC | z | S | CPU(μs)\n";
    file << "|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|\n";
    std::shared_ptr<Strategy> ptr;
    // ptr = std::make_shared<Greedy>();
    // ptr->computeSolution(test);
    ptr = std::make_shared<Grasp>();
    Mdp result;
    for (int s = 0; s < sizes.size(); s++) {
      for (int i = 2; i < 4; i++) {
        std::string fileName = "data/max_div_";
        fileName += sizes[s];
        fileName += "_";
        fileName += std::to_string(i);
        fileName += ".txt";
        for (int m = 2; m < 5; m++) {
          Mdp newMdp(fileName, m);
          ptr = std::make_shared<Grasp>();
          auto start = high_resolution_clock::now();
          result = ptr->computeSolution(newMdp);
          auto stop = high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(stop - start);
          file << fileName << "|" << sizes[s] << "|" << i << "|" << m << "|10|" << K << "|" << result.calculateZ() << "|" << result.toString() << "|" << duration.count() << "\n"; 
        }
      }
    }
    return 0;
  } catch(std::string err) {
    std::cout << err;
  }
}