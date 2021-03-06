/* FasTC
 * Copyright (c) 2013 University of North Carolina at Chapel Hill.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for educational, research, and non-profit purposes, without
 * fee, and without a written agreement is hereby granted, provided that the
 * above copyright notice, this paragraph, and the following four paragraphs
 * appear in all copies.
 *
 * Permission to incorporate this software into commercial products may be
 * obtained by contacting the authors or the Office of Technology Development
 * at the University of North Carolina at Chapel Hill <otd@unc.edu>.
 *
 * This software program and documentation are copyrighted by the University of
 * North Carolina at Chapel Hill. The software program and documentation are
 * supplied "as is," without any accompanying services from the University of
 * North Carolina at Chapel Hill or the authors. The University of North
 * Carolina at Chapel Hill and the authors do not warrant that the operation of
 * the program will be uninterrupted or error-free. The end-user understands
 * that the program was developed for research purposes and is advised not to
 * rely exclusively on the program for any reason.
 *
 * IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE
 * AUTHORS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF
 * THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF NORTH CAROLINA
 * AT CHAPEL HILL OR THE AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS SPECIFICALLY
 * DISCLAIM ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND ANY 
 * STATUTORY WARRANTY OF NON-INFRINGEMENT. THE SOFTWARE PROVIDED HEREUNDER IS ON
 * AN "AS IS" BASIS, AND THE UNIVERSITY  OF NORTH CAROLINA AT CHAPEL HILL AND
 * THE AUTHORS HAVE NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, 
 * ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Please send all BUG REPORTS to <pavel@cs.unc.edu>.
 *
 * The authors may be contacted via:
 *
 * Pavel Krajcevski
 * Dept of Computer Science
 * 201 S Columbia St
 * Frederick P. Brooks, Jr. Computer Science Bldg
 * Chapel Hill, NC 27599-3175
 * USA
 * 
 * <http://gamma.cs.unc.edu/FasTC/>
 */

// Our library include...
#include "FasTC/PVRTCCompressor.h"

// PVRLib library include...
#include "PVRTextureUtilities.h"

#include <cassert>

namespace PVRTCC {

  void CompressPVRLib(const FasTC::CompressionJob &cj,
                      bool bTwoBitMode,
                      const EWrapMode) {
    pvrtexture::CPVRTextureHeader pvrTexHdr;
    pvrTexHdr.setPixelFormat(pvrtexture::PVRStandard8PixelType);
    pvrTexHdr.setWidth(cj.Width());
    pvrTexHdr.setHeight(cj.Height());
    pvrTexHdr.setIsFileCompressed(false);
    pvrTexHdr.setIsPreMultiplied(false);

    pvrtexture::CPVRTexture pvrTex = pvrtexture::CPVRTexture(pvrTexHdr, cj.InBuf());
    bool result = pvrtexture::Transcode(pvrTex,
                                        ePVRTPF_PVRTCI_4bpp_RGBA,
                                        ePVRTVarTypeUnsignedByte,
                                        ePVRTCSpacelRGB,
                                        pvrtexture::ePVRTCFast);
    assert(result);
    (void)result;

    memcpy(cj.OutBuf(), static_cast<uint8 *>(pvrTex.getDataPtr()), cj.Width() * cj.Height() / 2);
  }

}  // namespace PVRTCC
