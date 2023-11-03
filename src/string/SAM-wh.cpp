struct SAM{
  int t[MAXN][26],pre[MAXN],len[MAXN];
  int sg[MAXN];
  int last,tot;
  SAM(){last=tot=1;}
  void clear(){
    while(tot)sg[tot]=0,memset(t[tot],0,sizeof t[tot]),pre[tot]=len[tot]=0,--tot;
    last=tot=1;
  }
  void extend(int w){
    int pos=last,cur=++tot;
    len[cur]=len[pos]+1,last=cur;
    while(pos&&!t[pos][w])t[pos][w]=cur,pos=pre[pos];
    if(!pos){pre[cur]=1;return;}
    int nxt=t[pos][w];
    if(len[nxt]==len[pos]+1)pre[cur]=nxt;
    else{
      int tmp=++tot;
      len[tmp]=len[pos]+1,memcpy(t[tmp],t[nxt],sizeof t[nxt]);
      pre[tmp]=pre[nxt],pre[cur]=pre[nxt]=tmp;
      while(pos&&t[pos][w]==nxt)t[pos][w]=tmp,pos=pre[pos];
    }
  }
  void dfs(int u){
    if(sg[u]>=0)return;
    bool vis[28];
    memset(vis,0,sizeof vis);
    for(int c=0;c<26;++c){
      int v=t[u][c];
      if(!v)continue;
      dfs(v),vis[sg[v]]=1;
    }
    int k=0;
    while(vis[k])++k;
    sg[u]=k;
  }
  void solve(){
    for(int i=1;i<=tot;++i)sg[i]=-1;
    dfs(1);
  }
}sam;