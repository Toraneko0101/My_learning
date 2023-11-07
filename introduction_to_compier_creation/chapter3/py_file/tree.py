import pydot

G = pydot.Dot()
G.add_edge(pydot.Edge('A', '"B_1"'))
G.add_edge(pydot.Edge('A', '"B_2"'))

G.write_png("nodes.png")