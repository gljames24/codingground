//C++ Final project
//Country and State facts
//Information sourced from:
	//http://www.census.gov/prod/cen2010/cph-2-1.pdf
	//http://www.ipl.org/div/stateknow/popchart.html
	//https://www.bea.gov/iTable/drilldown.cfm?reqid=70&stepnum=11&AreaTypeKeyGdp=5&GeoFipsGdp=XX&ClassKeyGdp=NAICS&ComponentKey=200&IndustryKey=1&YearGdp=2015Q2&YearGdpBegin=-1&YearGdpEnd=-1&UnitOfMeasureKeyGdp=Levels&RankKeyGdp=1&Drill=1&nRange=5
//Code written by James Garrard

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <sstream>
using namespace std;
//function prototypes
int findPos(double, double[]);
int findState(string ,string[]);
void posSuffix(int pos);
void addCommas(double num);
//main
int main(int argc, char *argv[]) {
	//variables
	int l = 1;
	int ans = 0;
	int position = 0;
	int pos=0,highPos=0,lowPos=0;
	double find = 0.0;
	//inputs
	//string inCountry = " ";
	string inState = " ";
	//data types from setup
	char area='Y';
	char pop='Y';
	char gdp='Y';
	char popDens='Y';
	char gdpPer='y';
	//states
	string states[51]={" "};
	double areaS[51] = {0.0};
	double areaSSorted[51]={0.0};
	double popS[51]={0.0};
	double popSSorted[51]={0.0};
	double gdpS[51]={0.0};
	double gdpSSorted[51]={0.0};
	double popDensS[51]={0.0};
	double popDensSSorted[51]={0.0};
	double gdpPerS[51]={0.0};
	double gdpPerSSorted[51]={0.0};
	//countries
	//string countries[195]={" "};
	//double areaC[51] = {0.0};
	
	//files
	//ifstream inCountries;
	ifstream inStates;
	
	//Set precision
	cout<<fixed<<setprecision(0);
	cout<<"This program lets you find features of states and how they compare to other states.(Including D.C.)"<<endl;
	//+++setup+++
	cout<<"Would you like to find Area? Y/N"<<endl;
	cin>>area;
	area = toupper(area);
	cout<<"Would you like to find Population? Y/N"<<endl;
	cin>>pop;
	pop = toupper(pop);
	cout<<"Would you like to find GDP? Y/N"<<endl;
	cin>>gdp;
	gdp = toupper(gdp);
	cout<<"Would you like to find Population Density? Y/N"<<endl;
	cin>>popDens;
	popDens = toupper(popDens);
	cout<<"Would you like to find GDP per Capita? Y/N"<<endl;
	cin>>gdpPer;
	gdpPer = toupper(gdpPer);
	cout<<endl;
	
	//+++start of program+++
	while(l>0){
		cout<<fixed<<setprecision(0);
		cout<< "Would you like to learn about:"<<endl<<"(1)States compared to States,"<<endl/*<<"(2)Countries to Countries,"<<endl<< "(3)States to Countries,"<<endl<< "(4)Countries to States?"<<endl*/<<"Enter 0 to quit."<<endl;
		cin>>ans;
		cout<<endl;
		
		//+++State V State++++
		if(ans == 1){
			
			//open file
			inStates.open("StateVState.txt");
			//read data
			for(int x=0;x<51;x++){
				//state
				getline(inStates,states[x],'#');
				//area
				inStates>>areaS[x];
				inStates.ignore(1);
				//population
				inStates>>popS[x];
				inStates.ignore(1);
				//gdp
				inStates>>gdpS[x];
				inStates.ignore(1);
			}
			//add ratio based info
			for(int x=0;x<51;x++){
			//population density
			popDensS[x] = popS[x]/areaS[x];
			//gdp per capita
			gdpPerS[x] = gdpS[x]/popS[x];
			}
			//add duplicate data to be sorted
			for(int i=0;i<51;i++){
				areaSSorted[i] = areaS[i];
				popSSorted[i] = popS[i];
				gdpSSorted[i] = gdpS[i];
				popDensSSorted[i] = popDensS[i];
				gdpPerSSorted[i] = gdpPerS[i];
			}
			
			//sort second arrays
			sort (areaSSorted, areaSSorted+51);
			sort (popSSorted, popSSorted+51);
			sort (gdpSSorted, gdpSSorted+51);
			sort (popDensSSorted, popDensSSorted+51);
			sort (gdpPerSSorted, gdpPerSSorted+51);

			//have user enter state
			cout<< "What State would you like to find?"<<endl;
			cin.ignore();
			getline(cin,inState);
			if (inState=="District of Columbia"){
				inState = "D.C.";
			}
			
			
			
			//find state location on array
			position = findState(inState, states);
			//If the computer doesn't find a state	
			if (position == -1){
				cout<<"Make sure you capitalize the first letter and don't abreviate."<<endl;
				}
				
		//+++Display Information to User+++		
			else{
				if (area == 'Y'){
				//+++AREA+++
					cout<<endl;
					//Find the position of the state in the sorted array	
					find=areaS[position];
					pos = findPos(find, areaSSorted);
					//find the states higher and lower
					highPos = findPos(areaSSorted[pos+1],areaS);
					lowPos = findPos(areaSSorted[pos-1],areaS);
					
					//Display
					cout<<"Area:"<<endl;
					cout<<states[position]<<" is the ";
					//put correct suffix
					posSuffix(pos);	
					cout<<" largest state at ";
					addCommas(areaS[position]);
					cout<<" square kilometers."<<endl;
					
					if (pos <50){
						cout<<states[highPos]<<" is larger at ";
						addCommas(areaSSorted[pos+1]);
						cout<<" square kilometers."<<endl;
					}
					if(pos >0){
						cout<<states[lowPos]<<" is smaller at only ";
						addCommas(areaSSorted[pos-1]);
						cout<<" square kilometers."<<endl;
					}

				}
				
				if (pop =='Y'){
				//+++Population+++
					cout<<endl;
					//Find the position of the state in the sorted array	
					find=popS[position];
					pos = findPos(find, popSSorted);
					//find the states higher and lower
					highPos = findPos(popSSorted[pos+1],popS);
					lowPos = findPos(popSSorted[pos-1],popS);
					
					//Display
					cout<<"Population: "<<endl;
					cout<<states[position]<<" is the ";
					//add suffixes
					posSuffix(pos);		
					cout<<" most populated state with a population of ";
					addCommas(popS[position]);
					cout<<" people."<<endl;
					
					if (pos <50){
						cout<<states[highPos]<<" is larger at ";
						addCommas(popSSorted[pos+1]);
						cout<<" people."<<endl;
					}
					if(pos >0){
						cout<<states[lowPos]<<" is smaller at only ";
						addCommas(popSSorted[pos-1]);
						cout<<" people."<<endl;
					}
					
				}
				if(gdp=='Y'){
					//+++GDP+++
					cout<<endl;
					//Find the position of the state in the sorted array	
					find=gdpS[position];
					pos = findPos(find, gdpSSorted);
					//find the states higher and lower
					highPos = findPos(gdpSSorted[pos+1],gdpS);
					lowPos = findPos(gdpSSorted[pos-1],gdpS);
					
					//Display
					cout<<"Gross Domestic Product: "<<endl;
					cout<<states[position]<<" is the ";
					posSuffix(pos);	
					cout<<" richest state, it makes $";
					addCommas(gdpS[position]);
					cout<<endl;
					
					if (pos <50){
						cout<<states[highPos]<<" makes more at $";
						addCommas(gdpSSorted[pos+1]);
						cout<<endl;
					}
					if(pos >0){
						cout<<states[lowPos]<<" makes less at only $";
						addCommas(gdpSSorted[pos-1]);
						cout<<endl;
					}
				} 
				if (popDens == 'Y'){
					//+++Population Density+++
						cout<<endl;
						//Find the position of the state in the sorted array	
						find=popDensS[position];
						pos = findPos(find, popDensSSorted);
						//find the states higher and lower
						highPos = findPos(popDensSSorted[pos+1],popDensS);
						lowPos = findPos(popDensSSorted[pos-1],popDensS);
						
						//Display
						cout<<"Population Density:"<<endl;
						cout<<states[position]<<" is the ";
						posSuffix(pos);	
						cout<<" densest state at ";
						addCommas(popDensS[position]);
						cout<<" people per square kilometer."<<endl;
						
						if (pos <50){
							cout<<states[highPos]<<" is denser at ";
							addCommas(popDensSSorted[pos+1]);
							cout<<" people per square kilometer."<<endl;
						}
						if(pos >0){
							cout<<states[lowPos]<<" is less dense at only ";
							addCommas(popDensSSorted[pos-1]);
							cout<<" people per square kilometer."<<endl;
						}
				if ( gdpPer == 'Y'){
					//+++Population Density+++
						cout<<endl;
						//Find the position of the state in the sorted array	
						find=gdpPerS[position];
						pos = findPos(find, gdpPerSSorted);
						//find the states higher and lower
						highPos = findPos(gdpPerSSorted[pos+1],gdpPerS);
						lowPos = findPos(gdpPerSSorted[pos-1],gdpPerS);
						
						//Display
						cout<<"Gross Domestic Product Per Capita:"<<endl;
						cout<<states[position]<<" is the ";
					 	posSuffix(pos);						
						cout<<" richest state at $";
						addCommas(gdpPerS[position]);
						cout<<" per capita."<<endl;
						
						if (pos <50){
							cout<<states[highPos]<<" makes more at $";
							addCommas(gdpPerSSorted[pos+1]);
							cout<<" per capita."<<endl;
						}
						if(pos >0){
							cout<<states[lowPos]<<" makes less at only $";
							addCommas(gdpPerSSorted[pos-1]);
							cout<<" per capita."<<endl;
						}
					}
				}
			}
			//close the file
			inStates.close();
			cout<<endl;
		}
		//Country V Country
		else if(ans == 2){
			cout<<"Sorry, this feature isn't out yet."<<endl;
		}
		//State V Country
		else if(ans == 3){
			cout<<"Sorry, this feature isn't out yet."<<endl;
		}
		//Country V State
		else if(ans == 4){
			cout<<"Sorry, this feature isn't out yet."<<endl;
		}

		else if(ans == 0){break;}//exit the while loop and end the program
		else if(ans != 0||1||2||3||4){
			cout<<"Please enter a valid option"<<endl<<endl;
		}
	l++;
	}
}
//+++functions+++

