#include<iostream>
#include<sstream>
#include<malloc.h>
#include <time.h>
#include <stdlib.h>
#include <map>
#include<ctime>
#include<cmath>
#include<fstream>

using namespace std;

typedef int*   type_vector;
typedef bool*  type_bool;

int V, E, target_sol;
type_vector WE, PA,  tabu;  
type_bool in_clique;

bool **graph_array;
bool **missing_list;
long best_iteration;

int impr_n[2000][2000];
//int plateau[2000];

struct node 
{ 
  int vertex;
  int next;
  int previous;
};

int cq_first=-1; //First element in the clique, initialized to NULL.

struct OM_struct
{
   int om;
   int in_cq;
   int next;
   int previous;
};
struct OM_struct *OM;
struct node *clique;

int pac = 0, omc =0, cc = 0; // number of elements in POSSIBLE_ADD, ONE_MISSING, and CURRENT_CLIQUE sets
int OM_first = -1; // first elements of the OM set. Initialize it to NULL.

int current_cost, best_cost;

long int iteration = 0;
long int iter_without_improvement = 0;


void free()
{
   
   /* delete [] PA;
     delete [] WE;
    delete [] counter;
    delete [] in_clique;
    delete [] tabu;
    delete [] missing;*/
    for( int i = 0 ; i <=V ; i++)
    {
       delete [] graph_array[i];
       delete [] missing_list[i];
    }
    delete [] graph_array;
    delete [] missing_list;
}
/******************************************** CHECK CODE ***************************************************************/
/****************************************************************************************************************/
int check_missing_list(unsigned int * missing)
{
    int sum=0, miss;
    for(int j=1; j<=V; j++)
    {
       sum=0; miss=0;
       for(int i=1; i<=V; i++)
       {
          if(in_clique[i]==true and graph_array[i][j]==0 and missing_list[j][i] == 0)
          {
             cout<<"NOT IN MISSING LIST BUT SHOUMD BE "<<j<< "  "<<i<<endl; 
          }else  if(in_clique[i]==true and graph_array[i][j]==1 and missing_list[j][i] == 1)
          {
               cout<<"IN MISSING LIST BUT SHOULD NOT BE "<<j<< "  "<<i<<endl;
          }
          if(missing_list[j][i] == 1)
            miss++;
          if(in_clique[i]==true and graph_array[i][j]==0)
            sum++; 
       }
       if(missing[j]!=sum)
       {
           cout<<"TROUBLE IN MISSING LIST "<<sum<<"  "<<miss<<"  "<<missing[j]<<endl;
       }
    } 
}
void verify()
{
   int sum=0;
   bool wrong = false;
   int temp1 = cq_first, temp2=cq_first;
   while(temp1!=-1)
   {
     sum+=WE[clique[temp1].vertex];
   //  cout<<temp1->vertex<<"  ";
     while(temp2!=-1)
     {
         if(clique[temp1].vertex != clique[temp2].vertex and graph_array[clique[temp1].vertex][clique[temp2].vertex]==0)
         {
            wrong = true;
         }
         temp2 = clique[temp2].next;
     } temp1 = clique[temp1].next;
   }//cout<<endl;
   cout<<"Wrong "<<wrong <<"   Cost "<<sum<<endl;
}
/***********************************************************************************************************/
/****************************************************************************************************************/

void input_graph()
{
   char j1; string j2;
   int v1, v2;
 
   cin>>j1>>j2;
  
   cin>>V>> E;
   
   graph_array = new bool *[V+1];
   missing_list = new bool* [V+1];
   WE = new int[V+1];
   PA = new int [V+1];
  
   OM = new OM_struct [V+1];
   clique = new node [V+1];

   in_clique = new bool[V+1];
   tabu = new int[V+1];

   for( int i = 0 ; i <= V ; i++)
   {
       WE[i] =1;// (i%200) +1;
       
       graph_array[i] = new bool[V+1];
       missing_list[i] = new bool[V+1];
   }
   for( int i = 0 ; i <= V ; i++)
       for( int j = 0 ; j <= V ; j++)
          graph_array[i][j]=1;
  
   for(int i=0; i<E; i++)
   {
       cin>>j1>>v1>>v2;
       graph_array[v1][v2] = 0;
       graph_array[v2][v1] = 0;
   } 
}

