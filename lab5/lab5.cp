#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;



int main() {

    #define PACKET_LENGTH 32
    #define CRC_LENGTH 8
    vector<int> a;
    a.resize(PACKET_LENGTH + CRC_LENGTH);
                                            //
    int packet[PACKET_LENGTH + CRC_LENGTH]; //= {1,1,1,0,1,0,1,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0};
    int call_packet[PACKET_LENGTH + CRC_LENGTH];


                    // 7 6 5 4 3 2 1 0
    int generator[] = {1,1,0,1,1,0,1,1}; // порождающий полином G для делителя: 11011011
    int i, j;

    printf("Заполнение пакета: ");
    for (i = 0; i < PACKET_LENGTH; i++) {
        a[i] = rand()%2;
    }
    
    

    printf("Заполнение пакета: ");
    for (i = 0; i < PACKET_LENGTH; i++) {
        packet[i] = a[i];
    }

    for (i = PACKET_LENGTH; i < PACKET_LENGTH+CRC_LENGTH; i++) {
        packet[i] = 0;
    }
    printf("\n");

// Вывод рандомного пакета данных
    printf("Рандомный пакет данных: ");
    for (i = 0; i < PACKET_LENGTH+CRC_LENGTH; i++) {
        printf("%d", packet[i]);
    }
    printf("\n");
// Вычисление CRC
    for (i = 0; i < PACKET_LENGTH; i++) {
        if (packet[i] == 1) {
            for (j = 0; j < CRC_LENGTH + 1; j++) {
                packet[i+j] = packet[i+j] ^ generator[j];
            }
        }
    }
// Вывод полученного значения CRC
    printf("Значение CRC: ");
    for (i = PACKET_LENGTH; i < PACKET_LENGTH + CRC_LENGTH; i++) {
        printf("%d", packet[i]);
    }
    printf("\n");




    for (int y = 0; y < PACKET_LENGTH + CRC_LENGTH; y++) {
        call_packet[y] = call_packet[y] + packet[y];
        }


// Искажение пакета данных и CRC
    int errors_detected = 0;
    int errors_undetected = 0;

    for (i = 0; i < PACKET_LENGTH + CRC_LENGTH; i++) {
        int bit = call_packet[i];
        call_packet[i] = !bit; // инвертирование бита

        int remainder = 0;
        for (j = 0; j < PACKET_LENGTH; j++) {
            if (call_packet[j] == 1) {
                for (int k = 0; k < CRC_LENGTH + 1; k++) {
                    call_packet[j+k] = call_packet[j+k] ^ generator[k];
                }
            }
        }

        for (int h = 0; h < PACKET_LENGTH + CRC_LENGTH; h++) {
            if (call_packet[h] == 1) {
                remainder += 1;
            }
        }
        if (remainder == 0) {
            errors_undetected++;
            printf("Искаженный бит: %d\n", i);
        } else {
            errors_detected++;
        }
        call_packet[i] = bit; // восстановление исходного бита
    }

// Вывод отчета об ошибках
    printf("Количество обнаруженных ошибок: %d\n", errors_detected);
    printf("Количество необнаруженных ошибок: %d\n", errors_undetected);

    return 0;
}