#include <bits/stdc++.h>
using namespace std;
int arbol[9999999];
int cambios[9999999];
void construir(int i, int j, int p, int arr[])
{
	if(i==j)
	{	
		if(arr[i]>0)
			arbol[p]=1;
		else
		{
			if(arr[i]<0)
				arbol[p]=-1;
			else
				arbol[p]=0;
		}
		//cout<<" arbol de: "<<p<<" tiene: "<<arbol[p]<<" por: "<<arr[i]<<" intervalo "<<i<<" "<<j<<endl;
		return ;
	}
	construir(i,(i+j)/2,p<<1,arr);
	construir(((i+j)/2)+1,j,(p<<1)+1,arr);
	if(arbol[2*p]*arbol[(2*p)+1]>0)
	{
		arbol[p]=1;
	}
	else
	{
		if(arbol[2*p]*arbol[(2*p)+1]<0)
			arbol[p]=-1;
		else 
			arbol[p]=0;
	}
	//cout<<" arbol de : "<<p<<" tiene: "<<arbol[p]<<" intervalo "<<i<<" "<<j<<endl;
}
void propagar (int p, int i, int j)
{
	if (cambios[p]==2)
		return;
	if(cambios[p]>0 and cambios[p]!=2)
		arbol[p]=1;
	else 
	{
		if(cambios[p]<0)
			arbol[p]=-1;
		else
			arbol[p]=0;
	}
	if(i!=j)
	{
		
		cambios[p<<1]=cambios[p];
		cambios[(p<<1)+1]=cambios[p];
	}
	cambios[p]=2;

}
int consul(int i,int j, int p, int a, int b)
{
//			cout<<" intervalo: "<<a<<" "<<b<<"   de: "<<i<<"  "<<j<<" p: es "<<p<<"  contenido "<<arbol[p]<<endl;

	if(a>j||b<i)
		return 1;
	//cout<<" intervalo: "<<a<<" "<<b<<" "<<" p: es "<<p<<"  contenido "<<arbol[p]<<"  combios de p: "<<cambios[p]<<endl;
	//propagar(p,i,j);
	
	if(i>=a and j<=b)
	{


		return arbol[p];
	}

	int izq=consul(i,(i+j)/2,p<<1,a,b);
	int der=consul(((i+j)/2)+1,j,(p<<1)+1,a,b);
	
	//cout<<" intervalo: "<<a<<" "<<b<<" "<<" p: es "<<p<<"  contenido "<<arbol[p]<<"  combios de p: "<<cambios[p]<<endl;


	return izq*der;
}
void actualizar (int p, int valor,int i, int j, int a, int b )
{
	//cout<<p<<" "<<i<<" "<<j<<"\n";
	//if (p>50) return;
	//cout<<" intervalo: "<<a<<" "<<b<<" "<<" p: es "<<p<<"  contenido "<<arbol[p]<<"  combios de p: "<<cambios[p]<<endl;
	//propagar(p,i,j);
	if(a>j || b<i)
		return ;
	if(i>=a&&j<=b)
	{
		if(valor>0)
			arbol[p]=1;
		else
		{
			if(valor<0)
				arbol[p]=-1;
			else
				arbol[p]=0;
		}
		return;
	}

	actualizar(p<<1,valor,i,(i+j)/2,a,b);
	actualizar((p<<1)+1,valor,((i+j)/2)+1,j,a,b);
	arbol[p]=arbol[p<<1]*arbol[(p<<1)+1];
}
int main()
{
	int tama,consultas;
	while(scanf("%d",&tama)==1)
	{
		int arr[tama];
		cin>>consultas;
		for(int h=0;h< tama; h++)
		{
			scanf("%d",&arr[h]);
		}
		construir(0,tama-1,1,arr);
		memset(cambios,2,sizeof(cambios));
		for(int i=0; i<50; i++)
			cambios[i]=2;
		for(int i=0; i<consultas;i++)
		{

			char tip;
			int a,b;
			cin>>tip;
			cin>>a;
			cin>>b;
			if(tip=='C')
			{
				//void actualizar (int p, int valor,int i, int j, int a, int b )
				actualizar(1,b,0,tama-1,a-1,a-1);
				//	for(int i=1; i<tama*4; i++)
					//cout<<"arbol de: "<<i<<" tiene: "<<arbol[i]<<endl;
				//cout<<endl;
			}
			else
			{
				//cout<<endl<<" intervalo a pedir: "<<a-1	<<" "<<b-1<<endl;
				int res=consul(0,tama-1,1,a-1,b-1);
				if(res>0)
					cout<<'+';
				else
					if(res<0)
						cout<<'-';
					else
						cout<<'0';
				//	cout<<endl<<endl;
			}
		}
		//if(i<consultas-1)
		cout<<endl;
		memset(arbol,1,sizeof(arbol));
	}
}