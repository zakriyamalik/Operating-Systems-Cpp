#include <fcntl.h>
#include<unistd.h>
#include<sys/file.h>
#include<string.h>
#include<cstring>
#include<sstream>
#include<cstdlib>
#include<iostream>
#include<cstdio>
#include <regex>
#include <sys/wait.h>
using namespace std;
void  executeCommand(char** ctrArray,int rows)
{
      cout<<"Executing Command\n";
    //  cout<<"Final\n";
        for(int i=0;i<rows;i++)
        {
      //  cout<<ctrArray[i]<<endl;
        }
        
        pid_t pid=fork();
        if(pid==0)
        {
        if(execvp(ctrArray[0],ctrArray)==-1)
        {
        cout<<"Error executing command\n";
        }
        delete[] ctrArray;
        exit(EXIT_FAILURE);
        }
        else if(pid>0)
        {
        int status;
        waitpid(pid,&status,0);
        if(WIFEXITED(status))
        {
        cout<<"Command exited with status \t"<<WEXITSTATUS(status)<<endl; 
        }
        else
        {
        cout<<"Command did not exit successfully"<<endl;
        }
        }
        else
        {
        cout<<"Fork failed\n";
        exit(EXIT_FAILURE);
        }
}
char** processing(string* data,int* colsArr,int rows)
{
 char** ctrArray=new char*[rows+1];
 for(int i=0;i<rows;i++)
 {
 ctrArray[i]=const_cast<char*>(data[i].c_str());
 }
  ctrArray[rows]=NULL;
  return ctrArray;  
  
}
void trimSpaces(string &str)
{
//cout<<"\nIn trim spaces\n";
  size_t end=str.find_last_not_of(" \t\n\r");
  if(end!=string::npos)
  {
  str.resize(end+1);
  }
  else
  {
  str.clear();
  }
}
bool specialCase(string output)
{

  regex pattern("^[a-zA-Z0-9._-]+$");
  return regex_match(output,pattern);
  
}
void processCommand(string output)
{
  int rows=0;
  int cols=0;
  int total=0;
  int rowCounter=0;
  int bufferCounter=0;
  if(specialCase(output))
  {
      cout<<"No special Character\n";
      
  }
  else
  {
      cout<<"There is special Character\n";
  }
  trimSpaces(output);
 // cout<<"In Process \n";
  //cout<<output<<endl;
  output=output+'\0';
  for(int i=0;output[i]!='\0';i++)
  {
    if(output[i]==' ')
    {
    rows++;
    }
  }
  rows=rows+1;
 // cout<<"CHeck1\t"<<rows<<endl;
  char** record=new char*[rows];
  int* colsArr=new int[rows];
  string* data=new string[rows];
  
  rowCounter=0;
  //cout<<"CHeck2\n";
   for(int i=0;output[i]!='\0';i++)
  {
        total++;
  }
  for(int i=0;i<total;i++)
  {
    while(output[i]!=' '&&output[i]!='\0')
    {
    i++;
    cols++;
    }
  //  cout<<"Check3\t"<<cols<<endl;
    colsArr[rowCounter++]=cols;
    cols=0;
  }
  for(int i=0;i<rows;i++)
  {
      record[i]=new char[colsArr[i]];
  }
  
   int j=0;
   for(int i=0;output[bufferCounter]!='\0';)
   {
  // cout<<"output["<<i<<"]"<<output[i]<<endl;
      while(output[bufferCounter]!=' '&& output[bufferCounter]!='\0')
      {
      record[i][j]=output[bufferCounter];
   //   cout<<"While output["<<bufferCounter<<"]"<<output[bufferCounter]<<endl;
      j++;
      bufferCounter++;
      }
      bufferCounter++;
      record[i][j]='\0';
        j=0;
        i++;     
   }
  //we we we we
 // cout<<"Data in the array is \n";
   for(int i=0;i<rows;i++)
   {
   for(int j=0;j<colsArr[i];j++)
   {
   //   cout<<"record[ "<<i<<" ]"<<"[ "<<j<<" ]"<<record[i][j]<<endl;
   }
   
   
  }
  
  //updation 
  
  
   for(int i=0;i<rows;i++)
   {
  
  data[i]=string(record[i]);
  
   }
  
  for(int i=0;i<rows;i++)
  {
  //cout<<data[i]<<endl;
  }
  
  char** ctrArray=processing(data,colsArr,rows);
   //cout<<"Final\n";
  for(int i=0;i<rows;i++)
  {
 // cout<<ctrArray[i]<<endl;
  }
  
  executeCommand(ctrArray,rows);
  
}
bool checkExit(string output)
{

if(output=="Exit"||output=="EXIT"||output=="exit")
{

return true;
}
else
{
return false;
}
}
int main()
{
  int choice=1;
  string output="";
  do
  {
     cout<<"Enter command\n";
     getline(cin,output);
     if(checkExit(output))
     {
     choice=3;
     }
     else
     {
     processCommand(output);
     }
  }
  while(choice!=3);
    
    return 0;
}