void initialize(unsigned int * missing, type_vector & counter)
{
   pac = omc = cc = 0;
   OM_first = -1;
   cq_first = -1;
   for(int i=0; i<=V; i++)
   {
     tabu[i]=0;
     in_clique[i] = 0;
     missing[i] = 0;
  
     counter[i] = 0;
     OM[i].om = i;
     OM[i].in_cq = -1;
     OM[i].next = -1;
     OM[i].previous = -1;
     clique[i].vertex = -1;
     clique[i].next = -1;
     clique[i].previous = -1;
     for(int j=0; j<=V; j++) 
      missing_list[i][j]=0;
   }
   for(int i=0; i<=target_sol; i++)
      for(int j=0; j<=target_sol; j++)
        impr_n[i][j] = 0;
   iteration = 0;
}
bool remove_element_from_clique(int v)
{
   bool removed=true;
   if(clique[v].vertex!=-1)
   {
       clique[v].vertex = -1;
       if(clique[v].previous == -1)
         cq_first = clique[v].next;
       else
         clique[clique[v].previous].next = clique[v].next;
       if(clique[v].next == -1)
         clique[clique[v].previous].next=-1; 
       else
         clique[clique[v].next].previous = clique[v].previous;
     
        clique[v].next = -1; clique[v].previous = -1; 
   }else
      removed = false;
  return removed;
  
}
void add_element_in_clique(int v)
{
   if(clique[v].vertex!=-1) 
   {
      clique[v].vertex = v;
      cout<<"Something s wrong with clique"<<endl;
   }
   else
   {
      clique[v].vertex = v;
      if(cq_first==-1)
      {
        cq_first = v;
        clique[v].previous = -1;
        clique[v].next = -1;
      }   
      else
      {
        clique[cq_first].previous = v;
        clique[v].next = cq_first;
        clique[v].previous = -1;
        cq_first = v;
      }
  }
}
void add_in_ONE_MISSING_set(int not_cq, int in_cq)
{
   if(OM[not_cq].in_cq!=-1) 
   {
      OM[not_cq].in_cq = in_cq;
      cout<<"Something s wrong"<<endl;
   }
   else
   {
      OM[not_cq].in_cq = in_cq;
      if(OM_first==-1)
      {
        OM_first = not_cq;
        OM[not_cq].previous = -1;
        OM[not_cq].next = -1;
      }   
      else
      {
        OM[OM_first].previous = not_cq;
        OM[not_cq].next = OM_first;
        OM[not_cq].previous = -1;
        OM_first = not_cq;
      }
     omc++;
  }
}
int remove_from_ONE_MISSING_set(int not_cq)
{
   int in = OM[not_cq].in_cq;
   
   OM[not_cq].in_cq = -1;

   if(OM[not_cq].previous == -1)
     OM_first = OM[not_cq].next;
   else
       OM[OM[not_cq].previous].next = OM[not_cq].next;
   if(OM[not_cq].next == -1)
       OM[OM[not_cq].previous].next=-1; 
   else
       OM[OM[not_cq].next].previous = OM[not_cq].previous;
     
   OM[not_cq].next = -1; OM[not_cq].previous = -1; 
   omc--;
   return in;
}

void create_intial_sol()
{
   int random, i, init_vertex  = 1 + rand()%V;
   int temp;
   current_cost = 0;
   in_clique[init_vertex] = 1;
   current_cost+=WE[init_vertex];

   add_element_in_clique(init_vertex); cc++;
   pac=omc=cc=0;
   
   for(int i=1; i<=V; i++)
   {
      if(graph_array[i][init_vertex]==1 and in_clique[i]==false)
      {
          PA[pac] = i; 
          pac++;
      } 
   } 
   while(pac!=0)
   {
      random = rand()%pac;
      add_element_in_clique(PA[random]); cc++;
      in_clique[PA[random]] = 1;
      current_cost+=WE[PA[random]];
      temp = PA[random];
      PA[random] = PA[pac-1];
      pac--;
      
      for(i=0; i<pac; i++)
      {
         if(graph_array[temp][PA[i]]==0)
         {
            PA[i] = PA[pac-1]; pac--;
            i--;
         }
      }
      
   }
}

