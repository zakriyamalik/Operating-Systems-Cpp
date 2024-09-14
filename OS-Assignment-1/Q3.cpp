#include <fcntl.h>
#include<unistd.h>
#include<sys/file.h>
#include<string.h>
#include<cstring>
#include<sstream>
#include<cstdlib>
#include<iostream>
#include<cstdio>
#include<regex>
#define ROWS 4
using namespace std;
bool correctFormat(string output)
{
  //cout<<"In correct format\n";
  
  int size=output.size();
 // cout<<"Size is:"<<size<<endl;
  int curr=size-4;
 // cout<<"output["<<curr<<"]"<<output[curr]<<endl;
  if(output[curr++]=='.')
  {  //cout<<"output1["<<curr<<"]"<<output[curr]<<" Curr: "<<curr<<endl;
  if(output[curr++]=='t')
  {  //cout<<"output2["<<curr<<"]"<<output[curr]<<" Curr: "<<curr<<endl;
   if(output[curr++]=='x')
  {  //cout<<"output3["<<curr<<"]"<<output[curr]<<" Curr: "<<curr<<endl;
   if(output[curr++]=='t')
  {  //cout<<"output4["<<curr<<"]"<<output[curr]<<" Curr: "<<curr<<endl;
  cout<<"Done it\n";
  
  return true;
  }
  else
  {
    cout<<"Not Done Yet\n";
  //  cout<<"output["<<curr<<"]"<<output[curr]<<" Curr: "<<curr<<endl;
    return false;
  }
  }
  else
  {
    cout<<"Not Done Yet\n";
  //  cout<<"output["<<curr<<"]"<<output[curr]<<" Curr: "<<curr<<endl;
    return false;
  }
  }
  else
  {
   cout<<"Not Done Yet\n";
  // cout<<"output["<<curr<<"]"<<output[curr]<<" Curr: "<<curr<<endl;
   return false;
  }  
  }
  // cout<<"output["<<curr<<"]"<<output[curr]<<" Curr: "<<curr<<endl;
  else
  {
  cout<<"Not Done Yet\n";
 // cout<<"output["<<curr<<"]"<<output[curr]<<" Curr: "<<curr<<endl;
  return false;
  }
   
  
}
bool specialCase(string output)
{

  regex pattern("^[a-zA-Z0-9._-]+$");
  return regex_match(output,pattern);
  
}
bool checkAccessKey(string lines,int i,int j,int* cols,int &updatedj)
{
      int counter=0;
        int passCounter=0;
       cout<<"In access check\n";
        char access[10]={'a','c','c','e','s','s','_','k','e','y'};
      //  cout<<"Lines["<<i<<"] "<<lines[j]<<"Password ["<<i<<"] "<<access[passCounter]<<endl;
        while(lines[j]==access[passCounter++])
        {
      //    cout<<"Lines["<<i<<"] "<<lines[j]<<"Password ["<<i<<"] "<<access[passCounter]<<endl;
      
        j++;
        counter++;
        }
        updatedj=j;
        if(counter==10)
        {
       // cout<<"In if\n";
      return true;
      }
      else
      {
     // cout<<"In else\n";
      return false;
      }
}
bool  checkPassword(string lines,int i,int j,int* cols,int &updatedj)
{
    int counter=0;
    int passCounter=0;
 //  cout<<"In password check\n";
    char pass[8]={'p','a','s','s','w','o','r','d'};
  //  cout<<"Lines["<<i<<"] "<<lines[j]<<"Password ["<<i<<"] "<<pass[passCounter]<<endl;
    while(lines[j]==pass[passCounter++])
    {
    j++;
    counter++;
    }
    updatedj=j;
    if(counter==8)
    {
   // cout<<"In if\n";
  return true;
  }
  else
  {
 // cout<<"In else\n";
  return false;
  }
}
string updatePassword(string lines,int i,int j,int* cols,int &updatedj)
{
       int counter=0;
    int passCounter=0;
    string mask="[PRIVATE]";
    updatedj=updatedj+1;
    int start=updatedj;
   cout<<"In  update password check\n";
   cout<<"Lines["<<i<<"] "<<lines[updatedj]<<endl;
    while(lines[updatedj]!=','&&lines[updatedj]!='\n')
    {
      cout<<"Lines["<<updatedj<<"] "<<lines[updatedj]<<endl;
    updatedj++;
    counter++;
    }
    cout<<"Counter:"<<counter<<endl;
    lines.erase(start,counter);
    cout<<"Line is "<<lines<<endl;
    lines.insert(start,mask);
    cout<<"Line is "<<lines<<endl;
  return lines;
}

