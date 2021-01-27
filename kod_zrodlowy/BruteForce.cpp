//
// Created by Aron on 2020-11-09.
//

#include <climits>
#include <algorithm>
#include <iostream>
#include <utility>
#include "BruteForce.h"

using namespace std;

BruteForce::BruteForce(vector<vector<int>> matrix)
{
    cost_matrix = std::move(matrix);
    cost_best = INT_MAX;
}

void BruteForce::find_best_path()
{
    vector<int> cities;

    for (int i = 1; i < cost_matrix.size(); i++)
        cities.push_back(i);

    int cost;
    int prev_idx;
    iterations = 0;

    while(next_permutation(cities.begin(), cities.end()))
    {
        cost = 0;
        prev_idx = 0;
        for (int i = 0; i < cities.size(); i++)
        {
            cost += cost_matrix[prev_idx][cities[i]];
            prev_idx = cities[i];
        }
        cost += cost_matrix[prev_idx][0];

        if(cost < cost_best)
        {
            cost_best = cost;
            path_best = cities;
        }

        iterations++;
    }
}

void BruteForce::print_best_path()
{
    cout << "path: 0 - ";
    for (int i = 0; i < path_best.size(); ++i)
    {
        cout << path_best[i] << " - ";
    }
    cout << "0 ,\tcost: " << cost_best << ",\titerations: "<< iterations<<endl;
}

BruteForce::~BruteForce()
{
    cost_matrix.clear();
    path_best.clear();
    cout <<"bruteforce deleted\n";
}

