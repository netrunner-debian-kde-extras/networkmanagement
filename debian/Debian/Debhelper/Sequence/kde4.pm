#!/usr/bin/perl -w

use strict;
use warnings;
use Debian::Debhelper::Dh_Lib;

# Support automatic detection of -dbg packages
sub sourcepackage {
    open (CONTROL, 'debian/control') ||
        error("cannot read debian/control: $!\n");
    while (<CONTROL>) {
        if (/^Source:\s*(\S+)/) {
            close(CONTROL);
            return $1;
        }
    }
    close CONTROL;
    error("could not find Source: line in control file.");
}

my @arch_packages = getpackages("arch");
my $srcpkg = sourcepackage();
if (grep( { $_ eq "$srcpkg-dbg" } @arch_packages) == 1) {
    my @options;
    if (exists $ENV{DH_STRIP_OPTIONS}) {
        push @options, $ENV{DH_STRIP_OPTIONS};
    }
    push @options, "--dbg-package=$srcpkg-dbg";
    $ENV{DH_STRIP_OPTIONS} = join(' ', @options);
}

1;
