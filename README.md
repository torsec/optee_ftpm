OP-TEE integration for the MS TPM 2.0 Reference Implementation (fTPM)
===========

## fTPM TA
The fTPM Trusted Application (TA) provides a secure firmware implementation
of a TPM using the [MS reference
implementation](https://github.com/microsoft/ms-tpm-20-ref).

The platform specific integration code is kept in this repository.

This is a fork from the the [MS reference
implementation](https://github.com/microsoft/ms-tpm-20-ref) sample
[ARM32-FirmwareTPM](https://github.com/microsoft/ms-tpm-20-ref/tree/Historical_Samples/Samples/ARM32-FirmwareTPM)
maintained to work with OP-TEE.

## Measured Boot support
The fTPM Trusted Application includes support for Measured Boot. This
feature allows the TA to read a TPM Event Log compatible with the
specification in Section 5 of the [TCG EFI Protocol
Specification](https://trustedcomputinggroup.org/wp-content/uploads/EFI-Protocol-Specification-rev13-160330final.pdf).
The event log is read and extended during the TA initialization.

Measure Boot support requires OP-TEE System Call
```PTA_SYSTEM_GET_TPM_EVENT_LOG```.

Flags related to Measured Boot support:

`CFG_TA_MEASURED_BOOT`: Controls whether Measured Boot is enabled
(`CFG_TA_MEASURED_BOOT=y`) or disabled (by default).
`CFG_TA_EVENT_LOG_SIZE`: Maximum size in bytes allowed for the Event Log.
Defaults to 1024 bytes.

