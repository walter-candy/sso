[node-expose-sspi](../README.md) › ["lib/sspi.d"](../modules/_lib_sspi_d_.md) › [ServerSecurityContext](_lib_sspi_d_.serversecuritycontext.md)

# Interface: ServerSecurityContext

## Hierarchy

* [SecurityContext](_lib_sspi_d_.securitycontext.md)

  ↳ **ServerSecurityContext**

## Index

### Properties

* [SECURITY_STATUS](_lib_sspi_d_.serversecuritycontext.md#optional-security_status)
* [SecBufferDesc](_lib_sspi_d_.serversecuritycontext.md#optional-secbufferdesc)
* [contextAttr](_lib_sspi_d_.serversecuritycontext.md#contextattr)
* [contextHandle](_lib_sspi_d_.serversecuritycontext.md#optional-contexthandle)

## Properties

### `Optional` SECURITY_STATUS

• **SECURITY_STATUS**? : *string*

*Inherited from [SecurityContext](_lib_sspi_d_.securitycontext.md).[SECURITY_STATUS](_lib_sspi_d_.securitycontext.md#optional-security_status)*

*Defined in [lib/sspi.d.ts:34](https://github.com/jlguenego/node-expose-sspi/blob/70cc17a/lib/sspi.d.ts#L34)*

___

### `Optional` SecBufferDesc

• **SecBufferDesc**? : *any*

*Inherited from [SecurityContext](_lib_sspi_d_.securitycontext.md).[SecBufferDesc](_lib_sspi_d_.securitycontext.md#optional-secbufferdesc)*

*Defined in [lib/sspi.d.ts:35](https://github.com/jlguenego/node-expose-sspi/blob/70cc17a/lib/sspi.d.ts#L35)*

___

###  contextAttr

• **contextAttr**: *[AscRetFlag](../modules/_lib_flags_ascretflag_d_.md#ascretflag)[]*

*Defined in [lib/sspi.d.ts:39](https://github.com/jlguenego/node-expose-sspi/blob/70cc17a/lib/sspi.d.ts#L39)*

___

### `Optional` contextHandle

• **contextHandle**? : *[CtxtHandle](_lib_sspi_d_.ctxthandle.md)*

*Inherited from [SecurityContext](_lib_sspi_d_.securitycontext.md).[contextHandle](_lib_sspi_d_.securitycontext.md#optional-contexthandle)*

*Defined in [lib/sspi.d.ts:33](https://github.com/jlguenego/node-expose-sspi/blob/70cc17a/lib/sspi.d.ts#L33)*