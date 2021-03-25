//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <math.h>
#include <vcl.h>
#pragma hdrstop

#include "FruitFlyAlgorithm.h"
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
int p,e,iter,popsize,i,counter;
float x,gbest,gbestx;
float pop[1000][1],elit[2],f[1000];
FILE *g;

// Reset Variables....
for(p=0;p<1000;p++)
  for(e=0;e<1;e++)
     pop[p][e]=0.0;
for(p=0;p<1000;p++)
  f[p]=1000000.0;
for(p=0;p<2;p++)
  elit[p]=1000000.0;

gbest= 1000000.0;
counter=1;

// Assign Variable....
popsize=StrToInt(Edit1->Text);
iter=StrToInt(Edit2->Text);
   if(popsize>1000) popsize=1000;

if((g=fopen("c:\\fruit_fly_results.txt","w")) ==NULL)
   ShowMessage("The file couldn't be opened");

randomize();
continuation:

// Random Population Generation...
for(p=0;p<popsize;p++){
   again:
   x = 0.5 + 0.01*(rand()%251); // Random x generation within range...
   pop[p][0]=x;   // x passed the test...
   }

// Calculation of target functions...
for(p=0;p<popsize;p++){
  f[p] = sin(pow(pop[p][0],0.5)) - pop[p][0];
  if(fabs(f[p])<gbest) {gbest=fabs(f[p]);
                         gbestx=pop[p][0];}
  }
counter++;
if(counter<=iter) goto continuation;

Edit3->Text=FloatToStr(gbestx);
Edit4->Text=FloatToStr(gbest);

fprintf(g,"\nOptimum x = %4.5f \n",gbestx);
fprintf(g,"Target Function = %4.5f \n",gbest);
fclose(g);

ShowMessage("Fruit Fly Algorithm Complete");}
//---------------------------------------------------------------------------
