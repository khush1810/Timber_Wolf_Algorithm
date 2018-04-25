#include "head.h"
#include<iostream>                                                              
#include<vector>
#include<fstream>                                                                
#include<string>
#include <iostream>
#include <sstream> 
#include <regex>
#include <map>



void initialPlacement();
void printCellMap();
void printRowMap();
int rowOverlap();
void update();
long int wireLength();
long int cellOverlap();
void timberWolfAlgorithm();
void update_Temp();
void moveCell(int xLimit);
bool checkMove(long int prevCost);
void readNets() 
void readPl() 
void readScl() 
void readNodes() 
void readWts() 

double Temp;

int main()
{                                                                  
    readNodes();
	readWts();
	readPl();
	readNets();
	readScl();

	update();
	RowToCellMapping()//to create mapping from row to cells
	timberWolfAlgorithm();   //performs the iterations required  
	timberWolfAlgorithm2();  //performs the algorithm when the 
	int a;
	cin>>a;
	return 0;
}




int macroPlacement() // performs placement when called by the algorithm
{
	int x=minX,yValue=0;
	xLimit=b.minX;
	map<int, row> ::iterator itRow;
	itRow = rowId.begin();
	int rowHeight = itRow->second.height; // The height is fixed to 16

	map<string,node>::iterator itNode;
	for(itNode = nodeId.begin();itNode != nodeId.end();++itNode)
	{
		if(itNode->second.terminal == false && itNode->second.height > rowHeight)
		{	
			if(xValue + itNode->second.width > xLimit)
			{
				xLimit = xValue + itNode->second.width+1;
			}
			if(yValue + itNode->second.height < b.maxY)
			{
				itNode->second.yCoordinate = yValue;
				itNode->second.xCoordinate = xValue;				
			}
			else
			{					
				yValue = 0;
				xValue = xLimit;
				itNode->second.yCoordinate = yValue;
				itNode->second.xCoordinate = xValue;			
			}
			yValue = yValue + itNode->second.height;
		}
	}
	return xLimit;
}

void initialPlacement()
{
map<string, node> ::iterator itNode;
map<int, row> ::iterator itRow=rowId.begin();
int totalWidth = 0, rowWidth = 0, cnt=0,count=0, xCord=xLimit, yCord=0;
for(itNode = nodeId.begin(); itNode != nodeId.end(); ++itNode)
{
	if(itNode->second.terminal == 0 && itNode->second.height == 16)
	{
		totalWidth += itNode->second.width;
		numNodes++;
	}
}
itNode = nodeId.begin();
//cout<<(itNode->second.terminal)<<endl;

totalWidth = totalWidth + numNodes;
rowWidth = totalWidth/rowId.size();
numCellsPerRow = ceil(float (numNodes)/rowId.size())-1;


cout<<"rowNum="<<rowId.size()<<endl;
cout<<"nodeNum(not fixed)="<<numNodes<<endl;

for(itNode = nodeId.begin(); itNode != nodeId.end(); ++itNode)
{
	if(itRow != rowId.end() && itNode->second.terminal == 0 && itNode->second.height <= itRow->second.height && cnt < (numCellsPerRow))
	{
		itNode->second.yCoordinate = itRow->second.coOrdinate;
		itNode->second.xCoordinate = xCord;
		xCord += itNode->second.width+1;
		cnt++;
					
		if(cnt == numCellsPerRow)
		{						
			cnt = 0;
			xCord = xLimit;
			++itRow;	
		}
	}			
}
update();
createRowToCellMap();*/
}

int rowOverlap()
{
	map<int, row> ::iterator itRow;
	int cost3=0;

	for(itRow = rowId.begin(); itRow != rowId.end(); ++itRow)
	{	
		itRow->second.calcRowOverlap();
		if(itRow->second.overlap >= 0)
		{
			cost3 += itRow->second.overlap;
		}		
	}
	cout<<"Overlap : "<<cost3<<endl;
return cost3;	
}

