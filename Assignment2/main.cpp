//
//  main.cpp
//  Assignment2
//
//  Created by Kemal Abdulrahman on 3/12/20.
//  Copyright © 2020 Kemal Abdulrahman. All rights reserved.
//

#include <iostream>
#include<fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
string year;
string name;
string data[74][5];
char option;
string disaster;
vector<string>disasteryear;
vector<string>disasterperyear;
vector<string>Totaldeathsperyear;
string loss_of_property;
string death;
int input;
string startyear;
string endyear;
string line;
static const int NAMECOL=0;
static const int DISASTERCOL=1;
static const int YEARCOL=2;
static const int LOSS_OF_PROPERTYCOL=3;
static const int DEATHCOL=4;

void menu(){
   cout<<"What would you like to do"<<endl;
   cout<<"1:Look up year range"<<endl;
   cout<<"2:Look up disaster"<<endl;
   cout<<"3:Generate summary report"<<endl;
   cout<<"4:Quit"<<endl;
}

//display the two year in the disaster
void year_range(){
   cout<<"Enter beginning year:"<<endl;
   cin>>startyear;
   cout<<"Enter ending year:"<<endl;
   cin>>endyear;
    
   ifstream file;
   file.open("catastrophe1.txt");
   

   
   if(file){
      cout<<"file is open now"<<endl;
      string str;
      int size;

         for(int i=0;i<74;i++)
            if(data[i][2]>=startyear && data[i][2]<=endyear){

               size=(int)data[i][0].length();
               cout<<data[i][0].substr(1,size-2)<<endl;

      }
      file.close();
   }




   return;

}

//display unique years based on the disaster
void search_disaster(){
   cout<<"Please enter the disaster"<<endl;
   cin>>disaster;
   ifstream file;
   file.open("catastrophe1.txt");//open the file

   
   if(file){//the file is exist
      cout<<"file is open now"<<endl;
      
      vector<string>disasteryear;
      while (getline(file,line))// read the line from the  file to store in line vaiable
      {
         
         size_t found= 0;
         found=line.find(disaster);
         if(found!=string::npos){//if found is a value


            stringstream bb(line);// line convert to stringstram called  bb

            int results=0;// count the number  of column  of text file
            while( bb.good() )// good() tell us they have more character to read from bb
            {
               string substring;//substring is short then orginal string
               getline( bb, substring, ',' );//read from the bb until we get the , then store in the substring
               results++;
               if(results==3 && 0==count(disasteryear.begin(),disasteryear.end(),substring))// check if count is 3 that mean year in the 3 column
                  disasteryear.push_back( substring );// substring add(push_back) to the disasteryear vector
            }
         }
      }
      cout<<disasteryear.at(0); //at the index 0 becuase they get rid of the ,.
      for(int i=1;i<disasteryear.size();i++){ //if i is equal to disasteryear.size() or greater then disasteryear.size() then stop
         cout<<','<<disasteryear.at(i);//display the year in disasteryear
      }
      cout<<endl;

      file.close();
   }else{
      cout<<"Cannot open the file"<<endl;
      //cout<<"file is open now"<<endl;
   }
   
   

}


void storedata(){

   string line;
   ifstream file;
   file.open("catastrophe1.txt");
   string str;
   int deathcount,deathint;
   while (!file.eof())
   {
      cout<<"Bye"<<endl;
      for (int row=0;row<74;row++){
         getline(file, name, ',' );
         getline(file, disaster, ',' );
         getline(file, year, ',' );
         getline(file, loss_of_property, ',' );
         getline(file, death, '\n' );
         data[row][NAMECOL]=name;
         data[row][DISASTERCOL]=disaster;
         data[row][YEARCOL]=year;
         data[row][LOSS_OF_PROPERTYCOL]=loss_of_property;
         data[row][DEATHCOL]=death;
      }
       cout<<"b"<<endl;
   }
   //file.close();
    cout<<"S"<<endl;

}
//display the summary report of the year and death
void  summaryreport(){
   string arr[]={"2012","2013","2014","2015","2016","2017","2018","2019"};
   int deathcount,deathint,year;
   string name, title="Year;\t Disaster;\t Total Deaths";

   string disasternames[8];
   string disasterperyear[8];
   int Totaldeathsperyear[8];
   string filename;
   string line;
   ofstream fout;
   cout<<"Enter a file name"<<endl;
   cin>>filename;
   fout.open(filename,ios::out);
           // intite array
            for(int col=0;col<8;col++){
               disasternames[col]="";
               disasterperyear[col]="";
               Totaldeathsperyear[col]=0;
            }

            for(int row=0;row<74;row++){//process each row
               name=data[row][DISASTERCOL];
               deathint=stoi(data[row][DEATHCOL]);
               year=stoi(data[row][YEARCOL])-2012;

               disasternames[year]+=name;
               Totaldeathsperyear[year]+=deathint;

            }
               fout<<title<<endl;
            for(int col=0;col<8;col++){
               fout<<arr[col];
               fout<<disasternames[col];
               fout<<Totaldeathsperyear[col]<<endl;
            }
         fout.close();

}

int main()
{
   cout<<"Hello"<<endl;
    storedata();
   char option;

   menu();
   while(true){
      cout<<"Select an option:"<<endl;
      cin>>option;
        if(option=='1'){
           cout<<"Year Range"<<endl;
           year_range();
        }
        else if(option=='2'){
            cout<<"All Disaster"<<endl;
           search_disaster();
         }
         else if(option=='3'){
            summaryreport();
            cout<<"Summary Report"<<endl;
         }
         else{
            cout<<"The error"<<endl;
            exit(0);
         }
   }

   
   

   

   
   return 0;
}

