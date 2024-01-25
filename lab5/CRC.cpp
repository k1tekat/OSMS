#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>

using namespace std;

#define PACKET_LENGTH 250
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


    vector<int> original;
    vector<int> packet;//= {1,1,1,0,1,0,1,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0};
    original.resize(PACKET_LENGTH + CRC_LENGTH);
    packet.resize(PACKET_LENGTH + CRC_LENGTH);
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

    output(original);

        for(int i = 0;i< PACKET_LENGTH+CRC_LENGTH;i++)
            packet[i] = original[i];
    output(packet);

        // Вычисление CRC
    for (int i = 0; i < PACKET_LENGTH; i++) {
        if (packet[i] == 1) {
            for (int j = 0; j < CRC_LENGTH ; j++) {
                packet[i+j] = packet[i+j] ^ generator[j];
            }
        }
    }

    cout<<"CRC:\n";
    for (int i = PACKET_LENGTH; i < PACKET_LENGTH + n; i++) //добавление n-1 нулей    
    {
        original[i] = packet[i];
        cout<<packet[i];
    }
    cout<<"\n";

    output(packet);

    

    for(int i = 0;i< PACKET_LENGTH+CRC_LENGTH;i++)
        packet[i] = original[i];
    
    // Вычисление CRC
    for (int i = 0; i < PACKET_LENGTH; i++) {
        if (packet[i] == 1) {
            for (int j = 0; j < CRC_LENGTH ; j++) {
                packet[i+j] = packet[i+j] ^ generator[j];
            }
        }
    }

    for(int i = 0;i< PACKET_LENGTH;i++)
        packet[i] = original[i];
    output(packet);





    // Искажение пакета данных и CRC
    int errors_detected = 0;
    int errors_undetected = 0;

    for (int i = 0; i < PACKET_LENGTH + CRC_LENGTH; i++) {
        int bit = packet[i];
        packet[i] = !bit; // инвертирование бита

        int remainder = 0;
        for (int j = 0; j < PACKET_LENGTH; j++) {
            if (packet[j] == 1) {
                for (int k = 0; k < CRC_LENGTH + 1; k++) {
                    packet[j+k] = packet[j+k] ^ generator[k];
                }
            }
        } 

        for (int h = 0; h < PACKET_LENGTH + CRC_LENGTH; h++) {
            if (packet[h] == 1) {
                remainder += 1;
            }
        }
        if (remainder == 0) {
            errors_undetected++;
            printf("Искаженный бит: %d\n", i);
        } else {
            errors_detected++;
        }
        packet[i] = bit; // восстановление исходного бита
    }

// Вывод отчета об ошибках
    printf("Количество обнаруженных ошибок: %d\n", errors_detected);
    printf("Количество необнаруженных ошибок: %d\n", errors_undetected);



}