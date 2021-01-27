//
// Created by Aron on 2020-11-09.
//

#ifndef CODE_BRANCHANDBOUND_H
#define CODE_BRANCHANDBOUND_H

#include <vector>

class BranchAndBound {
private:
    std::vector<std::vector<int>> cost_matrix;
    std::vector<int> path_best;

    std::vector<int> visited;

    int amount_of_vertices;
    int cost_best;
    int iterations;

private:
    int first_min(int vertex);
    int second_min(int vertex);
    void update_path_best(std::vector<int> path_curr);

public:
    explicit BranchAndBound(std::vector<std::vector<int>> matrix);
    ~BranchAndBound();

    void find_best_path();
    void ATSP(std::vector<int> path_curr, int cost_curr, int bound_lower_curr, int level);
    void print_best_path();
};


#endif //CODE_BRANCHANDBOUND_H
