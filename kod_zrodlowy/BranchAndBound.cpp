//
// Created by Aron on 2020-11-09.
//

#include <iostream>
#include <utility>
#include <cmath>
#include <climits>

#include "BranchAndBound.h"

using namespace std;

BranchAndBound::BranchAndBound(std::vector<std::vector<int>> matrix)
{
    cost_matrix = std::move(matrix);
    cost_best = INT_MAX;
    amount_of_vertices = cost_matrix.size();
}

void BranchAndBound::find_best_path()
{
    vector<int> path_curr;
    int bound_lower_curr = 0;

    iterations = 0;
    visited.clear();
    path_best.clear();

    //vectors initialization
    for (int i = 0; i < amount_of_vertices + 1 ; i++)//one more to go back to first node
    {
        path_curr.push_back(-1);
        visited.push_back(0);
    }

    //calculate first lower bound
    for (int j = 0; j < amount_of_vertices; j++)
        bound_lower_curr += first_min(j) + second_min(j);

    bound_lower_curr = ceil(bound_lower_curr / 2);

    //start at vertex '0'
    visited[0] = 1;
    path_curr[0] = 0;

    ATSP(path_curr, 0, bound_lower_curr, 1);
}

void BranchAndBound::ATSP(std::vector<int> path_curr, int cost_curr, int bound_lower_curr, int level)
{
    int vertex_before = path_curr[level - 1];
    //check if all nodes have been checked
    if(amount_of_vertices == level)
    {
        int cost_total = cost_curr + cost_matrix[vertex_before][path_curr[0]];

        //update solution if current is better than older
        if(cost_total < cost_best)
        {
            cost_best = cost_total;
            //update best path best
            update_path_best(path_curr);
        }
        return;
    }

    for (int vertex_curr = 0; vertex_curr < amount_of_vertices ; vertex_curr++)
    {
        //check unchecked vertices and not entry vertices
        if(visited[vertex_curr] == 0 && vertex_before != vertex_curr)
        {
            int bound_curr_backup = bound_lower_curr;
            cost_curr += cost_matrix[vertex_before][vertex_curr];

            //depending on level value, calculate new value for bound current
            if(level == 1)
                bound_lower_curr -= (first_min(vertex_before) + first_min(vertex_curr) ) / 2;
            else
                bound_lower_curr -= (second_min(vertex_before) + first_min(vertex_curr) ) / 2;

            //calculating potential of vertex_curr
            //if vertex_curr is promising, digg into it
            if(bound_lower_curr + cost_curr < cost_best)
            {
                visited[vertex_curr] = 1;
                path_curr[level] = vertex_curr;

                ATSP(path_curr, cost_curr, bound_lower_curr, level + 1);
            }

            //if vertex_curr is not promising, restore changes
            cost_curr -= cost_matrix[vertex_before][vertex_curr];
            bound_lower_curr = bound_curr_backup;

            for (int i = 0; i < visited.size(); i++)
                visited[path_curr[i]] = i <= level - 1;
        }
    }
}

int BranchAndBound::first_min(int vertex)
{
    int min = INT_MAX;
    for (int k = 0 ; k < amount_of_vertices ; k++)
        if (cost_matrix[vertex][k] < min && vertex != k)
            min = cost_matrix[vertex][k];

    return min;
}

int BranchAndBound::second_min(int vertex)
{
    int first = INT_MAX;
    int second = INT_MAX;
    for (int j = 0 ; j < amount_of_vertices ; j++)
    {
        if (vertex == j)
            continue;

        if (cost_matrix[vertex][j] <= first)
        {
            second = first;
            first = cost_matrix[vertex][j];
        }
        else if (cost_matrix[vertex][j] <= second && cost_matrix[vertex][j] != first)
            second = cost_matrix[vertex][j];
    }

    return second;
}

void BranchAndBound::update_path_best(std::vector<int> path_curr)
{
    path_best.clear();
    for (int i = 0 ; i < amount_of_vertices ; i++)
        path_best.push_back(path_curr[i]);
}

void BranchAndBound::print_best_path()
{
    for (int i = 0; i < path_best.size(); ++i)
    {
        cout << path_best[i] << " - ";
    }
    cout << "0, \tcost: " << cost_best<<endl;
}

BranchAndBound::~BranchAndBound()
{
    cost_matrix.clear();
    path_best.clear();
    visited.clear();
    cout <<"b&b deleted\n";
}

