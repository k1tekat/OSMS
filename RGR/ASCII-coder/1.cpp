#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <bitset>

using namespace std;

int main() {
    std::ifstream inputFile("input.txt");   
    std::ofstream outputFile("output.txt"); 
    
    if (inputFile.is_open() && outputFile.is_open()) { 
        std::string fullName;
        
        while (std::getline(inputFile, fullName)) { 
            for (char c : fullName) { 
                std::bitset<8> binary(c); 
                
                outputFile << binary; 
            }
            
            outputFile << std::endl; 
        }
        
        std::cout << "Successfully converted ASCII characters to binary sequence and saved in output.txt." << std::endl;
        
        inputFile.close(); 
        outputFile.close(); 
    } else {
        std::cerr << "Failed to open input.txt or output.txt." << std::endl;
    }

    return 0;
}