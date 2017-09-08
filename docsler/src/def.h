#ifndef DOCSLER_DEF_H_
#define DOCSLER_DEF_H_

#include <string>
#include <vector>
#include <random>

namespace docsler {

  using String = std::string;
  using size_t = std::size_t;

  template<typename T>
  using Vector = std::vector<T>;

  using Type = size_t;
  using Topic = size_t;

  using IntVector = Vector<size_t>;
  using DoubleVector = Vector<double>;
  using TypeVector = Vector<Type>;
  using TopicVector = Vector<Topic>;

  using IntMatrix = Vector<IntVector>;
  using DoubleMatrix = Vector<DoubleVector>;
  using TypeMatrix = Vector<TypeVector>;
  using TopicMatrix = Vector<TopicVector>;

  // Random
  using RandomNumberGenerator = std::mt19937;
  using TopicDistribution = std::discrete_distribution<Topic>;
  using TopicDistributionVector = Vector<TopicDistribution>;
  using TypeDistribution = std::discrete_distribution<Type>;
  using TypeDistributionVector = Vector<TypeDistribution>;

} // namespace docsler


#endif // DOCSLER_DEF_H_
