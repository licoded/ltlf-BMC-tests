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
    aalta_formula *xnf_tran::xnf0(aalta_formula *f)
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

    /**
     * Suppose the input `aalta_formula *f` is in nnf!!!
     * NEED_TESTs:
     *      - There is only `X[!]` in return formula, no `R` or `U`!!!
    */
    aalta_formula *xnf_tran::xnf(aalta_formula *f, int k)
    {
        if (k == 0)
            return xnf0(f);
        aalta_formula *res, *left, *right, *temp, *Xit;
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
            left = xnf(f->l_af(), k);
            right = xnf(f->r_af(), k);
            res = aalta_formula(f->oper(), left, right).unique();
            break;
        case aalta_formula::Next:
            res = aalta_formula(aalta_formula::Next, nullptr, xnf(f->r_af(), k-1)).unique();
            break;
        case aalta_formula::WNext:
            cout << "xnf.cpp::xnf0: Error reach here! (WNext shouldn't exist!)\n";
            exit(0);
            break;
        case aalta_formula::Until:
            Xit = aalta_formula(aalta_formula::Next, nullptr, f).unique();
            temp = (f->l_af() == aalta_formula::TRUE())
                ? xnf(Xit, k)
                : aalta_formula(aalta_formula::And, xnf(f->l_af(), k), xnf(Xit, k)).unique();
            res = aalta_formula(aalta_formula::Or, xnf(f->r_af(), k), temp).unique();
            break;
        case aalta_formula::Release:
            Xit = aalta_formula(aalta_formula::Next, nullptr, f).unique();
            temp = (f->l_af() == aalta_formula::FALSE())
                ? xnf(Xit, k)
                : aalta_formula(aalta_formula::Or, xnf(f->l_af(), k), xnf(Xit, k)).unique();
            res = aalta_formula(aalta_formula::And, xnf(f->r_af(), k), temp).unique();
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

    aalta_formula *xnf_tran::add_label_for_var(aalta_formula *f, int label_id)
    {
        if (f->oper() == aalta_formula::Not)
        {
            return aalta_formula(aalta_formula::Not, nullptr, add_label_for_var(f->r_af(), label_id)).unique();
        }
        string labeled_item_str = f->to_string()+to_string(label_id);
        quantifiers_[label_id].insert(labeled_item_str);
        return aalta_formula(labeled_item_str.c_str(), true).unique();
    }

    aalta_formula *xnf_tran::xnf_add_label_for_var(aalta_formula *f, int k)
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
            left = xnf_add_label_for_var(f->l_af(), k);
            right = xnf_add_label_for_var(f->r_af(), k);
            res = aalta_formula(f->oper(), left, right).unique();
            break;
        case aalta_formula::Next:
            // res = aalta_formula(aalta_formula::Next, nullptr, xnf(f->r_af(), k-1)).unique();
            res = xnf_add_label_for_var(f->r_af(), k+1);
            break;
        case aalta_formula::WNext:
            cout << "xnf.cpp::xnf0: Error reach here! (WNext shouldn't exist!)\n";
            exit(0);
            break;
        case aalta_formula::Until:
            cout << "xnf.cpp::xnf0: Error reach here! (Until shouldn't exist!)\n";
            exit(0);
            break;
        case aalta_formula::Release:
            cout << "xnf.cpp::xnf0: Error reach here! (Release shouldn't exist!)\n";
            exit(0);
            break;
        default:
            /**
             * literals: 
             *      1. Literals
             *      2. Negation of Literals
             *          (Because the input `aalta_formula *f` is in nnf!!!)
             *      3. Undefined(Atoms)
            */
            res = add_label_for_var(f, k);
            break;
        }
        return res;
    }
}