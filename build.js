const fs = require('fs');
const path = require('path');
const util = require('util');
const exec = util.promisify(require('child_process').exec);
const { fullRender } = require('./cp-highlight.js');

const sourceDir = path.join(__dirname, './src');
const sourceFilter = (file) => path.extname(file) === '.cpp' || path.extname(file) === '.hpp';

const options = {
  lineLimit: 59,
  cnLen: 1.6,
  theme: {
    header: [
      'let font-sans-serif = ("Helvetica","Arial","Source Han Sans","Source Han Sans SC","Hiragino Sans GB","Noto Sans CJK SC","Heiti")', //
      'let font-mono = ("Consolas",..font-sans-serif)',
      'set text(font: font-mono, size: 8pt)',
    ].join('\n'),
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

async function render(sourceFile) {
  if (!fs.existsSync(sourceFile)) {
    return;
  }
  const source = (await fs.promises.readFile(sourceFile)).toString();

  let flagHasNamespace = false;
  const lines = source.replace(/\r/g, '').split('\n');
  for (let l = 0, r = 0; l < lines.length; l = r + 1, r = l) {
    if (lines[l].startsWith('namespace ') && lines[l].endsWith('{')) {
      const namespace = lines[l].slice(10, -2);
      while (r + 1 < lines.length && lines[r] != '} // namespace ' + namespace) {
        ++r;
      }
      flagHasNamespace = true;
      const resultFile =
        sourceFile + //
        (namespace == 'stdlib' ? '' : '.' + namespace) + //
        '.code.typ';
      const result = fullRender(lines.slice(l + 1, r).join('\n'), options);
      console.log('[render]', resultFile);
      await fs.promises.writeFile(resultFile, result);
    }
  }

  if (!flagHasNamespace) {
    const resultFile = sourceFile + '.code.typ';
    const result = fullRender(source, options);
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
  if (process.argv.includes('--watch')) {
    watch();
  } else {
    build();
  }
}
