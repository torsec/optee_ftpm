/* Microsoft Reference Implementation for TPM 2.0
 *
 *  The copyright in this software is being made available under the BSD License,
 *  included below. This software may be subject to other third party and
 *  contributor rights, including patent rights, and no such rights are granted
 *  under this license.
 *
 *  Copyright (c) Microsoft Corporation
 *
 *  All rights reserved.
 *
 *  BSD License
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *  Redistributions of source code must retain the above copyright notice, this list
 *  of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright notice, this
 *  list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ""AS IS""
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
// This file contains the instance data for the Platform module. It is collected
// in this file so that the state of the module is easier to manage.

#ifndef _PLATFORM_DATA_H_
#define _PLATFORM_DATA_H_


#include      "TpmProfile.h"

// From Cancel.c
// Cancel flag.  It is initialized as FALSE, which indicate the command is not
// being canceled
extern int     s_isCanceled;

#ifndef HARDWARE_CLOCK
typedef uint64_t     clock64_t;
// This is the value returned the last time that the system clock was read. This
// is only relevant for a simulator or virtual TPM.
extern clock64_t       s_realTimePrevious;

// These values are used to try to synthesize a long lived version of clock().
extern clock64_t        s_lastSystemTime;
extern clock64_t        s_lastReportedTime;

// This is the rate adjusted value that is the equivalent of what would be read from
// a hardware register that produced rate adjusted time.
extern clock64_t        s_tpmTime;
#endif // HARDWARE_CLOCK

// This value indicates that the timer was reset
extern BOOL              s_timerReset;
// This value indicates that the timer was stopped. It causes a clock discontinuity.
extern BOOL              s_timerStopped;

// CLOCK_NOMINAL is the number of hardware ticks per mS. A value of 300000 means
// that the nominal clock rate used to drive the hardware clock is 30 MHz. The
// adjustment rates are used to determine the conversion of the hardware ticks to
// internal hardware clock value. In practice, we would expect that there woudl be
// a hardware register will accumulated mS. It would be incremented by the output
// of a pre-scaler. The pre-scaler would divide the ticks from the clock by some
// value that would compensate for the difference between clock time and real time.
// The code in Clock does the emulation of this function.
#define     CLOCK_NOMINAL           30000
// A 1% change in rate is 300 counts
#define     CLOCK_ADJUST_COARSE     300
// A 0.1% change in rate is 30 counts
#define     CLOCK_ADJUST_MEDIUM     30
// A minimum change in rate is 1 count
#define     CLOCK_ADJUST_FINE       1
// The clock tolerance is +/-15% (4500 counts)
// Allow some guard band (16.7%)
#define     CLOCK_ADJUST_LIMIT      5000

// This variable records the time when _plat__TimerReset is called.  This mechanism
// allow us to subtract the time when TPM is power off from the total
// time reported by clock() function
extern uint64_t        s_initClock;

// This variable records the timer adjustment factor.
extern unsigned int         s_adjustRate;

// For LocalityPlat.c
// Locality of current command
extern unsigned char s_locality;

// For NVMem.c
// Choose if the NV memory should be backed by RAM or by file.
// If this macro is defined, then a file is used as NV.  If it is not defined,
// then RAM is used to back NV memory. Comment out to use RAM.

#if (!defined VTPM) || ((VTPM != NO) && (VTPM != YES))
#   undef VTPM
#   define      VTPM            YES                 // Default: Either YES or NO
#endif

// For a simulation, use a file to back up the NV
#if (!defined FILE_BACKED_NV) || ((FILE_BACKED_NV != NO) && (FILE_BACKED_NV != YES))
#   undef   FILE_BACKED_NV
#   define  FILE_BACKED_NV          (VTPM && YES)     // Default: Either YES or NO
#endif

#if !SIMULATION
#   undef       FILE_BACKED_NV
#   define      FILE_BACKED_NV          NO
#endif // SIMULATION

// For PPPlat.c
// Physical presence.  It is initialized to FALSE
extern BOOL     s_physicalPresence;

// From Power
extern BOOL        s_powerLost;

// For Entropy.c
extern uint32_t        lastEntropy;

#endif // _PLATFORM_DATA_H_
