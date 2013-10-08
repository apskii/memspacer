#ifndef CORE_EFFECT_ALGEBRA_HPP
#define CORE_EFFECT_ALGEBRA_HPP

#include <utility>
#include "../defs.hpp"
#include "../effect.hpp"
#include "sequential.hpp"
#include "parallel.hpp"

TPL_2(ET1, ET2) struct SeqEffectTerm;
TPL_2(ET1, ET2) struct ParEffectTerm;

TPL_2(Self, T) struct EffectTerm {
    typedef T EffectTarget;
    TPL(ET) meth operator>>(ET other) -> inline SeqEffectTerm<Self, ET> {
        return SeqEffectTerm<Self, ET>(*((Self*) this), other);
    }
    TPL(ET) meth operator||(ET other) -> inline ParEffectTerm<Self, ET> {
        return ParEffectTerm<Self, ET>(*((Self*) this), other);
    }
};

TPL(T) struct WrapEffectTerm : public EffectTerm<WrapEffectTerm<T>, T> {
    Effect<T>* effect;
    WrapEffectTerm(Effect<T>* effect)
        : effect(effect)
    {}
    meth eval(Pool&) -> inline Effect<T>* {
        return effect;
    }
};

TPL_2(ET1, ET2) struct SeqEffectTerm
    : public EffectTerm<SeqEffectTerm<ET1, ET2>, typename ET1::EffectTarget>
    , public std::pair<ET1, ET2>
{
    SeqEffectTerm(ET1 first, ET2 second)
        : std::pair<ET1, ET2>(first, second)
    {}
    meth eval(Pool& pool) -> inline Effect<EffectTarget>* {
        return new (pool.malloc()) Sequential<EffectTarget>(*first.eval(pool), *second.eval(pool));
    }
};

TPL_2(ET1, ET2) struct ParEffectTerm
    : public EffectTerm<ParEffectTerm<ET1, ET2>, typename ET1::EffectTarget>
    , public std::pair<ET1, ET2>
{
    ParEffectTerm(ET1 first, ET2 second)
        : std::pair<ET1, ET2>(first, second)
    {}
    meth eval(Pool& pool) -> inline Effect<EffectTarget>* {
        return new (pool.malloc()) Parallel<EffectTarget>(*first.eval(pool), *second.eval(pool));
    }
};

#endif CORE_EFFECT_ALGEBRA_HPP