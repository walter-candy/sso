import express = require('express');
import { sso } from 'node-expose-sspi';

const app = express();

app.use(
  sso.auth({
    useGroups: true,
    useOwner: true,
    useActiveDirectory: true,
    useCookies: true,
    allowsAnonymousLogon: false,
    allowsGuest: false,
    // groupFilterRegex: ".*NT AUTHORITY.*"
  })
);

app.use((req, res) => {
  res.json({
    sso: req.sso,
  });
});

app.listen(3001, () => console.log('Server started on port 3001'));