void update()
  {
	map<string, node> ::iterator itNode;
	
	int xBy2 =0, yBy2 =0;
	for(itNode = nodeId.begin(); itNode != nodeId.end(); ++itNode)
	{	
		xBy2 = (itNode->second.xCoordinate)+((itNode->second.width)/2);
		yBy2 = (itNode->second.yCoordinate)+((itNode->second.height)/2);	
		itNode->second.setCenter(xBy2,yBy2);			
	}
  }

long int wireLength() //wireLength 没有考虑offset
{
	map<int, vector<string>> :: iterator itNet;
	vector<string> :: iterator itCellList;
	int xVal, yVal, wireLength=0;
	//cout<< "updating wire length "<< endl;
	for(itNet= netToCell.begin(); itNet != netToCell.end(); ++itNet)
	{
			int minXW = 32767, minYW = 32767, maxXW = -32768 , maxYW = -32768;
			for(itCellList = itNet->second.begin(); itCellList != itNet->second.end(); ++itCellList)
			{
				//cout<<"i am in";
				xVal = nodeId[*itCellList].xBy2;
				yVal = nodeId[*itCellList].yBy2;
				//cout<<"x = "<<xVal<<" y = "<<yVal<<endl;
				if(xVal < minXW)
				minXW = xVal;
				if(xVal > maxXW)
				maxXW = xVal;
				if(yVal < minYW)
				minYW = yVal;
				if(yVal > maxYW)
				maxYW = yVal;
			}
			wireLength += abs((maxXW-minXW)) + abs((maxYW-minYW));
	}
			cout << "New Wire length : " << wireLength << endl;
return wireLength;
}

long int cellOverlap()
{

map<string,node>::iterator nodeit=nodeId.begin();
map<int,row>::iterator rowit;
int x1=0,w1=0,x2=0,w2=0,h1=0,h2=0,overlap=0,i=0;
long int totaloverlap=0;

vector<string>list;
for(rowit=rowId.begin();rowit!=rowId.end();++rowit)
{
	overlap=0;
	list=rowit->second.sortByX();
	overlap=0;
	for(i=0;i<list.size();i++)
	{
		node nodeobj=nodeId.find(list[i])->second;
		x1=nodeobj.xCoordinate;
		w1=nodeobj.width;
		h1=nodeobj.height;
		i++;
		if(i==list.size())
		{
			break;		
		}
		x2=nodeId.find(list[i])->second.xCoordinate;
		w2=nodeId.find(list[i])->second.width;
		h2=nodeId.find(list[i])->second.height;
		h1 = h2>h1?h1:h2;
		if(x2<=(x1+w1)&&(x2+w2)>=(x1+w1))
		{
			overlap+=((x1+w1)-x2)*h1;
		}
		else if(x2>=x1 && x2<=(x1+w1) && (x2+w2)<=(x1+w1))//原来为(x2+w2)<=w1
		{
			overlap+=w2*h1;
		}
		i--;
	}
totaloverlap+=overlap;

}
cout << "Total cell overlap :" << totaloverlap << endl;
return totaloverlap;
}