int only_element_from_missing_list(int index)
{
   for(int i=1; i<=V; i++)
   {
       if(missing_list[index][i]==1)
         return i;
   }
   return -1;
}
void create_initial_OM_PA_sets(unsigned int * missing, type_vector & counter)
{
   int i, x;
   int iter;
   for(i=1; i<=V; i++)
   {
      if(in_clique[i]==false)
      {
          iter = cq_first;
          while(iter!=-1)
          {
             if(graph_array[i][clique[iter].vertex]==1)
               counter[i]+=WE[clique[iter].vertex];
             else
             {
                missing_list[i][clique[iter].vertex]=1;
                missing[i]++;
             }
             iter=clique[iter].next;
          } 
      }
   }
   for(i=1; i<=V; i++)
   {
       if(missing[i]==1 and in_clique[i]==false)
       {
          x = only_element_from_missing_list(i);
          add_in_ONE_MISSING_set(i, x);
       }
       else if(missing[i]==0 and in_clique[i]==false)
       {
          PA[pac]=i;
          pac++;
       }
   }
}
bool delete_from_PA(int v)
{
   bool deleted = false;
   for(int i=0; i<pac; i++)
   {
      if(PA[i]==v)
      {
         PA[i]= PA[pac-1];
         pac--;
         deleted = true;
      }
   }return deleted;
}

void update_PA_OM_sets_after_insert(int v, unsigned int * missing, type_vector & counter)
{
    int smtg;
    for(int i=1; i<=V; i++)
    {
        if(graph_array[v][i]==0)
        {
              if(missing_list[i][v]==0)
              {
                 missing_list[i][v]= 1;
                 missing[i]++;
                if(missing[i]==1)
                {
                   delete_from_PA(i);
                   add_in_ONE_MISSING_set(i, v);
              
                } else if(missing[i]==2)
                {
                   smtg = remove_from_ONE_MISSING_set(i);   
                }
            }else  cout<<"AHHHAHA 111"<<endl;
        }
        else if(graph_array[v][i]==1 and v!=i and in_clique[i]==false)
             counter[i] +=WE[v];
    }
}

void update_PA_OM_sets_after_remove(int v, unsigned int * missing, type_vector & counter)
{
    int smtg;
    int x;
    for(int i=1; i<=V; i++)
    {
        if(graph_array[v][i]==0)
        {
         
            if(missing_list[i][v]==1)
            {
              missing_list[i][v] = 0;
              missing[i]--;
            }
             else cout<<"AHHHAHA 000"<<endl;
            

            if(missing[i]==0)
            {
               smtg = remove_from_ONE_MISSING_set(i); 
               if(in_clique[i]==0)
               {
                     PA[pac]= i;
                     pac++;
               }
               
            }else if(missing[i]==1)
            {
                x = only_element_from_missing_list(i);
                add_in_ONE_MISSING_set(i, x);   
                
            }  
        }
        else if(graph_array[v][i]==1 and v!=i and in_clique[i]==false)
             counter[i] -=WE[v];
    }
}

