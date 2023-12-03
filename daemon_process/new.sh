#!/bin/bash

 wget "https://lloydrochester.com/code/become_daemon-1.0.tar.gz"
 tar zxf become_daemon-1.0.tar.gz
 cd become_daemon-1.0
 ./configure
 make
 ./src/become_daemon

 