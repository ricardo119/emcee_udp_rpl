#!/bin/bash
# Execute: "chmod 755 build.sh" to get run permissions

./clean.sh
#make APP=udp-client TARGET=sky
#make APP=udp-server TARGET=sky
#make APP=rpl-router TARGET=sky
make APP=sink TARGET=sky
make APP=sensor TARGET=sky

#make APP=udp-client TARGET=z1
#make APP=udp-server TARGET=z1
#make APP=rpl-router TARGET=z1
make APP=sink TARGET=z1
make APP=sensor TARGET=z1