void moveCell(int xLimit)
{
srand(time(NULL));
int randomCellnum, randRow, randXcord;
stringstream randomCellTemp;
string randomCellStr,randomCell, randomCell2;
node n;
row r;
map<string, node> ::iterator itNode, itNode2;
map<int, row> ::iterator itRow, itRow2;
bool accept;
long int cost2,cost1,prevCost;
//int cost3;
	//cost3 = rowOverlap();
	cost1 = wireLength();
	cost2 = cellOverlap();
	prevCost = cost1 + cost2;

	//cout<<numNodes<<endl;
	randomCellnum = rand() %  numNodes +1;
	randomCellTemp << randomCellnum;
	randomCellStr = randomCellTemp.str();
	randomCell = "a" + randomCellStr;

if (rand()/(RAND_MAX+0.0)<=0.8)//shoule be 0.8, i changed it to debug
{
	randRow = rand() % (rowId.size()) + 1;
	randXcord = rand() %((int)numCellsPerRow)+xLimit; //每行宽加上xlimit

	itRow = rowId.find(randRow);
	itNode = nodeId.find(randomCell);
	n = itNode->second;
	//r = itRow->second;
	cout<<" moving cell "<<randomCell<<" to Row "<<randRow<< endl;
	itNode->second.yCoordinate = itRow->second.coOrdinate;
	itNode->second.xCoordinate = randXcord;
	
	rowId[itNode->second.cellRowId].cellList.erase(std::remove(rowId[itNode->second.cellRowId].cellList.begin(), rowId[itNode->second.cellRowId].cellList.end(),randomCell), rowId[itNode->second.cellRowId].cellList.end());
	itRow->second.cellList.push_back(randomCell);
	itNode->second.cellRowId = randRow;
	update();
	
	accept = checkMove(prevCost);
	//accept = 0;
	if(!accept)
	{
		itNode->second = n;
		itRow->second.cellList.erase(std::remove(itRow->second.cellList.begin(),itRow->second.cellList.end(),randomCell), itRow->second.cellList.end());
		rowId[itNode->second.cellRowId].cellList.push_back(randomCell);
		if (rand()/(RAND_MAX+0.0)<=0.1)
		{
			itNode->second.setOrientation(intToOrient(rand()%4));
			accept = checkMove(prevCost);
			if(!accept)
				itNode->second = n;
		}
	}	
}
else
{	
	randomCellnum = rand() %  numNodes +1 ;
	randomCellTemp.str("");
	randomCellTemp << randomCellnum;
	randomCellStr = randomCellTemp.str();
	randomCell2 = "a" + randomCellStr;
	
	cout<<"exchange "<<randomCell<<" with "<<randomCell2<< endl;

	int n1, n2;
	node nodeSec1, nodeSec2;
	itNode = nodeId.find(randomCell);
	itNode2 = nodeId.find(randomCell2);
	n1 = itNode->second.cellRowId; n2 = itNode2->second.cellRowId;
	//cout<<"originally, n1 = "<<n1<<" n2 = "<<n2<<endl;
	itRow = rowId.find(n1);
	itRow2 = rowId.find(n2);
	nodeSec1 = itNode->second;
	nodeSec2 = itNode2->second;


	int xTemp, yTemp;
	xTemp = itNode->second.xCoordinate;
	yTemp = itNode->second.yCoordinate;
	itNode->second.xCoordinate = itNode2->second.xCoordinate;
	itNode->second.yCoordinate = itNode2->second.yCoordinate;
	itNode2->second.xCoordinate = xTemp;
	itNode2->second.yCoordinate = yTemp;

	//itRow->second.cellList.erase(std::remove(rowId[itNode->second.cellRowId].cellList.begin(), rowId[itNode->second.cellRowId].cellList.end(),randomCell), rowId[itNode->second.cellRowId].cellList.end());
	itRow->second.cellList.erase(std::remove(itRow->second.cellList.begin(), itRow->second.cellList.end(),randomCell), itRow->second.cellList.end());
	itRow->second.cellList.push_back(randomCell2);
	itNode->second.cellRowId = n2;

	//itRow2->second.cellList.erase(std::remove(rowId[itNode2->second.cellRowId].cellList.begin(), rowId[itNode2->second.cellRowId].cellList.end(),randomCell2), rowId[itNode2->second.cellRowId].cellList.end());
	itRow2->second.cellList.erase(std::remove(itRow2->second.cellList.begin(), itRow2->second.cellList.end(),randomCell2), itRow2->second.cellList.end());
	itRow2->second.cellList.push_back(randomCell);
	itNode2->second.cellRowId = n1;

	update();

	accept = checkMove(prevCost);
	//accept = 0; //i set it to 1 to debug
	if(!accept)
	{
		n1 = itNode->second.cellRowId; n2 = itNode2->second.cellRowId;
		//cout<<"after exchange, n1 = "<<n1<<" n2 = "<<n2<<endl;
		itNode->second = nodeSec1;
		itRow->second.cellList.erase(std::remove(itRow->second.cellList.begin(),itRow->second.cellList.end(),randomCell2), itRow->second.cellList.end());
		itRow->second.cellList.push_back(randomCell);
		//cout<<"first step completed"<<endl;

		itNode2->second = nodeSec2;
		itRow2->second.cellList.erase(std::remove(itRow2->second.cellList.begin(),itRow2->second.cellList.end(),randomCell), itRow2->second.cellList.end());
		itRow2->second.cellList.push_back(randomCell2);
	}	
}
update();
}

