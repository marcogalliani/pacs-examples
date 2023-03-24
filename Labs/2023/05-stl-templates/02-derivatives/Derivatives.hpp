#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP

/* f(x)
    f'(x) ~ (f(x+h)-f(x))/h
    f''(x) ~ (f'(x+h)-f'(x))/h

    we may use a recursive formula
    PROBLEMS: stability -> we alternate between backward and forward euler to gain stability
*/

#include <functional>

using func = std::function<double(double)>;

class Naive{
    public:
        Naive(const func &f, unsigned degree,double h):m_f(f),m_deg(degree),m_h(h){}

        double operator()(double x){
            return f_prime(x,m_deg);
        }

    private:   

        double f_prime(double x, unsigned deg){
            if(deg==0)
                return m_f(x);
            if(deg==1)
                return (m_f(x+m_h));

            return (f_prime(x+m_h,deg-1)-f_prime(x,deg-1))/m_h;
        }

        const func m_f;
        const unsigned m_deg;
        double m_h;
}

//template meta-programming: one of the nicest features of c++
/*
- template code is not real code, it has to be completed by the compiler: this fact gives us access to compiler optimization
*/

template<unsigned DEG, bool IS_FORWARD>
class Derivative{
    public:
        Derivative(const func &f, double h):m_f(f),m_h(h){}

        double operator()(double x){
            if constexp(IS_FORWARD) //being a template parameter IS_FORWARD is known at compile time
                return (m_f(x+m_h)-m_f(x))/m_h;
            else
                return (m_f(x)-m_f(x-m_h))/m_h;
        }

    private:   
        using PrevDerivative = Derivative<DEG-1,!IS_FORWARD>;
        const PrevDerivative m_f;
        double m_h;
}

template<>
class Derivative<0u> {

    public:
        Derivative(const func &f, unsigned degree,double h):m_f(f),m_deg(degree),m_h(h){}

        double operator()(double x){
            return m_f(x);
        }
    private:   
        const func m_f;
        double m_h;
    
}




#endif /* DERIVATIVES_HPP */
