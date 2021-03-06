/******************************************************************************
 * $Id$
 *
 * Project:  OGR
 * Purpose:  OGRNASDriver implementation
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *
 ******************************************************************************
 * Copyright (c) 2002, Frank Warmerdam <warmerdam@pobox.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#include "ogr_nas.h"
#include "cpl_conv.h"
#include "nasreaderp.h"
#include "cpl_multiproc.h"

CPL_CVSID("$Id$");


/************************************************************************/
/*                          ~OGRNASDriver()                           */
/************************************************************************/

OGRNASDriver::~OGRNASDriver()

{
    if( NASReader::hMutex != NULL )
        CPLDestroyMutex( NASReader::hMutex );
    NASReader::hMutex = NULL;
}

/************************************************************************/
/*                              GetName()                               */
/************************************************************************/

const char *OGRNASDriver::GetName()

{
    return "NAS";
}

/************************************************************************/
/*                                Open()                                */
/************************************************************************/

OGRDataSource *OGRNASDriver::Open( const char * pszFilename,
                                   int bUpdate )

{
    OGRNASDataSource    *poDS;

    if( bUpdate )
        return NULL;

    poDS = new OGRNASDataSource();

    if( !poDS->Open( pszFilename, TRUE )
        || poDS->GetLayerCount() == 0 )
    {
        delete poDS;
        return NULL;
    }
    else
        return poDS;
}

/************************************************************************/
/*                           TestCapability()                           */
/************************************************************************/

int OGRNASDriver::TestCapability( const char * pszCap )

{
    return FALSE;
}

/************************************************************************/
/*                           RegisterOGRNAS()                           */
/************************************************************************/

void RegisterOGRNAS()

{
    OGRSFDriverRegistrar::GetRegistrar()->RegisterDriver( new OGRNASDriver );
}

