//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <math.h>
#include <vcl.h>
#pragma hdrstop

#include "BatAlgorithm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
// What is the root value of the function y = x ^ 3 + 15 * x ^ 2 -514 * x +960
// The first random interval x [-30,13]

int x,popsize,iter,counter;
float d,gama,alpha,m,beta;
float f[100],pop[100],rpulse[100],loud[100],v[100],gbest;
float fmin,fmax,avloud,gbestx;
FILE *g;

// Assign Variable....
popsize=StrToInt(Edit1->Text); // population...
iter=StrToInt(Edit2->Text);    // iteration...
alpha=StrToFloat(Edit6->Text); // loudness...
gama=StrToFloat(Edit3->Text);  // pulse rate...

if(popsize>100) popsize=100;

for(x=0;x<100;x++){
  pop[x]=0.0;      // x values...
  f[x]=0.0;        // frequency...
  rpulse[x]=0.0;   // pulse rate...
  loud[x]=0.0;     // loudness...
  v[x]=0.0;}       // velocity...

// Initial variable assignments........
fmin=0.0;
fmax=0.001;
gbest=1000000.0;
randomize();
counter=1;

avloud=0.0;

// Noise average assignment........
for(x=0;x<popsize;x++){
     loud[x]=0.001*(rand()%1000);
     avloud=avloud+loud[x];}
avloud=avloud/popsize;

// Assignment of signal rates.....
for(x=0;x<popsize;x++){
     rpulse[x]=1-0.5*0.001*(rand()%1000);
     }
loop:

// Random Population Generation...
for(x=0;x<popsize;x++){
   pop[x] = -30 + 0.1*(rand()%431);  // Random generation of x in [1,3]...
   f[x] = pow(pop[x],3) + 15*(pow(pop[x],2)) - 514*pop[x] + 960; // Target function... if(fabs(f[x])<gbest) {gbest=fabs(f[x]);
      if(fabs(f[x])<gbest) {gbest=fabs(f[x]);
                         gbestx=pop[x];}
   }

for(x=0;x<popsize;x++){
  d=0.001*(rand()%1000);
  if(d<rpulse[x])  {

// Local research for x.bat......................
        for(x=0;x<popsize;x++)
          pop[x]=gbestx;

        for(x=0;x<popsize;x++){
          m=0.001*(rand()%2000)-1.0;
          pop[x]=pop[x]+ m*avloud;}
        }
  else  {

// Random research for x.bat.......................
          for(x=0;x<popsize;x++){
              beta=(rand()%1000)/1000.0;
              f[x]=fmin+(fmax-fmin)*beta;
              }
          for(x=0;x<popsize;x++){
                 v[x]=v[x]+(gbestx-pop[x])*f[x];
                }

          for(x=0;x<popsize;x++){
              pop[x]=pop[x]+v[x];
              }
         }
  }
counter=counter+1;

// Update loudness & pulse rate..................
for(x=0;x<popsize;x++){
     loud[x]=alpha*loud[x];
     rpulse[x]=1.0-0.5*pow(gama,counter);
   }
if(counter<iter) goto loop;

Edit4->Text=FloatToStr(gbest);
Edit5->Text=FloatToStr(gbestx);

// Write results to file.....
if((g=fopen("c:\\bat_results.txt","w")) ==NULL)
   ShowMessage("The file couldn't be opened");
fprintf(g,"Optimum x=%4.4f \n",gbestx);
fprintf(g,"Maximum Target Function=%4.4f \n",gbest);
fclose(g);

ShowMessage("Bat Algorithm Complete");

}
//---------------------------------------------------------------------------
 