#ifndef MAIN_H
#define MAIN_H

#include<boost/algorithm/string/split.hpp>                                      
#include<boost/algorithm/string.hpp>
#include<iostream>                                                              
#include<vector>
#include<fstream>                                                                
#include<string>
#include <iostream> 
#include <regex>
#include <map>

using namespace std;

class node;
map<string, node> nodeId;

 class node
{

public:

int width;
int height;
int weight;
int terminal;//terminal 是什么
int xCoordinate;
int yCoordinate;
int xBy2;
int yBy2;
string orientation; //orientation 还没有想好怎么改
int cellRowId;
vector <int> Netlist;
string nodeName;

void setParameterNodes(string nodeName, int width, int height,int terminal)
   {
 	this->nodeName = nodeName;
 	this->width = width;
	this->height = height;
	this->terminal = terminal;
   }

void setParameterWts(int weight)
   {
 	this->weight = weight;
   }

void setParameterPl(int xCoordinate,int yCoordinate,string orientation)
{
	this->xCoordinate = xCoordinate;
	this->yCoordinate = yCoordinate;
	this->orientation = orientation;
}

void setOrientation(string orient)
{
	cout<<(this->orientation)<<"   "<<orient<<endl;
	this->orientation = orient;
	if ((orient!=this->orientation) && (this->orientation[0]!='F'))
	{
		int rotateDistance = (8 + orientToInt(orient) - orientToInt(this->orientation)) % 4;
		if ((rotateDistance%2==1)&&(this->width<16))
		{
			int _width = this->width;
			int _height = this->height;
			this->width = _width;
			this->height = _height;
		}
	}
}


void setRowId(int cellRowId)
{
	this->cellRowId = cellRowId;
}

void setNetList(int NetId)
{
	Netlist.push_back(NetId);
}

void setCenter(int xBy2, int yBy2)
{
	this->xBy2 = xBy2;
	this->yBy2 = yBy2;
}


class row;
map<int, row> rowId;
int RowWidth;
int xLimit;
class row
{
public:
int Id;
int coOrdinate;
int height;
int siteWidth;
int siteSpacing;
string siteOrient;
string siteSymmetry;
int siteRowOrigin;
int numSites;
int overlap;
vector <string> cellList;

void setId(int Id)

{
	this->Id=Id;
}


void setParameterRows(int coOrdinate,int height,int siteWidth,int siteSpacing,string siteOrient,string siteSymmetry,int siteRowOrigin,int numSites)
   {
 	this->coOrdinate = coOrdinate;
 	this->height = height;
	this->siteWidth = siteWidth;
	this->siteSpacing = siteSpacing;
 	this->siteOrient = siteOrient;
	this->siteSymmetry = siteSymmetry;
	this->siteRowOrigin = siteRowOrigin;
	this->numSites = numSites;
   }

void setCellList(string cellId)
 {
	cellList.push_back(cellId);	
 }

vector<string> sortByX() //将cellList中的cell按x坐标排列
{
int i=0,x=0;
map<int,string> sortx;
map<int,string>::iterator it;
vector<string>::iterator itl;
vector<string>list;
for(i=0;i<(this->cellList.size());i++)
{
	x=nodeId.find(cellList[i])->second.xCoordinate;
	sortx.insert(pair<int,string> (x,cellList[i]));
}
for(it=sortx.begin();it!=sortx.end();++it)
{
	list.push_back(it->second);
}
this->cellList=list;
return this->cellList;
}

void calcRowOverlap() //
{
	vector <string> :: iterator it1;
	int xLast=0, widthLast = 0;

	xLast = nodeId[cellList[cellList.size()-1]].xCoordinate;
	widthLast = nodeId[cellList[cellList.size()-1]].width;
	overlap = xLast + widthLast - (RowWidth+xLimit);
	
	this ->overlap = overlap;	
}



map<int, vector<string> > netToCell;

#endif