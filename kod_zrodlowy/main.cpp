#include <iostream>
#include <chrono>
#include <bitset>
#include <list>
#include <iomanip>

#include "FileHandler.h"
#include "BruteForce.h"
#include "BranchAndBound.h"

using namespace std;

//----------------------TIMER-------------------------
struct{
    chrono::high_resolution_clock::time_point start_time;
    chrono::high_resolution_clock::time_point stop_time;
    uint64_t duration = -1;

    void start()
    {
        start_time = chrono::high_resolution_clock::now();
    }

    void stop()
    {
        stop_time = chrono::high_resolution_clock::now();
        duration =  chrono::duration_cast<chrono::nanoseconds>(stop_time-start_time).count();
    }

    void info()
    {
        cout << "time: " << float(duration)/1000000.0 << "ms" <<endl;
    }
}Timer;

//--------------GENERATOR------------------
struct{
    static void init()
    {
        srand(time_t(get_seed()));
    }

    //returns seed for generating random numbers
    static unsigned get_seed()
    {
        return chrono::system_clock::now().time_since_epoch().count();
    }

    static int get_rand_int(int min, int max)
    {
        if(min==max) return max;
        if((min<0   && max<0) || (min>0 &&   max>0))//if min and max are same signs
            if(min  < 0)
                return rand() % (min-max) + min;//negative
            else
                return rand() % (max-min) + min;//positive
        else return rand() % (abs(max)+abs(min)) + min;//if different signs
    }

    static std::vector<std::vector<int>> generate_random_matrix(int rows_total)
    {
        //initialize matrix veåctor
        vector<vector<int>> matrix(rows_total);

        for (int i = 0; i < rows_total; i++) {
            for (int j = 0; j < rows_total; j++) {
                if(i==j)
                {
                    matrix[i].push_back(0);
                    continue;
                }
                matrix[i].push_back(get_rand_int(10,70));
            }
        }

        return matrix;
    }
}Generator;

//----------------------MAIN-------------------------
vector< vector<int> > matrix;

int main(int argc, char *argv[])
{
    auto *pFileHandler = new FileHandler();
    BruteForce *pBruteForce = nullptr;
    BranchAndBound *pBranchAndBound = nullptr;
    Generator.init();

    bool running = true;
    char choice;
    string filename;
    int rows_total;

    while(running)
    {
        cout <<"\n--- MENU GLOWNE ---\n";
        cout <<"1.Wczytanie danych z pliku\n"
               "2.Wygenerowanie danych losowych\n"
               "3.Wyswietlenie danych\n"
               "4.Brutal Force\n"
               "5.Branch & Bound\n"
               "0.Wyjscie\n";
        cout <<"--- MENU GLOWNE ---\n";
        cout << "User choice:";
        cin >> choice;
        switch(choice)
        {
            case '1':
                cout << "Podaj nazwe pliku(uzupelnic pole X: tsp_X.txt): ";
                cin >> filename;
                filename.insert(0, "tsp/tsp_");
                filename.append(".txt");
                matrix = pFileHandler->read_from_file(filename.c_str());
                pFileHandler->print_matrix(matrix);
                break;

            case '2':
                cout <<"podaj liczbe wierszy: " <<endl;
                cin >> rows_total;
                matrix = Generator.generate_random_matrix(rows_total);
                pFileHandler->print_matrix(matrix);
                break;

            case '3':
                pFileHandler->print_matrix(matrix);
                break;

            case '4':
                pBruteForce = new BruteForce(matrix);

                Timer.start();
                pBruteForce->find_best_path();
                Timer.stop();

                pBruteForce->print_best_path();
                Timer.info();
                break;

            case '5':
                pBranchAndBound = new BranchAndBound(matrix);

                Timer.start();
                pBranchAndBound->find_best_path();
                Timer.stop();

                pBranchAndBound->print_best_path();
                Timer.info();
                break;

            case '0':
                running = false;
                break;

            default: break;
        }
    }//while running

    //free memory
    delete pBranchAndBound;
    delete pFileHandler;
    delete pBruteForce;
    pBranchAndBound = nullptr;
    pFileHandler = nullptr;
    pBruteForce = nullptr;

    system("pause");
    return 0;
}
