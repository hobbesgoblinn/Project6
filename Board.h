#pragma once
#include<iostream>
using namespace std;
struct Board
{
    void Print();
    void CopyBoard(const char toCopy[]);
    
    char data[42] =
    {//  0   1   2   3   4   5   6  << COLUMNS
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-' };
};

