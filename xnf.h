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

using namespace std;
using namespace aalta;

namespace xnf
{
    aalta_formula *xnf0(aalta_formula *f);
    aalta_formula *xnf(aalta_formula *f, int k);
    aalta_formula *xnf_add_label_for_var(aalta_formula *f, int k = 0);
}

#endif