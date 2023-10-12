/*
 * File:   xnf.h
 * Author: Yongkang Li
 * Note: An interface for xnf aid functions
 * Created on Oct 12, 2023
 */

#include "xnf.h"

namespace xnf
{
    /**
     * Suppose the input `aalta_formula *f` is in nnf!!!
    */
    aalta_formula *xnf0(aalta_formula *f)
    {
        aalta_formula *res, *left, *right;
        switch (f->oper())
        {
        case aalta_formula::Literal:
            cout
                << "xnf.cpp::xnf0: Error reach here!\n"
                << "\t\t You should work out, 'What does `aalta_formula::Literal` means?'\n";
            exit(0);
            break;
        case aalta_formula::Or:
        case aalta_formula::And:
            left = xnf0(f->l_af());
            right = xnf0(f->r_af());
            res = aalta_formula(f->oper(), left, right).unique();
            break;
        case aalta_formula::Next:
            res = aalta_formula::FALSE();
            break;
        case aalta_formula::WNext:
            cout << "xnf.cpp::xnf0: Error reach here! (WNext shouldn't exist!)\n";
            exit(0);
            break;
        case aalta_formula::Until:
        case aalta_formula::Release:
            res = xnf0(f->r_af());
            break;
        default:
            /**
             * literals: 
             *      1. Literals
             *      2. Negation of Literals
             *          (Because the input `aalta_formula *f` is in nnf!!!)
             *      3. Undefined(Atoms)
            */
            res = f;
            break;
        }
        return res;
    }
}