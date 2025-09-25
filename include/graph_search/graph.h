#ifndef GRAPH_SEARCH_GRAPH_H
#define GRAPH_SEARCH_GRAPH_H

#include <graph_search/node.h>
#include <thread>
#include <mutex>

namespace graph_search{
  class Planner{
  public:
    class TransitionCheckParam {
    };
    bool search();
    void addNodes2Graph(std::vector<std::shared_ptr<Node> > nodes);
    void extendThread(std::shared_ptr<unsigned long> itr,
		      std::shared_ptr<std::mutex> mutex,
		      const std::vector<std::shared_ptr<Node> >& graph,
		      std::shared_ptr<TransitionCheckParam> checkParam);
    const int& debugLevel() const {return this->debugLevel_;}
    int& debugLevel() {return this->debugLevel_;}
    const std::vector<std::shared_ptr<Node> >& graph() const {return this->graph_;}
    std::vector<std::shared_ptr<Node> >& graph() {return this->graph_;}
    std::shared_ptr<Node> goal() {return this->goal_;}
    const unsigned long& maxExtendNum() const {return this->maxExtendNum_;}
    unsigned long& maxExtendNum() {return this->maxExtendNum_;}
    const unsigned int& threads() const {return this->threads_;}
    unsigned int& threads() {return this->threads_;}

    virtual std::shared_ptr<TransitionCheckParam> generateCheckParam() = 0;
    virtual void preCheckTransition(std::shared_ptr<TransitionCheckParam> checkParam, std::shared_ptr<Node> extend_node) = 0; // extend_nodeの情報をcheckParamに取り込む
    virtual void postCheckTransition(std::shared_ptr<TransitionCheckParam> checkParam, std::shared_ptr<Node> extend_node) = 0; // checkParamの情報をextend_nodeに取り込む
    virtual bool checkTransition(std::shared_ptr<TransitionCheckParam> checkParam) = 0;
    virtual bool isGoalSatisfied(std::shared_ptr<TransitionCheckParam> checkParam) = 0;
    virtual std::vector<std::shared_ptr<Node> > gatherAdjacentNodes(std::shared_ptr<TransitionCheckParam> checkParam, std::shared_ptr<Node> extend_node) = 0;
    virtual void calcHeuristic(std::shared_ptr<Node> node) = 0;

  private:
    int debugLevel_ = 0;
    std::vector<std::shared_ptr<Node> > graph_;
    std::shared_ptr<Node> goal_ = nullptr;
    unsigned long maxExtendNum_ = 1e6;
    unsigned int threads_ = 1;
  };
}

#endif
