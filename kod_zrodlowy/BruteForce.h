//
// Created by Aron on 2020-11-09.
//

#ifndef CODE_BRUTEFORCE_H
#define CODE_BRUTEFORCE_H

#include <vector>

class BruteForce {
private:
    std::vector<std::vector<int>> cost_matrix;
    std::vector<int> path_best;
    int cost_best;
    int iterations;

public:
    explicit BruteForce(std::vector<std::vector<int>> matrix);
    ~BruteForce();

    void find_best_path();
    void print_best_path();
};


#endif //CODE_BRUTEFORCE_H
