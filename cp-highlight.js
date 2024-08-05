/**
 * cp-highlight.js
 *
 * @author memset0s
 * @version 0.4.1
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

const default_theme = {
  space: 'space',
  text: 'normal',
  keyword: 'bold',
  type: 'bold',
  operator: 'normal',
  macro: 'green',
  comments: 'underlined',
  hinter: '→',
  extend: 2,
  tabSize: 2,
  cnLen: 2,
  hinterLen: 1,
  header: '',
  footer: '',
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

const typstAdapter = function (data, theme) {
  theme = { ...default_theme, ...theme };

  const table = {
    normal: 'T',
    grey: 'Y',
    red: 'R',
    blue: 'B',
    green: 'G',
    bold: 'S',
    italic: 'I',
    underlined: 'U',
  };
  let result = '';
  result += '#{\n';
  result += theme.header + '\n';
  result += 'let T(x)=text(x)\n';
  result += 'let Y(x)=text(x,fill:luma(160))\n';
  result += 'let R(x)=text(x,fill:rgb(214,57,72))\n';
  result += 'let G(x)=text(x,fill:rgb(40,142,12))\n';
  result += 'let B(x)=text(x,fill:rgb(75,105,197))\n';
  result += 'let S(x)=text(x,weight: 900)\n';
  result += 'let I(x)=text(x)\n';
  result += 'let U(x)=underline(stroke:1pt,offset:2pt,text(x))\n';
  for (const item of data) {
    result +=
      table[item.style] +
      '("' +
      item.text
        .replace(/\\/g, '\\\\') //
        .replace(/\n/g, '\\n') //
        .replace(/\"/g, '\\"') +
      '");';
  }
  result += theme.footer + '\n';
  result += '}';
  return result;
};

function render(source, lineLimit, lang, theme) {
  theme = { ...default_theme, ...theme };

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
      if (isAlpha(char) || char == '_') {
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
          push_back('grey', theme.hinter);
          remain = lineLimit - indent - theme.extend - theme.hinterLen;
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

function fullRender(source, options = {}) {
  options = {
    lineLimit: 64,
    lang: 'cpp',
    adapter: typstAdapter,
    theme: {},
    ...options,
  };
  const rendered = render(source, options.lineLimit, options.lang, options.theme);
  const result = options.adapter(rendered, options.theme);
  return result;
}

module.exports = {
  cpp_keywords,
  render,
  fullRender,
};

if (require.main == module) {
  console.log(
    fullRender(`#include <bits/stdc++.h>
using namespace std;
int main() {
	#ifdef memset0
		freopen("1.in", "r", stdin);
	#endif
	cin.tie(0)->sync_with_stdio(0);
	int a, b;
	cin >> a >> b; // 输入两个数
	cout << a + b << endl;
	return 0;
}`)
  );
}
