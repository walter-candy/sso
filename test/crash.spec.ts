import {
  adsi,
  sysinfo,
  sspi,
  AcquireCredHandleInput,
  AcceptSecurityContextInput,
} from '../src';
import a from 'assert';
const assert = a.strict;
import dbg from 'debug';
import { sleep } from '../src/sso/sleep';
import { IADs } from '../lib/adsi';
const debug = dbg('node-expose-sspi:test');

describe('CRASH Unit Test', function () {
  this.timeout(15000);

  it('should crash', function () {
    adsi.CoInitializeEx(['COINIT_MULTITHREADED']);

    const clientCred = sspi.AcquireCredentialsHandle({
      packageName: 'Negotiate',
      credentialUse: 'SECPKG_CRED_BOTH',
    });

    const clientSecurityContext = sspi.InitializeSecurityContext({
      credential: clientCred.credential,
      targetName: 'kiki',
      cbMaxToken: 48256,
      targetDataRep: 'SECURITY_NATIVE_DREP',
    });

    adsi.ADsGestObject('LDAP://rootDSE').then(async (root: IADs) => {
      const distinguishedName = await root.Get('defaultNamingContext');
      debug('distinguishedName: ', distinguishedName);
    });

    setTimeout(() => {
      const serverSecurityContext = sspi.AcceptSecurityContext({
        credential: clientCred.credential,
        clientSecurityContext,
        contextReq: ['ASC_REQ_CONNECTION'],
        targetDataRep: 'SECURITY_NATIVE_DREP',
      });
      debug('serverSecurityContext: ', serverSecurityContext);
    }, 10);

    debug('clientCred: ', clientCred);
    adsi.CoUninitialize();
    // await sleep(5000);
  });
});