void remove(int v, unsigned int * missing, type_vector counter)  //Removing vertex from clique
{  
   in_clique[v] = 0; 
   bool removed = remove_element_from_clique(v);
   tabu[v] = iteration + 7; cc--;
   PA[pac]=v; pac++;
   update_PA_OM_sets_after_remove(v, missing, counter);
   if(removed==false) cout<<"NOT REMOVED FROM CLIQUE"<<endl;
   counter[v] = current_cost;
  // cout<<"After remove "<<endl;
   //check_counter_validity(counter);
}
void expand_move(int v_in, unsigned int * missing, type_vector & counter) // Inserting vertex from PA set to clique
{
    add_element_in_clique(v_in);  cc++;

    if(in_clique[v_in]==1) cout<<"Is already in clique"<<endl;

    in_clique[v_in] = 1; //Insert vertex in clique
    counter[v_in]=0;
    bool deleted = delete_from_PA(v_in); 
    
    if(missing[v_in]>0)
      cout<<"Missing list should be empty"<<endl;
    if(OM[v_in].in_cq != -1) cout<<"Should be -1 "<<OM[v_in].in_cq<<"  "<<missing[v_in]<<endl;

    update_PA_OM_sets_after_insert(v_in, missing, counter);
   // cout<<"After expand "<<endl;
   //check_counter_validity(counter); 
}
void swap_move(int v_in, int v_out, unsigned int * missing, type_vector counter)
{

  if(in_clique[v_in]==1) cout<<"SHOULD NOT BE IN CLIQUE "<<v_in<<"  "<<missing[v_in]<<"  "<<missing[v_out]<<endl;
    if(in_clique[v_out]==0) cout<<"SHOULD BE IN CLIQUE "<<v_out<<"  "<<missing[v_out]<<endl;
  // cout<<"AFTER SWAP "<<v_in<<"  "<<v_out<<"   WEIGHTS "<<WE[v_in]<<"  "<<WE[v_out]<<endl;
    // ALSO CONSIDER SPECIAL CASE, IS ALREADY IN CLIQUE BUT SHOUDNT BE 
   if(missing[v_in]==1 and missing[v_out]==0)  
   {
        if(in_clique[v_in]==0)
        {
             in_clique[v_in] = 1; //Insert vertex in clique
             in_clique[v_out] = 0;
             add_element_in_clique(v_in);
             update_PA_OM_sets_after_insert(v_in, missing, counter);
             counter[v_in] = 0;
        } 
        if(in_clique[v_in]==1)
        {
           // in_clique[v_out] = 0;
            bool removed = remove_element_from_clique(v_out);
            update_PA_OM_sets_after_remove(v_out, missing, counter); 
            counter[v_out] = current_cost - WE[v_in];
           if(removed==false) cout<<"NOT REMOVED "<<v_out<<" FROM CLIQUE"<<endl; 
        }
          tabu[v_out] = iteration + 7 + rand()%(omc+1);
   }else cout<<"REAL TROUBLE "<<missing[v_in]<<"  "<<missing[v_out]<<endl;
   
  // check_counter_validity(counter); 
}
bool descent(unsigned int * missing, type_vector counter) 
{
   // The neighorhood is the union of expand ans swap moves.
   int gain = 0;
   type_vector V_in = new int[V];

   type_vector move_type = new int[V]; // 1 if expand, 2 if swap;
   int inc=0;

   for(int i=0; i< pac; i++)
   {
       if(WE[PA[i]]>gain)
       {
          gain = WE[PA[i]];
          inc=0;
          V_in[inc] = i;
          move_type[inc] = 1;
          inc++;
       }else if(WE[PA[i]]==gain and gain!=0)
        {
            V_in[inc] = i;
            move_type[inc] = 1;
            inc++;
        }
   }
  int iter = OM_first;
   int brojac=0;
   while(iter!=-1)
   {  
      brojac++;
      if((WE[OM[iter].om] - WE[OM[iter].in_cq])>gain)
      {
         gain = WE[OM[iter].om] - WE[OM[iter].in_cq];
         inc = 0; 
         V_in[inc] = iter;
         move_type[inc] = 2;
         inc++;
      }else if((WE[OM[iter].om] - WE[OM[iter].in_cq])==gain and gain!=0)
      {
          V_in[inc] = iter;
          move_type[inc] = 2;
          inc++;
      }
      iter = OM[iter].next;
   } 
   if(gain==0)
   impr_n[current_cost][brojac]++;
   int random;
   
   //cout<<"INC "<<inc<<"  "<<current_cost<<"   "<<gain<<endl; 
   if(gain>0)
   {
        
        random = rand()%inc;
        if(move_type[random]==1) 
        {
           current_cost+=WE[PA[V_in[random]]]; 
           expand_move(PA[V_in[random]], missing, counter);  
        }
        else if(move_type[random]==2) 
        {
              current_cost+=(WE[OM[V_in[random]].om]-WE[OM[V_in[random]].in_cq]); 
             swap_move(OM[V_in[random]].om, OM[V_in[random]].in_cq, missing, counter);  
         }
    }
   iteration++;
   delete [] V_in;
   delete []move_type;

   if(gain>0) return 0; else return 1;
}

