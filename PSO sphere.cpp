#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<fstream>
#include <iomanip>

using namespace std ;
const int n=5;                     // problem dimesion
const int np=n+1;                  //fitness value
const int tp=50;                // population size(swarm size)
double pop[tp][np],x[n],l,U, vx[tp][n],pbest[tp][np],mini; //mini for gbest
double fun(double []);
int main()
  {       
    int i,j,best,iteration =0;
    double w, r1, r2, c1 = 2.0, c2 = 2.0;  
    cout<<"enter the lower and upper bounds    ";
    cin>>l>>U;
  	iteration=0;
  	srand(time(0)); //here time seed are used for generating random no.
      
    for(i=0;i<tp;i++)                            // initial population
    {
        for(j=0;j<n;j++)
            {
                x[j]=l+(U-l)*((float)rand()/RAND_MAX);
                pop[i][j]=x[j];
                vx[i][j] = l+(U-l)*((float)rand()/RAND_MAX);
                pbest[i][j] = pop[i][j];
            }
        pbest[i][j] = pop[i][j] = fun(x);
    }
    
    
    mini = pbest[0][n];
    best = 0;
      
      
    for(i=0;i<tp;i++)                            
    {
        if(pbest[i][n]<mini)
        {
            mini = pbest[i][n];
            best = i;
        }
    }    
                          
   while(iteration < 25)   //loop for No. of simulations
   {
       w=0.9-((0.9-0.4)/10)*iteration;  //Linearly Decreasing Inertia Weight
       iteration++;
       for(i=0;i<tp;i++)   //Loop for number of particles
       {
           for(j=0;j<n;j++)  //Loop for number of decision variables
           {
               r1=(float)rand()/RAND_MAX;  // r1 and r2 are U(0,1)
               r2=(float)rand()/RAND_MAX;
               vx[i][j] = w*vx[i][j] +c1*r1*(pbest[i][j] - pop[i][j]) +
				                     c2*r2*(pbest[best][j] - pop[i][j]); //Velocity Update
               pop[i][j] = pop[i][j] + vx[i][j];   //Position Update
               while(pop[i][j]<l)   //Variable Bounds
               {
                   pop[i][j] = l;
               }
               while(pop[i][j]>U)
               {
                   pop[i][j] = U;
               }
           }
       }
       for(i =0; i<tp;i++)    //Choosing pbest
       {
           pop[i][n] = fun(pop[i]);
           if(pop[i][n]<pbest[i][n])
         {
           for(j =0;j<=n;j++)
           pbest[i][j] =pop[i][j];
         }
       if(pop[i][n]<pbest[best][n])  //Choosing gbest
       best = i;
       }
	  
	  cout<<iteration<<"\t";
     cout<<fun(pbest[best]);
     cout<<endl;
   }

   for(j=0; j<n; j++)					//Final Solution
     cout<<pbest[best][j]<<"\t";
   cout<<"\t";
     cout<<fun(pbest[best]);

    return 0;
}                           
                  
   
 //*************** sphere function *******************//
double fun(double x[])
   {
 
 double f = 0;
        for ( int i = 0; i < n; i++ )
        {
          
          f = f + x[i] * x[i];
        }
       return f;
   }
