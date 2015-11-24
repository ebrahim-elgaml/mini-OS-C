void readString(char*);
void printString(char*);
void readSector(char*,int);
void handleInterrupt21(int,int,int,int);
void readFile(char*, char*);
void executeProgram(char*, int);
void writeSector(char*,int );
void deleteFile(char*);
int equals(char*, char*);
void writeFile (char*,char*,int);
void terminate();
char* subset(char*, int, int);
void printDir();
main( ){
    //M3 step 1 
    
//    char* buffer; 
    // makeInterrupt21();
    // interrupt(0x21, 3, "messag\0", buffer, 0); //
    // interrupt(0x21, 0, buffer, 0, 0); //
    // while(1);
     
    //M3 step2
    makeInterrupt21();
    interrupt(0x21, 4, "shell\0", 0x2000, 0);
    while(1);
    /*hang up*/
    /*char buffer[512];
    readSector(buffer, 30);
    printString(buffer);
    */
// char buffer[13312];
//  makeInterrupt21();
// interrupt(0x21, 7, "sgdf\0", 0, 0); //delete messag
// interrupt(0x21, 3, "sgdf\0", buffer, 0); // try to read messag
// interrupt(0x21, 0, buffer, 0, 0); //print out the contents of buffer
// while(1);
}

void deleteFile(char* name){
    char dirBuffer[512];
    char mapBuffer[512];
    int i = 0;
    int j = 0;
    int k ;
    int l ;
    int found ;
    int sectorNumber;
    readSector(mapBuffer , 1);
    readSector(dirBuffer , 2);
    

    found = 0;
    //16 file entries in the directory
    for( ;i< 16 && found!= 1;i++){
        found = 1; 
     for(j =0;j<6;j++){
        if(name[j] == dirBuffer[i*32+j]){
            found &= 1;
                 dirBuffer[i*32] = 0x0;
                 printString("1");

        }
        else{
        
        found = 0;
        printString("2");
        }

       
}
if(found)
{
    break;
}}
//k is the file address = position of the file in the dirbuffer* 32
k = i*32;
//clearing the remaining 26 bits that contain the sector number starting from l = 6 (after the name ) 
if(found == 1){
    l = 6;
    while (dirBuffer[k+l]!= '\0'){
        //getting the sector number from the last 26 bits in the dirBuffer
        sectorNumber = dirBuffer[k+l];
        //Clearing their crosponding values in the mapBuffer 
        mapBuffer[sectorNumber] = 0x00;
        //Move to the next sector
        l++;
    }
printString("found");
}
else{
    printString("file not found");
}

// writ eback the edited buffers to map & directory
writeSector(mapBuffer,1);
writeSector(dirBuffer ,2);
     }
//         if(name[j] == '\0' &&
//             dirBuffer[32*i+j] == '\0' &&
//             j != 0){
//             found = 1;
//                     printString("6");
// }
      // for(j = 0; j<6 ;j++){
 //        if(name[j] != dirBuffer[j+i])
 //            areEqual = -1;
 //    }
int equals(char* a, char* b){

}


void executeProgram(char* name, int segment){
    char buffer[13312];
    int i = 0 ;
    readFile(name,buffer);
    while(i<13312){
        putInMemory(segment, i, buffer[i]);
        i++;
    }
    launchProgram(segment);
}


// write file 