int findPos(double input, double regions[]){
	for(int x=0;x<51;x++){
		if(input==regions[x]){
			return x;
		}
	}
	return -1;
}
int findState(string inPut, string array[]){
	for(int i=0;i<51;i++){
		if (array[i] == inPut){
			return i;
		}
		
	}
	return -1;
}
void posSuffix(int pos){
	if (((51-pos)%10==1)){//add st when a number ends in 1
		cout<<51-pos<<"st";
	}
	else if ((51-pos)%10==2){//add nd when ending in 2
		cout<<51-pos<<"nd";
	}
	else if ((51-pos)%10==3){//add rd when 3
		cout<<51-pos<<"rd";
	}
	else{//add th to everything else
		cout<<51-pos<<"th";
	}
}
void addCommas(double num) {
	
	string numWithCommas=" ";// string which will contain the result
	ostringstream convert;// stream used for the conversion
	convert<<fixed<<setprecision(2)<<num;// insert double num into stream
	numWithCommas = convert.str();// set numWithCommas to the contents of the stream
	int insertPosition = numWithCommas.length() - 6;//find where the first comma should go
	while (insertPosition > 0) {
		numWithCommas.insert(insertPosition, ",");
		insertPosition-=3;//find where the next comma should go
	}
	cout<<numWithCommas;
}

