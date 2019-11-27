#include <stdio.h>
#include <stdlib.h>
void quicksort(float *v1,char *v2,int tam){
if(tam<=1)return;
float x=v1[0];
char  x2=v2[0];
int a=1,b=tam-1;
do{
while((a<tam)&&(v1[a]<=x))a++;
while(v1[b]>x)b--;
if(a<=b){
    float temp=v1[a];
    char  temp2=v2[a];
    v1[a]=v1[b];
    v2[a]=v2[b];
    v1[b]=temp;
    v2[b]=temp2;
    a++;b--;
}}while(a<=b);
v1[0]=v1[b];
v2[0]=v2[b];
v1[b]=x;
v2[b]=x2;
quicksort(v1,v2,b);
quicksort(&v1[b+1],&v2[b+1],tam-b-1);
}
void arqfreq(char *v1,float *v2){
FILE *fp1=fopen("freq.txt","rt");
if((!fp1))exit(1);
int r1;
char n1;
float n2;
r1=fscanf(fp1,"%c",&n1);
int i=0;
int j=0;
int cfreq=0;
while(r1!=EOF){
if(n1==37&&r1!=EOF){
r1=fscanf(fp1,"%c",&n1);
}
if(n1=='\n'&&r1!=EOF){
r1=fscanf(fp1,"%c",&n1);
}
while(n1==32&&r1!=EOF){
    r1=fscanf(fp1,"%c",&n1);
}
if(((n1>64&&n1<91)||(n1>96&&n1<123))&&r1!=EOF){
v1[i]=n1;
cfreq=1;
i++;
r1=fscanf(fp1,"%c",&n1);
}
if (cfreq==1){
r1=fscanf(fp1,"%f",&n2);
v2[j]=n2;
j++;
cfreq=0;}
r1=fscanf(fp1,"%c",&n1);
}fclose(fp1);
quicksort(v2,v1,52);
}
int main(){
char v1[52];
float v2[52];
arqfreq(v1,v2);
for(int n=0;n<52;n++)printf("%c ",v1[n]);
printf("\n");
for(int n=0;n<52;n++)printf("%f ",v2[n]);

	return 0;
}
