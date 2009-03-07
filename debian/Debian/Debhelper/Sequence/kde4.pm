#!/usr/bin/perl -w

use strict;
use warnings;
use Debian::Debhelper::Dh_Lib;

# Remove dh_auto_test
remove_command("dh_auto_test");

# Insert dh_bugfiles
insert_after("dh_installxfonts", "dh_bugfiles");

1;
