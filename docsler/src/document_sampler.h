#ifndef DOCSLER_DOCUMENT_SAMPLER_H_
#define DOCSLER_DOCUMENT_SAMPLER_H_

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
    size_t next_id_;

    RandomNumberGenerator generator_;
    TopicDistribution topic_dist_;
    TypeDistributionVector type_dists_;

    Topic next_topic();
    Type next_type(const Topic& topic);

  };

} // namespace docsler

#endif // DOCSLER_DOCUMENT_SAMPLER_H_
