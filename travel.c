#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmap.h"
#include "pq.h"


 typedef struct no_ 
{
    char start_pos[11];			//stores the start position
    char end_pos[11];			//stores the end position
    double d;			//stores the distance between start position and on end position
  
}no_;


typedef struct st{
    no_ * arr_heap;     //its the binary heap
    int size;			//stores the number of conncetions
    int ver;			//stores teh number of vertices

}st;

typedef struct noo
{
  char namee_[11];
  double dis;
  struct noo* next;

}noo;

typedef struct lin
{ int flagg;
  char Fname[11];
  noo *head;

}lin;

typedef struct arr_lin
{
 lin *adj_list;
 int lengthh;
}arr_lin;


arr_lin * adj_create(arr_lin *x,int siz)
{
  
x->adj_list= malloc(sizeof(lin)*siz);
int i;
for(i=0;i<siz;i++)
 x->adj_list[i].flagg=0;
  x->lengthh=siz; 
return x;
}


void adj_free(arr_lin *x)
{
 
free(x->adj_list);
}

arr_lin * adj_set(arr_lin *x,int i,char *Sna,char *Ena,double le)
{ noo *n=malloc(sizeof(noo));
strcpy(x->adj_list[i].Fname,Sna);
x->adj_list[i].head=n;
//strcpy(x->adj_list[i].head->namee_,Ena);
strcpy(n->namee_,Ena);
//x->adj_list[i].head->dis=le;
n->dis=le;
n->next=NULL;
x->adj_list[i].flagg=1;

return x;
}

 arr_lin * adj_set2(arr_lin *x,int i,char *Ena,double le)
 {
noo *n=malloc(sizeof(noo));
noo *a=x->adj_list[i].head;
while(a->next!=NULL)
{
 a=a->next; 
}
a->next=n;

strcpy(n->namee_,Ena);
n->dis=le;
n->next=NULL;


  return x;
 }

arr_lin * adj_set3(arr_lin *x,st *p)
{ 
int count=0;
    while(count < p->ver)
   {
    
    if(x->adj_list[count].flagg != 0)
    x->adj_list[count].head=x->adj_list[count].head->next;
   count++;
   }
   return x;
}

st * create(st *p)
{
p->arr_heap = malloc(sizeof(no_)*(p->size));
return p;

}

void free_st(st *p)
{
free(p->arr_heap);
}



PQ * update(PQ *pq,arr_lin *x,HMAP_PTR ha,double prio,int i)
{
noo *b=x->adj_list[i].head;
while(b!=NULL)
{
  int *a;
a=hmap_get(ha,b->namee_);  
double p;
pq_get_priority(pq,*a,&p);
//printf("\n %s old %lf ",b->namee_,p);
if(prio+b->dis < p)
{pq_change_priority(pq,*a,prio+b->dis);
  pq_get_priority(pq,*a,&p);
 //printf(" new %lf \n",p);
 }
 b=b->next; 
}
//printf("\n");
 return pq; 
}







  


