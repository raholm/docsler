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
        document <- sample_document_cpp(size, topic_probs, model)
    else
        document <-  sample_corpus_cpp(size, topic_probs, model)

    document %>%
        dplyr::as_data_frame()
}
