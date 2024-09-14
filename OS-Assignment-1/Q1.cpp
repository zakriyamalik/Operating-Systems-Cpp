#include <fcntl.h>
#include<unistd.h>
#include<sys/file.h>
#include<string.h>
#include<cstring>
#include<sstream>
#include<cstdlib>
#include<iostream>
#include<filesystem>
using namespace std;
namespace fs=std::filesystem;
bool checkDirName(string dirName)
{
    string command = "test -d \"" + dirName + "\"";

    // Execute command and capture exit status
    int result = system(command.c_str());
      if(result == 0)
      {
      return true;
      }
      else
      {
      return false;
      }
    // If result is 0, the directory exists
}
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
bool checkFileName(string filename)
{
  if(!correctFormat(filename))
  {
  return false;
  }
  else
  {
      if(fs::exists(filename))
      {
      return true;
      }
      else
      {
      return false;
      }
  }
}
bool deleteData(char buffer[999],string rollNo)
{

   // cout<<"In Delete Data \n";  
    int rows= 0;
    int cols=0;
    int rowCounter=0;
    int colCounter=0;
    int charCounter=1;
    int start=0;
    int updatedRow=0;
    int updatedCols=0;
    const char* rollNoArray=rollNo.c_str();
    
     for(int i=0;i<strlen(buffer);i++)
    {
    cout<<buffer[i]<<"";
    if (buffer[i]=='\n')
        {
          rows++;             
        }
    }
    cout<<endl;
    rows=rows+1;
    int* colsArr=new int[rows];
    int newColsCounter=0;
  //  cout<<"Rows Are\t"<<rows<<endl;
    char** rollNoArr=new char*[rows];
    char** updatedArr=new char*[rows];
    int bufferCounter=0;
     for(int i=0;i<strlen(buffer);i++)
    {
     
      while(buffer[i]!='\n')
      {
        
      cols++;
      
      i++;
       
      }
      
      rollNoArr[rowCounter]=new char[cols+1]; 
      updatedArr[rowCounter++]=new char[cols+1];
     
      colsArr[newColsCounter++]=cols;
       cols=0;
      
    }
    cout<<"Cols Array data:"<<endl;
    for(int i=0;i<rows;i++)
    {
    cout<<colsArr[i]<<" ";
    }
   
    for(int i=0;i<rowCounter;i++)
    {
   
      for(int j=0;j<colsArr[i];j++)
      {
      
        rollNoArr[i][j]=buffer[bufferCounter++];
      }
      cout<<endl;
    }
        
    for(int i=0;i<rowCounter;i++)
    {
      for(int j=0;j<colsArr[i];j++)
      {
      
        cout<<rollNoArr[i][j]<<" ";
      }
      cout<<endl;
    }
    cout<<"Done\n"<<endl;
        newColsCounter=1;
        rows=0;
        cout<<"rowCounter"<<rowCounter<<endl;
    for(int i=0;i<rowCounter;i++)
    { 
      for(int j=0;j<colsArr[i];j++)
      {
      rows=j+1;
       if(rollNoArr[i][j]==rollNoArray[0])
       {
        cout<<rollNoArray[0]<<" "<<rollNoArr[i][j]<<endl;
      
        while(rollNoArr[i][rows]==rollNoArray[newColsCounter])
        {
        
         cout<<rollNoArray[newColsCounter++]<<" "<<rollNoArr[i][rows++]<<endl;
        charCounter++;
      cout<<"Counter"<<charCounter<<endl;
        }
        cout<<"Out of while\n";
          cout<<rollNoArray[newColsCounter++]<<" "<<rollNoArr[i][rows++]<<endl;
      
      }
      }
      
      if(charCounter==8)
      {
       charCounter=1;
      newColsCounter=1;
      
        cout<<"Done it!!!\n";
      }
      else
      {
      charCounter=1;
      newColsCounter=1;
      
      cout<<"Marao\n";
      
     
      for(int s=i;s<i+1;s++)
      {
      cout<<"CHECK\t"<<i<<endl;
      for(int j=0;j<colsArr[s];j++)
      {
      
     
      updatedArr[updatedRow][updatedCols++]=rollNoArr[s][j];      
      }
      updatedArr[updatedRow][updatedCols]='\0';
      updatedCols=0;
       for(int k=0;k<strlen(updatedArr[updatedRow]);k++)
      {
      
      cout<<updatedArr[updatedRow][k]<<" ";
      
      }
      int fd=open("student.txt",O_RDWR | O_TRUNC ,0666);
      ssize_t bytesWritten=write(fd,updatedArr[updatedRow],strlen(updatedArr[updatedRow]));
   
    if(bytesWritten<0)
    {
      cerr<<"Errer writing to the file !"<<endl;
      flock(fd,LOCK_UN);
   
      close(fd);
      return 1;
    }
     
      
      }
      
      
    }
    }
   
    
  return true;

  
  
}
bool validateDuplicateRollNo(char buffer[999],string rollNo)
{   

   // cout<<"In validateDuplicateRollNo \n";  
    int rows= 0;
    int cols=9;
    int rowCounter=0;
    int colCounter=0;
    int charCounter=0;
    const char* rollNoArray=rollNo.c_str();
    
     for(int i=0;i<strlen(buffer);i++)
    {
    
    if (buffer[i]=='\n')
        {
          rows++;             
        }
    }
    rows=rows+1;
    
  //  cout<<"Rows Are\t"<<rows<<endl;
    char** rollNoArr=new char*[rows];
    int start =0;
    for( int i=0;i<rows;i++)
    {
      rollNoArr[i]=new char[cols];    
    }
    
    
    
    for(int i=0;i<strlen(buffer);i++)
    {
   
    if(buffer[1]==','){
    
    
      start=2;    
    for(int i=start;i<start+8;i++)
    {
       
        rollNoArr[rowCounter][colCounter++]=buffer[i];
    }
    break;
    }
    }
    rowCounter++;
    colCounter=0;
        
    for(int i=0;i<strlen(buffer);i++)
    {
    if (buffer[i]=='\n')
    {
      while(buffer[i]!=',')
      {
      i++;
      }
      //cout<<"Buffer data\t"<<buffer[i]<<endl;
     for(int j=i+1;j<=i+8;j++)
     {  
     
        rollNoArr[rowCounter][colCounter++]=buffer[j];
        //cout<<"Row counter:\t"<<rowCounter<<endl;
      
     }
     rollNoArr[rowCounter][colCounter]='\0';
     rowCounter++;
     colCounter=0;
    }
    else
    {
    }
    
    }
    
   // cout<<"RollNo array is \n";
    for(int i=0;i<rows-1;i++)
    {
      for(int j=0;j<strlen(rollNoArray);j++)
      {
      if(rollNoArray[j]==rollNoArr[i][j])
      {
      //cout<<rollNoArray[j]<<" "<<rollNoArr[i][j]<<endl;
        charCounter++;
     //   cout<<"Counter"<<charCounter<<endl;
      }
      else
      {
           continue;
          
      }
      }
       if(charCounter==strlen(rollNoArray))
      { 
       // cout<<"RollNo matched"<<endl;
        charCounter=0;
        return false;
      }
      else
      {
      charCounter=0;
        continue;
      }
      
      cout<<"Length of RollNo is \t"<<strlen(rollNoArray)<<endl;
     
      
      
      
    }
    return true;
    
}
bool checkArgs(string rollNo,string gpa)
{
 // cout<<"RollNo: "<<rollNo<<endl;
  //cout<<"GPA: "<<gpa<<endl;
  const char* rollNoArr=rollNo.c_str();
  
  float value=atof(gpa.c_str());
  
  
      if (strlen(rollNoArr) != 8) {
        std::cout << "Wrong Format: Roll number should have 8 characters.\n";
        return false;
    }

    // Check if the first character is a digit
    if (!isdigit(rollNoArr[0])) {
        std::cout << "Wrong Format: First character should be a digit.\n";
        return false;
    }

    // Check if the second character is a digit
    if (!isdigit(rollNoArr[1])) {
        std::cout << "Wrong Format: Second character should be a digit.\n";
        return false;
    }

    // Check if the third character is 'L'
    if (rollNoArr[2] != 'L') {
        std::cout << "Wrong Format: Third character should be 'L'.\n";
        return false;
    }

    // Check if the fourth character is '-'
    if (rollNoArr[3] != '-') {
        std::cout << "Wrong Format: Fourth character should be '-'.\n";
        return false;
    }

    // Check if the fifth, sixth, seventh, and eighth characters are digits
    for (int i = 4; i <= 7; ++i) {
        if (!isdigit(rollNoArr[i])) {
            std::cout << "Wrong Format: Character at position " << (i + 1) << " should be a digit.\n";
            return false;
        }
    }

    // If all checks pass, the format is valid
    

      if(value<1.0||value>4.0)
      {
          cout<<"Wrong GPA \n"<<endl;
          return false;
      }
  
  
    
    return true;
}

