#define MYSQL_DYNAMIC_PLUGIN
#include <mysql/plugin_auth.h>
#include "blowfish/bcrypt.h"
#include <mysql/auth_dialog_client.h>

static int bcrypt_hash_verify(MYSQL_PLUGIN_VIO *vio, MYSQL_SERVER_AUTH_INFO *info)
{
  unsigned char *pkt;
  int pkt_len;
  int encrypted_len = sizeof(char) * 128;
  unsigned char *encrypted = malloc(encrypted_len);


  /* send a password question */
  if (vio->write_packet(vio, (const unsigned char *) PASSWORD_QUESTION "Enter password:", 16))
    return CR_ERROR;

  /* read the answer */
  if ((pkt_len = vio->read_packet(vio, &pkt)) < 0)
    return CR_ERROR;

  info->password_used = PASSWORD_USED_YES;

  /* check against stored hash */
  bcrypt_hashpass((const char *) pkt, info->auth_string, encrypted, encrypted_len);

  if (strncmp(info->auth_string, encrypted, strlen(info->auth_string)))
    return CR_ERROR;

  return CR_OK;
}

static struct st_mysql_auth bcrypt_info =
{
  MYSQL_AUTHENTICATION_INTERFACE_VERSION,
  "mysql_clear_password",
  bcrypt_hash_verify
};

mysql_declare_plugin(bcrypt)
{
  MYSQL_AUTHENTICATION_PLUGIN,
  &bcrypt_info,
  "bcrypt",
  "Linus Törngren",
  "Password authentication with bcrypt.",
  PLUGIN_LICENSE_GPL,
  NULL,
  NULL,
  0x0100,
  NULL,
  NULL,
  NULL
}
mysql_declare_plugin_end;
