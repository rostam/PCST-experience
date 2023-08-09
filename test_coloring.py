import PCST
import networkx as nx
import matplotlib.pyplot as plt

def visualize_graph(nodes, edges, colors):
    G = nx.Graph()
    for edge in edges:
        G.add_edge(edge.node1, edge.node2, weight=edge.cost)
    pos = nx.spring_layout(G)  # positions for all nodes

    # nodes
    nx.draw_networkx_nodes(G, pos, node_size=700, node_color=colors, cmap=plt.cm.rainbow)

    # edges
    nx.draw_networkx_edges(G, pos, width=6)

    # labels
    labels = {node.id: str(node.id) + '\n' + str(node.prize) for node in nodes}
    nx.draw_networkx_labels(G, pos, labels=labels, font_size=16, font_family='sans-serif')

    plt.axis('off')
    plt.show()

def visualize_tree(tree, colors):
    G = nx.Graph()
    for edge in tree:
        G.add_edge(edge.node1, edge.node2, weight=edge.cost)
    pos = nx.spring_layout(G)  # positions for all nodes

    # nodes
    nx.draw_networkx_nodes(G, pos, node_size=700, node_color=colors, cmap=plt.cm.rainbow)

    # edges
    nx.draw_networkx_edges(G, pos, width=6)

    # labels
    labels = {node.id: str(node.id) + '\n' + str(node.prize) for node in nodes}
    nx.draw_networkx_labels(G, pos, font_size=20, font_family='sans-serif')

    plt.axis('off')
    plt.show()

# ... [Your nodes and edges definition]

colors = PCST.greedyVertexColoring(edges, len(nodes))

visualize_graph(nodes, edges, colors)
visualize_tree(tree, colors)
