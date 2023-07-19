如果用于本机对拍，考虑用毫秒级的时间函数而非 `clock()`。

```cpp
long long seed = std::chrono::steady_clock::now().time_since_epoch().count();
std::mt19937 rng(seed);
std::mt19937_64 rng64(seed);
int x = rng();
long long y = rng64();
```

可用 `std::uniform_int_distribution` 生成范围随机数。

```cpp
template <typename T> inline T rand(T l, T r) {
  return std::uniform_int_distribution<T>(l, r)(rng);
}
template <typename T> inline T rand64(T l, T r) {
  return std::uniform_int_distribution<T>(l, r)(rng64);
}
```