char** EncryptDecrypt2D(char** updatedArray,int* cols,char key)
{
    cout<<"In EncryptDecrypt2D\n";
    for(int i=0;i<ROWS;i++)
    {
    for(int j=0;j<cols[i];j++)
    {
      updatedArray[i][j]=updatedArray[i][j]^key;
    }
    }
   
  return updatedArray;
    
}


char** sanitizer(char** updatedArray,int* cols)
{
  cout<<"In sanitizer\n";
    string * lines=new string[ROWS];
    int updatedj=0;
    string line="";
    
    
   
    for(int i=0;i<ROWS;i++)
    {
    
      lines[i]=string(updatedArray[i]);
    
    }
   // cout<<"Lines\n";
    //for(int i=0;i<ROWS;i++)
    //{
    //cout<<lines[i]<<endl;
    //}
    
    // First 
   for(int i=0;i<ROWS;i++)
   {
   for(int j=0;j<cols[i];j++)
   {// cout<<lines[i][j]<<" ";
    if(lines[i][j]=='p'||lines[i][j]=='P')
    {
        if(checkPassword(lines[i],i,j,cols,updatedj))
        {
       // cout<<"Back in\n";
        
       // cout<<"Curr index\t"<<lines[i][updatedj]<<" "<<endl;
        line=updatePassword(lines[i],i,j,cols,updatedj);
         lines[i]=line;
        }
        else
        { 
     //   cout<<"Back else\n";
        }
    }
   }
   }
   
   //Second
   updatedj=0;
   for(int i=0;i<ROWS;i++)
   {
   for(int j=0;j<cols[i];j++)
   {// cout<<lines[i][j]<<" ";
    if(lines[i][j]=='a'||lines[i][j]=='A')
    {
        if(checkAccessKey(lines[i],i,j,cols,updatedj))
        {
        cout<<"Back in\n";
        
        cout<<"Curr index\t"<<lines[i][updatedj]<<" "<<endl;
        line=updatePassword(lines[i],i,j,cols,updatedj);
         lines[i]=line;
        }
        else
        { 
        cout<<"Back else\n";
        }
    }
   }
   }
   
   
   cout<<"Finally\n\n\n";
   for(int i=0;i<ROWS;i++)
   {
    
    cols[i]= lines[i].length();
    
   }
   for(int i=0;i<ROWS;i++)
   {
   for(int j=0;j<cols[i];j++)
    {
    cout<<lines[i][j]<<" ";
    }
     cout<<endl;
   }
   
   
   for(int i=0;i<ROWS;i++)
   {
    for(int j=0;j<cols[i];j++)
    {
    updatedArray[i][j]=lines[i][j];
    }
   }
   for(int i=0;i<ROWS;i++)
   {
    for(int j=0;j<cols[i];j++)
    {
    cout<<updatedArray[i][j];
    }
    cout<<endl;
   }
   
   
  return updatedArray;
    
}




char** encryptConfiguration(char** record,int* cols)
{
    cout<<"In encryptConfiguration\n";
  char** updatedArray=new char*[ROWS];
  char key='2';
  for(int i=0;i<ROWS;i++)
  {
    updatedArray[i]=new char[cols[i]];
  }
  
  for(int i=0;i<ROWS;i++)
  {
  for(int j=0;j<cols[i];j++)
  {
    updatedArray[i][j]=record[i][j];
  }
  }
  cout<<"Updated Array\n";
  
   for(int i=0;i<ROWS;i++)
  {
  for(int j=0;j<cols[i];j++)
  {
    cout<<updatedArray[i][j];
  }
  cout<<endl;
  }
  

  cin.ignore();
  cout<<"Enter a character as a key\n";
  cin>>key;
  updatedArray=EncryptDecrypt2D(updatedArray,cols,key);
  
   cout<<"Encrypted Array\n";
  
   for(int i=0;i<ROWS;i++)
  {
  for(int j=0;j<cols[i];j++)
  {
    //cout<<updatedArray[i][j];
  }
  cout<<endl;
  }
  //updatedArray=EncryptDecrypt2D(updatedArray,cols,key);
  // cout<<"Encrypted Array two\n";
  
   for(int i=0;i<ROWS;i++)
  {
  for(int j=0;j<cols[i];j++)
  {
  //  cout<<updatedArray[i][j];
  }
  cout<<endl;
  }
  return updatedArray;
  
}
char** sanitizeConfiguration(char** record,int* cols)
{

cout<<"In sanitizeConfiguration\n";
  char** updatedArray=new char*[ROWS];
  for(int i=0;i<ROWS;i++)
  {
    updatedArray[i]=new char[cols[i]];
  }
  
  for(int i=0;i<ROWS;i++)
  {
  for(int j=0;j<cols[i];j++)
  {
    updatedArray[i][j]=record[i][j];
  }
  }
  
  
  
  updatedArray=sanitizer(updatedArray,cols);
  
  //cout<<"Updated Array 2\n";
  
   for(int i=0;i<ROWS;i++)
  {
  for(int j=0;j<cols[i];j++)
  {
 //   cout<<updatedArray[i][j];
  }
  cout<<endl;
  }
  
  
  return updatedArray;
  
}

















  

