#include<iostream>
#include <cstdlib>
#include <string.h>
#include "map.h"
using namespace std;
Map::Map(){
    map=new char *[length];
    for(int i=0;i<length;i++)
            map[i]=new char [height];
    for(int i=0;i<length;i++)
        for(int j=0;j<height;j++)
            map[i][j]='.';
}
