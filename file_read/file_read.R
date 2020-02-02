#!/usr/bin/Rscript --vanilla
# a program in R language
# R version 3.4.4 (2018-03-15)

FILENAME <-  './eng-uk_web_2002_1M-words.txt'

# --------------------------------------------------------------------------
read_file <- function(name) {
   cat('Reading txt file ', name, '... ')
   f <- file(name, 'r', encoding = 'UTF-8')
   lines <- readLines(f, encoding = 'UTF-8')
   close(f)
   cat('done!\n')
   cat('Lines:', length(lines), '\n')
}
# ------------------------- "main" (global) ---------------------------------
cat('R script started.\n')
read_file(FILENAME)
cat('R exit.\n')
