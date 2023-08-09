import PCST
import networkx as nx
import matplotlib.pyplot as plt

def visualize_graph(nodes, edges):
    G = nx.Graph()
    for edge in edges:
        G.add_edge(edge.node1, edge.node2, weight=edge.cost)
    pos = nx.spring_layout(G)  # positions for all nodes

    # nodes
    nx.draw_networkx_nodes(G, pos, node_size=700)

    # edges
    nx.draw_networkx_edges(G, pos, width=6)

    # labels
    labels = {node.id: str(node.id) + '\n' + str(node.prize) for node in nodes}
    nx.draw_networkx_labels(G, pos, labels=labels, font_size=16, font_family='sans-serif')

    plt.axis('off')
    plt.show()

def visualize_tree(tree):
    G = nx.Graph()
    for edge in tree:
        G.add_edge(edge.node1, edge.node2, weight=edge.cost)
    pos = nx.spring_layout(G)  # positions for all nodes

    # nodes
    nx.draw_networkx_nodes(G, pos, node_size=700)

    # edges
    nx.draw_networkx_edges(G, pos, width=6)

    # labels
    labels = {node.id: str(node.id) + '\n' + str(node.prize) for node in nodes}
    nx.draw_networkx_labels(G, pos, font_size=20, font_family='sans-serif')

    plt.axis('off')
    plt.show()

# nodes = [PCST.Node(id=0, prize=1), PCST.Node(id=1, prize=2), PCST.Node(id=2, prize=3)]
# edges = [PCST.Edge(node1=0, node2=1, cost=1), PCST.Edge(node1=1, node2=2, cost=2)]

nodes = [
    PCST.Node(id=0, prize=1),
    PCST.Node(id=1, prize=2),
    PCST.Node(id=2, prize=3),
    PCST.Node(id=3, prize=4),
    PCST.Node(id=4, prize=5),
    PCST.Node(id=5, prize=6),
    PCST.Node(id=6, prize=7),
    PCST.Node(id=7, prize=8),
    PCST.Node(id=8, prize=9),
    PCST.Node(id=9, prize=10)
]

edges = [
    PCST.Edge(node1=0, node2=1, cost=1),
    PCST.Edge(node1=1, node2=2, cost=2),
    PCST.Edge(node1=2, node2=3, cost=3),
    PCST.Edge(node1=3, node2=4, cost=4),
    PCST.Edge(node1=4, node2=5, cost=5),
    PCST.Edge(node1=5, node2=6, cost=6),
    PCST.Edge(node1=6, node2=7, cost=7),
    PCST.Edge(node1=7, node2=8, cost=8),
    PCST.Edge(node1=8, node2=9, cost=9),
    PCST.Edge(node1=0, node2=9, cost=10),
    PCST.Edge(node1=1, node2=8, cost=11),
    PCST.Edge(node1=2, node2=7, cost=12),
    PCST.Edge(node1=3, node2=6, cost=13),
    PCST.Edge(node1=4, node2=5, cost=14),
    PCST.Edge(node1=0, node2=5, cost=15)
]

tree = PCST.kruskalPCST(nodes, edges)

# print(tree)
visualize_graph(nodes, edges)
visualize_tree(tree)