int main(int argc,char* argv[])
{
  
    if(argc !=6&&argc!=2)
    {
      cerr<<"Not the correct arguments passed\nArguments Are:"<<argc<<endl;
    }
    else
    {
      cerr<<"Arguments Are:"<<argc<<endl;
    }
    if(argc==2)
    {
     const char* filename=argv[1];
      string fileDirCheck=filename;
      if(!checkDirName(fileDirCheck))
    {
     cout<<"Dir does not exist!\n";
    }
    else
    {
     cout<<"Dir exist !\n";
    }
      
    }
    else
    {
    const char* filename=argv[1];
    string fileNameCheck=filename;
    if(!checkFileName(fileNameCheck))
    {
     cout<<"File does not exist!\n";
    }
    else
    {
      cout<<"File exist!\n";
    string rollNo=string(argv[2]);
    string fName=string(argv[3]);
    string lName=string(argv[4]);
    string GPA =string(argv[5]);
    if(checkArgs(rollNo,GPA))
    {
    
  //  cout<<"Data is :\n";
   // cout<<rollNo<<" "<<fName<<" "<<lName<<" "<<GPA<<" "<<endl;
    
    
    int fd=open(filename,O_RDWR | O_CREAT | O_APPEND,0666);
    char buffer[999];
   
    ssize_t bytesRead = read(fd,buffer,sizeof(buffer)-1);
   
    if(bytesRead<0)
    {
     cerr<<"Error reading file\n";
     flock(fd,LOCK_UN);
     close(fd);
     return 1;
     }
     buffer[bytesRead]='\0';
     flock(fd,LOCK_UN);
     // cout<<"File Content: "<<buffer<<"\n";
    
     if(deleteData(buffer, rollNo))
     {
     cout<<"Kuch bhi nahi\n";
     }
     
     if(!validateDuplicateRollNo(buffer,rollNo))
     {
     cout<<"Roll No matched"<<endl;
     return 0;
     }
        
     
    
    int lineNumber = 1; 
     for (char* ptr = buffer; *ptr; ++ptr) 
     { 
        if (*ptr == '\n')
        {
            ++lineNumber; 
        }
    }  
    if(fd<0)
    {
      cerr<<"Error opening the file"<<endl;
      return 1;
    }
    if(flock(fd,LOCK_EX)<0)
    {
        cerr<<"Errr locking file \n";
        close(fd);
        return 1;
    }
   // cout<<"LineNumber is \t"<<lineNumber<<endl;
   stringstream ss; 
   ss << lineNumber << "," << rollNo << "," << fName << " " << lName << "," << GPA << "\n"; 
   string dataNew = ss.str(); 
   ssize_t bytesWritten=write(fd,dataNew.c_str(),dataNew.length());
   
    if(bytesWritten<0)
    {
      cerr<<"Errer writing to the file !"<<endl;
      flock(fd,LOCK_UN);
   
      close(fd);
      return 1;
    }
    else
    {
      cerr<<"Data is been written in  the file\n";
    }
    if(fsync(fd)<0)
    {
        cerr<<"Error syncing the file!"<<endl;
        flock(fd,LOCK_UN);
        close(fd);
        return 1;
      }
    lseek(fd,0,SEEK_SET);
   
     buffer[999];
   
     bytesRead = read(fd,buffer,sizeof(buffer)-1);
   
    if(bytesRead<0)
    {
     cerr<<"Error reading file\n";
     flock(fd,LOCK_UN);
     close(fd);
     return 1;
     }
     buffer[bytesRead]='\0';
     flock(fd,LOCK_UN);
     
     //cout<<"File Content: "<<buffer<<"\n";
     
     
     close(fd);
     
     }
     else
     {
        cout<<"Enter data in correct format and limit \n"<<endl;
     }
     return 0;
     }
     }
     }
