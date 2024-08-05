function parseDocHeader(code) {
  const match = code.match(/^\s*?\/\*\*([\s\S]*?)\*\/\s*/);
  if (!match) {
    return { header: {}, code };
	}
	console.log(match);
  code = code.slice(match[0].length);
  const lines = match[1].split('\n');
  const dict = {};
  for (let line of lines) {
    line = line.trim();
    if (line.startsWith('* @')) {
      const tagLine = line.substring(3);
      const tagParts = tagLine.split(' ');
      const tagName = tagParts[0];
      tagParts.shift();
      if (tagName === 'param') {
        const typeMatch = tagParts[0].match(/{(.*)}/);
        tagParts.shift();
        const paramName = tagParts[0];
        tagParts.shift();
        if (!dict[tagName]) {
          dict[tagName] = [];
        }
        dict[tagName].push({
          name: paramName,
          type: typeMatch ? typeMatch[1] : null,
          description: tagParts.join(' '),
        });
      } else {
        dict[tagName] = tagParts.join(' ');
      }
    }
  }
  return { header: dict, code };
}

const comment = `
/**
 * @author antileaf
 */
int l[2], r[2], x[B + 10][2], w[B + 10];
int n, op, ans = 0, cnt = 0, tmp = 0;
int d;
`;
console.log(parseDocHeader(comment));
