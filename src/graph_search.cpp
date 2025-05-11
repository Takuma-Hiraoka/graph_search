#include <iostream>
#include <graph_search/graph.h>

namespace graph_search{
  bool Graph::search() {
    if (this->graph_.size() < 1) {
      std::cerr << "[graph_search] error. graph is empty!" << std::endl;
      return false;
    }
    while (true) {
      std::shared_ptr extend_node = this->graph_.front();
      std::vector<std::shared_ptr> adjacent_nodes = Graph::gatherAdjacentNodes(extend_node);
      Graph::addNodes(adjacent_nodes);
    }
  }
  bool Graph::isGoalSatisfied() {
    return true;
  }
}
