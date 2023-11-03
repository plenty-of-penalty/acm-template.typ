struct StableSum{
  int cnt=0;
  vector<double> v,pref{0};
  inline void operator+=(double a){
    assert(a>=0);
    int s=++cnt;
    while(s%2==0){
      a+=v.back();
      v.pop_back();
      pref.pop_back();
      s/=2;
    }
    v.push_back(a);
    pref.push_back(pref.back()+a);
  }
  inline double val(){return pref.back();}
};