void moveCell2()
{
row r;
map<string, node> ::iterator itNode, itNode2;
map<int, row> ::iterator itRow, itRow2;
bool accept;
long int cost2,cost1,prevCost;
	cost1 = wireLength();
	cost2 = cellOverlap();
	prevCost = cost1 + cost2;

	int randRow = rand() % (rowId.size()) + 1;
	itRow = rowId.find(randRow);
	int rowCellNum = itRow->second.cellList.size();
	int choosenCell=rand()%rowCellNum, choosenCell2;
	itRow->second.cellList[choosenCell];
	if (choosenCell == 0)
		choosenCell2 = 1;
	else if (choosenCell == rowCellNum-1)
		choosenCell2 = rowCellNum - 1;
	else
		choosenCell2 = (rand()%2==0)?(choosenCell - 1):(choosenCell + 1);

	cout<<" exchange cell "<<itRow->second.cellList[choosenCell]<<" with cell "<<itRow->second.cellList[choosenCell2]<< endl;
	itNode = nodeId.find(itRow->second.cellList[choosenCell]);
	itNode2 = nodeId.find(itRow->second.cellList[choosenCell2]);
	if (itNode2->second.terminal==0)
	{
	r = itRow->second;

	int xTemp, yTemp;
	xTemp = itNode->second.xCoordinate;
	yTemp = itNode->second.yCoordinate;
	itNode->second.xCoordinate = itNode2->second.xCoordinate;
	itNode->second.yCoordinate = itNode2->second.yCoordinate;
	itNode2->second.xCoordinate = xTemp;
	itNode2->second.yCoordinate = yTemp;

	itRow->second.sortByX();

	update();

	accept = checkMove(prevCost);
	if(!accept)
	{
		itRow->second = r;
	}	


	update();
	}
}

void update_Temp()
{

if(Temp>5000)
{
	Temp=0.8*Temp;
}
else if(Temp<=5000 && Temp >200)
{
	Temp=0.94*Temp;
}
else if(Temp<200)
{
	Temp=0.8*Temp;
}
else if(Temp<1.5)
{
	Temp=0.1*Temp;
}
 cout<<" new Temp is "<< Temp <<endl;
}

bool checkMove(long int prevCost)
{
srand(time(NULL));
long int cost2=0,cost1=0,newCost=0;
//int cost3=0;
int delCost=0;
double factor=0;
double prob = rand()/(RAND_MAX+0.0); 
		//cout<<"Checking validity of the move"<<endl;
		cost1 = wireLength();
		cost2 = cellOverlap();
		//cost3 = rowOverlap();
		newCost = cost1 + cost2;
		delCost = newCost - prevCost;
		factor = exp(-delCost/Temp);

		if(delCost < 0)//|| prob < (exp(-delCost/Temp)) )//这里做了修改，改为小于
		{
			prevCost = newCost;
			//cout << "Cell position is updated " << endl;
			return true; 
		}
		else
		{
			//cout << "Move is NOT valid, reverting" << endl;
			return false;
		}	
}

