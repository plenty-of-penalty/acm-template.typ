如果用于本机对拍，考虑用毫秒级的时间函数而非 `clock()`。

```cpp
long long seed=chrono::steady_clock::\
      now().time_since_epoch().count();
mt19937 rng(seed);
mt19937_64 rng64(seed);
int x=rng();
long long y=rng64();
```

可用 `uniform_int_distribution` 生成范围随机数。

```cpp
template<class T> inline T rand(T l,T r){
  return uniform_int_distribution<T>(l,r)(rng);
}
template<class T> inline T rand64(T l,T r){
  return uniform_int_distribution<T>(l,r)(rng64);
}
```