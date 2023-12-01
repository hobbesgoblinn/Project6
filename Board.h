#pragma once
#include<iostream>
using namespace std;
struct Board
{
    int size = 42;
    const int width = 7;
    const int height = 6;
    void Print();
    void CopyBoard(const Board& toCopy);
    
    char data[42] =
    {//  0   1   2   3   4   5   6  << COLUMNS
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-',
        '-','-','-','-','-','-','-' };
};