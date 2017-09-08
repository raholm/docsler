#ifndef DOCSLER_UTIL_H_
#define DOCSLER_UTIL_H_

#include "def.h"

namespace docsler {

  struct Document {
    explicit Document(size_t length, size_t id)
      : id{id},
        types(length),
        topics(length) {}

    size_t id;
    TypeVector types;
    TopicVector topics;

  };

  class DocumentSampler {
  public:
    virtual ~DocumentSampler() = default;

    virtual Document next(size_t length) = 0;

  private:

  };

  class LdaDocumentSampler : public DocumentSampler {
  public:
    LdaDocumentSampler(const DoubleVector& topic_probs,
                       const DoubleMatrix& topic_type_probs);

    Document next(size_t length) override;

  private:
    RandomNumberGenerator generator_;
    TopicDistribution topic_dist_;
    TypeDistributionVector type_dists_;
    size_t next_id_;

    inline Topic next_topic() {
      return topic_dist_(generator_);
    }

    inline Type next_type(const Topic& topic) {
      return type_dists_.at(topic)(generator_);
    }

  };

} // namespace docsler

#endif // DOCSLER_UTIL_H_
