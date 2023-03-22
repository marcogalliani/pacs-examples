#include "Contagion.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <execution>

Contagion::Contagion(const std::string &filename)
  : m_params(filename),
  m_time(m_params.contagion.n_timesteps+1),
  m_n_infected(m_time.size()),
  m_n_recovered(m_time.size()),
  m_n_susceptible(m_time.size())
{
  std::default_random_engine engine(m_params.seed);
  //make a loop to initialize each agent 
  //some will be healthy, some sick according to m_param
  m_agents.reserve(m_params.contagion.n_agents);
  for(size_t i=0; i < m_params.contagion.n_init_infected; i++){
    m_agents.emplace_back(engine(), State::Infected,m_params);
  }
  for(size_t i=0; i < m_params.contagion.n_agents-m_params.contagion.n_init_infected; i++){
    m_agents.emplace_back(engine(), State::Infected,m_params);
  }
  
}

void
Contagion::run() {
  for (unsigned step = 0; step < m_params.contagion.n_timesteps; step++)
  {
    m_time[step] = static_cast<double>(step)/m_params.contagion.n_timesteps_per_day;

    if(step >=1){
      //move aech agent
      std::for_each(std::execution::par_unseq,
      m_agents.begin(),
      m_agents.end(),
      [](Agent &a){return a.move()});
      
      //check the distance between each couple of agents
      //if smaller than toll, become sick
      for(size_t i= 0; i<m_agents.size();i++){
        for(size_t j=0; j<m_agents.size();j++){

          if(m_agents[i].susceptible() && m_agents[j].infected() || m_agents[j].susceptible() && m_agents[i].infected()){
            
            if(m_agents[i].is_home())
            
            const auto dx = m_agents[i].x()-m_agents[j].x();
            const auto dy = m_agents[i].y()-m_agents[j].y();
            const auto d2 = dx*dx + dy*dy;
            if(d2 < m_params.contagion.r_infection_2){
              m_agents[i].set_state(State::Infected);
              m_agents[j].set_state(State::Infected);
            }
          }

        }
      }
      
      m_n_susceptible[step] = std::count_if(m_agents.begin(),m_agents.end(),[](const Agent &a){return a.susceptible(); });
      m_n_infected[step] = std::count_if(m_agents.begin(),m_agents.end(),[](const Agent &a){return a.infected(); });
      m_n_recovered[step] = std::count_if(m_agents.begin(),m_agents.end(),[](const Agent &a){return a.recovered(); });
      
      if (m_params.dump && (step % m_params.dump==0)){
        std::ostringstream oss;
        oss << "snapshot" << std::setfill("0") << std::setw(5) << step << ".csv";
        std::ofstream file(oss.str(),std::ofstream::out);
        file << "x,y,state\n";
        for (const auto &a : m_agents)
        {
          file << a.x() << "," << a.y() << "," << static_cast<int>(a.state()) << "\n";
        }
        file.close();
      }

    }
  }
  output_results();
  
}

void
Contagion::output_results() const {
  std::ofstream file("output.csv",std::ofstream::out);
  file << "time,n_susceptible,n_infected,n_recovered\n";
  for(size_t i=0;i<m_time.size();i++){
    file << m_time[i] << "," << m_n_susceptible[i] << "," << m_n_infected[i] << "," << m_n_recovered[i] << "\n";
  }

}
