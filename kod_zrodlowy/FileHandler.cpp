//
// Created by Aron on 2020-11-09.
//

#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>

#include "FileHandler.h"

using namespace std;

FileHandler::FileHandler()
{

}

vector<vector<int>> FileHandler::read_from_file(const char *datafile)
{
    ifstream f;
    vector<vector<int>> matrix;

    f.open(datafile);

    if(f.is_open())
    {
        int val, row = 0, col = 0, rows_total;

        f >> rows_total;
        //initialize matrix vector
        matrix.resize(rows_total);

        //input values from file
        for (int i = 0; i < rows_total; i++) {
            for (int j = 0; j < rows_total; j++) {
                f >> val;
                matrix[i].push_back(val);
            }

        }
    }else
        cout << "\n\tNie ma takiego pliku.\n";

    f.close();

    return matrix;
}

void FileHandler::print_matrix(std::vector<std::vector<int>> matrix)
{
    cout << endl <<matrix.size() << endl;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout<< setw(2) << right << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

FileHandler::~FileHandler()
{
    cout<<"filehandler deleted\n";
}

