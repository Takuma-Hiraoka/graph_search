#ifndef GRAPH_SEARCH_NODE_H
#define GRAPH_SEARCH_NODE_H

#include <memory>
#include <vector>

namespace graph_search{
  class Node{
  public:
    std::weak_ptr<Node> parent() {return this->parent_;}
    double heuristic() {return 1.0;}    
  private:
    std::weak_ptr<Node> parent_;
  };
}

#endif
