#ifndef BIOINFOI_GRAPH_H
#define BIOINFOI_GRAPH_H

#include <algorithm>
#include <list>
#include <memory>
#include <vector>
#include <iostream>

/**
 * Generic implementation of a graph class.
 */
template <typename NodeLabel> class Graph
{
  public:

  	/**
  	 * Node class that contains a label and all outgoing edges. Ingoing
  	 * edges are not needed.
  	 */
	struct Node
	{
		explicit Node(const NodeLabel& l) : label(l) {}
		NodeLabel label;
		std::vector<std::pair<Node*, size_t>> out_edges;
	};

	/**
  	 * Edge class that contains the source and target node as well as
  	 * an edge weight.
  	 */
	struct Edge
	{
		Edge(Node* a, Node* b, size_t w) : source(a), target(b), weight(w) {}
		Node* source;
		Node* target;
		size_t weight;
	};

	/**
	 * Defines how the data is stored internally.
	 *
	 * Can be changed if desired.
	 */
	using NodeContainer = std::list<Node>;
	using node_iterator = typename NodeContainer::iterator;
	using const_node_iterator = typename NodeContainer::const_iterator;

	/**
	 * Default constructor.
	 * TODO 
	 */
	Graph() = default; // Was muss man hier genau machen?

	/**
	 * Detailed constructor that also creates the nodes
	 * of the Graph.
	 * TODO-done
	 */
	explicit Graph(const std::vector<NodeLabel>& new_nodes) {
        for (const auto& label : new_nodes) {
            addNode(label);
        }
    }

	/**
	 * Node iterators.
	 * TODO-done
	 */
	node_iterator beginNodes() { return nodes_.begin(); }
    node_iterator endNodes() { return nodes_.end(); }

	const_node_iterator beginNodes() const { return nodes_.begin(); }
    const_node_iterator endNodes() const { return nodes_.end(); }

	/**
	 * Creates a Node with a distinct label and return a pointer to the
	 * new Node.
	 * TODO-done
	 */
	Node* addNode(const NodeLabel& label) {
        nodes_.emplace_back(label);
        return &nodes_.back();
    }

	/**
	 * Checks if there is a Edge between n1 and n2 and returns an iterator
	 * pointing to the found edge. Points to
	 * std::end(std::vector<std::pair<Node*, size_t>>) if the edge is not
	 * present in the graph.
	 * TODO-done
	 */
	typename std::vector<std::pair<Node*, size_t>>::const_iterator findEdge(const Node* n1, const Node* n2) const {
	
    for (auto it = n1->out_edges.begin(); it != n1->out_edges.end(); ++it) { // Durchläuft die out_edges von n1
        if (it->first == n2) {  	// it führt zu n2?
            return it;           	// -> it wird zurück gegeben
        }
    }
    return n1->out_edges.end();
}

	/**
	 * Creates an edge and returns a copy of it.
	 * TODO-done
	 */
	Edge addEdge(Node* n1, Node* n2, size_t weight = 0){
        n1->out_edges.emplace_back(n2, weight);
        return Edge(n1, n2, weight);
    }

	/**
	 * Removes the given edge.
	 * TODO-done
	 */
	void removeEdge(const Edge& e) {
    for (auto it = e.source->out_edges.begin(); it != e.source->out_edges.end(); ) { // Durchläuft die out_edges vom Knoten, von der e beginnt
        if (it->first == e.target) {   				// it hat gleiches target (und source) wie e?
            it = e.source->out_edges.erase(it);  	// -> it wird gelöscht und es wird weiter iteriert durch erase()
        } else {
            ++it;
        }
    }
}


	/**
	 * If the graph contains an edge between n1 and n2,
	 * it is removed.
	 * TODO-done
	 */
	void removeEdge(Node* n1, const Node* n2) {
    for (auto it = n1->out_edges.begin(); it != n1->out_edges.end(); ) { // Durchläuft die out_edges von n1
        if (it->first == n2) {    					// it führt zu n2?
            it = n1->out_edges.erase(it);  			// -> it wird gelöscht und es wird weiter iteriert durch erase()
        } else {
            ++it;
        }
    }
}

	/**
	 * Performs an edge contraction. (see: Wikipedia)
	 * TODO-done?
	 */
	Node* contractEdge(const Edge& rem) {
        for (auto& edge : rem.target->out_edges) {		// Durchläuft die out_edges vom target von rem
            rem.source->out_edges.push_back(edge);		// Fügt entsprechend out_edges vom target bei der source hinzu
        }
        removeEdge(rem);								// Entfernt rem (hinterlässt einen nicht erreichbaren Knoten rem.target)
        return rem.source;								// der übrig bleibende/neue rem wird zurück gegeben?
    }

	/**
	 * Return the number of nodes in the graph.
	 * TODO-done
	 */
	size_t numNodes() const {
        return nodes_.size();
    }

	template <typename type>
	friend std::ostream& operator << (std::ostream& strm, const Graph<type>& graph);

  private:
	NodeContainer nodes_;
};

/**
 * TODO 
 */
template <typename NodeLabel>
std::ostream& operator<<(std::ostream& strm, const Graph<NodeLabel>& graph) {
    strm << "digraph Graph {\n";
    strm << "  nodesep=0.7;\n"; 					// siehe  https://de.wikipedia.org/wiki/Graphviz#Beispiel
    for (const auto& node : graph.nodes_) { 		// Durchläuft jeden Knoten
        for (const auto& edge : node.out_edges) {  	// Durchläuft alle ausgehenden Kanten
            strm << " " << node.label << " -> " << (edge.first->label) << " [label=\"" << edge.second << "\"];\n"; // siehe  https://de.wikipedia.org/wiki/Graphviz#Beispiel
        }
    }
    strm << "}";
    return strm;
}

#endif // BIOINFOI_GRAPH_H