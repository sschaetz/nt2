##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Soft_mm_cvtpsware License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  abs.cpp
  abss.cpp
  adds.cpp
  arg.cpp
  average.cpp
  ceil.cpp
  conj.cpp
  correct_fma.cpp
  dec.cpp
  dist.cpp
  divceil.cpp
  divfix.cpp
  divfloor.cpp
  divround.cpp
  divs.cpp
  fast_hypot.cpp
  fast_iround2even.cpp
  fast_rec.cpp
  fast_rsqrt.cpp
  fast_sqrt.cpp
  floor.cpp
  fma.cpp
  hypot.cpp
  iceil.cpp
  idivceil.cpp
  idivfix.cpp
  idivfloor.cpp
  idivround.cpp
  idivround2even.cpp
  ifloor.cpp
  iround.cpp
  iround2even.cpp
  logical_xor.cpp
  max.cpp
  min.cpp
  minmod.cpp
  minusone.cpp
  mod.cpp
  muls.cpp
  negs.cpp
  oneminus.cpp
  oneplus.cpp
  rec.cpp
  remainder.cpp
  rem.cpp
  remquo.cpp
  remround.cpp
  round.cpp
  round2even.cpp
  rsqrt.cpp
  sqr.cpp
  sqr_abs.cpp
  sqrs.cpp
  sqrt.cpp
  subs.cpp
  tofloat.cpp
  toint.cpp
  toints.cpp
  touint.cpp
  touints.cpp
  trunc.cpp
  two_add.cpp
  two_prod.cpp
  two_split.cpp
# List of simd test files for toolbox arithmetic
   )

nt2_module_add_tests(boost.simd.base.arithmetic.simd.bench ${SOURCES})
