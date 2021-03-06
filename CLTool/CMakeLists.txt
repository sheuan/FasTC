# FasTC
# Copyright (c) 2012 University of North Carolina at Chapel Hill. All rights reserved.
#
# Permission to use, copy, modify, and distribute this software and its documentation for educational, 
# research, and non-profit purposes, without fee, and without a written agreement is hereby granted, 
# provided that the above copyright notice, this paragraph, and the following four paragraphs appear 
# in all copies.
#
# Permission to incorporate this software into commercial products may be obtained by contacting the 
# authors or the Office of Technology Development at the University of North Carolina at Chapel Hill <otd@unc.edu>.
#
# This software program and documentation are copyrighted by the University of North Carolina at Chapel Hill. 
# The software program and documentation are supplied "as is," without any accompanying services from the 
# University of North Carolina at Chapel Hill or the authors. The University of North Carolina at Chapel Hill 
# and the authors do not warrant that the operation of the program will be uninterrupted or error-free. The 
# end-user understands that the program was developed for research purposes and is advised not to rely 
# exclusively on the program for any reason.
#
# IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE AUTHORS BE LIABLE TO ANY PARTY FOR 
# DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE 
# USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE 
# AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS SPECIFICALLY DISCLAIM ANY WARRANTIES, INCLUDING, 
# BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND ANY 
# STATUTORY WARRANTY OF NON-INFRINGEMENT. THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY 
# OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS HAVE NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, 
# ENHANCEMENTS, OR MODIFICATIONS.
#
# Please send all BUG REPORTS to <pavel@cs.unc.edu>.
#
# The authors may be contacted via:
#
# Pavel Krajcevski
# Dept of Computer Science
# 201 S Columbia St
# Frederick P. Brooks, Jr. Computer Science Bldg
# Chapel Hill, NC 27599-3175
# USA
# 
# <http://gamma.cs.unc.edu/FasTC/>

INCLUDE_DIRECTORIES( ${FasTC_SOURCE_DIR}/Base/include )
INCLUDE_DIRECTORIES( ${FasTC_BINARY_DIR}/Base/include )

INCLUDE_DIRECTORIES( ${FasTC_SOURCE_DIR}/Core/include )
INCLUDE_DIRECTORIES( ${FasTC_SOURCE_DIR}/IO/include )

ADD_EXECUTABLE(
  tc
  "src/tc.cpp"
)

ADD_EXECUTABLE(
  compare
  "src/compare.cpp"
)

ADD_EXECUTABLE(
  decomp
  "src/decomp.cpp"
)

# Add flag for link time code generation. This was used to build the libpng
# libraries, so we should probably also include it for this project as well...
IF( MSVC )
  SET_TARGET_PROPERTIES(tc PROPERTIES LINK_FLAGS "/LTCG")
  SET_TARGET_PROPERTIES(compare PROPERTIES LINK_FLAGS "/LTCG")
  SET_TARGET_PROPERTIES(decomp PROPERTIES LINK_FLAGS "/LTCG")
ENDIF()

TARGET_LINK_LIBRARIES( tc FasTCBase )
TARGET_LINK_LIBRARIES( tc FasTCIO )
TARGET_LINK_LIBRARIES( tc FasTCCore )

TARGET_LINK_LIBRARIES( compare FasTCBase )
TARGET_LINK_LIBRARIES( compare FasTCIO )

TARGET_LINK_LIBRARIES( decomp FasTCBase )
TARGET_LINK_LIBRARIES( decomp FasTCIO )

INSTALL(TARGETS tc compare decomp EXPORT FasTCTargets
  RUNTIME DESTINATION bin COMPONENT bin)
