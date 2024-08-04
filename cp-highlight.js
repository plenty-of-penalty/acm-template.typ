/**
 * cp-highlight.js
 *
 * @author memset0s
 * @version 0.1.0
 * @date 20240804
 */

const cpp_keywords = [
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
  'll', // long long
  'lll', // __int128
  'ull', // unsigned long long
  'lf', // long double
  'vi', // vector<int>
  'vll', // vector<ll>
  'pi', // pair<int, int>
];

const theme = {
  space: 'space',
  text: 'normal',
  keyword: 'bold',
  type: 'bold',
  operator: 'highlight',
  macro: 'underlined',
  comments: 'underlined',
  hinter: '→',
  extend: 2,
  tabSize: 2,
  cnLen: 1.501,
  hinterLen: 1,
};

function isChineseChar(char) {
  return char >= '\u4e00' && char <= '\u9fa5';
}
function isAlpha(char) {
  return (
    ('0' <= char && char <= '9') || //
    ('a' <= char && char <= 'z') || //
    ('A' <= char && char <= 'Z')
  );
}

const typstAdapter = function (data) {
  const table = {
    normal: 'T',
    grey: 'G',
    highlight: 'H',
    bold: 'B',
    italic: 'I',
    underlined: 'U',
  };
  let result = '';
  result += '#{\n';
  result += 'set text(font: font-mono)\n';
  result += 'let T(x) = text(x)\n';
  result += 'let G(x) = text(x, fill: luma(160))\n';
  result += 'let H(x) = text(x, fill: color.red)\n';
  result += 'let B(x) = text(x, weight: 900)\n';
  result += 'let I(x) = text(x)\n';
  result += 'let U(x) = underline(stroke: 1pt, offset: 2pt, text(x))\n';
  for (const item of data) {
    result +=
      table[item.style] + //
      '("' + //
      item.text.replace(/\n/g, '\\n') + //
      '")\n';
  }
  result += '}';
  return result;
};

function render(source, lineLimit = 16) {
  const result = [];

  function push_back(style, text) {
    // console.debug('>', { style, text });
    if (
      result.length > 0 && //
      (result[result.length - 1].style == style || //
        (style == 'space' && result[result.length - 1].style != 'underlined'))
    ) {
      result[result.length - 1].text += text;
    } else {
      result.push({
        style: style == 'space' ? 'normal' : style,
        text,
      });
    }
  }

  function getType(pattern) {
    if (cpp_keywords.includes(pattern)) {
      return 'keyword';
    }
    return 'text';
  }
  function analysis(source) {
    if (source[0] == '#') {
      return [{ type: 'macro', text: source }];
    }
    const result = [];
    let pattern = '';
    for (let i = 0; i < source.length; i++) {
      const char = source[i];
      if (char == '/' && i + 1 < source.length && source[i + 1] == '/') {
        result.push({
          type: 'comments',
          text: source.slice(i),
        });
        break;
      }
      if (isAlpha(char)) {
        pattern += char;
      } else {
        if (pattern.length > 0) {
          result.push({
            type: getType(pattern),
            text: pattern,
          });
          pattern = '';
        }
        if (char == ' ' || char == '\t') {
          result.push({
            type: 'space',
            text: char,
          });
        } else {
          result.push({
            type: 'operator',
            text: char,
          });
        }
      }
    }
    if (pattern.length > 0) {
      result.push({
        type: getType(pattern),
        text: pattern,
      });
    }
    return result;
  }

  for (let line of source.split('\n')) {
    let indent = 0;
    let stripLen = 0;
    while (stripLen < line.length && (line[stripLen] == ' ' || line[stripLen] == '\t')) {
      indent += line[stripLen] == '\t' ? theme.tabSize : 1;
      stripLen += 1;
    }
    line = line.slice(stripLen);
    data = analysis(line);
    let remain = lineLimit - indent;
    // console.debug('?', line);
    // console.debug('!', data);
    if (indent > 0) {
      push_back('space', ' '.repeat(indent));
    }
    for (let item of data) {
      let style = theme[item.type];
      for (let char of item.text) {
        let len = isChineseChar(char) ? theme.cnLen : 1;
        if (remain < len) {
          push_back('space', '\n' + ' '.repeat(indent + theme.extend));
          push_back('grey', theme.hinter + ' ');
          remain = lineLimit - indent - theme.extend - theme.hinterLen - 1;
        }
        push_back(style, char);
        remain -= len;
      }
    }
    push_back('space', '\n');
  }
  // console.debug(result);
  return result;
}

function fullRender(source, adapter = typstAdapter) {
  const rendered = render(source);
  const result = adapter(rendered);
  return result;
}

console.log(
  fullRender(`#include <bits/stdc++.h>
using namespace std;
int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b;
	cin >> a >> b; // 输入两个数
	cout << a + b << endl;
	return 0;
}`)
);
