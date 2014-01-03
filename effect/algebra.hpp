#pragma once

#include <utility>
#include "../core/defs.hpp"
#include "../core/effect.hpp"
#include "sequential.hpp"
#include "parallel.hpp"

namespace effect {
    using core::Effect;

    TPL_2(ET1, ET2) struct SeqEffectTerm;
    TPL_2(ET1, ET2) struct ParEffectTerm;

    TPL(Self) struct EffectTerm {
        TPL(ET) inline SeqEffectTerm<Self, ET> operator>>(ET other) {
            return SeqEffectTerm<Self, ET>(*((Self*) this), other);
        }
        TPL(ET) inline ParEffectTerm<Self, ET> operator||(ET other) {
            return ParEffectTerm<Self, ET>(*((Self*) this), other);
        }
    };

    TPL(T) struct WrapEffectTerm : public EffectTerm<WrapEffectTerm<T>> {
	typedef T EffectTarget;
        Effect<T>* effect;
        WrapEffectTerm(Effect<T>* effect)
            : effect(effect)
        {}
        inline Effect<T>* eval(Pool&) {
            return effect;
        }
    };

    TPL_2(ET1, ET2) struct SeqEffectTerm
        : public EffectTerm<SeqEffectTerm<ET1, ET2>>
    {
	typedef typename ET1::EffectTarget EffectTarget;
	ET1 first;
	ET2 second;
        SeqEffectTerm(ET1 first, ET2 second)
            : first(first)
	    , second(second)
        {}
        inline Effect<EffectTarget>* eval(Pool& pool) {
            return new (pool.malloc()) Sequential<EffectTarget>(*first.eval(pool), *second.eval(pool));
        }
    };

    TPL_2(ET1, ET2) struct ParEffectTerm
        : public EffectTerm<ParEffectTerm<ET1, ET2>>
    {
	typedef typename ET1::EffectTarget EffectTarget;
	ET1 first;
	ET2 second;
        ParEffectTerm(ET1 first, ET2 second)
            : first(first)
	    , second(second)
        {}
        inline Effect<EffectTarget>* eval(Pool& pool) {
            return new (pool.malloc()) Parallel<EffectTarget>(*first.eval(pool), *second.eval(pool));
        }
    };
}
