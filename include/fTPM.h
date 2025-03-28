/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2024, Linaro Limited
 */

/* Microsoft Reference Implementation for TPM 2.0
 *
 * The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third
 * party and contributor rights, including patent rights, and no such
 * rights are granted under this license.
 *
 * Copyright (c) 2018 Microsoft Corporation
 *
 * All rights reserved.
 *
 * BSD License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FTPM_H
#define FTPM_H

#include <TpmProfile.h>
#include <ftpm_ta.h>

//
// These must match values from reference/TPM/include/TpmProfile.h
//
#define  MAX_COMMAND_SIZE       4096
#define  MAX_RESPONSE_SIZE      4096

//
// Macro for intentionally unreferenced parameters
//
#define UNREFERENCED_PARAMETER(_Parameter_) (void)(_Parameter_)

//
// Shorthand for TA functions taking uniform arg types
//
#define TA_ALL_PARAM_TYPE(a) TEE_PARAM_TYPES((a), (a), (a), (a))

#ifndef BYTE_ARRAY_TO_UINT32
//
// Used to extract size field from TPM command buffers
//
#define BYTE_ARRAY_TO_UINT32(b)  (uint32_t)(  ((b)[0] << 24) \
                                            + ((b)[1] << 16) \
                                            + ((b)[2] << 8 ) \
                                            +  (b)[3])
#endif

//
// Entrypoint for reference implemntation
//
extern void ExecuteCommand(
    uint32_t         requestSize,   // IN: command buffer size
    unsigned char   *request,       // IN: command buffer
    uint32_t        *responseSize,  // OUT: response buffer size
    unsigned char   **response      // OUT: response buffer
    );

//
// External functions supporting TPM initialization
//
extern int  _plat__NVEnable(void *platParameter);
extern int  TPM_Manufacture(bool firstTime);
extern bool _plat__NvNeedsManufacture(void);
extern void _TPM_Init(void);
extern void _plat__NVDisable(void);
extern void _admin__SaveChipFlags(void);

//
// External types/data supporting TPM initialization
//
typedef union {
    uint32_t   flags;
    struct {
        uint32_t Remanufacture : 1;   // Perform a TPM_Remanufacture() on startup (SET by default)
        uint32_t TpmStatePresent : 1; // Init TPM and NV with contents of TpmState and NVState on startup
        uint32_t Reserved : 30;
    }        fields;
} TPM_CHIP_STATE;

extern TPM_CHIP_STATE g_chipFlags;
#endif /* FTPM_H */
