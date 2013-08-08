divel-calendar
==============

Source code of Divel Calendar for Windows, Linux and Android under the GPLv2

# Compiling

## Linux

### Standard

Go to wxWidgets dir and run the following commands:

cmake . -DCMAKE_INSTALL_PREFIX=/usr

make

make install

### Debian/Ubuntu/Linux Mint

Go to wxWidgets dir and run the following commands:

dpkg-buildpackage -rfakeroot -kINSERT_GPG_KEY_OR_EMAIL

Go up and install it

sudo dpkg -i DEB_FILE

### Ubuntu PPA

Go to wxWidgets dir and run:

debuild -S -kINSERT_GPG_KEY_OR_EMAIL

Go up and upload it:

dput ppa:PPA_NAME SOURCE.CHANGES_FILE

