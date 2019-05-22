#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include<fstream>
using namespace std;

class Student
{
	
	int sub_atd[12];
	int total_atd[12];
	float per_atd[12];
	
	public:
	int roll;
	
	void input()
	{
		int i;
		for(i=0;i<9;i++)
		{
			cout<<"Enter Attended Lectures of ";
			subName(i+1);
			cout<<": ";
			cin>>sub_atd[i];
			cout<<"Enter Total Lectures of ";
			subName(i+1);
			cout<<": ";
			cin>>total_atd[i];
			if(sub_atd[i]>total_atd[i])
			{
				cout<<"Attended Lectures can't be greater than Total Lectures. Try Again!"<<endl;
				i--;
			}
		}
		
	}
		
	void calc_atd()
	{
		int i, temp1=0, temp2=0;
		
		for(i=0;i<6;i++)
		{
			temp1=temp1+sub_atd[i];
			temp2=temp2+total_atd[i];
		}
		sub_atd[9]=temp1;
		total_atd[9	]=temp2;
		
		temp1=0;
		temp2=0;
		
		for(i=6;i<9;i++)
		{
			temp1=temp1+sub_atd[i];
			temp2=temp2+total_atd[i];
		}
		sub_atd[10]=temp1;
		total_atd[10]=temp2;
		
		sub_atd[11]=sub_atd[9]+sub_atd[10];
		total_atd[11]=total_atd[9]+total_atd[10];
		
		for(i=0;i<12;i++)
		{
			per_atd[i]=(float)sub_atd[i]/(float)total_atd[i]*100;
		}
	}
	
	void subName(int x)
	{
		switch(x)
		{
			case 1:
			{
				cout<<"FCPIT";
				break;
			}
			case 2:
			{
				cout<<"Maths";
				break;
			}
			case 3:
			{
				cout<<"EME";
				break;
			}
			case 4:
			{
				cout<<"Chemistry";
				break;
			}
			case 5:
			{
				cout<<"ED";
				break;
			}
			case 6:
			{
				cout<<"EVS";
				break;
			}
			case 7:
			{
				cout<<"FCPIT Lab";
				break;
			}
			case 8:
			{
				cout<<"CG Lab";
				break;
			}
			case 9:
			{
				cout<<"Chemistry Lab";
				break;
			}
			
		}
		
	}
	
	void display()
	{
		cout<<"\t\tFCPIT\tMaths\tEME\tChem.\tED\tEVS\tFCPITL\tCG-Lab\tCh-Lab\tS-Total\tL-Total\tG-Total"<<endl;
		cout<<"Sub:\t\t";
		for(int i=0;i<12;i++)
		{
			cout<<sub_atd[i]<<"\t";
		}
		
		cout<<endl;
		cout<<"Total:\t\t";
		for(int i=0;i<12;i++)
		{
			cout<<total_atd[i]<<"\t";
		}
		
		cout<<endl;
		cout<<"Percentage:\t";
		for(int i=0;i<12;i++)
		{
			cout<<fixed<<setprecision(2)<<per_atd[i]<<"\t";
		}
		
	}
	
	void bunkDisplay()
	{
		int i,count,j;
		cout<<"\nSubjects with less than 75% Attendance:"<<endl;
		for(i=0;i<9;i++)
		{
			if(per_atd[i]<75)
			{
				subName(i+1);
				cout<<endl;
			}
		}
		
		cout<<endl<<endl<<"Lectures not to be Bunked"<<endl;
		cout<<"Subject\t\tAttendance after 1 Bunk"<<endl;
		for(i=0;i<9;i++)
		{
			int percent;
			percent=(float)sub_atd[i]/(float)(total_atd[i]+1)*100;
			if(percent<75&&per_atd[i]>=75)
			{
				subName(i+1);
				cout<<":\t\t"<<percent<<"%"<<endl;
			}
		}
		
		
		cout<<endl<<endl<<"Lectures can be Bunked"<<endl;
		for(i=0;i<9;i++)
		{
			j=1;
			count=0;
			while(1)
			{
				if(((float)sub_atd[i]/(float)(total_atd[i]+j)*100)>=75)
				{
					j++;
					count++;
				}
				else
				{
					break;
				}
					
			}
			if(count!=0)
			{
				subName(i+1);
				cout<<":\t\t"<<count<<" Lectures"<<endl;
			}
			
			
		}
	}
	
	void updateAttendance()
	{
		char ch='n';
		int i;
		for(i=0;i<9;i++)
		{
			
			subName(i+1);
			cout<<" Lecture Today(y/n)? ";
			cin>>ch;
			if(ch=='y'||ch=='Y')
			{
				total_atd[i]++;
				cout<<" Lecture Attended(y/n)? ";
				cin>>ch;
				if(ch=='y'||ch=='Y')
					sub_atd[i]++;
			}
		}
		calc_atd();
		system("cls");
		display();
	}
	
	
	
};



int main()
{
	Student std1;
	int roll,flag=0,count=0;
	cout<<"Enter Roll No: ";
	cin>>roll;
	
	ifstream fin;
	fin.open("Attendance.bmx",ios::binary);
	if(fin.is_open())
	{
		while(fin.read((char*)&std1,sizeof(std1)))
		{
			
			if(roll==std1.roll)
			{
				flag=1;
				break;
			}
			count++;
		}
	}
	fin.close();
	
	if(flag==0)
	{
		std1.roll=roll;
		std1.input();
		std1.calc_atd();
		ofstream fout;
		fout.open("Attendance.bmx",ios::binary|ios::app);
		if(fout.is_open())
		{
			fout.write((char*)&std1,sizeof(std1));
			fout.close();
		}
	}
	
	std1.display();
	int choose;
	
	do
	{
		cout<<"\n\n1. Update Attendance";
		cout<<"\n2. Assist Bunk";
		cout<<"\n3. Exit";
		cout<<"\nYour Choice: ";
		cin>>choose;
		switch(choose)
		{
			case 1:
			{
				std1.updateAttendance();
				fstream ft;
				ft.open("Attendance.bmx",ios::binary|ios::ate|ios::in|ios::out);
				if(ft.eof())
					ft.clear();
				ft.seekp(count*sizeof(std1));
				ft.write((char*)&std1,sizeof(std1))<<flush;
				ft.close();
				break;
			}
			case 2:
			{
				std1.bunkDisplay();
				break;
			}
			case 3:
			{
				break;
			}
			default:
			{
				cout<<endl<<"Invalid Input! Try Again"<<endl;
			}
		}
	}while(choose!=3);
	cout<<"\n\nBunk Manager\t(Smart Bunk Assistant)\nCreated By:\nAbhishek Goyal\tCSE\nAkshay Singla\tCSE";
}
