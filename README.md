# GeoIP Update

## Deprecation Notice

This is the repository for the deprecated C version of geoipupdate. For the
new version as well as to report issues related to C version, please visit
the [new repository](https://github.com/maxmind/geoipupdate).

## Description

The GeoIP Update program performs automatic updates of GeoIP2 and GeoIP Legacy
binary databases. CSV databases are _not_ supported.

Currently the program only supports Linux and other Unix-like systems.

## Installing on Ubuntu

MaxMind provides a PPA for recent version of Ubuntu. To add the PPA to your
sources, run:

    $ sudo add-apt-repository ppa:maxmind/ppa

Then install `geoipupdate` by running:

    $ sudo apt update
    $ sudo apt install geoipupdate

## Installing From Source File

To install this from the source package, you will need a C compiler, Make,
the zlib library and headers, and the curl library and headers.

On Debian or Ubuntu, you can install these
dependencies by running:

    $ sudo apt-get install build-essential libcurl4-openssl-dev zlib1g-dev

On Centos 7 or RHEL 7, you can install these
dependencies by running:

    $ sudo yum groupinstall 'Development Tools'
    $ sudo yum install libcurl-devel zlib-devel

Then, configure the build build. The `configure` script takes the standard options to set where files are
installed such as `--prefix`, etc. See `./configure --help` for details.

On Debain/Ubuntu a few options need to be passed:

    $ ./configure --prefix=/usr --bindir=/usr/sbin --sysconfdir=/etc --sharedstatedir=/usr/share --localstatedir=/var --mandir=/usr/share/man
    
On Centos 7 or RHEL 7 run:

    $ ./configure

To build the program, run:

    $ make
    
To install the freshly-built program as a package, you can use `checkinstall`.

To install `checkinstall` on Debain/Ubuntu, run:

    $ sudo apt-get install checkinstall

To install `checkinstall` on Centos/RHEL, run:

    $ sudo yum install checkinstall
    
To build and install the `geoipupdate` package, run:

    $ sudo checkinstall -y --deldoc=yes
    
Or, if you would rather not use `checkinstall`, run:

    $ sudo make install

## Installing From GitHub

To install from Git, you will need `autoconf`,`automake`, and `libtool` installed.

On Debain/Ubuntu, run:

    $ sudo apt-get install git autoconf automake libtool

On Centos/RHEL:

    $ sudo yum install git autoconf automake libtool

Our public git repository is hosted on GitHub at
https://github.com/maxmind/geoipupdate-legacy

You can clone this repository and bootstrap it by running:

    $ git clone https://github.com/maxmind/geoipupdate-legacy
    $ cd geoipupdate-legacy
    $ ./bootstrap

Then follow the instructions above for "Installing From Source Files".

# Configuring

Please see our [online guide](http://dev.maxmind.com/geoip/geoipupdate/) for
directions on how to configure GeoIP Update.

# Bug Reports

Please report bugs by filing an issue with our GitHub issue tracker at
https://github.com/maxmind/geoipupdate-legacy/issues

# License

This software is licensed under the GNU General Public License (GPL), version
2 or later.

# Copyright

This software is Copyright (c) 2014 - 2018 by MaxMind, Inc.
