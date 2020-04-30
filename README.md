# Authenticate MySQL/MariaDB users with bcrypt hashed passwords

Build with `make` and install with `make install` (as root).

To load the plugin in MySQL or MariaDB, run the following command.

```sql
INSTALL SONAME 'auth_bcrypt.h';
```

The following command adds an user that authenticates with the plugin.

```sql
CREATE USER <name>@'localhost' IDENTIFIED WITH bcrypt USING '<hash>';
```
## Secure connections
Make sure to secure database connections with TLS since passwords are sent in clear text!
