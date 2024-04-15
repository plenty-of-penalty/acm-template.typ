#let project(title: "", authors: (), special_thanks: (), body) = {
  set document(author: authors, title: title)
  set page(
    margin: (left: 8mm, right: 8mm, top: 12mm, bottom: 8mm),
    numbering: "1",
    number-align: center,

    header: stack(
      locate(loc => {
        if query(selector(heading.where(level: 1)).before(loc), loc).len() == 0 {
          "ACM Template"
        } else {
          counter(heading).display()
          " "
          query(selector(heading.where(level: 1)).before(loc), loc).last().body
        }
      }),
      v(0.5em),
      line(length: 100%, stroke: 0.5pt)
    ),
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

  set text(
    font: (
      "New Computer Modern",
      "Source Han Serif",
      "Source Han Serif SC",
      "Simsun",
      "STSong",
    ),
    size: 10pt,
    lang: "zh",
  )

  show math.equation: set text(weight: 400)

  show par: set block(above: 0.8em, below: 0.8em)

  set heading(numbering: "1.1.1")

  show heading: it => {
    if it.level > 3 {
      parbreak()
      text(11pt, style: "italic", weight: "regular", it.body + ".")
    } else {
      it
    }
  }

  set par(leading: 0.58em)

  align(center)[
    #block(pad(top: 2em, bottom: 0.5em, text(weight: 700, 1.75em, title)))
  ]

  pad(
    bottom: 2em,
    x: 2em,
    grid(
      columns: (1fr,) * calc.min(3, authors.len()),
      gutter: 1em,
      ..authors.map(author => align(center, strong(author))),
    ),
  )

  set par(justify: true)

  show raw.where(block: true): it => {
    let codes = it.text.split("\n")
    set text(font: ("Go Mono"), size: 0.9em)
    
    set par(justify: false)
    grid(
      columns: (100%, 98%),
      column-gutter: -98%,
      block(width: 98%, inset: 1em, for i in range(codes.len()) {
        box(width: 0pt, align(right, text(
          style: "italic",
          size: 6pt,
          fill: rgb("#a0a0a0"),
          str(i + 1) + h(0em)
        )))
        hide(codes.at(i))
        linebreak()
      }),
      block(width: 100%, inset: 1em, it),
    )
  }

  show "。": "．"

  {
    set text(lang: "en")

    show: columns.with(3, gutter: 2em)
    outline()

    strong("Special Thanks to: ")
    text("Qingyu, Sulfox and seniors from Zhejiang University.")

    v(2em)
    set align(center)
    set text(size: 1.2em, weight: 800)
    [
      Good Luck & Have Fun!
    ]
  }
  pagebreak(weak: true)
  {
    show: columns.with(2, gutter: 0.5em)
    body
  }
}


#let importCode(file, namespace: none, lang: "cpp") = {
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

#let note = strong("Note:")
#let hint = strong("Hint:")