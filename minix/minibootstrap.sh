#!/bin/sh

# This .sh script can be executed by the base system to let
# the pkgsrc system put things right. Currently only needed
# for mk.conf.

MKCONF=mk.conf.minix
if [ ! -f $MKCONF ]
then	echo "No $MKCONF. Please run me from pkgsrc/minix/."
	exit 1
fi

cp $MKCONF /usr/pkg/etc/mk.conf

