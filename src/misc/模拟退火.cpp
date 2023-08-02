// BZOJ3680 吊打XXX
#include <bits/stdc++.h>
const int N=1e4+9;
int n,x[N],y[N],w[N];
double ansx,ansy,dis;
namespace SimulateAnneal {
double rng(){
  return (double)rand()/RAND_MAX;
}
double calc(double xx,double yy){
  double res=0;
  for(int i=1;i<=n;++i){
    double dx=x[i]-xx,dy=y[i]-yy;
    res+=sqrt(dx*dx+dy*dy)*w[i];
  }
  if(res<dis) dis=res,ansx=xx,ansy=yy;
  return res;
}
void SA(){
  double t=100000;
  double nowx=ansx,nowy=ansy;
  while(t>0.001){
    double nxtx=nowx+t*(rng()-0.5);
    double nxty=nowy+t*(rng()-0.5);
    double delta=calc(nxtx,nxty)-calc(nowx,nowy);
    if(exp(-delta/t)>rng()) nowx=nxtx,nowy=nxty;
    t*=0.97;
  }
  for(int i=1;i<=1000;++i){
    double nxtx=ansx+t*(rng()-0.5);
    double nxty=ansy+t*(rng()-0.5);
    calc(nxtx,nxty);
  }
}
} // namespace SimulateAnneal
using namespace SimulateAnneal;
int main(){
  srand(0);
  scanf("%d",&n);
  for(int i=1;i<=n;++i){
    scanf("%d%d%d",&x[i],&y[i],&w[i]);
    ansx+=x[i],ansy+=y[i];
  }
  ansx/=n,ansy/=n,dis=calc(ansx,ansy);
  SA();
  printf("%.3lf %.3lf\n",ansx,ansy);
}