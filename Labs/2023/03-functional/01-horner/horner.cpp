#include "horner.hpp"


#include <algorithm>
#include <cmath>

double
eval(const std::vector<double> &a, const double &x)
{
    double res=a[0];
    for(size_t i=1; i<a.size();i++)
        res += a[i]*std::pow(x,i);
    return res;
}

double
eval_horner(const std::vector<double> &a, const double &x)
{
    double result=a.back();
    for(size_t i=a.size()-1;i>=0;i--){
        result=result*x+a[i];
    }
    return result;
}

std::vector<double>
evaluate_poly(const std::vector<double> &points,
              const std::vector<double> &a,
              eval_method                method)
{

    std::vector<double> result;
    /* 
    //POINT1
    result.reserve(points.size());
    for (const auto &p:points){
        result.push_back(method(a,p));
    }
    */

   //POINT2: TO BE COMPLETED
    const auto unary_op = [&](double x){return method(a,x);};

    std::transform(points.begin(),points.end(),result.begin(),unary_op);
    return result;

}