char** readData(string inputConfig,int *colsArr)
{
      cout<<"In ReadData\n";
    const char* inputConfiguration=inputConfig.c_str();
    int fd=open(inputConfiguration,O_RDWR | O_CREAT ,0666);
    char buffer[999];
     int counter=0;
    char**record=new char*[ROWS];
    for(int i=0;i<ROWS;i++)
    {
      record[i]=new char[colsArr[i]];
    }

   
    ssize_t bytesRead = read(fd,buffer,sizeof(buffer)-1);
   
    if(bytesRead<0)
    {
     cerr<<"Error reading file\n";
     flock(fd,LOCK_UN);
     close(fd);
    
     }
     else
     {
     cerr<<"Data read successfully \n";
     buffer[bytesRead]='\0';
     }
     counter=0;
     for(int i=0;i<ROWS;i++)
     {
     int j=0;
     for(;j<colsArr[i];j++)
     {
      
      record[i][j]=buffer[counter++];
       
     }
     record[i][j]='\n';
     }
    
   
     return record;
}
int* inputData(string inputConfig ,char buffer[999])
{
    cout<<"Input Data\n";
    const char* inputConfiguration=inputConfig.c_str();
    cout<<"Input configuration is :\n";
    for(int i=0;buffer[i]!='\0';i++)
    {
    cout<<"buffer ["<<i<<"]"<<buffer[i]<<" ";
    }

    int bufferSize=0;
   int fd=open(inputConfiguration,O_RDWR | O_CREAT | O_TRUNC,0666);
    int* colsArr=new int[4];
    int newColsCounter=0;
    int cols=0;
    int counter=0;
   
    
    
    bufferSize=strlen(buffer);
    buffer[bufferSize]='\0';
     ssize_t bytesWritten=write(fd,buffer,strlen(buffer));
   
     for(int i=0;i<strlen(buffer);i++)
    {
     
      while(buffer[i]!='\n')
      {
        
      cols++;
      
      i++;
       
      }     
      colsArr[newColsCounter++]=cols+1;
       cols=0;
    }
   
   
   
    if(bytesWritten<0)
    {
     cerr<<"Error writing file\n";
     flock(fd,LOCK_UN);
     close(fd);
     }
     else
     {
     cerr<<"Data is been written in  the file\n";
     }
     buffer[bytesWritten]='\0';
     flock(fd,LOCK_UN);
     return colsArr;
}

