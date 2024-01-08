#include <iostream>
#include <vector>
#include <math.h>


using namespace std;


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

    vector<int> a = {1,3,5,-1,-4,-5,1,4};
    vector<int> b = {2,4,7,0,-3,-4,2,5};
    vector<int> c = {-5,-1,3,-4,2,-6,4,-1};
    
    cout<<"corr(a,b): "<<corr(a,b)<<"\n";
    cout<<"corr(a,c): "<<corr(a,c)<<"\n";
    cout<<"corr(b,c): "<<corr(b,c)<<"\n\n";

    cout<<"norm_corr(a,b): "<<norm_corr(a,b)<<"\n";
    cout<<"norm_corr(a,c): "<<norm_corr(a,c)<<"\n";
    cout<<"norm_corr(b,c): "<<norm_corr(b,c)<<"\n";

    cout<<"\n  | a | b | c |\n"<<"|a|"<<" - |"<<corr(a,b)<<"|"<<corr(a,c)<<"\n"<<"|b|"<<corr(a,b)<<"|"<<" - "<<"|"<<corr(b,c)<<"\n"<<"|c| "<<corr(a,c)<<"| "<<corr(b,c)<<"| - \n\n";
    cout<<"  |    a   |    b   |    c   |\n"<<"|a|"<<"    -   |"<<norm_corr(a,b)<<"|"<<norm_corr(a,c)<<"\n"<<"|b|"<<norm_corr(a,b)<<"|"<<"   -    "<<"|"<<norm_corr(b,c)<<"\n"<<"|c|"<<norm_corr(a,c)<<"|"<<norm_corr(b,c)<<" |   - \n\n";
}