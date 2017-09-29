#' Latent Dirichlet Allocation
#'
#' Samples documents based on the generative process in Latent Dirichlet Allocation.
#'
#' @param size An integer or vector of integers.
#' @param model A matrix of probabilities. Model[i, j] should be the probability of word j given topic i. The value can either be a probability, [0, 1], or a frequency, [0, inf).
#' @param alpha A numeric or vector of numerics. The parameter(s) to the topic dirichlet distribution. The distribution will be symmetric if alpha is a single value.
#'
#' @export
lda <- function(size, model, alpha) {
    checkr::assert_integer(size, lower=1)
    checkr::assert_numeric(alpha, lower=0)

    n <- length(size)
    ntopics <- nrow(model)

    if (length(alpha) != 1 & length(alpha) != ntopics)
        stop("length of alpha has to be either one or the number of topics.")

    if (length(alpha) == 1)
        alpha <- rep(alpha, ntopics)

    topic_probs <- MCMCpack::rdirichlet(n, alpha)

    if (n == 1)
        document <- sample_document_by_lda_cpp(size, topic_probs, model)
    else
        document <-  sample_corpus_by_lda_cpp(size, topic_probs, model)

    dplyr::as_data_frame(document)
}
