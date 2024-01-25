
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include "math.h"


using namespace std;

void read_file(std::vector<char>& vect)
{
    std::ifstream File("input.txt");
    
    if (File.is_open()) 
    { 
        std::string str;
        
        while (std::getline(File, str)) { 
            for (char c : str) { 
                vect.push_back(c);
            }
        }

        for(auto i : vect)
            cout<<i;
        
        std::cout << "Successfully." << std::endl;
        
        File.close(); 
    } else {
        std::cerr << "Failed to open input.txt." << std::endl;
    }



}