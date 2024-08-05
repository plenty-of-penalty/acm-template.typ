const int SZ = 1 << 16;
int getc() {
  static char buf[SZ], *ptr = buf, *top = buf;
  if (ptr == top) {
    ptr = buf, top = buf + fread(buf, 1, SZ, stdin);
    if (top == buf) return ‐1;
  }
  return *ptr++;
}