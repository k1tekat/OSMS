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
        cout<<i<<" ";
    }
    cout<<"\n";
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


int corr(vector<int> x,vector<int> y) //classic corr (formula 3.2)
{
    int cor = 0; 
    for(int i = 0;i<x.size();i++)
        cor = cor + (x[i]*y[i]);
    return cor;

}

int under_b(vector<int> x)//Подсчет части под дробью в формуле (3.3)
{
    int cor = 0; 
    for(int i = 0;i<x.size();i++)
        cor = cor + pow(x[i],2);
    return cor;

}

float norm_corr(vector<int> x,vector<int> y)//normal corr по формуле (3.3)
{
    float up_b = corr(x,y);//Верхняя часть дроби 
    float un_b = (sqrt(under_b(x) * under_b(y)));//нижняя часть дроби

    //cout<<"up_b: "<<up_b<<"\n";
    //cout<<"un_b: "<<un_b<<"\n";
    //cout<<"un_b/un_b: "<<up_b/un_b<<"\n";

    return up_b/un_b;
}

int main() 
{
    vector<int> original;
    vector<int> move;
    vector<int> arr;

    move.resize(BIT_DEPTH);
    arr.resize(BIT_DEPTH);
    original.resize(BIT_DEPTH);

    move = original;
    
    vector<int> x = {0,1,1,0,0}; //12
    vector<int> y = {1,0,0,1,1}; //12 + 7 = 19

    vector<int> x_edit = {0,1,1,0,1};//12 + 1 = 13
    vector<int> y_edit = {0,1,1,1,1};//12 - 5 = 7 

    vector<int> x_edit2 = {0,0,1,0,1};//12 + 1 = 13
    vector<int> y_edit2 = {1,0,0,0,1};//12 - 5 = 7 

    vector<int> x_edit3 = {0,0,1,1,1};//12 + 1 = 13
    vector<int> y_edit3 = {0,0,0,0,1};//12 - 5 = 7 

    gold_seq(original,x,y);
    output_vect(original);
    move = original;
    output_vect(move);
    cout<<"\n";

    // Вывод заголовка таблицы
    printf("Сдвиг|              Биты               | Автокорреляция\n");

    // Вывод строк таблицы
    for (int shift = 0; shift <= BIT_DEPTH; shift++) {
        printf("%4d | ", shift);

        // Вывод битов оригинала
        for (int i = 0; i < BIT_DEPTH ; i++) {
            printf("%d", move[i]);
        }

        printf(" | ");

        //  вычисление автокорреляции
        float corr = norm_corr(original,move);

        printf("%+1.3f\n", corr);


        // replace
        int last_place = move[BIT_DEPTH-1];
        for(int i = move.size();i > 0; i--)
            move[i] = move[i-1];
        move[0] = last_place;
    }
    cout<<"\n";

    output_vect(move);
    gold_seq(arr,x_edit2,y_edit2);

    move = arr;


    // Вывод заголовка таблицы
    printf("Сдвиг|              Биты               | Автокорреляция\n");

    // Вывод строк таблицы
    for (int shift = 0; shift <= BIT_DEPTH; shift++) {
        printf("%4d | ", shift);

        // Вывод битов оригинала
        for (int i = 0; i < BIT_DEPTH ; i++) {
            printf("%d", move[i]);
        }

        printf(" | ");

        //  вычисление автокорреляции
        float corr = norm_corr(original,move);

        printf("%+1.3f\n", corr);


        // replace
        int last_place = move[BIT_DEPTH-1];
        for(int i = move.size();i > 0; i--)
            move[i] = move[i-1];
        move[0] = last_place;
    }
    cout<<"\n";


       gold_seq(arr,x_edit3,y_edit3);

    move = arr;
    output_vect(move);


    // Вывод заголовка таблицы
    printf("Сдвиг|              Биты               | Автокорреляция\n");

    // Вывод строк таблицы
    for (int shift = 0; shift <= BIT_DEPTH; shift++) {
        printf("%4d | ", shift);

        // Вывод битов оригинала
        for (int i = 0; i < BIT_DEPTH ; i++) {
            printf("%d", move[i]);
        }

        printf(" | ");

        //  вычисление автокорреляции
        float corr = norm_corr(original,move);

        printf("%+1.3f\n", corr);


        // replace
        int last_place = move[BIT_DEPTH-1];
        for(int i = move.size();i > 0; i--)
            move[i] = move[i-1];
        move[0] = last_place;
    }
    cout<<"\n";
    //output_vect(original);
    //output_vect(arr);

    //cout<<"\nnorm corr: "<<norm_corr(original,arr)<<"\n\n";


   
}