void timberWolfAlgorithm()
{
	initialPlacement(); //this performs the initial random placement 
	Temp = 40000; //initial temperature is selected high
	int k;

	while (Temp > 1 )
	{
		k=3;
		while(k > 0)
		{
			moveCell(xLimit);
			k--;	
		}
		update_Temperature();
		
	}
	
}

void timberWolfAlgorithm2()
{
	Temp = 40000; //initial temperature is selected high
	int k;

	while (Temp > 1 )
	{
		k=2;
		while(i > 0)
		{
			moveCell2();
			k--;
		}
		update_Temperature();
	}	
}

void printCellMap()
{
	map<string, node> ::iterator itNode;

	if(itNode != nodeId.end()){
	for(itNode = nodeId.begin(); itNode != nodeId.end(); ++itNode)
		{
			
			itNode->second.printParameter();	
			
		}
	}
}

void printRowMap()
{
	map<int, row> ::iterator itRow;

	if(itRow != rowId.end()){
	for(itRow = rowId.begin(); itRow != rowId.end(); ++itRow)
		{
			
			itRow->second.printParameter();	
			
		}
	}
	
}
void readNodes() //read .nodes file
   {
    	fstream file;
    	string buf;
	int i=0;
    	vector<string> strVec;                                                      
    	using boost::is_any_of;
	int flag=2;                                                     

    	file.open("ibm05.nodes", ios :: in);
	while (getline(file, buf))
	{       
		i++;
		if(i>7)
		{
			boost::algorithm::split(Vec,buf,boost::token_compress_on);
			node node1; 
			if (Vec[4] == "terminal")
			{
				flag = 1;
			}
			else
			{
				flag = 0;
			}
			node1.setParameterNodes(Vec[1],atoi(Vec[2].c_str()),atoi(Vec[3].c_str()),flag);
			nodeId.insert(pair<string,node>(Vec[1],node1));
		}
	}
	file.close();
   }

void readWts() //read .wts file
   {
	fstream file;
	string buf;
	int i=0;
	vector<string> Vec;
	using boost::is_any_of;
	map<string, node>::iterator itr;

	file.open("ibm05.wts", ios :: in);//opening .wts file to read and store weights

	while (getline(file, buf))
	{       
		i++;
		if(i>5)
		{
			boost::algorithm::split(Vec,buf,boost::token_compress_on);
			nodeId[Vec[1]].setParameterWts(atoi(Vec[2].c_str()));

		}
	}
	file.close();
   }

void readPl()// reading .pl file
   {
    	fstream file;
    	string buf;
	int i=0;
    	vector<string> strVec;                                                      
    	using boost::is_any_of;                                                     

    	file.open("ibm05.pl", ios :: in);//opening .pl file to update orientations

	while (getline(file, buf)) 
	{       
		i++;
		if(i>6)
		{
			boost::algorithm::split(strVec,buf,is_any_of(" ,\t"),boost::token_compress_on);
			nodeId[strVec[0]].setParameterPl(atoi(strVec[1].c_str()),atoi(strVec[2].c_str()),strVec[4]);

		}
	}
	file.close();
   }

void readNets() // reading .nets file to read hypergraph structure
{
    	fstream file;
    	string buf;
	int i=0,a=0,j=0,NetId=1;
    	vector<string> Vec;                                                      
    	using boost::is_any_of;

	regex find ("\\b(NetDegree : )");
	smatch flag;
	string Out;                                                    

    	file.open("ibm05.nets", ios :: in);//opening .nets file

	while (getline(file, buf))
	{       
		i++;
		if(i>7)
		{
			regex_search(buf, flag, find);
			Out = flag.suffix();
			a = atoi(Out.c_str());
			vector<string> strTemp;
			for (j=0; j<a; j++)
			{
				
				getline(file,buf);
				boost::algorithm::split(Vec,buf,is_any_of(" ,\t"),boost::token_compress_on);
				strTemp.push_back(Vec[1]);
				nodeId[Vec[1]].setNetList(NetId);
			}
			netToCell.insert(pair<int, vector <string> >(NetId,Temp));
			NetId++;
		}
		
   	}
}

