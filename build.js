const fs = require('fs');
const path = require('path');
const util = require('util');
const exec = util.promisify(require('child_process').exec);
const { fullRender } = require('./cp-highlight.js');

const sourceDir = path.join(__dirname, './src');
const sourceFilter = (file) => path.extname(file) === '.cpp' || path.extname(file) === '.hpp';

const options = {
  detailed: false, // options for this script
  lineLimit: 54,
  cnLen: 1.5,
  theme: {
    header: ['set text(font:font-mono,size:8pt)'].join('\n'),
    footer: [].join('\n'),
  },
};

async function scanDir(dirPath) {
  let entries = await fs.promises.readdir(dirPath, { withFileTypes: true });

  let filePromises = entries.map((entry) => {
    let fullPath = path.join(dirPath, entry.name);

    if (entry.isDirectory()) {
      return scanDir(fullPath);
    } else {
      return fullPath;
    }
  });

  let files = await Promise.all(filePromises);

  return files //
    .flat()
    .filter(sourceFilter);
}

function parseDocHeader(code) {
  const match = code.match(/^\s*?\/\*\*([\s\S]*?)\*\/\s*/);
  if (!match) {
    return { docs: {}, code };
  }
  code = code.slice(match[0].length);
  const lines = match[1].split('\n');
  const dict = {};
  for (let line of lines) {
    line = line.trim();
    if (line.startsWith('* @')) {
      const tagLine = line.substring(3);
      const tagParts = tagLine.split(' ');
      const tagName = tagParts[0].endsWith(':') ? tagParts[0].slice(0, -1) : tagParts[0];
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
  return { docs: dict, code };
}

async function render(sourceFile) {
  if (!fs.existsSync(sourceFile)) {
    return;
  }
  const source = (await fs.promises.readFile(sourceFile)).toString().replace(/\r/g, '');
  const { docs, code } = parseDocHeader(source);
  let header = '';
  header += '#import "' + path.relative(path.dirname(sourceFile), path.join(__dirname, './src/template.typ')).replace(/\\/g, '/') + '": *\n';
  if (docs.description) {
    header += '#desc ' + docs.description + '\n\n';
  }
  if (options.detailed) {
    if (docs.author) {
      header += '#author ' + docs.author + '\n\n';
    }
  }

  let flagHasNamespace = false;
  const lines = code.split('\n');
  for (let l = 0, r = 0; l < lines.length; l = r + 1, r = l) {
    if (lines[l].startsWith('namespace ') && lines[l].endsWith('{')) {
      const namespace = lines[l].slice(10, -2);
      while (r + 1 < lines.length && lines[r] != '} // namespace ' + namespace) {
        ++r;
      }
      flagHasNamespace = true;
      const resultFile = sourceFile + (namespace == 'stdlib' ? '' : '.' + namespace) + '.code.typ';
      const result = header + fullRender(lines.slice(l + 1, r).join('\n'), options);
      console.log('[render]', resultFile);
      await fs.promises.writeFile(resultFile, result);
    }
  }

  if (!flagHasNamespace) {
    const resultFile = sourceFile + '.code.typ';
    const result = header + fullRender(code, options);
    console.log('[render]', resultFile);
    await fs.promises.writeFile(resultFile, result);
  }
}

async function build() {
  console.log('[build] start!');

  for (const sourceFile of await scanDir(sourceDir)) {
    await render(sourceFile);
  }

  if (!process.argv.includes('--no-typst')) {
    await exec('typst compile ' + path.join(__dirname, './src/main.typ'));
  } else {
    console.log('[build] skip run `typst compile`');
  }

  console.log('[build] end.');
}

async function watch() {
  console.log('[watch] start!');

  for (const sourceFile of await scanDir(sourceDir)) {
    await render(sourceFile);
  }

  if (!process.argv.includes('--no-typst')) {
    exec('typst watch ' + path.join(__dirname, './src/main.typ'));
  } else {
    console.log('[watch] skip run `typst watch`');
  }

  async function watchDirectory(directory) {
    console.log('watch !!', directory);
    // 监听当前目录
    fs.watch(directory, (eventType, filename) => {
      const file = path.join(directory, filename);
      if (!sourceFilter(file)) return;
      render(file);
    });
    // 读取目录中的所有文件/目录
    try {
      const files = await fs.promises.readdir(directory);
      // 对每个文件/目录，如果是目录则递归调用 watchDirectory
      for (const file of files) {
        const fullPath = path.join(directory, file);
        const stats = await fs.promises.stat(fullPath);
        if (stats.isDirectory()) {
          await watchDirectory(fullPath);
        }
      }
    } catch (err) {
      console.error(`Error reading directory: ${err}`);
    }
  }
  watchDirectory(sourceDir);
}

if (require.main == module) {
  if (process.argv.includes('--detailed')) {
    options.detailed = true;
  }

  if (process.argv.includes('--watch')) {
    watch();
  } else {
    build();
  }
}
