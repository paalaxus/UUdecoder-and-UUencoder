//Paa Kofi Boafo
// PROJECT 1 CS 350 
//uuencode

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
using namespace std;

int changetoAsciiDecimal( char originaldecimal)
{
		int changed;	
		if (originaldecimal==0)
			changed=48;
	    else if(originaldecimal==1)
			changed=49;
		else if(originaldecimal==2)
			changed=50;
		else if(originaldecimal==3)
			changed=51;
		else if(originaldecimal==4)
			changed=52;
		else if(originaldecimal==5)
			changed=53;
		else if(originaldecimal==6)
			changed=54;
		else if(originaldecimal==7)
			changed=55;
		else if(originaldecimal==8)
			changed=56;
		else {
			changed=57;}
			
			return changed;
}
			
string padding(string binary, int n)
{
	while(n-binary.length()>0)
	{
		binary = "0"+ binary;
	}
	return binary;
}

string getUserInput(string prompt)
   {
      string t="";
      cout<<prompt;
      getline(cin,t);
      return t;
   }

void errorMsg(string msg, bool term)
   {
      cout<<msg<<endl;
      if (term)
         exit(0);
   }


 string makeBinaryRep(unsigned int n)
{
    if ( n == 0 ) 
    {
		return "0";
	}
	 if ( n == 1) 
    {
		return "1";
	}
   
    if ( n % 2 == 0 )
       {
		return makeBinaryRep((n / 2)) + "0";
		}
    else
    {
        return makeBinaryRep((n / 2)) + "1";
	}
}

int makeDecimalRep( string binary)
{
	const unsigned int length = binary.length();
	unsigned long number=  0;
	for (unsigned int i=0;i<length;i++)
	{
		number<<=1;
		number|= binary[i]-'0';
	}
	return number;
}
char converttoascii(int n)
{
	
	return (char)n;
}
string convertcharToString(unsigned char* a, int size) 
{ 
    int i; 
    string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + (char)a[i]; 
    } 
    return s; 
} 



