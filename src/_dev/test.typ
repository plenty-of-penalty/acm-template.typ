#import "../template.typ": *
#show: styled

#{
	let T(x) = text(x, font: font-mono)
	let H(x) = text(x, font: font-mono, fill: luma(200))
	let B(x) = text(x, font: font-mono, weight: 900)
	let U(x) = underline(stroke: 1pt, offset: 2pt, text(x, font: font-mono))
	B("int ")
	T("main")
	H("() {\n")
	T("  cin >> a >> b; ")
	U("// 这句话是注释")
}
