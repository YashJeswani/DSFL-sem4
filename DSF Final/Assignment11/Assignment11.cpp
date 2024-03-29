//============================================================================
// Name        : SequentialFiles.cpp
// Author      : 23270
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
using namespace std;
const int MAX=20;
class Student
{
 int rollno;
 char name[20],city[20];
 char div;
 int year;
public:
 Student()
{
  strcpy(name,"");
  strcpy(city,"");
  rollno=year=div=0;
}
 Student(int rollno,char name[MAX],int year,char div,char city[MAX])
 {
  strcpy(this->name,name);
  strcpy(this->city,city);
  this->rollno=rollno;
  this->year=year;
  this->div=div;
 }
 int getRollNo()
 {
  return rollno;
 }
 void displayRecord()
 {

  cout<<endl<<setw(5)<<rollno<<setw(20)<<name<<setw(5)<<year<<setw(5)<<div<<setw(10)<<city;
 }
};
//==========File Operations ===========
class FileOperations
{
 fstream file;
public:
 FileOperations(char* filename)
{
file.open(filename,ios::in|ios::out|ios::ate|ios::binary);
}
 void insertRecord(int rollno, char name[MAX],int year, char div,char city[MAX])
 {
  Student s1(rollno,name,year,div,city);
  file.seekp(0,ios::end);
  file.write((char *)&s1,sizeof(Student));
  file.clear();
 }
 void displayAll()
 {
  Student s1;
  file.seekg(0,ios::beg);
  while(file.read((char *)&s1, sizeof(Student)))
  {
   s1.displayRecord();
  }
  file.clear();
 }
 void displayRecord(int rollNo)
 {
  Student s1;
  file.seekg(0,ios::beg);
  bool flag=false;
  while(file.read((char*)&s1,sizeof(Student)))
  {
   if(s1.getRollNo()==rollNo)
   {
    s1.displayRecord();
    flag=true;
    break;
   }
  }
  if(flag==false)
  {
   cout<<"\nRecord of "<<rollNo<<"is not present.";
  }
  file.clear();
 }
 void deleteRecord(int rollno)
 {
  ofstream outFile("new.dat",ios::binary);
  file.seekg(0,ios::beg);
  bool flag=false;
  Student s1;

  while(file.read((char *)&s1, sizeof(Student)))
  {
   if(s1.getRollNo()==rollno)
   {
    flag=true;
    continue;
   }
   outFile.write((char *)&s1, sizeof(Student));
  }
  if(!flag)
  {
   cout<<"\nRecord of "<<rollno<<" is not present.";
  }
  file.close();
  outFile.close();
  remove("student.dat");
  rename("new.dat","student.dat");
  file.open("student.dat",ios::in|ios::out|ios::ate|ios::binary);
 }
 ~FileOperations()
 {
  file.close();
  cout<<"\nFile Closed.";
 }
};
int main() {
 ofstream newFile("student.dat",ios::app|ios::binary);
  newFile.close();
  FileOperations file((char*)"student.dat");
     int rollNo,year,choice=0;
     char div;
     char name[MAX],address[MAX];
     while(choice!=5)
     {
         //clrscr();
         cout<<"\n*****Student Database*****\n";
         cout<<"1) Add New Record\n";
         cout<<"2) Display All Records\n";
         cout<<"3) Display by RollNo\n";
         cout<<"4) Deleting a Record\n";
         cout<<"5) Exit\n";
         cout<<"Choose your choice : ";
         cin>>choice;
         switch(choice)
         {
             case 1 : //New Record
               cout<<endl<<"Enter RollNo and name : \n";
               cin>>rollNo>>name;
               cout<<"Enter Year and Division : \n";
               cin>>year>>div;
               cout<<"Enter address : \n";
               cin>>address;
               file.insertRecord(rollNo,name,year,div,address);
               cout<<"\nRecord Inserted.";
               break;
             case 2 :
              cout<<endl<<setw(5)<<"ROLL"<<setw(20)<<"NAME"<<setw(5)<<"YEAR"<<setw(5)<<"DIV"<<setw(10)<<"CITY";
               file.displayAll();
               break;
             case 3 :
               cout<<"Enter Roll Number";
               cin>>rollNo;
                file.displayRecord(rollNo);

               break;
             case 4:
               cout<<"Enter rollNo";
               cin>>rollNo;
               file.deleteRecord(rollNo);
               break;
            case 5 :break;
         }

     }

 return 0;
}
/*    output

*****Student Database*****
1) Add New Record
2) Display All Records
3) Display by RollNo
4) Deleting a Record
5) Exit
Choose your choice : 1

Enter RollNo and name :
23128
soham
Enter Year and Division :
2
9
Enter address :
nanded

Record Inserted.
*****Student Database*****
1) Add New Record
2) Display All Records
3) Display by RollNo
4) Deleting a Record
5) Exit
Choose your choice : 2

 ROLL                NAME YEAR  DIV      CITY
23128               soham    2    9    nanded
*****Student Database*****
1) Add New Record
2) Display All Records
3) Display by RollNo
4) Deleting a Record
5) Exit
Choose your choice : 1

Enter RollNo and name :
23134
loya
Enter Year and Division :
2
10
Enter address :

Record Inserted.
*****Student Database*****
1) Add New Record
2) Display All Records
3) Display by RollNo
4) Deleting a Record
5) Exit
Choose your choice : 1

Enter RollNo and name :
23132
kunal
Enter Year and Division :
3
11
Enter address :

Record Inserted.
*****Student Database*****
1) Add New Record
2) Display All Records
3) Display by RollNo
4) Deleting a Record
5) Exit
Choose your choice : 2

 ROLL                NAME YEAR  DIV      CITY
23128               soham    2    9    nanded
23134                loya    2    1         0
23132               kunal    3    1         1
*****Student Database*****
1) Add New Record
2) Display All Records
3) Display by RollNo
4) Deleting a Record
5) Exit
Choose your choice : 1

Enter RollNo and name :
23125
jeswani
Enter Year and Division :
1
6
Enter address :
akola

Record Inserted.
*****Student Database*****
1) Add New Record
2) Display All Records
3) Display by RollNo
4) Deleting a Record
5) Exit
Choose your choice : 1

Enter RollNo and name :
23126
kabra
Enter Year and Division :
2
8
Enter address :
bhandara

Record Inserted.
*****Student Database*****
1) Add New Record
2) Display All Records
3) Display by RollNo
4) Deleting a Record
5) Exit
Choose your choice : 2

 ROLL                NAME YEAR  DIV      CITY
23128               soham    2    9    nanded
23134                loya    2    1         0
23132               kunal    3    1         1
23125             jeswani    1    6     akola
23126               kabra    2    8  bhandara
*****Student Database*****
1) Add New Record
2) Display All Records
3) Display by RollNo
4) Deleting a Record
5) Exit
Choose your choice : 3
Enter Roll Number23126

23126               kabra    2    8  bhandara
*****Student Database*****
1) Add New Record
2) Display All Records
3) Display by RollNo
4) Deleting a Record
5) Exit
Choose your choice : 4
Enter rollNo23125

*****Student Database*****
1) Add New Record
2) Display All Records
3) Display by RollNo
4) Deleting a Record
5) Exit
Choose your choice : 2

 ROLL                NAME YEAR  DIV      CITY
23128               soham    2    9    nanded
23134                loya    2    1         0
23132               kunal    3    1         1
23126               kabra    2    8  bhandara
*****Student Database*****
1) Add New Record
2) Display All Records
3) Display by RollNo
4) Deleting a Record
5) Exit
Choose your choice :
*/
 */
