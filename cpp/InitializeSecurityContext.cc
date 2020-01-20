#include "misc.h"

namespace myAddon {

Napi::Value e_InitializeSecurityContext(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  // get the credentials.
  if (info.Length() < 1) {
    throw Napi::Error::New(
        env,
        "InitializeSecurityContext: Wrong number of arguments. "
        "InitializeSecurityContext({ hCredential })");
  }

  Napi::Object input = info[0].As<Napi::Object>();
  Napi::Object hCredential = input.Get("hCredential").As<Napi::Object>();
  Credentials c;
  c.credHandle.dwLower =
      hCredential.Get("dwLower").As<Napi::Number>().Int64Value();
  c.credHandle.dwUpper =
      hCredential.Get("dwUpper").As<Napi::Number>().Int64Value();
  std::u16string ws = input.Get("pszTargetName").As<Napi::String>();
  LPWSTR pszTargetName = (LPWSTR)ws.c_str();
  log("pszTargetName=%S", pszTargetName);

  TimeStamp tsExpiry;
  CredHandle cred = credMap[c.serialize()].credHandle;

  logHandle("credentials handle", &cred);

  CtxtHandle clientContext;

  BYTE buffer[cbMaxMessage];
  SecBuffer secBuffer;
  secBuffer.cbBuffer = cbMaxMessage;
  secBuffer.BufferType = SECBUFFER_TOKEN;
  secBuffer.pvBuffer = buffer;

  SecBufferDesc fromClientSecBufferDesc;
  fromClientSecBufferDesc.ulVersion = 0;
  fromClientSecBufferDesc.cBuffers = 1;
  fromClientSecBufferDesc.pBuffers = &secBuffer;

  ULONG ulContextAttr;

  // TimeStamp tsExpiry;

  SECURITY_STATUS secStatus = InitializeSecurityContext(
      &cred, NULL, pszTargetName, ISC_REQ_CONNECTION, RESERVED,
      SECURITY_NATIVE_DREP, NULL, RESERVED, &clientContext,
      &fromClientSecBufferDesc, &ulContextAttr, &tsExpiry);

  if (secStatus < SEC_E_OK) {
    char buffer[BUFFER_SIZE];
    if (secStatus == SEC_E_INVALID_HANDLE) {
      snprintf(buffer, BUFFER_SIZE,
               "Cannot InitializeSecurityContext: invalid handle");
    } else {
      snprintf(buffer, BUFFER_SIZE,
               "Cannot InitializeSecurityContext: secStatus = 0x%08x",
               secStatus);
    }

    throw Napi::Error::New(env, buffer);
  }

  Napi::Object result = Napi::Object::New(env);

  switch (secStatus) {
    case SEC_I_CONTINUE_NEEDED:
      result["SECURITY_STATUS"] =
          Napi::String::New(env, "SEC_I_CONTINUE_NEEDED");
          result["SecBufferDesc"] = JS::convert(env, &fromClientSecBufferDesc);
      break;
    default:
      result["SECURITY_STATUS"] =
          Napi::String::New(env, std::to_string(secStatus));
  }

  // if (secStatus != SEC_I_CONTINUE_NEEDED) {
  // 	error("InitializeSecurityContext did not returned
  // SEC_I_CONTINUE_NEEDED"); 	cleanup(); 	exit(1);
  // }
  // log("need to send to the server the output token.");

  // logHandle("clientContext handle", &clientContext);
  // logSecBufferDesc("client token #1", &fromClientSecBufferDesc);

  return result;
}

}  // namespace myAddon
