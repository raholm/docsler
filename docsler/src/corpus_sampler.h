#ifndef DOCSLER_CORPUS_SAMPLER_H_
#define DOCSLER_CORPUS_SAMPLER_H_

#include "def.h"

namespace docsler {

  struct Corpus {
    explicit Corpus(size_t length)
      : doc_ids(length),
        types(length),
        topics(length) {}

    IntVector doc_ids;
    TypeVector types;
    TopicVector topics;

  };

  class CorpusSampler {
  public:
    virtual ~CorpusSampler() = default;

    virtual Corpus next(const IntVector& length) = 0;
    virtual Corpus next(size_t length) = 0;

  private:

  };

  class LdaCorpusSampler : public CorpusSampler {
  public:
    LdaCorpusSampler(size_t ndocs,
                     const DoubleVector& topic_probs,
                     const DoubleMatrix& topic_type_probs);
    LdaCorpusSampler(size_t ndocs,
                     const DoubleMatrix& topic_probs,
                     const DoubleMatrix& topic_type_probs);

    Corpus next(const IntVector& length) override;
    Corpus next(size_t length) override;

  private:
    size_t next_id_;
    size_t ndocs_;

    RandomNumberGenerator generator_;
    TopicDistributionVector topic_dists_;
    TypeDistributionVector type_dists_;

    Topic next_topic(const size_t& doc);
    Type next_type(const Topic& topic);

  };

} // namespace docsler

#endif // DOCSLER_CORPUS_SAMPLER_H_
