#include <bits/stdc++.h>
using namespace std;
namespace DeletableHeap {
template <class T> struct DeletableHeap {
  priority_queue<T> p, q;
  inline void maintain() {
    while (!q.empty() && p.top() == q.top()) {
      p.pop(), q.pop();
    }
  }
  void push(const T &x) {
    if (!q.empty() && q.top() == x) {
      q.pop(), maintain();
    } else {
      p.push(x);
    }
  }
  void pop(const T &x) {
    if (p.top() == x) {
      p.pop(), maintain();
    } else {
      q.push(x);
    }
  }
  void pop() { p.pop(), maintain(); }
  T top() { return p.top(); }
  bool empty() { return p.empty(); }
};
} // namespace DeletableHeap
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
}