#include "document_sampler.h"

#include <random>

namespace docsler {

  LdaDocumentSampler::LdaDocumentSampler(const DoubleVector& topic_probs,
                                         const DoubleMatrix& topic_type_probs)
    : generator_{},
      topic_dist_{topic_probs.cbegin(), topic_probs.cend()},
      type_dists_(topic_type_probs.size()),
      next_id_{0}
  {
    generator_.seed(std::random_device()());

    for (unsigned i = 0; i < topic_type_probs.size(); ++i)
      type_dists_.at(i) = TypeDistribution{topic_type_probs.at(i).cbegin(),
                                           topic_type_probs.at(i).cend()};
  }

  Document LdaDocumentSampler::next(size_t length) {
    Document document{length, next_id_++};

    auto& types = document.types;
    auto& topics = document.topics;

    for (unsigned i = 0; i < length; ++i) {
      auto current_topic = next_topic();
      auto current_type = next_type(current_topic);

      types.at(i) = current_type;
      topics.at(i) = current_topic;
    }

    return document;
  }

}