int main(int argc, char *argv[])
   {  
	 //char arrays used
	   char chararray [3];//bytes to encode
	   unsigned char endbits[4]={0,0,0,0}; //these are the 4 chunks of 6bit binary
	   unsigned char endbits32[4]={0,0,0,0};		
  
	  //int declarations/indexing   
	  int totalbytestoencode =0;
	  int totalbytesencoded=0; 
	  int endbits32_size = sizeof(endbits32)/sizeof(char);
	  unsigned int bytesperline=0;
	
	  //string declarations
	  string total="";  
	  string total2="";  
	  string padded=""; 
	  string decodedto="";
	  string newstring="";
	  string linelength="";
	  string startstring ="";
	  string binaryoutput ="";
	  string finishedstring=""; 
	  string result1= startstring + finishedstring;
	 
	  //char declarations
	  char startoflinechar='0';							
	 								
	  string startfile = getUserInput("Enter file to encode: ");
	  string endfile = getUserInput("Encoded output filename: ");
	  string newfile= "bird007.txt"; //contains first file without line length characters
	  cout<<"Bytesperline: ";
	  cin>>bytesperline;
	  cout<<"Name of file to decode to(begin line name)"<<endl;
	  cin>>decodedto;
	  int  encodedperline = (((4*bytesperline)/3));
	  cout<<"Bytes per line "<<bytesperline<<endl;
	  ofstream outfile("bird007.txt", ios::out | ios::binary);
	  outfile<<"begin 644 "<<decodedto<<endl;
	  
	  ifstream sfile;
	  sfile.open(startfile.c_str(),ios::in | ios::binary);
	
	  if (!sfile)
		{
			errorMsg("File not found...terminating",true);
		}	
         
        else 
        { 
			
				while(!sfile.eof())
				{	
					sfile.read(chararray,3); //read 3 bytes into array
				
					for (int i=0;i<3;i++)
					{
						//padding with 0's	
						if(sfile.gcount()==3)
						{
							//shifting and masking to get 4 6 bit chunks
							//top 6 bits using the forward shift
							endbits[0] = (((unsigned char)chararray[0] >> 2) & 0x3f);
							//bottom 2 and next 4 of the next byte
							endbits[1] = ((((unsigned char)chararray[0] << 4) | (((unsigned char)chararray[1] >> 4) & 0x0f)) & 0x3f);
							//bottom 4 bits and top 2 of next byte
							endbits[2] = ((((unsigned char)chararray[1] << 2) | (((unsigned char)chararray[2] >> 6) & 0x03)) & 0x3f);
							//last 6 bytes
							endbits[3] = ((unsigned char)chararray[2] & 0x3f); 
						}
									
							else if(sfile.gcount()==2)
								{	
									//shifting and masking to get 4 6 bit chunks
									//top 6 bits using the forward shift
									endbits[0] = (((unsigned char)chararray[0] >> 2) & 0x3f);
									//bottom 2 and next 4 of the next byte
									endbits[1] = ((((unsigned char)chararray[0] << 4) | (((unsigned char)chararray[1] >> 4) & 0x0f)) & 0x3f);
									//bottom 4 bits and top 2 of next byte
									endbits[2] = ((((unsigned char)chararray[1] << 2) | ((0 >> 6) & 0x03)) & 0x3f);
									//last 6 bytes
									endbits[3] = (0 & 0x3f); 
								}
							else if (sfile.gcount()==1)
								{
								  //shifting and masking to get 4 6 bit chunks
								  //top 6 bits using the forward shift
								  endbits[0] = (((unsigned char)chararray[0]>>2) & 0x3f);
								  //bottom 2 and next 4 of the next byte
								  endbits[1] = ((((unsigned char)chararray[0] << 4) | ((0 >> 4) & 0x0f)) & 0x3f);
								  //bottom 4 bits and top 2 of next byte
								  endbits[2] = (((0 << 2) | ((0 >> 6) & 0x03)) & 0x3f);
							      //last 6 bytes				
								  endbits[3] = (0 & 0x3f); 
								}
																
						}
							 
					if (sfile.gcount()==0)
					{
						continue;
				    }	
					totalbytestoencode += sfile.gcount();
				
					for (int i =0;i<4;i++)
						{
							endbits32[i] = endbits[i]+32;
			 						
							if(endbits32[i]==32)
							{
								endbits32[i]=96;
							}
									
							finishedstring = convertcharToString(endbits32,endbits32_size);
							totalbytesencoded++;
									
						}
							total += finishedstring;				
					}
						cout<<endl;
						cout<<"		Encoded: "<<startfile<<endl;
						cout<<"		To: "<<endfile<<endl;
						cout<<"		Number of bytes to encode: "<<totalbytestoencode<<endl;
						cout<<"		Encoded byte count: "<<totalbytesencoded<<endl;
											
		}
		cout<<endl;
		for(unsigned int i =0;i<=total.length();i++)
			{	
				
				cout<<total[i];
				outfile<<total[i];
				if((i+1)%encodedperline==0)
				{
					cout<<'\n';
					outfile<<'\n';
				}
			}
	
		sfile.close();
		outfile.close();
		
		//creating output file
		ifstream newfile2;
		newfile2.open(newfile.c_str(),ios::in | ios::binary);
		
		//re-write first output to desired output(with line length characters)
		
		ofstream outfile2(endfile.c_str(), ios::out | ios::binary);
		
		if (!newfile2)
			{
				errorMsg("File not found...terminating",true);
			}	
			else
			{
				
					getline(newfile2,linelength);
					outfile2<<linelength<<endl;
					while(getline(newfile2,linelength))
						{
							
							if(linelength.length()>=60)
							{
								startoflinechar= converttoascii(77);
								outfile2<< startoflinechar+linelength<<endl;
							}
						
							else if(linelength=="end" or linelength=="`" )
							{
								outfile2<<linelength<<endl;
								
							}
							
							else if(linelength.length() !=0 and linelength.length() <60)
							{
								startoflinechar= converttoascii((0.75*(linelength.length())) +32);
								outfile2<< startoflinechar+linelength<<endl;
							}
							
						}		
				}
				//cout<<"Encoded output filename: "<<endfile<<endl;					 
				outfile2<<converttoascii(96)<<endl; // ' character
				outfile2<<endl; //blank line
				outfile2<<"end"<<endl;	//text 
				newfile2.close();
				outfile2.close();
			
   }
   
