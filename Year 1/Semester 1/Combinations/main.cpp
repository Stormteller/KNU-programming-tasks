#include <iostream>

using namespace std;
 
int n;
int mas[100]; 
void comb(int i)
{ int j, t;
  if(i==n)
  { for(i=0; i<n; ++i)
  cout << mas[i] << " "; 
  if(!(i<n-1)) ;
   cout <<'\n';
    return;
  }
  for(j=i; j<n; ++j)
  { if(i!=j && mas[i]==mas[j]) 
      continue;
    t=mas[i];
	mas[i]=mas[j];
    mas[j]=t;
    comb(i+1);
  }
  t=mas[i];
  for(j=i+1; j<n; ++j)
	  mas[j-1]=mas[j];
  mas[n-1]=t;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	mas[i] = i+1;
	comb(0);
	system("pause");
	return 0;
}