void func1(int choice,string inputConfiguration,string outputFile)
{

  int fd[2];
  pipe(fd);
  pid_t pid;
  int id =fork();
  int* colsArr;
     char buffer[999]; sprintf(buffer,"username=admin,password=123,access_key=ABC123\nusername=HR,password=456,access_key=ABC124\nusername=SQA,password=789,access_key=ABC125\nusername=admin,password=234,access_key=ABS121\n");
  if(id)
  {
  
  close(fd[1]);
  int* cols=new int[ROWS];
  char** finalArray=new char*[ROWS];
  int bufferCounter=0;
    cout<<"Back in parent\n";
  read(fd[0],cols,sizeof(int)*ROWS);
  for(int i=0;i<ROWS;i++)
  {
    finalArray[i]=new char[cols[i]];
  }
  for(int i=0;i<ROWS;i++)
  {
  read(fd[0],finalArray[i],cols[i]);
  }
  close(fd[0]);
  
   
          for(int i=0;i<ROWS;i++)
          {
       
           for(int j=0;j<cols[i];j++)
           {
           
          
           buffer[bufferCounter++]=finalArray[i][j];
         
           }
          
          }
            buffer[bufferCounter]='\0';
         bufferCounter=0;
         
           cout<<"Final data is\n";
          for(int i=0;i<ROWS;i++)
          {
       
           for(int j=0;j<cols[i];j++)
           {
            cout<<buffer[bufferCounter++];
           }
           cout<<endl;
          }
             const char* inputConfiguration=outputFile.c_str();
      int fd=open(inputConfiguration,O_RDWR | O_CREAT | O_TRUNC,0666);
   
     ssize_t bytesWritten=write(fd,buffer,bufferCounter);
  
  
  
   
   
  }
  else
  {
    close(fd[0]);
         if(choice==1)
        {
          cout<<"Configuration mathod\n";
        
       
          colsArr=inputData(inputConfiguration,buffer);
          for(int i=0;i<ROWS;i++)
          {
          //  cout<<"colsArr["<<i<<"] "<<colsArr[i]<<endl;
          }
           char**record=new char*[ROWS];
           char** updatedArr=new char*[ROWS];
           
          for(int i=0;i<ROWS;i++)
          {
            record[i]=new char[colsArr[i]];
            char** updatedArr=new char*[ROWS];
          }
          
        
         record= readData(inputConfiguration,colsArr);
    
          updatedArr=encryptConfiguration(record,colsArr);
          
       //   cout<<"Final data is\n";
          for(int i=0;i<ROWS;i++)
          {
           for(int j=0;j<colsArr[i];j++)
           {
        
       //    cout<<updatedArr[i][j];
           }
       //    cout<<endl;
          }
       
          cout<<"Back in 1\n";
          cout<<"Sizeof  updatedArr\t"<<sizeof(updatedArr)<<endl;
          cout<<"Sizeof  colsArr\t"<<sizeof(colsArr)<<endl;
             write(fd[1],colsArr,sizeof(int)*ROWS);
             for(int i=0;i<ROWS;i++)
             {
             
          write(fd[1],updatedArr[i],colsArr[i]);
          }
       
          close(fd[1]);
          
     
         
        }
        else
        {
        cout<<"Senitize Method\n";
        
       colsArr= inputData(inputConfiguration,buffer);
          char**record=new char*[ROWS];
          char** updatedArr=new char*[ROWS];
           
          for(int i=0;i<ROWS;i++)
          {
            record[i]=new char[colsArr[i]];
            char** updatedArr=new char*[ROWS];
          }
         record=readData(inputConfiguration,colsArr);
         updatedArr=sanitizeConfiguration(record,colsArr);
          cout<<"Back in 1\n";
         //cout<<"Updated Array 1\n";
           for(int i=0;i<ROWS;i++)
            {
            for(int j=0;j<colsArr[i];j++)
            {
         //    cout<<updatedArr[i][j];
            }
            cout<<endl;
            }
           write(fd[1],colsArr,sizeof(int)*ROWS);
             for(int i=0;i<ROWS;i++)
             {
             
          write(fd[1],updatedArr[i],colsArr[i]);
          }
       
          close(fd[1]);
        
        }
        
  }
}

int main(int argc,char* argv[])
{
  string inputConfiguration="configInput.txt";
  string outputFile="output.txt";
  int choice=0;
  while (true) {
        cout << "Enter name of input Configuration file: ";
        getline(cin, inputConfiguration);
        if (specialCase(inputConfiguration)&& correctFormat(inputConfiguration)) {
            break; // Exit loop if the input is valid
        } else {
            cout << "Invalid file name or file format. Please try again.\n";
        }
    }

    while (true) {
        cout << "Enter name of output file: ";
        getline(cin, outputFile);
        if (specialCase(outputFile)&& correctFormat(outputFile)) {
            break; // Exit loop if the output is valid
        } else {
            cout << "Invalid file name or file format. Please try again.\n";
        }
    }
   cout<<"Enter 1 for Encrypt Confugration\nEnter 2 for Sanitize Configuration\n";
    cin>>choice;
    func1(choice,inputConfiguration,outputFile);
    
 // cout<<"Names of files are\t"<<inputConfiguration<<" "<<outputFile<<endl;
  
  
  
    
    
    return 0;
  }
