#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


using namespace std;


void external_sort (char *name){
  int a1, a2;
  FILE *f, *f1, *f2;
  int input_len = 0;
  f = fopen(name,"r");
  if ( !f )
    printf("FILE NOT FOUND");
  else {
    while ( !feof(f) ) {
      fscanf(f,"%d",&a1);
      input_len++;
    }
    fclose(f);
  }
  int serial_len = 1;
  int i, j;
  while ( serial_len < input_len ){
    f = fopen(name,"r");
    f1 = fopen("temp1.txt","w");
    f2 = fopen("temp2.txt","w");
    if ( !feof(f) ) fscanf(f,"%d",&a1);
    while ( !feof(f) ){
      for ( i = 0; i < serial_len && !feof(f) ; i++ ){
        fprintf(f1,"%d ",a1);
        fscanf(f,"%d",&a1);
      }
      for ( j = 0; j < serial_len && !feof(f) ; j++ ){
        fprintf(f2,"%d ",a1);
        fscanf(f,"%d",&a1);
      }
    }
    fclose(f2);
    fclose(f1);
    fclose(f);

    f = fopen(name,"w");
    f1 = fopen("temp1.txt","r");
    f2 = fopen("temp2.txt","r");
    if ( !feof(f1) ) fscanf(f1,"%d",&a1);
    if ( !feof(f2) ) fscanf(f2,"%d",&a2);
    while ( !feof(f1) && !feof(f2) ){
      i = 0;
      j = 0;
      while ( i < serial_len && j < serial_len && !feof(f1) && !feof(f2) ) {
        if ( a1 < a2 ) {
          fprintf(f,"%d ",a1);
          fscanf(f1,"%d",&a1);
          i++;
        }
        else {
          fprintf(f,"%d ",a2);
          fscanf(f2,"%d",&a2);
          j++;
        }
      }
      while ( i < serial_len && !feof(f1) ) {
        fprintf(f,"%d ",a1);
        fscanf(f1,"%d",&a1);
        i++;
      }
      while ( j < serial_len && !feof(f2) ) {
        fprintf(f,"%d ",a2);
        fscanf(f2,"%d",&a2);
        j++;
      }
    }
    while ( !feof(f1) ) {
      fprintf(f,"%d ",a1);
      fscanf(f1,"%d",&a1);
    }
    while ( !feof(f2) ) {
      fprintf(f,"%d ",a2);
      fscanf(f2,"%d",&a2);
    }
    fclose(f2);
    fclose(f1);
    fclose(f);
    serial_len *= 2;
  }
  //remove("temp1.txt");
  //remove("temp2.txt");
};


int main(){
	external_sort("input.txt");
	system("pause");
	return 0;
}