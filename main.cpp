#include<iostream>
#include<string>
#include<cmath>
#include<ctime>
#include<cstdlib>
using namespace std;
typedef int real;

const char pl='1',mon='9';

class Mob{
public:
	int hp,dm;
	real r,v,x;
};
class player: public Mob{
public:
	int Action(string act, int sizeMap){
		if((act=="L" || act=="l")&& x-v>0){
			x-=v;
			return 0;
		}
		else if((act=="R" || act=="r")&& x+v<sizeMap-1){
			x+=v;
			return 0;
		}
		if(act=="A" || act=="a") return 1;
		else return -1;
	}
	player(real x,real hp,real r,real dm,real v){
		this->x=x; this->hp=hp; this->r=r; this->dm=dm; this->v=v;
	}
};
class monster: public Mob{
public:
	real R;
	int Action(real k, int sizeMap){
		real random;
		if(abs(k)>R){
			if(x+v>sizeMap-1) x-=v;
			else if(x-v<0) x+=v;
			else{
				random=0.01*(rand()%101);
				if(random>=0.5 && x+v<sizeMap-1){
					x+=v;
				} else{
					x-=v;
				}
			}
			return 1;
		} else{
			if(abs(k)>r){
				if(k>0) x+=v;
				else x-=v;
				return 1;
			} else return 0;
		}
	}
	monster(real x,real hp,real R,real r,real dm,real v){
		this->x=x; this->hp=hp; this->R=R; this->r=r; this->dm=dm; this->v=v;
	}
};
void showMap(int sizeMap, int xp, int xm){
	cout<<'|';
	for(int i=0;i<sizeMap;i++)
		if(xp==i) cout<<pl;
		else if(xm==i) cout<<mon;
		else cout<<'0';
	cout<<'|'<<endl;
}

int randomM(int sizeMap){
	return rand()%sizeMap;
}

int main(){
	srand(time(NULL));
	string act;
	cout<<"Commands: L,l for moving left; R,r for moving right; A,a for attack"<<endl;
	cout<<"Enter map size"<<endl;
	int sizeMap;
	cin>>sizeMap;
	real xp=randomM(sizeMap),xm=randomM(sizeMap);
	if(xp==xm)
		if(xp<sizeMap) xp++;
		else xp--;
	system("clear");
	showMap(sizeMap,xp,xm);
	player p(xp,10,2,2,2);
	monster m(xm,10,5,1,5,1);
	while(p.hp>0 && m.hp>0){
		cin>>act;
		system("clear");
		int i=p.Action(act,sizeMap);
		if(i==1 && abs(p.x-m.x)<=p.r) m.hp-=p.dm;
		else if(i==-1) cout<<"You skipped your move"<<endl;
		i=m.Action(p.x-m.x,sizeMap);
		if(i==0 && abs(p.x-m.x)<=m.r && m.hp>0) p.hp-=m.dm;
		showMap(sizeMap,p.x,m.x);
		cout<<" Player's health: "<<p.hp<<endl;
		cout<<" Monster's health: "<<m.hp<<endl;
	}
	return 0;
}