====================================================
FogLAMP Google Hangouts notification delivery plugin
====================================================

A simple Google Hangouts Chat notification delivery plugin.

The plugin uses the simple Google Hangouts Chat webhook API to send notification
messages to a chat room.

You must obtain a URL go to your Google Hangouts Chat room 
  - Select "Configure webhooks

  - Enter a name for your application

  - Add an option Avatar URL

  - Copy the Webhook URL into the plugin URL configuration item


You may also configure some static text that will be sent in each notification.

Installation
------------

The plugin can be installed with given `requirements.sh <requirements.sh>`_ or the following steps:


.. code-block:: bash

   $ sudo apt install -y libcurl4-openssl-dev


Build
-----
To build FogLAMP "Hangouts notification" C++ plugin:

.. code-block:: console

  $ mkdir build
  $ cd build
  $ cmake ..
  $ make

- By default the FogLAMP develop package header files and libraries
  are expected to be located in /usr/include/foglamp and /usr/lib/foglamp
- If **FOGLAMP_ROOT** env var is set and no -D options are set,
  the header files and libraries paths are pulled from the ones under the
  FOGLAMP_ROOT directory.
  Please note that you must first run 'make' in the FOGLAMP_ROOT directory.

You may also pass one or more of the following options to cmake to override 
this default behaviour:

- **FOGLAMP_SRC** sets the path of a FogLAMP source tree
- **FOGLAMP_INCLUDE** sets the path to FogLAMP header files
- **FOGLAMP_LIB sets** the path to FogLAMP libraries
- **FOGLAMP_INSTALL** sets the installation path of Random plugin

NOTE:
 - The **FOGLAMP_INCLUDE** option should point to a location where all the FogLAMP 
   header files have been installed in a single directory.
 - The **FOGLAMP_LIB** option should point to a location where all the FogLAMP
   libraries have been installed in a single directory.
 - 'make install' target is defined only when **FOGLAMP_INSTALL** is set

Examples:

- no options

  $ cmake ..

- no options and FOGLAMP_ROOT set

  $ export FOGLAMP_ROOT=/some_foglamp_setup

  $ cmake ..

- set FOGLAMP_SRC

  $ cmake -DFOGLAMP_SRC=/home/source/develop/FogLAMP  ..

- set FOGLAMP_INCLUDE

  $ cmake -DFOGLAMP_INCLUDE=/dev-package/include ..
- set FOGLAMP_LIB

  $ cmake -DFOGLAMP_LIB=/home/dev/package/lib ..
- set FOGLAMP_INSTALL

  $ cmake -DFOGLAMP_INSTALL=/home/source/develop/FogLAMP ..

  $ cmake -DFOGLAMP_INSTALL=/usr/local/foglamp ..
