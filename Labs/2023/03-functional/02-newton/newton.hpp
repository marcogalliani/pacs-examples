#ifndef NEWTON_HPP
#define NEWTON_HPP

#include <iostream>
#include <limits>

class NewtonSolver
{
private:
    const std::function<double(double)> &m_f;
    const std::function<double(double)> &m_df;
    const double m_toll_res;
    const double m_toll_incr;
    const int m_max_it;

    double m_x; //current guess for the 0
    double m_df_x; //current value of the derivative valued in x
    double m_res; //current value of the residual
    double m_iter; //current iteration

public:
    NewtonSolver(const std::function<double(double)> &f,
    const std::function<double(double)> &df,
    double toll_res = std::numeric_limits<double>::epsilon*1000.0,
    double toll_incr = std::numeric_limits<double>::epsilon*1000.0,
    unsigned int max_it = 100
    ):
    m_f(f),
    m_df(df),
    m_toll_res(toll_res),
    m_toll_incr(toll_incr),
    m_max_it(max_it),
    m_x(0),
    m_df_x(0){}

    void solve(double x0){
        m_x = x0;
        for(m_iter = 0; m_iter < m_max_it; m_iter++){
            m_res = m_f(m_x)
            if(std::abs(m_res)<m_toll_res)
                break;
                
            m_df_x=m_df(m_x);
            m_dx = m_res/

        }
    }


};




#endif // NEWTON_HPP