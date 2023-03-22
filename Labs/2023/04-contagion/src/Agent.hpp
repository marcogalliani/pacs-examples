#ifndef AGENT_HPP
#define AGENT_HPP

#include "Parameters.hpp"
// docs: https://en.cppreference.com/w/cpp/numeric/random
#include <random>



enum class State{
  Susceptible, 
  Infected,
  Recovered
};

enum class Move{
  Stay,
  Walk,
  ReturnFromPub,
  GoToPub
};

class Agent
{
public:
  Agent(size_t seed, State state, const Parameters &param);

  double x() const {return m_x; }
  double y() const {return m_y; }
  State state() const {return m_state; };
  bool susceptible() const {return m_state == State::Susceptible; }
  bool recovered() const {return m_state == State::Recovered; }
  bool infected() const {return m_state == State::Infected; }

  void set_state(State s){m_state = s; }

  bool is_home() const {};

  void move();


protected:
  const Parameters &m_params;
  double m_x;
  double m_y;
  double m_x_bak;
  double m_y_bak;
  State m_state;

  bool m_does_sd;
  unsigned int m_t_infection;
  bool m_is_at_pub;
  unsigned m_t_spent_at_pub;
  int m_t_go_to_pub;

  //declaring a member random engine
  std::default_random_engine m_engine;

  //utility
  std::pair<double,double> generate_random_step();

};

#endif /* AGENT_HPP */
