/*
 * Copyright (c) 2018 Manuel Deneu
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
//
//  ApplicationKit.h
//  
//
//  Created by Manuel Deneu on 31/05/2018.
//

#ifndef ApplicationKit_h
#define ApplicationKit_h

#define ApplicationKitVersion_Maj   (int) 0
#define ApplicationKitVersion_Min   (int) 0
#define ApplicationKitVersion_Patch (int) 0

#include <AKView.h>

#include <AKWindow.h>

#include <AKColor.h>
#include <AKGeometry.h>

#include <AKEvent.h>
#include <AKImage.h>

// Basic components
#include <AKGridView.h>
#include <AKLabel.h>
#include <AKButton.h>
#include <AKSlider.h>
#include <AKTextField.h>
#include <AKImageView.h>
#include <AKTextView.h>

// Top level components
#include <AKColorPickerWindow.h>
#include <AKAlertWindow.h>
#include <AKApplication.h>



/*
 General notes : AK* object are defined in header - an thus not opaque- so they can be stack-allocated, BUT you should'nt access struct fields directly.
 Especialy, every AK* object have a `init` method (always named `AKObjectNameInit`) method that will modify Callback methods and possibly other fields, thus you should'nt do
 anything with the object instance before calling the init method
 */

/*
 Widget lifecycle:
 - Widget are NOT destroyed when top widget are distroyed
 */




#endif /* ApplicationKit_h */
