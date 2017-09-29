#include <Rcpp.h>

#include "def.h"
#include "util.h"
#include "document_sampler.h"
#include "corpus_sampler.h"

using namespace docsler;

// [[Rcpp::export]]
Rcpp::DataFrame sample_document_by_lda_cpp(size_t length,
                                        const Rcpp::NumericVector& topic_probs,
                                        const Rcpp::NumericMatrix& topic_type_probs) {
  LdaDocumentSampler sampler{convert_from_R(topic_probs),
      convert_from_R(topic_type_probs)};
  Document document = sampler.next(length);
  IntVector doc_ids(length, document.id);
  return Rcpp::DataFrame::create(Rcpp::Named("doc") = doc_ids,
                                 Rcpp::Named("type") = document.types,
                                 Rcpp::Named("topic") = document.topics);
}

// [[Rcpp::export]]
Rcpp::DataFrame sample_corpus_by_lda_cpp(const Rcpp::IntegerVector length,
                                      const Rcpp::NumericMatrix& topic_probs,
                                      const Rcpp::NumericMatrix& topic_type_probs) {
  LdaCorpusSampler sampler{(size_t) length.size(),
      convert_from_R(topic_probs),
      convert_from_R(topic_type_probs)};
  Corpus corpus = sampler.next(convert_from_R(length));
  return Rcpp::DataFrame::create(Rcpp::Named("doc") = corpus.doc_ids,
                                 Rcpp::Named("type") = corpus.types,
                                 Rcpp::Named("topic") = corpus.topics);
}
