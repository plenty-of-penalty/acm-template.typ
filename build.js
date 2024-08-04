const fs = require('fs').promises;
const path = require('path');
const util = require('util');
const exec = util.promisify(require('child_process').exec);
const { fullRender } = require('./cp-highlight.js');

const sourceDir = path.join(__dirname, './src');

async function scanDir(dirPath) {
  let entries = await fs.readdir(dirPath, { withFileTypes: true });

  let filePromises = entries.map((entry) => {
    let fullPath = path.join(dirPath, entry.name);

    if (entry.isDirectory()) {
      return scanDir(fullPath);
    } else {
      return fullPath;
    }
  });

  let files = await Promise.all(filePromises);

  return files.flat();
}

async function build() {
  console.log('[build] start!');

  for (const sourceFile of (await scanDir(sourceDir)).filter((file) => path.extname(file) === '.cpp' || path.extname(file) === '.hpp')) {
    console.log('[build] render', sourceFile);
    const source = (await fs.readFile(sourceFile)).toString();
    const resultFile = sourceFile + '.code.typ';
    const result = fullRender(source, {
      theme: {
        header: [
          'let font-sans-serif = ("Helvetica","Arial","Source Han Sans","Source Han Sans SC","Hiragino Sans GB","Noto Sans CJK SC","Heiti")', //
          'let font-mono = ("Consolas",..font-sans-serif)',
          'set text(font: font-mono, size: 8pt)',
        ].join('\n'),
      },
    });
    await fs.writeFile(resultFile, result);
  }

  await exec('typst compile ' + path.join(__dirname, './src/main.typ'));

  console.log('[build] end.');
}

async function watch() {
  console.log('[watch] start!');
}

if (require.main == module) {
  build();
}