void writeFile(char* name, char* buffer, int secNum){
    char dirBuffer[512];
    char mapBuffer[512];
    char* s;
    int i = 0;
    int j = 0;
    int subsetBuffferLength = 0;
    int k = 0 ;
    int sCounter = 0;
    char print ;
    char subsetBuffer[512];
    int bufferStart = 0 ;
    int findSectors = 0;
    int mapSector = 1;
    int nameLength = 0;
    readSector(mapBuffer , 1);
    readSector(dirBuffer , 2);
    while(name[nameLength]!='\0'){
        nameLength++;
    }
    //16 file entries in the directory
    for( ;i< 16 ;i++){    
        if(dirBuffer[i*32]==0x00){      
            break;
        }
    }
    //print[0] = i ;
    if(i==16){
        return;
    }
    j= 0 ;
    // setting name of the file 
    for(j = 0 ; j<6 ; j++){
        
        if(j<nameLength){
            dirBuffer[j+i*32] = name[j];
           // printString("7");
        }
        else{
            dirBuffer[j+i*32] = 0x00;

        }
    }
    for(;findSectors<secNum;findSectors++){ 
        while(mapBuffer[mapSector]!=0x00){
            
            mapSector++;
            if(mapSector==512){
                printString("7");
                return;// ask rana delete the file name or not befor deleting it
            }
        }
        
        if(mapSector==512){
            printString("7");
            return;// ask rana delete the file name or not befor deleting it
        }

        mapBuffer[mapSector] = 0xff;
        writeSector(mapBuffer, 1);
        dirBuffer[i*32+6+findSectors] = mapSector;
        // go to the sector and fill it with the buffer write 512 bytes
        s  = subset(buffer,k,k+512);
        while(s[sCounter]!='\0'){
            subsetBuffer[sCounter]=s[sCounter];
            sCounter++;
        }
        // check if the subset buffer is empty 
        for(;subsetBuffer[subsetBuffferLength]!='\0';subsetBuffferLength++){
            //printString("7");
        }
        if(subsetBuffferLength==0){
            return;
        }
        subsetBuffferLength = 0;
        writeSector(subsetBuffer,mapSector);

        k+=512;
    }
    // fill the remaining 
    for(;findSectors<26;findSectors++){
        print = '0' + mod(findSectors,20);
        //interrupt(0x10, 0xE*256+print, 0,0,0);
        dirBuffer[i*32+6+findSectors] = 0x00;
        //printString("7");
    }

    //printString(dirBuffer);

// writ eback the edited buffers to map & directory
    writeSector(mapBuffer,1);
    writeSector(dirBuffer ,2);
  //  printString("11");
  }
// end write file 

char* subset(char* buffer , int start , int end ){
    char result[512] ;
    int i = 0;
    
    while (start<end && buffer[start]!='\0'){
        result[i] = buffer[start];
        start++;
        i++;
        ///printString("7");
    }
    return result;
}


 void printDir(){
    char dirBuffer[512];
    char mapBuffer[512];
    char print[2];
    int i = 0;//dir counter
    int j = 0;// name counter 
    int k = 6 ;// sectors counter 
    int secNum = 0;
    readSector(mapBuffer , 1);
    readSector(dirBuffer , 2);
    //16 file entries in the directory
    for( ;i< 16 ;i++){
        if(dirBuffer[i*32]==0x00){    
            break;
        }else{
            for(;j<6&&dirBuffer[i*32+j]!='\0';j++){
                interrupt(0x10, 0xE*256+dirBuffer[i*32+j], 0,0,0);
            }
            j=0;
            interrupt(0x10, 0xE*256+':', 0,0,0);
            for(;dirBuffer[i*32+k]!=0x00&&k<26;k++){
               // printString('1');
                secNum++;
            }
            print[0] ='0'+mod((secNum/10),10);
            print[1] = '0'+mod((mod(secNum,10)),10);
            interrupt(0x10, 0xE*256+print[0], 0,0,0);
            interrupt(0x10, 0xE*256+print[1], 0,0,0);
            secNum = 0;
            k = 6;
        }
        interrupt(0x10, 0xE*256+'\n', 0,0,0);
        interrupt(0x10, 0xE*256+'\r', 0,0,0);
    }
 }





