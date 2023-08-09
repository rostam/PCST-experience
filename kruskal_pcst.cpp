#include <vector>
#include <algorithm>
#include <cassert>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <set>

namespace py = pybind11;

class Edge {
public:
    int node1;
    int node2;
    double cost;
    Edge(int node1, int node2, double cost) : node1(node1), node2(node2), cost(cost) {}
};

class Node {
public:
    int id;
    double prize;
    Node(int id, double prize) : id(id), prize(prize) {}
};

// Function to find the parent of a node in the disjoint set
int find(std::vector<int>& parent, int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// Function to union two sets
void unionSet(std::vector<int>& parent, int i, int j) {
    int i_set = find(parent, i);
    int j_set = find(parent, j);
    parent[i_set] = j_set;
}

std::vector<Edge> kruskalPCST(std::vector<Node>& nodes, std::vector<Edge>& edges) {
    // Sort edges in increasing order of cost and decreasing order of prize-to-cost ratio
    std::sort(edges.begin(), edges.end(), [&nodes](const Edge& a, const Edge& b) {
        double ratioA = std::max(nodes[a.node1].prize, nodes[a.node2].prize) / a.cost;
        double ratioB = std::max(nodes[b.node1].prize, nodes[b.node2].prize) / b.cost;
        if (a.cost == b.cost) {
            return ratioA > ratioB;
        } else {
            return a.cost < b.cost;
        }
    });

    std::vector<int> parent(nodes.size(), -1);
    std::vector<Edge> result;

    for (const auto& edge : edges) {
        int x = find(parent, edge.node1);
        int y = find(parent, edge.node2);

        // If including this edge does not form a cycle and the cost of the edge is less than the prize of either node
        if (x != y && (edge.cost < nodes[edge.node1].prize || edge.cost < nodes[edge.node2].prize)) {
            result.push_back(edge);
            unionSet(parent, x, y);
        }
    }

    return result;
}


double calculateCost(const std::vector<Edge>& tree) {
    double cost = 0;
    for (const auto& edge : tree) {
        cost += edge.cost;
    }
    return cost;
}

double calculatePrize(const std::vector<Edge>& tree, const std::vector<Node>& nodes) {
    double prize = 0;
    std::vector<bool> included(nodes.size(), false);
    for (const auto& edge : tree) {
        if (!included[edge.node1]) {
            prize += nodes[edge.node1].prize;
            included[edge.node1] = true;
        }
        if (!included[edge.node2]) {
            prize += nodes[edge.node2].prize;
            included[edge.node2] = true;
        }
    }
    return prize;
}


std::set<int> getAvailableColors(int node, const std::vector<std::set<int>>& adjacencyList, const std::vector<int>& colors) {
    std::set<int> neighborColors;
    for (int neighbor : adjacencyList[node]) {
        if (colors[neighbor] != -1) {
            neighborColors.insert(colors[neighbor]);
        }
    }

    return neighborColors;
}

std::vector<int> greedyVertexColoring(std::vector<Edge>& edges, int numNodes) {
    // Create an adjacency list
    std::vector<std::set<int>> adjacencyList(numNodes);
    for (const auto& edge : edges) {
        adjacencyList[edge.node1].insert(edge.node2);
        adjacencyList[edge.node2].insert(edge.node1);
    }

    std::vector<int> colors(numNodes, -1); // -1 indicates no color assigned

    for (int i = 0; i < numNodes; i++) {
        std::set<int> unavailableColors = getAvailableColors(i, adjacencyList, colors);
        int color = 0;
        while (unavailableColors.find(color) != unavailableColors.end()) {
            color++;
        }
        colors[i] = color;
    }

    return colors;
}

PYBIND11_MODULE(PCST, m) {
    py::class_<Node>(m, "Node")
        .def(py::init([](int id, double prize) { return new Node(id, prize); }), py::arg("id"), py::arg("prize"))
        .def_readwrite("id", &Node::id)
        .def_readwrite("prize", &Node::prize);

    py::class_<Edge>(m, "Edge")
        .def(py::init([](int node1, int node2, double cost) { return new Edge(node1, node2, cost); }), py::arg("node1"), py::arg("node2"), py::arg("cost"))
        .def_readwrite("node1", &Edge::node1)
        .def_readwrite("node2", &Edge::node2)
        .def_readwrite("cost", &Edge::cost);

    m.def("kruskalPCST", &kruskalPCST, "A function that solves the PCST problem using a modified Kruskal's algorithm");
    m.def("greedyVertexColoring", &greedyVertexColoring, "A function that colors the vertices using a greedy algorithm");
}

void test1() {
    std::vector<Node> nodes = {{0, 1}, {1, 2}, {2, 3}};
    std::vector<Edge> edges = {{0, 1, 1}, {1, 2, 2}};
    std::vector<Edge> tree = kruskalPCST(nodes, edges);
    assert(calculateCost(tree) <= 3);
    assert(calculatePrize(tree, nodes) >= 6);
}

void test2() {
    std::vector<Node> nodes = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    std::vector<Edge> edges = {{0, 1, 1}, {1, 2, 2}, {2, 3, 3}};
    std::vector<Edge> tree = kruskalPCST(nodes, edges);
    assert(calculateCost(tree) <= 6);
    assert(calculatePrize(tree, nodes) >= 10);
}

void test3() {
    std::vector<Node> nodes = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}};
    std::vector<Edge> edges = {{0, 1, 1}, {1, 2, 2}, {2, 3, 3}, {3, 4, 4}};
    std::vector<Edge> tree = kruskalPCST(nodes, edges);
    assert(calculateCost(tree) <= 10);
    assert(calculatePrize(tree, nodes) >= 15);
}

void test4() {
    std::vector<Node> nodes = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}};
    std::vector<Edge> edges = {{0, 1, 1}, {1, 2, 2}, {2, 3, 3}, {3, 4, 4}};
    std::vector<int> coloring = greedyVertexColoring(edges, nodes.size());
    assert(coloring.size() <= 2);
    // assert(calculatePrize(tree, nodes) >= 15);
}


int main() {
    test1();
    test2();
    test3();
    test4();
    return 0;
}
