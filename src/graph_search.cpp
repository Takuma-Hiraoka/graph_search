#include <iostream>
#include <graph_search/graph.h>
#include <algorithm>

namespace graph_search{
  bool Planner::search() {
    if (this->graph_.size() < 1) {
      std::cerr << "[graph_search] error. graph is empty!" << std::endl;
      return false;
    }

    std::vector<std::shared_ptr<TransitionCheckParam> > checkParams;
    for (unsigned int i=0; i < this->threads_; i++) {checkParams.push_back(this->generateCheckParam());}

    for (int i=0; i<this->graph_.size(); i++) this->calcHeuristic(this->graph_[i]);
    std::sort(graph_.begin(), graph_.end(),
              [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
                return a->heuristic() < b->heuristic();
              });

    std::shared_ptr<unsigned long> itr = std::make_shared<unsigned long>(0);
    std::vector<std::thread *> th(this->threads_);
    std::shared_ptr<std::mutex> threadLock = std::make_shared<std::mutex>();
    for (unsigned int i=0; i < this->threads_; i++) {
      th[i] = new std::thread([&itr, &threadLock, this, &checkParams, i]
                              { this->extendThread(itr, threadLock, this->graph_, checkParams[i]);
                              });
    }
    for (unsigned int i=0; i < this->threads_; i++) {
      th[i]->join();
      delete th[i];
    }

    if (this->goal_) {
      return true;
    } else {
      return false;
    }
  }

  void Planner::extendThread(std::shared_ptr<unsigned long> itr,
                             std::shared_ptr<std::mutex> mutex,
                             const std::vector<std::shared_ptr<Node> >& graph,
                             std::shared_ptr<TransitionCheckParam> checkParam) {
    while(true) {
      mutex->lock();
      if (((*itr) >= this->maxExtendNum_) || this->goal_) {mutex->unlock(); break;}
      else {
        if (this->debugLevel_ >= 1) std::cerr << "iter " << (*itr) << " graph size " << graph.size() << std::endl;
        (*itr)++;
        std::shared_ptr<Node> extend_node = nullptr;
        for (int i=0; i<graph.size();i++) {
          if (!graph[i]->extended()) {
            graph[i]->extended() = true;
            extend_node = graph[i];
            break;
          }
        }
        if (!extend_node) { mutex->unlock(); continue;}
        this->preCheckTransition(checkParam, extend_node);
        mutex->unlock();

        if (!(this->checkTransition(checkParam))) continue;
        if (this->isGoalSatisfied(checkParam)) {
          mutex->lock();
          this->postCheckTransition(checkParam, extend_node);
          this->goal_ = extend_node;
          mutex->unlock();
          break;
        }
        // 遷移可能かつgoalでない
        mutex->lock();
        this->postCheckTransition(checkParam, extend_node);
        std::vector<std::shared_ptr<Node> > adjacent_nodes = this->gatherAdjacentNodes(checkParam, extend_node);
        mutex->unlock();
        for (int i=0; i<adjacent_nodes.size(); i++) this->calcHeuristic(adjacent_nodes[i]);
        mutex->lock();
        this->addNodes2Graph(adjacent_nodes);
        mutex->unlock();
      }
    }
  }

  void Planner::addNodes2Graph(std::vector<std::shared_ptr<Node> > nodes) {
    this->graph_.insert(graph_.end(), nodes.begin(), nodes.end());
    std::sort(graph_.begin(), graph_.end(),
              [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
                return a->heuristic() < b->heuristic();
              });
  }
}