void random_perturbe(int pstr, double percentage, unsigned int * missing, type_vector counter)
{
   int random;
   int iter;
   type_vector v_to_clique = new int[V+1];
   int vtc=0;
   int V_rm[V+1];
   int vrm=0;
   
   for(int i=0; i<pstr; i++)
   {
       vtc=0;
      for(int g=1; g<=V; g++)
      {
         if(counter[g]!=0 and in_clique[g]==0 and (counter[g]+ WE[g])>(current_cost*percentage))// or counter[g]==(cc-3) or counter[g]==(cc-4)))
         {
           v_to_clique[vtc] = g;
           vtc++;
         }
      } 
     if(vtc!=0)
     {
        random = v_to_clique[rand()%vtc];
        vrm=0;
        
        iter = cq_first;
        while(iter!=-1)
        {
           if(graph_array[random][clique[iter].vertex]==0 and clique[iter].vertex!=random)
           {
             V_rm[vrm] = clique[iter].vertex;
             vrm++;        
           }
           iter = clique[iter].next;
        }  
     
         for(int i=0; i<vrm; i++)
         { 
            current_cost-=WE[V_rm[i]]; 
            remove(V_rm[i], missing, counter);
         }
         current_cost+=WE[random]; 
        expand_move(random, missing, counter);
  } iteration++;
   }
   
   delete [] v_to_clique;
}
void directed_perturbe2(int pstr, unsigned int * missing, type_vector counter)
{
   int random;
   int iter;
   type_vector v_to_clique = new int[V+1];
   int vtc=0;
   int V_rm[V+1];
   int vrm=0;
   int gain;
   int smtg;
   for(int i=0; i<pstr; i++)
   {
      gain = 9999999;
      //cout<<"Biggin"<<endl;
       vtc=0;
      for(int g=1; g<=V; g++)
      {
         smtg = counter[g] + WE[g];
         if(in_clique[g]==0 and (((current_cost - smtg) < gain and tabu[g]<iteration) or smtg>best_cost))
         {
            
           if((counter[g]+WE[g])>best_cost)
           {
               cout<<"ASPIRATION YUPPPIII "<<counter[g]+WE[g]<<"  best cost "<<best_cost<<"    GAIN "<<current_cost - (counter[g] + WE[g])<<endl;
           //    verify();
             //  best_cost = counter[g]+WE[g];
           }
           vtc=0;
           v_to_clique[vtc] = g;
           gain = current_cost - smtg;
          
         }else if(in_clique[g]==0 and ((current_cost - smtg) == gain and tabu[g]<iteration) or smtg>best_cost)
         {
            v_to_clique[vtc] = g;
            vtc++;
         }
        
      }
    
     if(vtc!=0)
     {
        random = v_to_clique[rand()%vtc];
        vrm=0;        
        iter = cq_first;
        while(iter!=-1)
        {
           if(graph_array[random][clique[iter].vertex]==0 and clique[iter].vertex!=random)
           {
             V_rm[vrm] = clique[iter].vertex;
             vrm++;        
           }
           iter = clique[iter].next;
        }  
     
         for(int i=0; i<vrm; i++)
         { 
            current_cost-=WE[V_rm[i]]; 
            remove(V_rm[i], missing, counter);
           // check_missing_list();
            //check_ONE_MISSING_set();
         }
         current_cost+=WE[random]; 
        expand_move(random, missing, counter);
        
      } 
     if(best_cost<current_cost)
    {
               best_cost=current_cost;
               iter_without_improvement = 0;
               cout<<"Best check "<<best_cost<<"  "<<iteration<<"  best gain  "<<gain<<endl;
                verify();
   } 
   iteration++;
 }
   delete [] v_to_clique;
}
void directed_perturbe(int pstr, unsigned int * missing, type_vector counter)
{
   int gain = -999999;
   type_vector V_in = new int[V];
  
   type_vector move_type = new int[V]; // 1 if expand, 2 if swap, 3 if remove one vertex from clique
   int inc=0;
   for(int r=0; r<pstr; r++)
   {
      //cout<<"OMC "<<omc<<"  "<<pac<<endl;
       gain=-999999; inc=0;
       for(int i=0; i< pac; i++)
       {
          if(WE[PA[i]]>gain and (tabu[PA[i]]<iteration or (WE[PA[i]] + current_cost)>best_cost))
          {
              gain = WE[PA[i]];
              inc=0;
              V_in[inc] = i;
              move_type[inc] = 1;
              inc++;
          }else if(WE[PA[i]]==gain and (tabu[PA[i]]<iteration or (WE[PA[i]] + current_cost)>best_cost))
          {
              V_in[inc] = i;
              move_type[inc] = 1;
              inc++;
          }
     }

   int iter = OM_first; //cout<<"started"<<endl; int coun=0; bool ended_brutally = false;

 //cout<<"This"<<endl;
  while(iter!=-1)
   {  
      if((WE[OM[iter].om] - WE[OM[iter].in_cq])>gain and (tabu[OM[iter].om]<iteration or (current_cost + WE[OM[iter].om] - WE[OM[iter].in_cq])>best_cost))
      {
         gain = WE[OM[iter].om] - WE[OM[iter].in_cq];
         inc = 0; 
         V_in[inc] = iter;
         move_type[inc] = 2;
         inc++;
      }else if((WE[OM[iter].om] - WE[OM[iter].in_cq])==gain and (tabu[OM[iter].om]<iteration or (current_cost + WE[OM[iter].om] - WE[OM[iter].in_cq])>best_cost))
      {
          V_in[inc] = iter;
          move_type[inc] = 2;
          inc++;
      }
      iter = OM[iter].next;
   }
   //  cout<<"Ended stupid loop"<<endl;
    int temp = cq_first;
     while(temp!=-1)
     {
        if((-WE[clique[temp].vertex])>gain)
        {
              gain = -WE[clique[temp].vertex];
              inc=0;
              V_in[inc] = clique[temp].vertex;
              move_type[inc] = 3;
              inc++;
          }else if((-WE[clique[temp].vertex])==gain)
          {
              V_in[inc] = clique[temp].vertex;
              move_type[inc] = 3;
              inc++;
          }
        temp=clique[temp].next;
     } 
     int random;

    if(inc>0)
    {
     random = rand()%inc;
     if(move_type[random]==1) 
     {
         current_cost+=WE[PA[V_in[random]]];
         expand_move(PA[V_in[random]], missing, counter);
      }
      else if (move_type[random]==2) 
      {
               current_cost+=(WE[OM[V_in[random]].om]-WE[OM[V_in[random]].in_cq]); 
               swap_move(OM[V_in[random]].om, OM[V_in[random]].in_cq, missing, counter); 
       }else
       {
           current_cost-=WE[V_in[random]];
           remove(V_in[random], missing, counter);
           
       }
   
     }
     if(current_cost>best_cost)
     {
        best_iteration = iteration;
        best_cost = current_cost;
        cout<<"Improved solution "<<best_cost<<endl;
        iter_without_improvement=0;
     }
     iteration++;
   /*  if(pstr>(0.1*V))
     {
       pstr = V*0.1;
       cout<<"Problem "<<r<<"  "<<pstr<<endl;
     }*/
   } //cout<<"EXited dp"<<endl;
     delete [] V_in;
   delete []move_type;
}
bool returned_to_previous_local_opt(bool * previous_sol)
{
   for(int i=1; i<=V; i++)
   {
      if(in_clique[i] != previous_sol[i])
        return false;
   }
   return true;
}
void print_missing_list(unsigned int *missing)
{
   int checkOM=0, checkPA=0;
   for(int i=1; i<=V; i++)
   { 
      if(missing[i]>0 and in_clique[i]==true) cout<<"TROUBLE "<<cc<<endl;
      if(missing[i]==1)
      {
          checkOM++;
      }else if(missing[i]==0 and in_clique[i]==false)
         checkPA++;
   }
   if(checkOM!=omc) cout<<"Not same num as in ml om "<<checkOM<<"  "<<omc<<endl;
   if(checkPA!=pac) cout<<"Not same num as in ml pa "<<checkPA<<"  "<<pac<<endl;
}
void print_ONE_MISSING_set()
{
   cout<<"Printing one missing set"<<endl;
   int iter = OM_first;
   while(iter!=-1)
   {
      cout<<OM[iter].om<<"  "<<OM[iter].in_cq<<endl;
      iter = OM[iter].next;
   }cout<<"---------"<<endl;
}
int BLS(long num_iter, unsigned int * missing, type_vector  counter)
{
   best_cost=current_cost;
    bool local_optimum = 0;
    double d, e;
    int perturb_str = 10;
    bool* previous_sol = new bool[V+1];
    bool restart =false;
    bool returned_to_lo, perturbed_once = false;
   
    for(long long int i=0; i<num_iter; i++)
    {
         
        if(local_optimum==0)
        {
            local_optimum = descent(missing, counter);     
             perturbed_once = false;
             if(best_cost<current_cost)
             {
                 best_cost=current_cost;
                 best_iteration = iteration;
                 iter_without_improvement = 0;
                 cout<<"Improved solution "<<best_cost<<endl;
                 // verify();
              }
        }
        else
        {  
           //No improvement on the best found solution has happened for more than T = 1000 descent phases. (T is the max. number of non-improving attractors visited before strong perturb. ) 
 
           if(iter_without_improvement > 1000)
           {
              iter_without_improvement=0;
              perturb_str= static_cast<int>(V*0.1); // In this case, apply a restart. Here, the parameter Lmax = V*0.1
              restart = true;
   
           }
           else
           { 
               restart = false;
               returned_to_lo = returned_to_previous_local_opt(previous_sol);
               if((perturbed_once==false and returned_to_lo==false) or (perturbed_once and returned_to_lo==false))
              // Escaped from the previous local optimum. New local optimum reached
               {
                  iter_without_improvement++;
                  perturb_str= static_cast<int>(V*0.01); //Here, initial jump magnitude L0 = V*0.01
               }
               else if(returned_to_lo)
               {
                   perturb_str+= 1; // increment of the jump magnitude
              }
           }
          
           //Save previous local optimum

           for(int j=1; j<=V; j++)
              previous_sol[j] = in_clique[j];
 
           d = static_cast<double>(iter_without_improvement)/1000;
           e = pow(2.718, -d);
           if(e<0.75) e=0.75; // Here, e=0.75 denotes the smallest probability for applying directed perturb. (e is denoted as P0 in the COR paper). For some instances, it is the best to apply directed perturbation all the time (then P0 = 1).

    
           //Apply perturbation part
           if(restart)
               random_perturbe(perturb_str, 0.8, missing, counter); //Here, coefficient for random pertur. alpha_r = 0.8  
            else if(e>(static_cast<double>(rand()%101)/100.0)) 
           {
                  directed_perturbe(perturb_str, missing, counter);         
          }
          else
          {
               random_perturbe(perturb_str, 0.8, missing, counter); // Strongest perturbation like restart
          }
         
          local_optimum=0;
          perturbed_once = true;
       } 
         // This is the stopping condition of the algorithm. If you want the algo to stop earlier, reduce the number of iterations.
         if(iteration>16000000000 or best_cost ==target_sol) break;
 
    } 
    delete [] previous_sol;
    return best_cost;
}

