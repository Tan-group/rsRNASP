#include<stdio.h>
#include<math.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

double ***read_potential(char potential_file[], int intervals)
{
 int i, j;
 double ***p=(double ***)malloc(85*sizeof(double**));

 for(i=0;i<85;i++) 
  p[i]=(double **)malloc(85*sizeof(double*));
 
 for(i=0;i<85;i++)
  for(j=0;j<85;j++)
   p[i][j]=(double *)malloc(intervals*sizeof(double));

 FILE *p_f;
 int n1, n2, n3, nnn;

 p_f=fopen(potential_file,"r+");
 while(!feof(p_f))
 {
  for(n1=0;n1<85;n1++)
   for(n2=0;n2<85;n2++)
    for(n3=0;n3<intervals;n3++)
     fscanf(p_f,"%d %d %d %lf\n",&nnn,&nnn,&nnn,&p[n1][n2][n3]);
 }
 fclose(p_f);

  if(intervals != n3)
  {
   printf("Error---loading_potential---Error!\n");
   exit(-1);          
  }

 return p;
}

int read_pdb(char pdb_file[300], char type1[][5], char type2[][5], char type[][10], char chain[][5], char num[][10], float x[], float y[], float z[], int L)
{
 FILE *pdb_f;
 char aline[500], x1[L][10], y1[L][10], z1[L][10];
 int i, cc1, cc2, lll;

 pdb_f=fopen(pdb_file,"r+");
 
 i=0;
 memset(x1, 0, sizeof(x1));
 memset(y1, 0, sizeof(y1));
 memset(z1, 0, sizeof(z1));
 while(fgets(aline,500,pdb_f)!=NULL)
 {
  if(aline[0]=='A' && aline[1]=='T' && aline[2]=='O' && aline[3]=='M')
  {
   sprintf(type1[i],"%c%c%c",aline[13],aline[14],aline[15]);//atom_type
   if(type1[i][0]==' ')
    for(cc1=1;cc1<strlen(type1[i]);cc1++)
     if(type1[i][cc1]!=' ')
     {
      for(cc2=cc1;cc2<strlen(type1[i]);cc2++)
       type1[i][cc2-cc1]=type1[i][cc2];
      type1[i][cc2-1]='\0';
      break;
     }
   sprintf(type2[i],"%c",aline[19]);//residue_type
   sprintf(chain[i],"%c",aline[21]);//chain_type

   sprintf(num[i],"%c%c%c%c",aline[22],aline[23],aline[24],aline[25]);//residue_number
   sprintf(x1[i],"%c%c%c%c%c%c%c%c",aline[30],aline[31],aline[32],aline[33],aline[34],aline[35],aline[36],aline[37]);//x_coordinate
   x[i]=atof(x1[i]);
   sprintf(y1[i],"%c%c%c%c%c%c%c%c",aline[38],aline[39],aline[40],aline[41],aline[42],aline[43],aline[44],aline[45]);//y_coordinate
   y[i]=atof(y1[i]);
   sprintf(z1[i],"%c%c%c%c%c%c%c%c",aline[46],aline[47],aline[48],aline[49],aline[50],aline[51],aline[52],aline[53]);//z_coordinate
   z[i]=atof(z1[i]);

   sprintf(type[i],"%s%s",type2[i],type1[i]);
   for(lll=0;lll<strlen(type[i]);lll++)
    if(type[i][lll]==' ')
     type[i][lll]='\0';

   i++;
  }
  memset(aline,0,sizeof(aline));
 }
 return i;
}

