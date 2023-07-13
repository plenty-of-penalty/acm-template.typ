#let project(title: "", authors: (), body) = {
  set document(author: authors, title: title)
  set page(
    margin: (left: 10mm, right: 10mm, top: 15mm, bottom: 15mm),
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
      #v(-0.25em)
      #line(length: 100%, stroke: 0.5pt)
    ],
    header-ascent: 30%,
  )
  set text(font: "New Computer Modern", lang: "en")
  show math.equation: set text(weight: 400)

  show par: set block(above: 0.75em, below: 0.75em)

  set heading(numbering: "1.1")

  show heading: it => {
    if it.level > 2 {
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

  body
}