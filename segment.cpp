#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int>> arbol[9999999];
void contruir(int i, int j, int p,int arr[])
{
	//cout<<" La i: "<<i<<" la j:"<<j<<endl;
	if(i==j)
	{
		
		pair <int, int> nuevo;
		nuevo.first=1;
		nuevo.second=arr[i];
		arbol[p].push_back(nuevo);

		//cout<<"  p= "<<p<<"intervalo: "<<i<<"  "<<j<<"  tiene: "<<1<<"  de: "<<arr[i]<<endl;
		//arbol[p].push_back(nuevo);
		return;
	}
	contruir(i, (i+j)/2, 2*p,arr);

	contruir(((i+j)/2)+1,j,(2*p)+1,arr);
	
	for (auto a: arbol[2*p])
	{
		arbol[p].push_back(a);
	}
	for (auto a: arbol[(2*p)+1])
	{
		arbol[p].push_back(a);
	}
	/*	if(p==1)
	{
		for(auto a: arbol[p])
		{
			cout<<"  numero: "<<"   arbol de: "<<p<<" Tiene: "<<a.first<<"  de: "<<a.second<<endl;
		}
		cout<<endl;
	}*/

		int con=0,valor,ind=0;
		for(int i=0; i<arbol[p].size(); i++)
		{
			if(i==0)
			{
				valor=arbol[p][0].second;
				ind=arbol[p][0].first;
			}
			else
			{
				if(arbol[p][i].second!=arbol[p][i-1].second)
				{
					
					arbol[p][con].first=ind;
					arbol[p][con].second=valor;
					valor=arbol[p][i].second;
					ind=arbol[p][i].first;
					con++;
				}
				else
				{
					ind+=arbol[p][i].first;
				}
				if(i==arbol[p].size()-1)
				{
					arbol[p][con].first=ind;
					arbol[p][con].second=valor;
					valor=arbol[p][i].second;
				}
			}
		}

			for(int i=arbol[p].size()-1; i>con; i--)
		{
			arbol[p].pop_back();
		}
		
		int to=arbol[p].size()-1;
		int que=arbol[p][1].first;
		int se=arbol[p][1].second;
//
//		cout<<"   tamaño : "<<to<<"  cuantos: "<<que<<"   de:"<<se<<endl;
		for(int i=1; i< to;i++)
		{
			if(arbol[p][i].first>que)
				{
					que=arbol[p][i].first;
					se=arbol[p][i].second;
				}
		}
		arbol[p][1].first=que;
		arbol[p][1].second=se;
		if(arbol[p].size()>3)
		{
		int tod=arbol[p].size()-1;
		arbol[p][2].first=arbol[p][tod].first;
		arbol[p][2].second=arbol[p][tod].second;
		for(int i=arbol[p].size()-1; i>2; i--)
		{
			arbol[p].pop_back();
		}
		}
	/*	for(auto a: arbol[p])
		{
			cout<<"  numero: "<<"   arbol de: "<<p<<" Tiene: "<<a.first<<"  de: "<<a.second<<" intervalo de: "<<i<<"  "<<j<<endl;
		}
		cout<<endl;*/
		
	return;
}
typedef vector<pair<int,int>> nodo;

nodo consu (int p, int i,int j, int a, int b)
{
	//	cout<<" La i: "<<i<<" la j:"<<j<<endl;
	if(a>j||b<i)
	{
		nodo nulo;
		pair <int,int> no;
		no.first=0;
		no.second=0;
		nulo.push_back(no);
		return nulo;
	}
	if(i>=a&&j<=b)
		return arbol[p];
	nodo izq=consu(p<<1,i,(i+j)/2,a,b);
	nodo der=consu((p<<1)+1,((i+j)/2)+1,j,a,b);
	if(izq[0].first!=0 and der[0].first!=0)
	{
		/*if(a==1 and b==3)
		{
			cout<<endl<<endl;
			for(auto w: izq)
			{
				cout<<"  tine: "<<w.first<<"  de: "<<w.second<<"  p: "<<p<<"   Izquierda"<<endl;
			}
			for(auto w: der)
			{
				cout<<"  tine: "<<w.first<<"  de: "<<w.second<<"  p: "<<p<<"  Derecha"<<endl;
			}
		}*/
	nodo res;
	for(auto a: izq)
	{
		res.push_back(a);
	}
	for( auto a: der)
	{
		res.push_back(a);
	}	
		int con=0, valor, ind=0;
		for(int i=0; i<res.size(); i++)
		{
			if(i==0)
			{
				valor=res[0].second;
				ind=res[0].first;
			}
			else
			{
				if(res[i].second!=res[i-1].second)
				{
					res[con].first=ind;
					res[con].second=valor;
					valor=res[i].second;
					ind=res[i].first;
					con++;
				}
				else
				{
					ind+=res[i].first;
				}
				if(i==res.size()-1 )
				{
					res[con].first=ind;
					res[con].second=valor;
					valor=res[i].second;
				}
			}
		}

			for(int i=res.size()-1; i>con; i--)
		{
			res.pop_back();
		}
		nodo ultimo;
		for (auto x: res)
		{
			if(x.first!=0)
			{
				ultimo.push_back(x);
			}
		}	
		
	/*	if(a==1 and b==3 and p==2)
		{
			for( auto m: ultimo)
				cout<<"  tine: "<<m.first<<"  de: "<<m.second<<"  p: "<<p<<"  resultado"<<"  tamaño"<<ultimo.size()-1<<endl;

		}*/
		int to=ultimo.size()-1;
		int que=ultimo[1].first;
		int se=ultimo[1].second;

		//cout<<"   tamaño : "<<to<<"  cuantos: "<<que<<"   de:"<<se<<endl;
		for(int i=1; i< to;i++)
		{
			if(ultimo[i].first>que)
				{
					que=ultimo[i].first;
					se=ultimo[i].second;
				}
		}
		ultimo[1].first=que;
		ultimo[1].second=se;
		return res;
	}

	else
	{
		if(izq[0].first!=0)
			return izq;
		else
			return der;
	}
}

int main()
{
	int contador=0;
	int tama,consultas;
	cin>>tama;
	while(tama!=0)
	{
		//contador++;
	cin>>consultas;
	int arr[tama];
	for(int i=0; i< tama; i++)
	{
			scanf("%d",&arr[i]);
	}

	contruir(0,tama-1,1,arr);
	/*for(int i=0; i<40;i++)
	{
		cout<<" primera i: "<<i<<endl;
		for(auto a: arbol[i])
			cout<<"  i: "<<i<<"   valor: "<<a.first<<"   numero: "<<a.second<<endl;
		cout<<endl;*/
	//cout<<"Aqui.."<<endl;
	
	for(int i=0; i<consultas; i++)
	{	
		contador++;

		
		int a,b;
		cin>>a;
		cin>>b;
			//	cout<<"   resultado de la linea: "<<contador<<	"  intervalo: "<<a<<"  "<<b<<endl;
		nodo res=consu(1,0, tama-1,a-1,b-1);
		
		
		/*	for(auto a: res)
			{
				cout<<" tiene "<<a.first<<"   de "<<a.second<<endl;
			}
		cout<<endl;*/
		int mayor= res[0].first;
		for(int i=0; i< res.size(); i++)
		{
			if(res[i].first>mayor)
				mayor=res[i].first;
		}
		cout<<mayor<<endl;

	}

	cin>>tama;
	if(tama!=0)
	{

		for(int i=0 ;i< tama*4;i++)
		arbol[i].clear();
	}
	
	}
}