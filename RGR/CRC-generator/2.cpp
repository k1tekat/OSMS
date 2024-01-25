#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>

using namespace std;

#define PACKET_LENGTH 32
#define CRC_LENGTH 8


void output(vector<int> &arr)
{
    cout<<"Вывод последовательности: ";
    for(int i = 0;i< PACKET_LENGTH+CRC_LENGTH;i++)
        cout<<arr[i];
    cout<<"\n";
}
int main() 
{


    FILE*  file = fopen("../ASCII-coder/output.txt","r");
    fseek(file, 0, SEEK_END);
    size_t  size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    cout<<"size= "<<size;


    vector<int> original;
    vector<int> packet;//= {1,1,1,0,1,0,1,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0};
    original.resize(size);
    packet.resize(size);
                            //   7 6 5 4 3 2 1 0
    int generator[CRC_LENGTH] = {1,1,0,1,1,0,1,1}; // порождающий полином G для делителя: 11011011
    int n = CRC_LENGTH - 1;


    cout<<"Заполнение original: \n";
    for (int i = 0; i < PACKET_LENGTH; i++) {
        original[i] = rand()%2;
    }
    
    cout<<"Заполнение пакета: \n";
    for (int i = 0; i < PACKET_LENGTH; i++)
    {
        packet[i] = original[i];
    }
    for (int i = PACKET_LENGTH; i < PACKET_LENGTH + n; i++) //добавление n-1 нулей    
    {
        packet[i] = 0;
    }
    output(original);
    output(packet);

    // Вычисление CRC
    for (int i = 0; i < PACKET_LENGTH; i++) {
        if (packet[i] == 1) {
            for (int j = 0; j < CRC_LENGTH ; j++) {
                packet[i+j] = packet[i+j] ^ generator[j];
            }
        }
    }
    output(packet);



    cout<<"CRC:\n";
    for (int i = PACKET_LENGTH; i < PACKET_LENGTH + n; i++) //добавление n-1 нулей    
    {
        original[i] = packet[i];
        cout<<packet[i];
    }
    cout<<"\n";
    std::ifstream inputFile("../ASCII-coder/output.txt");   
    std::ofstream outputFile("output.txt"); 
    
    if (inputFile.is_open() && outputFile.is_open()) { 
        std::string fullSequence;
        
        while (std::getline(inputFile, fullSequence)) { 
            for (char c : fullSequence) { 
                
                outputFile << c; 
            }
            for (int i = PACKET_LENGTH; i < PACKET_LENGTH + n; i++) //добавление n-1 нулей    
            {
                
                outputFile << packet[i];
            }
            
            outputFile << std::endl; 
        }

        
        std::cout << "Successfully added CRC sequence and saved in output.txt." << std::endl;
        
        inputFile.close(); 
        outputFile.close(); 
    } else {
        std::cerr << "Failed to open input.txt or output.txt." << std::endl;
    }

    std::ofstream outputFile_crc("crc.txt"); 

    if (outputFile_crc.is_open()) { 

        
        for (int i = PACKET_LENGTH; i < PACKET_LENGTH + n; i++) //добавление n-1 нулей    
            {
                
                outputFile_crc << packet[i];
            }
            
        outputFile_crc << std::endl; 

        
        std::cout << "Successfully added CRC sequence and saved in output.txt." << std::endl;
        
        inputFile.close(); 
        outputFile.close(); 
    } else {
        std::cerr << "Failed to open input.txt or output.txt." << std::endl;
    }
}