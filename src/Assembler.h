#ifndef BIOINFO1_ASSEMBLER_H
#define BIOINFO1_ASSEMBLER_H

#include "Graph.h"
#include "Sequence.h"
#include "DNA.h"

#include <unordered_map>

class Assembler
{
  public:
  	/**
  	 * Make things pretty.
  	 */
	using Seq = Sequence<Alphabet::DNA>;
	using OGraph = Graph<Seq>;

	/**
	 * Creates an overlap graph.
	 * TODO-done
	 */
	Assembler(const std::vector<Assembler::Seq>& sequences);

	/**
	 * Getter for graph_
	 * TODO-done
	 */
	OGraph& getGraph();

  public:
	/**
	 * Initializes the appropriate Edges between the given nodes to create
	 * the Overlay-Graph.
	 * TODO-done
	 */
	void buildEdges();

	OGraph graph_;

	std::vector<OGraph::Edge> edges_;
	std::unordered_map<OGraph::Node*, bool> valid_nodes_;
};

#endif // BIOINFO1_ASSEMBLER_H

