#include "corpus_sampler.h"

#include <exception>
#include <stdexcept>

namespace docsler {

  LdaCorpusSampler::LdaCorpusSampler(size_t ndocs,
                                     const DoubleVector& topic_probs,
                                     const DoubleMatrix& topic_type_probs)
    : next_id_{0},
      ndocs_{ndocs},
      generator_{},
      topic_dists_(1),
      type_dists_(topic_type_probs.size())
  {
    generator_.seed(std::random_device()());

    topic_dists_.at(0) = TopicDistribution{topic_probs.cbegin(), topic_probs.cend()};

    for (unsigned i = 0; i < topic_type_probs.size(); ++i)
      type_dists_.at(i) = TypeDistribution{topic_type_probs.at(i).cbegin(),
                                           topic_type_probs.at(i).cend()};
  }

  LdaCorpusSampler::LdaCorpusSampler(size_t ndocs,
                                     const DoubleMatrix& topic_probs,
                                     const DoubleMatrix& topic_type_probs)
    : next_id_{0},
      ndocs_{ndocs},
      generator_{},
      topic_dists_(ndocs),
      type_dists_(topic_type_probs.size())
  {
    generator_.seed(std::random_device()());

    if (ndocs != topic_probs.size())
      throw std::invalid_argument("The number of topic probabilities mismatches the number of documents.");

    for (unsigned i = 0; i < ndocs; ++i)
      topic_dists_.at(i) = TopicDistribution{topic_probs.at(i).cbegin(),
                                             topic_probs.at(i).cend()};

    for (unsigned i = 0; i < topic_type_probs.size(); ++i)
      type_dists_.at(i) = TypeDistribution{topic_type_probs.at(i).cbegin(),
                                           topic_type_probs.at(i).cend()};
  }

  Corpus LdaCorpusSampler::next(const IntVector& length) {
    if (length.size() != ndocs_)
      throw std::invalid_argument("The number of lengths mismatches the number of documents.");

    unsigned size = std::accumulate(length.cbegin(), length.cend(), 0);
    Corpus corpus{size};

    auto& doc_ids = corpus.doc_ids;
    auto& types = corpus.types;
    auto& topics = corpus.topics;

    size_t current_doc = next_id_++;
    size_t cumsum_of_processed_doc_lengths = 0;

    for (unsigned i = 0; i < size; ++i) {
      auto current_topic = next_topic(current_doc);
      auto current_type = next_type(current_topic);

      doc_ids.at(i) = current_doc;
      types.at(i) = current_type;
      topics.at(i) = current_topic;

      if ((i - cumsum_of_processed_doc_lengths) == length.at(current_doc))
        cumsum_of_processed_doc_lengths += length.at(current_doc++);
    }

    return corpus;
  }

  Corpus LdaCorpusSampler::next(size_t length) {
    unsigned size = ndocs_ * length;
    Corpus corpus{size};

    auto& doc_ids = corpus.doc_ids;
    auto& types = corpus.types;
    auto& topics = corpus.topics;

    size_t current_doc = next_id_++;
    size_t cumsum_of_processed_doc_lengths = 0;

    for (unsigned i = 0; i < size; ++i) {
      auto current_topic = next_topic(current_doc);
      auto current_type = next_type(current_topic);

      doc_ids.at(i) = current_doc;
      types.at(i) = current_type;
      topics.at(i) = current_topic;

      if ((i - cumsum_of_processed_doc_lengths) == length) {
        cumsum_of_processed_doc_lengths += length;
        ++current_doc;
      }
    }

    return corpus;
  }

  inline Topic LdaCorpusSampler::next_topic(const size_t& doc) {
    if (topic_dists_.size() == 1)
      return topic_dists_.at(0)(generator_);
    return topic_dists_.at(doc)(generator_);
  }

  inline Type LdaCorpusSampler::next_type(const Topic& topic) {
    return type_dists_.at(topic)(generator_);
  }

}
