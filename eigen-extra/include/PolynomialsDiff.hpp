
#include <type_traits>
#include <Eigen/Dense>
#include <unsupported/Eigen/Polynomials>

template<typename Vec>
struct IsDynamicVector : std::is_same<Vec,Eigen::Matrix<typename Vec::Scalar, Eigen::Dynamic, 1> >::type
{};

//! Compute the first derivative of a polynomial of a degree only known at runtime
template<typename Polynomial>
Polynomial poly_diff(const typename std::enable_if<IsDynamicVector<Polynomial>::value,Polynomial>::type& p)
{
  Polynomial df;
  df.resize(p.size()-1);
  for(unsigned int i=0; i<df.size(); i++)
  {
    df[i] = p[i+1]*(i+1); 
  }
  return df;
}

//! Compute the first derivative of a polynomial of a degree known at compile time
template<typename Polynomial>
Eigen::Matrix<typename Polynomial::Scalar,Polynomial::RowsAtCompileTime-1,1> poly_diff(const typename std::enable_if<!IsDynamicVector<Polynomial>::value,Polynomial>::type& p)
{
  Eigen::Matrix<typename Polynomial::Scalar,Polynomial::RowsAtCompileTime-1,1> df;
  for(unsigned int i=0; i<Polynomial::RowsAtCompileTime-1; i++)
  {
    df[i] = p[i+1]*(i+1); 
  }
  return df;
}