void readFile(char* fileName , char* buffer)
{
    char readingBuffer[512];
    int flag = 1;
    int found= 0;
    int j = 1;
    int start;
    char readingFileSectors[512];
    int c = 0;
    int i = 0;
    int k = 0 ;
    char fileSectors[26];
    fileName[6];
    readSector(readingBuffer,2);
    while (i<512&&found==0){
        flag=1;
       if(readingBuffer[i]==fileName[0])
        {
            j = 1;
            while(j<6&&flag==1){
                if(fileName[j]!=readingBuffer[i+j]){
                    flag = 0;
                }
                j++;
            }
            if(flag==1){//find the file now its sectors
                found = 1;
                while (k<26){
                    fileSectors[k] = readingBuffer[i+j+k];
                    k++;
                }
            }
        }
        i++; 
    }

    if(found == 0){
        return;
    }
    i = 0 ;
    k = 0 ;
    j = 0 ;
    while( c <26 && fileSectors[c] != 0x0 ){
        readSector(readingFileSectors,fileSectors[c]);
        start = c*512;
        j = 0 ;
        while(j<512){
            
            buffer[j+start] = readingFileSectors[j];
            j++;
        }
        c++;
    }
}


void readString(char* line)
{
 int i = 0;
 char in = 0x0;
 while (in != 0xd && i<80)
   {
    in = interrupt(0x16, 0x0, 0x0, 0x0, 0x0);

    interrupt(0x10,0xe*0x100+in,0x0,0x0,0x0);
    if(in == 0x8 && i!=0){

        interrupt(0x10,0xe*0x100+0x20,0x0,0x0,0x0);
        interrupt(0x10,0xe*0x100+0x8,0x0,0x0,0x0);
        *(line + (i-1)) = 0x0;
        i--;
        
    }else{
        *(line + i) = in;
    /* add LF to CR */
    if (in == 13) interrupt(0x10,0xe*0x100+10,0x0,0x0,0x0);
    i++;
    }
   }
 *(line + i) = 0xa;
 *(line + i) = 0x0;
 
}

void printString(char* string)
{
 int i = 0;
 while (*(string + i) != '\0')
   {
    char al = *(string + i);
    char ah = 0xe;
    int ax = ah * 256 + al;
    interrupt(0x10,ax,0,0,0);
    /* add LF to CR */
    if (al == 13) interrupt(0x10,0xe*0x100+10,0x0,0x0,0x0);
    i++;
   }
}

int divide(int a,int b){
    int q = 0;
    while(a>=b){
        q++;
        a=a-b;
    }
    return q;
}

int mod (int a ,int b){
    
    return a - (a/b)*b;
}   


 void readSector(char* buffer,int sector)
{

int AH =2;
int AL = 1;
int ax = AH*256 + AL;
int CH = (sector/36);
int CL = mod(sector,18)+1;
int CX = CH *256+CL;
int DH = mod((sector/18),2);
int DL = 0;
int DX = DH*256 + DL;
interrupt(0x13,ax,buffer,CX,DX);


}
void writeSector(char* buffer,int sector)
{

int AH =3;
int AL = 1;
int ax = AH*256 + AL;
int CH = (sector/36);
int CL = mod(sector,18)+1;
int CX = CH *256+CL;
int DH = mod((sector/18),2);
int DL = 0;
int DX = DH*256 + DL;
interrupt(0x13,ax,buffer,CX,DX);


}
void terminate(){
    char shell[6];
    shell[0]='s';
    shell[1]='h';
    shell[2]='e';
    shell[3]='l';
    shell[4]='l';
    shell[5]='\0';
    interrupt(0x21, 4, shell, 0x2000, 0);
 }

void handleInterrupt21(int ax, int bx, int cx, int dx) {
    //ax = 1;
    if(ax == 0){
        printString(bx);
        }else{

            if(ax == 1){
                readString(bx);
            }else{
                if (ax == 2){
                    readSector(bx,cx);
                }else{
                    if (ax == 3){
                    readFile(bx,cx);
                    }else{
                        if (ax == 4){
                            executeProgram(bx,cx);
                        }
                        else{
                            if (ax == 5)
                            {
                                 terminate();
                            }
                            else {
                                if (ax == 6){
                                    writeSector(bx,cx);
                                          }
                            else{
                                if (ax == 7){
                                    deleteFile(bx);
                                }else{
                                    if(ax==8){
                                        writeFile(bx,cx,dx);
                                    }else{
                                        if(ax==9){
                                            printDir();
                                        }
                                    }
                                }
                            }

                        }
                        }
                    }
                    
                    }
                }
        }
            
}
