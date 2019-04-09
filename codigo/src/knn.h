#ifndef __KNN_H__
#define __KNN_H__

#include "../src_catedra/types.h"

bool knn(const VectorizedEntriesMap &entries, const std::vector<double> &words, int k);

#endif
