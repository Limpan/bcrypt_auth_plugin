CC=gcc
CFLAGS=

lib/auth_bcrypt.so: src/auth_bcrypt.c src/blowfish/bcrypt.c src/blowfish/blf.c
	$(CC) -o lib/auth_bcrypt.so src/auth_bcrypt.c src/blowfish/bcrypt.c src/blowfish/blf.c `mysql_config --cflags` -shared -fPIC -lbsd

debug: src/auth_bcrypt.c src/blowfish/bcrypt.c src/blowfish/blf.c
	$(CC) -g -o lib/auth_bcrypt.so src/auth_bcrypt.c src/blowfish/bcrypt.c src/blowfish/blf.c `mysql_config --cflags` -shared -fPIC -lbsd

install: lib/auth_bcrypt.so
	chmod 644 lib/auth_bcrypt.so && cp lib/auth_bcrypt.so `mysql_config --plugindir`
