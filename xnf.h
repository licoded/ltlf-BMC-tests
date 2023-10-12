/*
 * File:   xnf.h
 * Author: Yongkang Li
 * Note: An interface for xnf aid functions
 * Created on Oct 12, 2023
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "formula/aalta_formula.h"
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;
using namespace aalta;

namespace xnf
{
    class xnf_tran
    {
    public:
        xnf_tran(aalta_formula *f, int bounded_k) : f_(f), bounded_k_(bounded_k)
        {
            quantifiers_.clear();
            for (int i = 0; i <= bounded_k_; i++) // YES, there are k+1 layers totally.
            {
                quantifiers_.push_back(unordered_set<string>());
            }
            for (auto& layer : quantifiers_)
            {
                layer.clear();
            }
        }

        aalta_formula *add_label_for_var(aalta_formula *f, int label_id);

        aalta_formula *xnf0(aalta_formula *f);
        aalta_formula *xnf(aalta_formula *f, int k);
        aalta_formula *xnf_add_label_for_var(aalta_formula *f, int k = 0);

        unordered_set<string>& get_quantifiers_by_layer(int layer)
        {
            return quantifiers_[layer];
        }

    private:
        aalta_formula *f_;
        int bounded_k_;
        vector<unordered_set<string>> quantifiers_;
    };
}

#endif