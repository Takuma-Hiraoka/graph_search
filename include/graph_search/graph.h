#ifndef GRAPH_SEARCH_GRAPH_H
#define GRAPH_SEARCH_GRAPH_H

#include <graph_search/node.h>

namespace graph_search{
  class Graph{
  public:
    bool search();
    bool isGoalSatisfied();
    std::vector<std::shared_ptr> gatherAdjacentNodes(std::shared_ptr extend_node);
    void addNodes(std::vector<std::shared_ptr> nodes);
  private:
    std::vector<std::shared_ptr> graph_;
  };
}

#endif
