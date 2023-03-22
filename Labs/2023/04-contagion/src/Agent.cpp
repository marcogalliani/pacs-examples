#include "Agent.hpp"
#include <cmath>
#include <numeric>
#include <numbers>

Agent::Agent(size_t seed, State initial_state, const Parameters &params): 
    m_params(params),
    m_engine(seed),
    m_state(initial_state),
    m_does_sd(false),
    m_t_infection(0),
    m_is_at_pub(false),
    m_t_spent_at_pub(0){

        std::uniform_real_distribution<double> real_dist(0.0,1.0);
        m_x = real_dist(m_engine)*m_params.domain.domain_size;
        m_y = real_dist(m_engine)*m_params.domain.domain_size;
}

void Agent::move(){

    if(m_t_go_to_pub >= 0)
        m_t_go_to_pub--;
    
    if(m_is_at_pub)
        m_t_spent_at_pub++;
    else{
        m_x_bak = m_x;
        m_y_bak = m_y;
    }

    Move next_move;
    if(m_t_go_to_pub >0){
        if(m_does_sd){
            next_move = Move::Stay;
        }
        else{
            next_move = Move::Walk;
        }
    } else if(m_is_at_pub){
        if(m_t_spent_at_pub < m_params.agent.n_timesteps_at_pub){
            next_move = Move::Stay;
        }
        else{
            next_move = Move::ReturnFromPub;
        }
    }

    //we try to move until our next is inside the domain
    for(int i=0; i<1000; i++){
        //TO DO: generate a random angle alpha (which is the direction of the step), take a step of size defined in the
        // mparams in the direction aplpha, and check if it is in the domain
        auto [dx, dy] = generate_random_step();

        const auto newx = m_x + dx;
        const auto newy = m_y + dy;

        const bool inside = (newx >= 0) && (newx <= m_params.domain.domain_size) && (newy >= 0) && (newy <= m_params.domain.domain_size);

        if (inside){
            m_x = newx;
            m_y = newy;
            break;
        }

    }
}


std::pair<double,double> Agent::generate_random_step(){
    //TO DO: generate a random angle alpha (which is the direction of the step), take a step of size defined in the
    // mparams in the direction alpha
    std::uniform_real_distribution<double> real_dist(0.0, 2.0* std::numbers::pi) ;
        double alpha = real_dist(m_engine);
        double dx = m_params.agent.dr * std::cos(alpha);
        double dy = m_params.agent.dr * std::sin(alpha);

    return std::make_pair(dx,dy);
    
}

