#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include "math.h"

//#include<boost/python.hpp>


using namespace std;



void read_file(std::vector<char>& vect,string filename)
{
    std::ifstream File(filename);
    
    if (File.is_open()) 
    { 
        std::string str;
        std::getline(File, str);
        for (char c : str) {      
            vect.push_back(c);
        }
        std::cout << "Successfull open file.\n" << std::endl;       
        File.close(); 
    } else {
        std::cerr << "Failed to open input.txt." << std::endl;
    }

}
void read_file(std::vector<int>& vect,string filename)
{
    std::ifstream File(filename);
    
    if (File.is_open()) 
    { 
        std::string str;
        std::getline(File, str);
        for (char c : str) {      
            vect.push_back(c);
        }

        std::cout << "Successfull open file.\n" << std::endl;       
        File.close(); 
    } else {
        std::cerr << "Failed to open input.txt." << std::endl;
    }

}
void write_file(vector<bitset<8>> vect,string filename)
{
    std::ofstream outputFile(filename); 
    
    if (outputFile.is_open()) {
        for(auto i : vect)
            outputFile << i;
        
        std::cout << "Successfully saved in output.txt." << std::endl;
        

        outputFile.close(); 
    } else {
        std::cerr << "Failed to open input.txt or output.txt." << std::endl;
    }

}
void write_file(vector<int> vect,string filename)
{
        std::ofstream outputFile(filename); 
    
    if (outputFile.is_open()) {
        for(auto i : vect)
            outputFile << i;
        
        std::cout << "Successfully saved in output.txt." << std::endl;
        

        outputFile.close(); 
    } else {
        std::cerr << "Failed to open input.txt or output.txt." << std::endl;
    }
}
void ascii_coder(vector<char>& input,vector<bitset<8>>& output)
{
    for(char i : input)
    {
        bitset<8> binary(i);
        output.push_back(binary);
    }
}



int main()
{
    vector<char> name;
    vector<bitset<8>> binary_name;
    string file_fullname = "data_txt file/input.txt";
    string file_binary_name = "data_txt file/output.txt";



    read_file(name,file_fullname);
    ascii_coder(name,binary_name);
    write_file(binary_name,file_binary_name);
}