void readScl()
   {
    	fstream file;
    	string buf;
	int i=0,j=0,Id=1;
    	vector<string> Vec;                                                      
    	using boost::is_any_of;
                                                     
	int coordinate;//coOrdinate
	int h;//height
	int W;//width
	int Spacing;//side spacing
	string Orient;//site orientation
	string Symmetry;//site symmetry
	int subRowOrigin;//subrow origin
	int numSites;//number of site

    	file.open("ibm05.scl", ios :: in);//opening standard cell library file

	while (getline(file, buf))
	{       
		i++;
		if(i>8)
		{	
			boost::algorithm::split(Vec,buf,is_any_of(" ,\t"),boost::token_compress_on);
			j = i%9;// because the parameters for each row occupy 9 lines in the scl file
			if(l == 1)
			{
				coOrdinate = atoi(Vec[3].c_str());			
			}
			else if(l == 2)
			{
				h = atoi(Vec[3].c_str());
			}
			else if(l == 3)
			{
				W = atoi(Vec[3].c_str());			
			}
			else if(l == 4)
			{
				Spacing = atoi(Vec[3].c_str());			
			}
			else if(l == 5)
			{
				Orient = Vec[3];
			}
			else if(l == 6)
			{
				Symmetry = Vec[3];
			}
			else if(l == 7)
			{
				subRowOrigin = atoi(Vec[3].c_str());
				numSites = atoi(Vec[6].c_str());
			}
			else if(l == 8)
			{
				row r;				
				r.setId(Id);
				rowId.insert(pair<int,row>(Id,r));
				rowId[Id].setParameterRows(coordinate,h,W,Spacing,Orient,Symmetry,subRowOrigin,numSites);
				Id++;
			}
			
		}
	}
	file.close();
   }


struct bound //structure to set boundaries for placement
{
int Xmin, Xmax, Ymin, Ymax;
};

int  numNodes =0; //number of nodes
float numCells = 0;
bound b; //instance of structure b 

void CalcBoundaries() //Set the border, the default is the maximum type of int minimum, the terminal are framed
{
int x,y;
b.minX = 32767, b.maxX = -32768,b.minY = 32767, b.maxY = -32768;
	map<string, node> ::iterator itNode;
	for(itNode = nodeId.begin(); itNode != nodeId.end(); ++itNode)
	{
		if(itNode->second.terminal == 1)
		{
			xval = itNode->second.xCoordinate;
			yval = itNode->second.yCoordinate;
			if(xval < b.minX)
			{
				b.minX = xval;
			}
			if(xval > b.maxX)
			{
				b.maxX = xval;
			}
			if(xval < b.minY)
			{
				b.minY = yval;
			}
			if(xval > b.maxY)
			{
				b.maxY = yval;
			}
			
		}
	}
	if (b.minX==32767)
		cout<<"error"<<endl;
		b.minX = 0;
	if (b.minY == 32767)
		b.minY = 0;
}

void RowToCellMapping()//to create mapping from row to cells
{
	map<int, r> ::iterator Row;
	map<string, node> ::iterator itNode;
	for(Row = rowId.begin(); Row != rowId.end(); ++Row)
	{
		for(Node = nodeId.begin(); Node != nodeId.end(); ++Node)
		{
			if(Node->second.height = 16)
			{
			if((Row->second.coordinate <= Node->second.yCoordinate) && ((Row->second.coOrdinate)+(Row->second.height)) >= Node->second.yCoordinate)
			{
				Node->second.setRowId(Row->first);
				Row->second.setCellList(Node->first);	
			}
			}
		}
	}
}