int main()
{
   int type=2, n1, n2; // Here, type denotes the problem type. If type=1, we want to solve the maximum unweighted clique problem. If type =2, we want to consider the weighted clique problem
   int best_result = 0;
   int cost;
   double avg=0.0, avg_time=0.0;
   long long int avg_iter=0;
   int num_runs = 20; // The number of independent runs
   srand ( time(NULL) );
   string file_name; // Beside the graph, this algorithms requires as input the file name, followed by the optimal values in case of unweighted and weightd clique respectively. 
   getline(cin, file_name); // Input file name
   cin>>n1>>n2; //Input n1 (optimal value for unweighted clique), n2 (optimal value for weighted clique)
   if(type==1)
     target_sol = n1;
   else
     target_sol = n2;
   file_name.append("LS_exp3.out");
   char una[70];
   for(int i=0; i<file_name.size(); i++)
      una[i]=file_name[i];
   una[file_name.size()]=0;
   ofstream out;
   out.open(una);

   input_graph(); // Input the given graph.
   type_vector counter = new int[V+1];
   unsigned int * missing = new unsigned int[V+1];
  clock_t start, time;
  for(int i=0; i<num_runs; i++)
  {
      start = clock();
      initialize(missing, counter);
      create_intial_sol();
      create_initial_OM_PA_sets(missing, counter);

     cost = BLS(100000000000, missing, counter);
    cout<<"DONE"<<endl;
     time = clock()-start;
     avg_iter+=best_iteration;
     out<<cost<<"    "<<best_iteration<<"   "<<time/static_cast<double>(CLOCKS_PER_SEC)<<endl;

     avg_time+=time/static_cast<double>(CLOCKS_PER_SEC);
     avg+=cost;
     if(cost>best_result)
        best_result = cost;
     
   }

  out<<"Best "<<best_result<<endl;
  out<<"Avg cost "<<avg/static_cast<double>(num_runs)<<endl;
  out<<"Avg iter num "<<avg_iter/static_cast<double>(num_runs)<<endl;
  out<<"Avg time in sec "<<avg_time/static_cast<double>(num_runs)<<endl;
   cout<<avg/static_cast<double>(num_runs)<<endl;

   free();
}
