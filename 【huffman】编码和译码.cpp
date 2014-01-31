#include <cstdlib>
#include <iostream>

using namespace std;

static int root = -1; 

class Hafu{

public:
            
      string code; 
      
      int left,right,weight;
      
      Hafu(){
           
           code = "";
           
           weight = 0; 
           
           left = -1;
           
           right = -1; 
             
             } 
      
      }; 
 
  
void Hunt(string str,Hafu ha[],int flag[]){                                          //统计输入字符串的频率 
                  
     int j = 0;
     
     while(str[j] != '\0'){
                  
          flag[str[j]] ++;
          
          ha[str[j]].weight ++; 
          
          j++; 
              
                  }                 
                  
}

int Min(Hafu ha[],int flag[],int sta,int end)               //取频率最小字符 
{
      int i = 0,j = 255,min = 10000;
      
      for(i = 0;i < end;i++)
      {
         if(ha[i].weight&&flag[i]&&min > ha[i].weight){
                              
               flag[j] = 1;flag[i] = 0; 
               
               min = ha[i].weight; 
                
               j = i; 
                        
             }    
       
      } 
      
      if(j == 255) { return -2;}
      
      return j; 

} 


void MakeTree(Hafu ha[],int flag[]){                              //构造hrfuman树 
           
     int i = 128;
     
     int c1,c2; 
     
     while((c1 = Min(ha,flag,0,254))!= -2&&(c2 = Min(ha,flag,0,254)) != -2){
              
          ha[i].weight = ha[c1].weight + ha[c2].weight;
          
          flag[c1] = 0; flag[c2] = 0;flag[i] = 1; 
          
          ha[i].left = c1;
          
          ha[i].right = c2; 
           
          i ++;  
              
              }
      root = i - 1;         
           
           
} 


void EnCode(Hafu ha[],string strt,int r)                      //编码 
{
     int i = 0;
     
     if(ha[r].left != -1) {
                   
                   string strtem = strt + "0";
                   
                   int t = ha[r].left;
                   
                   EnCode(ha,strtem,t); 
                   
                   } 
     if(ha[r].right != -1) {
                   
                   string strtem = strt + "1";
                   
                   int t = ha[r].right;
                   
                   EnCode(ha,strtem,t); 
                   
                   }
      if(ha[r].right == -1&&ha[r].left == -1)  {ha[r].code = strt;} 
 
 
} 

void Show(Hafu ha[],string str)                             //输出编码结果 
{
     int j = 0;int i= 0;
     
     cout<<"编码表："<<endl; 
     
     while(i < 127){
              
              if(ha[i].weight > 0) {
                              
                     cout<<(char)i<<":  "<<ha[i].code<<endl;
                              
                     }
             
             i++;
             
             }
             
             cout<<endl; 
     
     while(str[j] != '\0'){
                  
           cout<<ha[str[j]].code;
           
           j++; 
              
                  }  
     cout<<endl; 
 
} 

void Tran(Hafu ha[],string restr,int r)                      //译码并输出 
{
     int i = 0,pos = r;
     
     while(i < restr.length()) { 
              
     char c = restr[i]; 
     
     if(c == '0') {
                   
                   pos = ha[pos].left;
                  
                   } 
     if(c == '1') {
                   
                  pos = ha[pos].right;
                  
                   }
      if(ha[pos].right == -1&&ha[pos].left == -1)  {
                       
                       cout<<(char)pos;pos = r;
                       
                       }
      
      i++; 
      
      } 
 
 
} 

int main(int argc, char *argv[])
{   
    string str,strt = "",restr="";
    
    cin>>str;
    
    int flag[256] = {0};  
    
    Hafu ha[256];
    
    Hunt(str,ha,flag);
    
    MakeTree(ha,flag);
    
    EnCode(ha,strt,root);
    
    Show(ha,str);
    
    cin>>restr; 
    
    Tran(ha,restr,root); 
    
    system("PAUSE");
    
    return 0;
}
