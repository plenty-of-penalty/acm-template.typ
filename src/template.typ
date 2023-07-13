#let project(title: "", authors: (), body) = {
  set document(author: authors, title: title)
  set page(
    margin: (left: 10mm, right: 10mm, top: 18mm, bottom: 18mm),
    numbering: "1",
    number-align: center,

    header: [
      #locate(loc => {
        if query(selector(heading.where(level: 1)).before(loc), loc).len() == 0 {
          "ACM Template"
        } else {
          counter(heading).display()
          " "
          query(selector(heading.where(level: 1)).before(loc), loc).last().body
        }
      })
      #v(-0.4em)
      #line(length: 100%, stroke: 0.5pt)
    ],
    header-ascent: 30%,
  )

  set text(
    font: (
      "New Computer Modern",
      "Source Han Serif",
      "Source Han Serif SC VF",
    ),
    size: 10pt,
    lang: "zh",
  )

  show math.equation: set text(weight: 400)

  show par: set block(above: 0.75em, below: 0.75em)

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
  show: columns.with(2, gutter: 1em)

  show raw.where(block: true): it => {
    let codes = it.text.split("\n")
    let font = (font: ("Cascadia Code"), size: 0.95em)
  
    set text(..font)
    
    set par(justify: false)
    grid(
      columns: (100%, 98%),
      column-gutter: -98%,
      block(width: 98%, inset: 1em, for i in range(codes.len()) {
        box(width: 0pt, align(right, text(
          style: "italic",
          size: 6.5pt,
          fill: rgb("#a0a0a0"),
          str(i + 1) + h(0em)
        )))
        hide(codes.at(i))
        linebreak()
      }),
      block(width: 100%, inset: 1em, it),
    )
  }

  body
}


#let importCode(file, namespace: none, lang: "cpp") = {
  let source_code = read(file)
  let code = ""
  let note = ""
  let flag = false
  let firstlines = true

  for line in source_code.split("\n") {
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