##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
#  compan.cpp
#  conv.cpp
#  deconv.cpp
#  degree.cpp
#  polyadd.cpp
#  polyder.cpp
  polyfit.cpp
#  polyint.cpp
#  polysub.cpp
  polyval.cpp
#  polyvalm.cpp
#  ratfracder.cpp
#  reduce.cpp
  roots.cpp
#  valuation.cpp
# List of scalar test files for toolbox polynomials
   )

nt2_module_add_tests(type.complex.polynom.scalar.unit ${SOURCES})
