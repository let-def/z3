/*++
Copyright (c) 2021 Microsoft Corporation

Module Name:

    polysat unsigned <= constraint

Author:

    Nikolaj Bjorner (nbjorner) 2021-03-19
    Jakob Rath 2021-04-6

--*/
#pragma once
#include "math/polysat/constraint.h"


namespace polysat {

    class ule_constraint : public constraint {
        pdd m_lhs;
        pdd m_rhs;
    public:
        ule_constraint(unsigned lvl, pdd const& l, pdd const& r, p_dependency_ref& dep):
            constraint(lvl, dep, ckind_t::ule_t), m_lhs(l), m_rhs(r) {
            m_vars.append(l.free_vars());
            for (auto v : r.free_vars())
                if (!m_vars.contains(v))
                    m_vars.push_back(v);
        }
        ~ule_constraint() override {}
        std::ostream& display(std::ostream& out) const override;
        bool propagate(solver& s, pvar v) override;
        constraint* resolve(solver& s, pvar v) override;
        bool is_always_false() override;
        bool is_currently_false(solver& s) override;
        void narrow(solver& s) override;
    };

}