double fun(int n)
{
 return -2685.0/sqrt(n+16) + 542.0;
}
int main(int argc, char *argv[])
{
 clock_t start,end;
 start=clock();

 float spendtime;

 int k1, k2, intervals1, intervals2, iii;
 double Rc1, Rc2;
 k1=2; k2=4;
 Rc1=13.0; Rc2=24.0;
 intervals1=43; intervals2=80;

//atomtype
/////////////////////////////////////////////////////////
 char atomtype[85][6];
 FILE *atom_type;
 iii=0;
 memset(atomtype,0,sizeof(atomtype));
 atom_type=fopen("data/85atom_type.dat","r+");
 while(!feof(atom_type))
 {
  fscanf(atom_type,"%s\n",atomtype[iii]);
  iii++;
 }
 fclose(atom_type);

/////////////////////////////////////////////////////////
//potential
/////////////////////////////////////////////////////////
 double ***potential1, ***potential2;
 potential1 = read_potential("data/short-ranged.potential", intervals1);
 potential2 = read_potential("data/long-ranged.potential", intervals2);
/////////////////////////////////////////////////////////

//read_pdb
/////////////////////////////////////////////////////////
 FILE *pdb_f;
 char aline[500];
 int Len;

 pdb_f=fopen(argv[1],"r+");
 Len=0;
 memset(aline,0,sizeof(aline));
 while(fgets(aline,500,pdb_f)!=NULL)
 {
  Len++;
  memset(aline,0,sizeof(aline));
 }

 int N;
 char type1[Len][5], type2[Len][5], type[Len][10], chain[Len][5], num[Len][10];
 float x[Len], y[Len], z[Len];
 memset(type1,0,sizeof(type1)); memset(type2,0,sizeof(type2)); memset(type,0,sizeof(type));
 memset(chain,0,sizeof(chain));
 memset(num,0,sizeof(num));
 memset(x,0,sizeof(x)); memset(y,0,sizeof(y)); memset(z,0,sizeof(z));

 N=read_pdb(argv[1], type1, type2, type, chain, num, x, y, z, Len);
/////////////////////////////////////////////////////////
//obtainig_energy
/////////////////////////////////////////////////////////
 int n1, n2, n3, n4, n5;
 double distance, energy, energy1, energy2;
 
 energy=0.0;
 for(n1=0;n1<N;n1++)
  for(n2=n1+1;n2<N;n2++)
   if(strcmp(num[n1], num[n2])!=0 || strcmp(chain[n1], chain[n2])!=0)
    for(n3=0;n3<85;n3++)
     if(strcmp(type[n1],atomtype[n3])==0)
     {
      for(n4=0;n4<85;n4++)
       if(strcmp(type[n2],atomtype[n4])==0)
       {
        distance=sqrt((x[n1]-x[n2])*(x[n1]-x[n2])+(y[n1]-y[n2])*(y[n1]-y[n2])+(z[n1]-z[n2])*(z[n1]-z[n2]));
        if(abs(atoi(num[n1])-atoi(num[n2]))>k2 || strcmp(chain[n1], chain[n2])!=0)//long-ranged
        {
         if(distance>0 && distance<=Rc2)
          for(n5=0;n5<intervals2;n5++)
           if(distance>n5*0.3 && distance<=(n5+1)*0.3)
           {
            energy2+=potential2[n3][n4][n5];
            break;
           }
        }
        else if(abs(atoi(num[n1])-atoi(num[n2]))>k1 && abs(atoi(num[n1])-atoi(num[n2]))<=k2 && strcmp(chain[n1], chain[n2])==0)//short-ranged
        {
         if(distance>0 && distance<=Rc1)
          for(n5=0;n5<intervals1;n5++)
           if(distance>n5*0.3 && distance<=(n5+1)*0.3)
           {
            energy1+=potential1[n3][n4][n5];
            break;
           }
        }
        break;
       }
     break;
    }
  
 int length;

 length=1;
 for(n1=0;n1<N-1;n1++)
  if(strcmp(type2[n1],type2[n1+1])!=0 || strcmp(num[n1],num[n1+1])!=0 || strcmp(chain[n1],chain[n1+1])!=0)
   length++;
 
 energy = energy1 + 16.0*energy2/fun(length);
 
 FILE *FP;
 FP = fopen(argv[2],"a+");
 fprintf(FP,"%s     %lf\n", argv[1], energy);
 
/////////////////////////////////////////////////////////

  int i, j;
  for(i=0;i<85;i++)
   for(j=0;j<85;j++)
    free(potential1[i][j]);
  for(i=0;i<85;i++)
   free(potential1[i]);
  free(potential1);

  for(i=0;i<85;i++)
   for(j=0;j<85;j++)
    free(potential2[i][j]);
  for(i=0;i<85;i++)
   free(potential2[i]);
  free(potential2);

  end = clock();
  spendtime = (float)(end-start)/(CLOCKS_PER_SEC);
  printf("the spendtime is %f s.\n",spendtime);

  return 6;
}



