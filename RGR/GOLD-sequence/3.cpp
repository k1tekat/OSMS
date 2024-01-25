#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include "math.h"

using namespace std;

const int BITS = 5;           // установка битности
int BIT_DEPTH  = pow(2,BITS); // кол-во состояний


void output_vect(vector<int> vect)
{
    for( auto i:vect)
    {
        cout<<i;
    }
    //cout<<"\n";
}

void gold_seq(vector<int>& orig,vector<int>& x,vector<int>& y)
{
    for(int i = 0; i < BIT_DEPTH; i++)
    {
        orig[i] = x[4] ^ y[4];
        int sum_x = x[3] ^ x[4];
        int sum_y = y[1] ^ y[4];

        for(int j = BITS-1;j > 0;j--)
            x[j] = x[j-1],y[j] = y[j-1];

        x[0] = sum_x;
        y[0] = sum_y;
        // cout<<"x ";
        // output_vect(x);
        // cout<<"y ";
        // output_vect(y);
        // cout<<"---------------------------------------------------\n";
    }
}

int main() 
{
    vector<int> original;
    original.resize(BIT_DEPTH);

    vector<int> x = {0,1,1,0,0}; //12
    vector<int> y = {1,0,0,1,1}; //12 + 7 = 19

    gold_seq(original,x,y);
    output_vect(original);

    cout<<"\n";


    std::ifstream inputFile("../CRC-generator/output.txt");   
    std::ofstream outputFile("output.txt"); 
    
    if (inputFile.is_open() && outputFile.is_open()) { 
        std::string fullSequence;
        
        while (std::getline(inputFile, fullSequence)) { 

            for( auto i:original)
            {
                outputFile << i;
            }

            for (char c : fullSequence) { 
                
                outputFile << c; 
            }


             for( auto i:original)
            {
                outputFile << i;
            }
            
            outputFile << std::endl; 
        }

        
        std::cout << "Successfully added GOLD sequence and saved in output.txt." << std::endl;
        
        inputFile.close(); 
        outputFile.close(); 
    } else {
        std::cerr << "Failed to open input.txt or output.txt." << std::endl;
    }

    std::ofstream outputFile_gold("gold.txt"); 
    
    if (outputFile_gold.is_open()) { 
        
            for( auto i:original)
            {
                outputFile_gold << i;
            }
            outputFile_gold << std::endl; 

        
        std::cout << "Successfully added GOLD sequence and saved in output.txt." << std::endl;
        
        inputFile.close(); 
        outputFile.close(); 
    } else {
        std::cerr << "Failed to open input.txt or output.txt." << std::endl;
    }

}