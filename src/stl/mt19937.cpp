// 使用chrono库获得毫秒级时间
auto seed = chrono::steady_clock::now().time_since_epoch().count();
mt19937 rng(seed);
mt19937_64 rng64(seed);
// 使用uniform_int_distribution生成区间均匀随机分布的整数
int rand(int l, int r) { return uniform_int_distribution<>(l, r)(rng); }
ll rand64(ll l, ll r) { return uniform_int_distribution<>(l, r)(rng64); }