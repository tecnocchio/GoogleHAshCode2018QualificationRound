/*
Hash Code 2018, team '123Prova'

Assign rides to vehicles choosing first one to start
Get perfect score with data sets:
        10 - 'A - example'
   176,877 - 'B - should be easy'
21,465,945 - 'E - high bonus'
*/

#include<stdio.h>
#include<math.h>

#define DIE(a) {fprintf(stderr,a"\n",*v);return 1;}
#define DIST(a,b,x,y) (abs((a)-(x))+abs((b)-(y)))
#define MAX(a,b) ((a)>(b)?(a):(b))

FILE*fp;
int R,C,F,N,B,T,
    a[10000],b[10000],x[10000],y[10000],s[10000],f[10000],
    D[10000], //rides' length
    L[400]={0},X[400]={0},Y[400]={0}, //local time and position of vehicles
    P[400]={0}, //number of rides assigned to each vehicle
    O[400][512], //O[j][k]: 'k'-th ride assigned to vehicle 'j'
    S=0, //score
    i,j,k,t,m,M;

int main(int u,char**v){

	if(u!=3)
		DIE("Assign rides to vehicles (to be used with A, B, and E data sets)\n"
		    "  Usage: %s InputFile OutputFile")

	//read data
	if(!(fp=fopen(*++v,"r")))
		DIE("File \"%s\" not found!")
	fscanf(fp,"%d%d%d%d%d%d\n",&R,&C,&F,&N,&B,&T);
	printf("R=%d\nC=%d\nF=%d\nN=%d\nB=%d\nT=%d\n\n",R,C,F,N,B,T);
	for(i=0;i<N;i++){
		fscanf(fp,"%d%d%d%d%d%d\n",&a[i],&b[i],&x[i],&y[i],&s[i],&f[i]);
		D[i]=DIST(a[i],b[i],x[i],y[i]);} //ride's length
	fclose(fp);

	//repeat until local time of all vehicles is 'T'
	for(;;){
		//find the vehicle 'j' with minimum local time
		t=T;
		for(i=0;i<F;i++)
			if(t>L[i]){t=L[i];j=i;}
		if(t>=T)break;
		//find the ride 'k' that vehicle 'j' can start first
		m=T;
		for(i=0;i<N;i++)
			if(f[i]>=t+DIST(X[j],Y[j],a[i],b[i])+D[i]){
				M=MAX(t+DIST(X[j],Y[j],a[i],b[i]),s[i]); //time at which vehicle 'j' would start ride 'i'
				if(m>M){m=M;k=i;}}
		if(m==T){L[j]=T;continue;}
		//assign ride 'k' to vehicle 'j' and then update local variables and score
		f[k]=0;
		O[j][P[j]++]=k;
		X[j]=x[k];
		Y[j]=y[k];
		L[j]=D[k]+m;
		S+=D[k]+B*(m==s[k]);}

	printf("Score=%d\n",S);

	//save rides' schedule
	if(!(fp=fopen(*++v,"wb")))
		DIE("Cannot write to file \"%s\"!")
	for(j=0;j<F;j++){
		fprintf(fp,"%d",P[j]);
		for(k=0;k<P[j];k++)
			fprintf(fp," %d",O[j][k]);
		fprintf(fp,"\n");}
	fclose(fp);}
