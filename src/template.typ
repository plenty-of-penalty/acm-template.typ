#let font-serif = (
  "New Computer Modern",
  "Source Han Serif",
  "Source Han Serif SC",
  "Simsun",
  "STSong",
)
#let font-sans-serif = (
  "Helvetica",
  "Arial",
  "Source Han Sans",
  "Source Han Sans SC",
  "Hiragino Sans GB",
  "Noto Sans CJK SC",
  "Heiti",
  ..font-serif,
)
#let font-mono = (
  "Go Mono",
  "Cascadia Code",
  "Consolas",
  ..font-sans-serif,
)


#let state-style = state("style", 0)


#let styled(body) = {
  context {
    set text(
      font: font-serif,
      size: if (state-style.get() == 0) {
        17pt
      } else {
        10pt
      },
      lang: "zh",
    )

    show math.equation: set text(weight: 400)

    show par: set block(above: 0.8em, below: 0.8em)
    show raw: set block(above: 0.8em, below: 0.8em)
    show list: set block(above: 0.8em, below: 0.8em)
    show heading: set block(above: 0.8em, below: 0.8em)

    set heading(numbering: "1.1.1 ")

    show heading: it => {
      if it.level <= 3 {
        it
        parbreak()
      } else if it.level == 4 {
        parbreak()
        underline(stroke: 0.5pt, offset: 2pt, text(stroke: 0.28pt, text(style: "italic", weight: "regular", it.body)))
        h(0.5em)
      } else {
        parbreak()
        text(1.1em, style: "italic", weight: "regular", it.body + ".")
      }
    }

    set par(leading: 0.58em)

    set par(justify: true)

    show "。": "．"
    show "，": ", "
    show "；": "; "

    body
  }
}


#let project(title: "", authors: (), special_thanks: (), body) = {
  set document(author: authors, title: title)
  set page(
    margin: (left: 8mm, right: 8mm, top: 12mm, bottom: 8mm),
    flipped: true,
    numbering: "1",
    number-align: center,

    header:
      locate(loc => {
        if query(selector(heading.where(level: 1)).before(loc), loc).len() == 0 {
          v(0pt)
        } else {
          stack(
            {
              counter(heading).display()
              " "
              query(selector(heading.where(level: 1)).before(loc), loc).last().body
            },
            v(0.36em),
            line(length: 100%, stroke: 0.5pt),
          )
        }
      }),
    // header-ascent: 30%,
    footer: {
      // set text(10pt, baseline: 8pt, spacing: 3pt)
      grid(
        columns: (1fr, 1fr),
        align(left, text("Plenty of Penalty / 十发罚时", size: 0.8em)),
        align(right, text(counter(page).display("1/1", both: true), size: 0.9em)),
      )
    }
  )


  state-style.update(1)
  show: styled

  show raw.where(block: true): it => {
    let codes = it.text.split("\n")
    set text(font: font-mono, size: 0.9em)

    set par(justify: false)
    grid(
      columns: (100%, 95%),
      column-gutter: -95%,
      block(
        width: 100%,
        inset: 0em,
        for i in range(codes.len()) {
          h(1em)
          box(
            width: 0pt,
            align(
              right,
              text(
                style: "italic",
                size: 6pt,
                fill: rgb("#a0a0a0"),
                str(i + 1) + h(0em),
              ),
            ),
          )
          hide(codes.at(i))
          linebreak()
        },
      ),
      block(width: 100%, inset: 0em, it),
    )
  }

  align(center)[
    #block(pad(top: 1.6em, bottom: 0.8em, text(weight: 700, 1.75em, title)))
  ]

  pad(
    bottom: 1.2em,
    x: 2em,
    grid(
      columns: (1fr,) * calc.min(3, authors.len()),
      gutter: 1em,
      ..authors.map(author => align(center, strong(author))),
    ),
  )

  {
    set text(size: 9pt)

    show: columns.with(5, gutter: 2em)
    show outline.entry.where(level: 1): it => {
      v(1.2em, weak: true)
      strong(it)
    }
    // show outline.entry.where(level: 3): it => {
    //   let number = it.fields().body.fields().children.at(0).fields().text
    //   if (number.starts-with("1.3")) {
    //     v(-1em)
    //   } else {
    //     it
    //   }
    // }
    //
    set text(size: 0.95em)
    outline(
      depth: 3,
      indent: n => {
        if (n == 0) {
          return 0pt
        }
        if (n == 1) {
          return 1em
        }
        if (n == 2) {
          return 2em
        }
      },
    )

    v(1em)
    strong("Special Thanks to: ")
    special_thanks

    v(1em)
    set align(center)
    set text(size: 1.1em, weight: 800)
    [
      Good Luck & Have Fun!
    ]
  }
  pagebreak(weak: true)
  {
    show: columns.with(3, gutter: 0.5em)
    body
  }
}

#let source_old(file, namespace: none, lang: "cpp") = {
  let source_code = read(file)
  let code = ""
  let note = ""
  let flag = false
  let firstlines = true

  for line in source_code.split(regex("\r?\n")) {
    if namespace != none and line == ("} // namespace " + namespace) {
      flag = false
    }
    if namespace == none or flag {
      if firstlines and line.starts-with("// ") {
        note += line.slice(3) + "\n"
      } else {
        code += line + "\n"
        firstlines = false
      }
    }
    if namespace != none and line == ("namespace " + namespace + " {") {
      flag = true
    }
  }

  if note.len() > 0 {
    block(note)
  }

  if code.len() > 0 {
    code = code.slice(0, code.len() - 1)
  } else {
    code = "// no code"
  }
  raw(lang: lang, block: true, code)
}

#let source(file, namespace: none, lang: none) = {
  include (file + ".code.typ")
}

#let usage = strong("Usage:")
#let note = strong("Note:")
#let desc = strong("Description:")
#let hint = strong("Hint:")
#let time = strong("Time:")
#let caution = strong("Caution:")

#let bold(x) = {
  context {
    set text(stroke: 0.02857em + text.fill)
    x
  }
}