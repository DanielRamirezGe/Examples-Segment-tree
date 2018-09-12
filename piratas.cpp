#include <bits/stdc++.h>
using namespace std;
#define tama 1024000
int arbol[tama<<2];
int cambios[tama<<2];
bitset<tama> piratas;
void construir(int p,int i,int j)
{
	//cout<<p<<" "<<i<<" "<<j<<"\n";
	if(i==j)
	{
		arbol[p]=piratas[i];
		return;
	}
	
	construir(p<<1,i,(i+j)/2);
	construir((p<<1)+1,((i+j)/2)+1,j);
	arbol[p]=(arbol[p<<1]+arbol[(p<<1)+1]);
}
int modifi(int papa, int hijo)
{
	if(papa=='I')  ///inversion
	{
		if(hijo=='I')
			return -1;
		if(hijo==0)
			return 1;
		if(hijo==1)
			return 0;

	}

	return papa;

/*	if(papa==1)
		return 1;
	if(papa==0)
		return 0;*/
}
void propagar (int p, int i, int j)
{
	if (cambios[p]==-1)
		return	;
	
	if(cambios[p]=='I')
		arbol[p]=(j-i+1)-arbol[p];
	else arbol[p]=(j-i+1)*cambios[p];

	if(i!=j)
	{
		
		cambios[p<<1]=modifi(cambios[p],cambios[p<<1]);
		cambios[(p<<1)+1]=modifi(cambios[p],cambios[(p<<1)+1]);
	}
	cambios[p]=-1;

}
void actualizar (int p, int valor,int i, int j, int a, int b )
{
	//cout<<p<<" "<<i<<" "<<j<<"\n";
	//if (p>50) return;
	propagar(p,i,j);
	if(a>j || b<i)
		return ;
	if(i>=a&&j<=b)
	{
		//cout<<"esta contenido\n";
		if(valor=='I')
			arbol[p]=(j-i+1)-arbol[p];
		else
			arbol[p]=(j-i+1)*valor;
		if(i!=j)
		{
			cambios[p<<1]=modifi(valor,cambios[p<<1]);
			cambios[(p<<1)+1]=modifi(valor,cambios[(p<<1)+1]);
		}
		//cout<<"esta contenidssssssso\n";
		return;
	}

	actualizar(p<<1,valor,i,(i+j)/2,a,b);
	actualizar((p<<1)+1,valor,((i+j)/2)+1,j,a,b);
	arbol[p]=arbol[p<<1]+arbol[(p<<1)+1];
}
int  consulta(int p,int i,int j,int a, int b)
{
	
	if(a>j||b<i)
		return 0;
	propagar(p,i,j);
	if(i>=a&&j<=b)
		return arbol[p];
	
	int izq=consulta(p<<1,i,(i+j)/2,a,b);
	int der=consulta((p<<1)+1,((i+j)/2)+1,j,a,b);
	return izq+der;
	
}
int main()
{
	int cont=0;
	int casos,veces,num,a,b;
	cin>>casos;
	for(int i=0;i<casos; i++)
	{
		memset(cambios,-1,sizeof(cambios));
		int repetciones; 
		int numero=1;
		cin>>veces;
		cont=0;
		for(int j=0;j<veces;j++)
		{
			
			cin>>repetciones;
			string cad;
			cin>>cad;
			for(int h=0;h<repetciones;h++)
			{
				for(int m=0;m<cad.size();m++)
					{
						piratas[cont]=cad[m]-'0';
						cont++;
					}
			}
		}
			construir(1,0,cont-1);
	//		for(int n=0;n<cont;n++)
	//			cout<<arbol[n];
			//cout<<"\n";

			int consultas;
			int a,b;
			char intruccion;
			cin>> consultas;
			cout<<"Case "<<i+1<<":\n";
			for(int otro=0;otro<consultas;otro++)
			{
				cin>>intruccion;
				cin>>a>>b;
			//	cout<<intruccion<<" "<<a<<" "<<b<<"\n";
				
	
				if(intruccion=='F')
				{
					actualizar (1,  1, 0,  cont-1, a, b);
						
				} 	
				if(intruccion=='E')
				{
					actualizar ( 1, 0, 0, cont-1, a, b);
				}
				if(intruccion=='I')
				{
					actualizar(1,'I',0, cont-1, a, b);
				}
				if(intruccion=='S')
				{
					cout<<"Q"<<numero<<": "<< consulta(1,0,cont-1,a,b)<<"\n";
					numero++;
				}
			}


		}

	return 0;
}