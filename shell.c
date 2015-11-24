char* split(char*,char*);
void print(char*);
void clear(char*);
int check(char*);
void buildBuffer(char*);
void split2(char*,char*,char*);
int isEmpty(char* );
int getSecNum(int);


main()
{  
  char line[80];
  char output[13313];
  char buffer[13313];
  char filename[80]; 
  char file1[80];
  char c;
  char file2[80];   
  int s = 0;
  int secNum = 0;
	  while(1){
      print("SHELL>\0");
      interrupt(0x21,1,line,0,0);

     if(check(line)== 0){
      split(line ,filename);
     	interrupt(0x21 ,3,filename,buffer,0);
      print(buffer);
      print("\n\r");
      clear(buffer);
     }
else{     
      if(check(line)==1){
      split(line ,filename);
     	interrupt(0x21 ,4,filename,0x2000,0);
       print("\n\r");
         }
      else{
         if(check(line)==2){
      split(line ,filename);
      interrupt(0x21 ,7,filename,0,0);
         }
            else{
      if(check(line)==4){
          interrupt(0x21 ,9,"",0,0);
           }
                else{
            if(check(line)==3){
              interrupt(0x21 ,10,0,0);
            }
            else {
             if(check(line)==8){
       split(line,filename);
       buildBuffer(buffer);
       secNum = getSecNum(buffer);
            //print(secNum);
       interrupt(0x21 ,8,filename,buffer,secNum);
          }
          else {
             interrupt(0x21 ,0,"Bad Command!\0",0,0);
             print("\n\r");
          }
        
}
}
}
}
}

 }
}
int getSecNum(char* line){
  int result = 0 ;
  int i = 0 ;
  while(line[i]!='\0'){
    i++;
    
  }
  result = i/512;
  if(result<i){
    result++;
    //print("1");
  } 
  return result;
}

 //     if(check(line)==3){
      //       split2(line ,file1 ,file2);
      //   interrupt(0x21 ,3,file1 ,output,0);
      //   s = isEmpty(output);
      //   print(file1);
      //   print(file2);
      //   print(output);
      //   if(s == 0){
      //     print("file does not exists");
      //     return;
      //   }
      //   else{
      //     split2(line ,file1 ,file2);
      //     print(file1);
      //     print(file2);
      //   secNum = getsectornumber(buffer);
      //   print("IN");
      //   c ='0'+secNum;
      //   interrupt(0x10,0xe*256+c,0,0,0);
      // interrupt(0x21 ,8,file2,output,1);
      // print("finished");
      //   }
      // }
      
      // if(check(line)==8){
      //  split(line,filename);
      //  buildBuffer(buffer);
      //  secNum = getSecNum(buffer);
      //       //print(secNum);
      //  interrupt(0x21 ,8,filename,buffer,secNum);
      //     }

void buildBuffer(char* line){
  char input[512] ;
  int c = 0 ;
  int k = 0 ;
  int i = 0;
  while(1){
    i= 0;
    c=0;
    k=0;
    while(input[i]!='\0'){
      input[i] = 0x00;
      i++;
    }
    i= 0;
    print("SHELL/fileBuffer>\0");
    interrupt(0x21,1,input,0,0);
    while(input[i]!='\0'){
      i++;
    }
    //print("stop line ");
    if(input[0]==0xd){
      //print("stop");
      break;
    }else{
      //line+=input;
      //print("No stop");
      while(line[c]!='\0'){
        c++;
        
      }
      while(input[k]!='\0'){       
        //print("L");
        //print(line[c]);
        line[c]=input[k];
        k++;
        c++;
      }
      
    }
  }
  //print(line);
}

int mod (int a ,int b){
    
    return a - (a/b)*b;
}  
int isEmpty(char* line){
  if(line[0]!='\0'){

    return 1;
  } 
  return 0;
}
int getsectornumber(char* line){
    int result = 0 ;
  int i = 0 ;
  while(line[i]==0x0){
    i++;
    
  }
  result = divide(i,512);
  // if(result<i){
  //   result++;
  //   //print("1");
  // } 
  return result;
}
int divide(int a,int b){
    int q = 0;
    while(a>=b){
        q++;
        a=a-b;
    }
    return q;
}
void split2(char*filename ,char*ret1 ,char*ret2){
    int i =5;
    int j =0;
    while(filename[i] != 0x0){
        ret1[j] = filename[i];
        i++;
        j++;
    }
    i++;
    j = 0;
    while(filename[i]!='\0'){
        ret2[j] = filename[i];
        i++;
        j++;
          
    }
   
}
void clear(char buffer[13313]){
  int i = 0;
  while(buffer[i]!='\0'){
    buffer[i] = 0x0;
    i++;
  }
}
void print(char* lin){
    interrupt(0x21,0,lin,0,0);
}

char* split(char string[80] ,char result[80] ){
    
    int i,j;
    j = 0;

     if(check(string)==0){
      i = 5;
      }
      else{
        if(check(string)==1){
          i = 8;
        } 
        else{
          if (check(string)==2){
          i = 7;
        }
        else{
          if (check(string)==3){
          i = 5;
        }
        else{
          if(check(string)==8){
            i=7;
          }
      }
      }
    } 
  }
    for(;string[i]!='\0';i++){
        result[j]=string[i];
        j++;
    }
  
    return result;

}
int check(char buffer[80]){
         if(buffer[0] == 'v'&&
            buffer[1] == 'i'&&
            buffer[2] == 'e'&&
            buffer[3] == 'w')
            return 0;
        else{
            if (buffer[0] == 'e'&&
                buffer[1] == 'x'&&
                buffer[2] == 'e'&&
                buffer[3] == 'c'&&
                buffer[4] == 'u'&&
                buffer[5] == 't'&&
                buffer[6] == 'e'){
                return 1;
               }
            else{     
              if(buffer[0] == 'd'&&
                 buffer[1] == 'e'&&
                 buffer[2] == 'l'&&
                 buffer[3] == 'e'&&
                 buffer[4] == 't'&&
                 buffer[5] == 'e'
                ){
              return 2;
            }
            else{
               if(buffer[0] =='c'&&
                 buffer[1] == 'o'&&
                 buffer[2] == 'p'&&
                 buffer[3] == 'y'
                ){
                   return 3;
               }
             else{
              if(buffer[0] == 'c'&&
                buffer[1] == 'r'&&
                buffer[2] == 'e'&&
                buffer[3] == 'a'&&
                buffer[4] == 't'&&
                buffer[5] == 'e'){
                  return 8;
                }
                else{
                  if(buffer[0] == 'd'&&
                     buffer[1] == 'i'&&
                     buffer[2] == 'r'){
                    return 4;
                  }
                  else{ 
                  print(buffer);    
                    return -1;
                  }
                }
               
            
          }
            }
          }
          }
        }