int main(int argc, char *argv[]){
    HMAP_PTR ha;
    arr_lin *l=malloc(sizeof(arr_lin)); 
    st *p=malloc(sizeof(st));
        int i=0;
        char line[40];
        //char line1[40];
        char n1[11];
        char n2[11];
        double dist;
        FILE * file = fopen(argv[1], "r");
        if(file==NULL)
            printf("\nCant open file\n");

            

while (fgets(line,sizeof(line),file) != NULL) 
     i++;
 

fclose(file);
file = fopen(argv[1], "r");



int j=0;
    while (fgets(line,sizeof(line),file) != NULL) 
    {  
        if(j==0)
            {sscanf(line,"%d",&p->ver); 
            p->size=(i-1)*2;
            p=create(p);
            l=adj_create(l,p->ver);
            ha= hmap_create(p->ver,1);
            j++;
            }   
        else
           {
            
            sscanf(line,"%s %s %lf",n1,n2,&dist);

            strcpy(p->arr_heap[j-1].start_pos, n1);
            strcpy(p->arr_heap[j-1].end_pos, n2);
            p->arr_heap[j-1].d=dist;

            strcpy(p->arr_heap[j].start_pos, n2);
            strcpy(p->arr_heap[j].end_pos, n1);
            p->arr_heap[j].d=dist;
          j=j+2;
          }
          
 
    }

    int count=0;
    int counter2=0; 
    int temp_var[p->ver];
/*
printf("\nThe strings are\n");
printf("number of vertices = %d\n", p->ver);
printf("number of connections = %d\n", p->size);
    
    
 
    while(count<p->size)
    {
     printf("%s", p->arr_heap[count].start_pos);
          printf(" %s ", p->arr_heap[count].end_pos);
          printf(" %lf ",p->arr_heap[count].d);
          printf("\n");
          count++;
    }
*/
count=0;

    while(count<p->size)
    {

     if(!hmap_contains(ha,p->arr_heap[count].start_pos))
      {
      //printf("%s", p->arr_heap[count].start_pos);
      temp_var[counter2]=counter2;
      hmap_set(ha,p->arr_heap[count].start_pos,&temp_var[counter2]);
      counter2++;
      //printf("\n");
      }
      if(!hmap_contains(ha,p->arr_heap[count].end_pos))
       { //printf("%s", p->arr_heap[count].end_pos);
         temp_var[counter2]=counter2;
         hmap_set(ha,p->arr_heap[count].end_pos,&temp_var[counter2]);
        
         counter2++;
        }
          count++;
        //printf("\n");

    }



count=0;
 int *a;
 int *b;
    while(count<p->size)
    {
     
      a=hmap_get(ha,p->arr_heap[count].start_pos);
 if(l->adj_list[*a].flagg == 0)
{l=adj_set(l,*a,p->arr_heap[count].start_pos,p->arr_heap[count].end_pos,p->arr_heap[count].d);
 }
          count++;
    }

count=0;
    while(count < p->size)
    {
      a=hmap_get(ha,p->arr_heap[count].start_pos);
    if(l->adj_list[*a].flagg != 0)
    {
      adj_set2(l,*a,p->arr_heap[count].end_pos,p->arr_heap[count].d);
      
    }
    count++;
   }
adj_set3(l,p);

/*
  
count=0;

    while(count < p->ver)
    {
    if(l->adj_list[count].flagg != 0)
    {
    printf("\n %d ",l->adj_list[count].flagg);
    printf(" %s ",l->adj_list[count].Fname);
    printf(" %s \n",l->adj_list[count].head->namee_);
    printf(" %lf \n",l->adj_list[count].head->dis);
    }
    count++;
   }
*/
/*
   noo *pq1=l->adj_list[0].head;
while(pq1!=NULL)
{printf("\n %s  %lf \n",pq1->namee_,pq1->dis);
pq1=pq1->next;
}
*/
count=0;
printf("\nWELCOME\nThe List of vertices are\n");
while(count<p->ver)
{
printf("\n %s\n",l->adj_list[count].Fname);
count++;
}  
char destination[11];
char source[11];
printf("\n Enter current location\n");
scanf("%s",&source);

printf("\n Enter Destination\n");
scanf("%s",&destination);



//destination=l->adj_list[0].Fname;
count =0;
PQ* pq= pq_create(p->ver, 1);
PQ* pq2= pq_create(p->ver, 1);
    while(count<p->ver)
     {
     
      
        a=hmap_get(ha,l->adj_list[count].Fname);
      if(strcmp(destination,l->adj_list[count].Fname)==0)
      pq_insert(pq, *a,0.0);
      else
        pq_insert(pq,*a,99999999999.0);        
     
     count++;
   }
/*
double as;

count=0;
while(count< p->ver)
  { 
    printf("\nadj list contains %s\n",l->adj_list[count].Fname);
printf("\nhmap contains %d\n",hmap_contains(ha,l->adj_list[count].Fname));
printf("\n priority queue %d\n",pq_get_priority(pq,count,&as) );
count++;
}
*/
//printf("\n priority queue %d\n",pq_get_priority(pq,4,&as) );
   //printf("\n %lf \n",pq->a[0]);
   count=0;
     double prio;
    
     while(pq_size(pq)!=0)
   {char *te;
    te=l->adj_list[count].Fname;
    a=hmap_get(ha,te);
    //printf("\na comtains ids as %d \n",*a);
//printf("\n deleteed ? %d \n",pq_get_priority(pq,*a,&prio));
     pq_delete_top(pq,&*a,&prio);
   //printf("\n deleteed ? %d \n",pq_get_priority(pq,*a,&prio));
     pq_insert(pq2, *a,prio);
     pq=update(pq,l,ha,prio,*a);
     count++;
   }
 
 /*
   count=0;
   while(count<p->ver)
   { double abcd;
    pq_get_priority(pq2,count,&abcd);
printf("yaa1   %lf\n",abcd);

count++;
   }
*/

   double idk;
   a=hmap_get(ha,source);
while(a!=hmap_get(ha,destination))
{ printf("\nThe\n");
if(pq_get_priority(pq2,*a,&idk)==99999999999.0)
  printf("\nDestination cant be reached\n");
else
{
  pq_get_priority(pq2,*a,&idk);
  printf("\nThe shortest path %lf \n",idk);
int counter3=1;
noo *ab=l->adj_list[*a].head;
printf("\n possible moves\n 0 I give up\n");

while(ab!=NULL)
{
printf("\n %d %s\n",counter3,ab->namee_);
 ab=ab->next; 
counter3++;
}
scanf("\n %d \n",&counter3);
if(counter3==0)
  {
    printf("\n returning\n");
    return 0;
  }
else
{count3=count3-1;
  int count4=1;
ab=l->adj_list[*a].head;
while(ab!=NULL)
{
if(count4==counter3)
 {   a=hmap_get(ha,ab->namee_);
  break;
}
ab=ab->next;
  count4++;

}

}

}
}
///////////////////////////////////

/*




struct Graph* graph = createGraph(p->ver);
    while(count<p->size)
    {addEdge(graph,p->arr_heap[count].start_pos, p->arr_heap[count].end_pos, p->arr_heap[count].d);
    count++;
    }
    dijkstra(graph, 0);
    
    //return 0;


*/



















//hmap_display(ha);


adj_free(l);
 //   free(l);
hmap_free(ha,0);
   free_st(p);
   

    }
    

