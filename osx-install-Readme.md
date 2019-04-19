##Install OSX

macOS Build Instructions and Notes
====================================
The commands in this guide should be executed in a Terminal application.
The built-in one is located in `/Applications/Utilities/Terminal.app`.

Preparation
-----------
Install the macOS command line tools:

`xcode-select --install`

When the popup appears, click `Install`.

Then install [Homebrew](https://brew.sh).

Dependencies
----------------------

    brew install automake berkeley-db4 libtool miniupnpc openssl pkg-config protobuf python qt libevent qrencode
	
	latest version of mac needs boost 1.57 to work, so we manually install it and link to brew(if boost is already installed and is greater than version 1.57 uninstall it using: 
		brew uninstall boost
		or
		brew uninstall boost@<version number>
		( for e.g 1.60 would be boost@1.60 etc.)
	brew install boost@1.57
	brew link boost@1.57 --force
	
If you want to build the disk image with `make deploy` (.dmg / optional), you need RSVG

    brew install librsvg

Build SmartCloud Core
------------------------

1. Clone the SmartCloud Core source code and cd into `posq`

        git clone https://github.com/SMRT-Cloud/posq.git
        cd posq

2.  Build posq Core:

    Configure and build the headless posq Core binaries as well as the GUI (if Qt is found).

    You can disable the GUI build by passing `--without-gui` to configure.

	prepair export for fix with:
		export LDFLAGS=-L/usr/local/opt/openssl/lib
		export CPPFLAGS=-I/usr/local/opt/openssl/include
	
	then proceed with:
        ./autogen.sh
        ./configure
        make

3.  It is recommended to build and run the unit tests:

        make check

4.  You can also create a .dmg that contains the .app bundle (optional):

        make deploy

Running
-------

posq Core is now available at `./src/posqd`

Before running, it's recommended that you create an RPC configuration file.

    echo -e "rpcuser=posqrpc\nrpcpassword=$(xxd -l 16 -p /dev/urandom)" > "/Users/${USER}/Library/Application Support/posq/posq.conf"

    chmod 600 "/Users/${USER}/Library/Application Support/posq/posq.conf"

The first time you run posqd, it will start downloading the blockchain. This process could take several hours.

You can monitor the download process by looking at the debug.log file:

    tail -f $HOME/Library/Application\ Support/posq/debug.log

Other commands:
-------

    ./src/posqd -daemon # Starts the posq daemon.
    ./src/posq-cli --help # Outputs a list of command-line options.
    ./src/posq-cli help # Outputs a list of RPC commands when the daemon is running.

Notes
-----

* Tested on OS X 10.10 Yosemite through macOS 10.13 High Sierra on 64-bit Intel processors only.

