//Paa kofi Boafo
// PROJECT 1 CS 350 
//uudecode

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string.h>
#include <cstring>
#include <cctype>
using namespace std;



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

void getTokens(string s, string &begin, string &code, string &newfilename)
{
	//read by line
		stringstream line(s);
		string word;
		int w = 0;
		while (getline(line, word ,' '))
		{
			if (w == 0){
				begin = word;
			}
			if (w == 1){
				code = word;
			}
			if (w == 2){
				newfilename=word;
			}
			w++;
		}
}


int main()
{
	 char chararray[4]={0,0,0,0};
	
	 unsigned char threechunks32[4]={0,0,0,0};
	 unsigned char threechunks[3]={0,0,0};
	 
	 string finalstr = "";
	 string str="";
	 string str2="";
	 string str3="";
	 string str4="";
	 string total="";
	 string character="";
	 string firstchar="";
	 string finishedstring="";
	 string begin,code,newfilename;
	 
	 int totalbytesdecoded=0;
	 int len =0;
	
	 string startfile = getUserInput("Enter file to decode: ");
	 ifstream sfile;
	 sfile.open(startfile.c_str(),ios::in | ios::binary);
	 
	 ofstream outfile;
	  if (!sfile)
			{
				errorMsg("File not found...terminating",true);
			}	
         
        else 
        { 
			while(!sfile.eof())
			{
				getline(sfile,str);
				getTokens(str,begin,code,newfilename);
			
				while(getline(sfile,str))
					{
						 if(str.length()<=1)
							{	
							  break;
							} 
						
						else if(str=="end")
							{
							  break;
							}
							
					
							else if(int((str[0]))==77)
							{
								str[0]=60;
								len = 60;
							}
							else
							{
								len = (((int(str[0])-32)*4)/3);
							
							}
							
							totalbytesdecoded += len; 			
							cout<<str[0];
							//skip first character in each line
							str2= str.substr(1,str.length()-1);
							
						int len = str2.length();
						for(int start=0; start<len; start +=4)
						{
							
							str3 = str2.substr(start, 4);
							
							
							if(isspace(str3[0]))
							{
								continue;
							}
						
	       					for (int i=0;i<4;i++)
							{
							   chararray[i]= str3[i];
																
							}
							
							for(int i=0; i<3;i++)
							{
								
								
								threechunks32[0]= (((unsigned char)chararray[0]-32)&0x3F);
								threechunks32[1]= (((unsigned char)chararray[1]-32)&0x3F);
								threechunks32[2]= (((unsigned char)chararray[2]-32)&0x3F);
								threechunks32[3]= (((unsigned char)chararray[3]-32)&0x3F);  
								
									
									if(str3.length()>=4)
									{	
										threechunks[0] = ((unsigned char)threechunks32[0]<<2 | ((unsigned char)threechunks32[1])>>4);	
										
										threechunks[1] = ((unsigned char)threechunks32[1] << 4 | (unsigned char)threechunks32[2] >> 2);
												
										threechunks[2] = ((unsigned char)threechunks32[2] << 6 | (unsigned char)threechunks32[3]);
											
									}
							
									else if(str3.length()>=2)
										{
											
											threechunks[0] = ((unsigned char)threechunks32[0]<<2 | (unsigned char)threechunks32[1]>>4);
											
											threechunks[1] = ((unsigned char)threechunks32[1] << 4 | (unsigned char)threechunks32[2] >> 2);
											
											threechunks[2] = (0 << 6 | 0);
											
											
										}
											
										else if(str3.length()>=1)
										{
											
											threechunks[0] = ((unsigned char)threechunks32[0]<<2 | (unsigned char)threechunks32[1]>>4);
											
											threechunks[1] = (0 << 4 | 0 >> 2);
											
											threechunks[2] = (0 << 6 | 0);
											
										}
										
										else if(str3.length()<1)
										{
											
											threechunks[0] = (0<<2 | 0>>4);
											
											threechunks[1] = (0 << 4 | 0 >> 2);
											
											threechunks[2] = (0 << 6 | 0);
											 										
										}
										
										
							}
							
									
								//put output into one string so we can loop through later
								finalstr+=char(threechunks[0]);
								finalstr+=char(threechunks[1]);
								finalstr+=char(threechunks[2]);	
						}
			
					}		
		sfile.close();
		
			}	
		}			
		outfile.open(newfilename.c_str(), ios::out | ios::binary);
		if(outfile.is_open())
			{
				
				int k = finalstr.length();
				//new char array to hold string values to work with write function
				char array[k];
				for(int i = 0; i<k; i++)
				{
					array[i] = finalstr[i];
					
				}
				
				//cout<<array;
				outfile.write(array, k);
				
				outfile.close();
				}		
cout<<"	  Opened for output: "<<newfilename<<endl;	
cout<<"	  Wrote: "<<((totalbytesdecoded*3)/4)<<" bytes"<<endl;

}
		
		
						

