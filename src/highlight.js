sample_code = `
#include <bits/stdc++.h>
using namespace std;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  return 0;
}
`.trim();

const keywords = [
  'alignas',
  'alignof',
  'and',
  'and_eq',
  'asm',
  'atomic_cancel',
  'atomic_commit',
  'atomic_noexcept',
  'auto',
  'bitand',
  'bitor',
  'bool',
  'break',
  'case',
  'catch',
  'char',
  'char8_t',
  'char16_t',
  'char32_t',
  'class',
  'compl',
  'concept',
  'const',
  'consteval',
  'constexpr',
  'constinit',
  'const_cast',
  'continue',
  'co_await',
  'co_return',
  'co_yield',
  'decltype',
  'default',
  'delete',
  'do',
  'double',
  'dynamic_cast',
  'else',
  'enum',
  'explicit',
  'export',
  'extern',
  'false',
  'float',
  'for',
  'friend',
  'goto',
  'if',
  'inline',
  'int',
  'long',
  'mutable',
  'namespace',
  'new',
  'noexcept',
  'not',
  'not_eq',
  'nullptr',
  'operator',
  'or',
  'or_eq',
  'private',
  'protected',
  'public',
  'reflexpr',
  'register',
  'reinterpret_cast',
  'requires',
  'return',
  'short',
  'signed',
  'sizeof',
  'static',
  'static_assert',
  'static_cast',
  'struct',
  'switch',
  'synchronized',
  'template',
  'this',
  'thread_local',
  'throw',
  'true',
  'try',
  'typedef',
  'typeid',
  'typename',
  'union',
  'unsigned',
  'using',
  'virtual',
  'void',
  'volatile',
  'wchar_t',
  'while',
  'xor',
	'xor_eq',
	// ext
	'size_t',
	'l',
];

function render(code, width = 60) {
  let isLineStart = true;
  let isComment = false;
  let countIndent = 0;
  let result = [];
  let pattern = '';

  const printPattern = () => {
    if (pattern.length == 0) return;
    if (keywords.includes(pattern)) {
      result.push({ type: 'bold', text: 'pattern' });
    }
  };

  for (let i = 0; i < code.length; i++) {
    let c = code[i];
    if (c == '\r') {
      continue;
    }
    if (c == '\n') {
      printPattern();
      printLn();
      isLineStart = true;
      countIndent = 0;
    }
    if (isLineStart) {
      if (c == ' ') {
        countIndent += 1;
      } else if (c == '\t') {
        countIndent += 2;
      } else {
        isLineStart = false;
      }
    }
  }
}
