package Debian::Debhelper::Dh_Lib::Ex;
use strict;

do "/usr/share/perl5/Debian/Debhelper/Dh_Lib.pm";
Debian::Debhelper::Dh_Lib->import();

sub _prepend_args_from_env {
    my $envvar = shift;
    if (defined($ENV{$envvar})) {
        # Ignore leading/trailing whitespace.
        unshift @ARGV,
            split("\0", `$^X -e 'print join("\\0", \@ARGV)' -- $ENV{$envvar}`);
    }
}

my $dh_lib_init = \&Debian::Debhelper::Dh_Lib::init;
sub init_ex {
    # If {DH_HELPER}_OPTIONS is set, prepend it to @ARGV
    my $dh_helpername = uc(basename($0));
    if ($dh_helpername =~ /DH_/) {
        # Only for dh_* helpers, not for dh(1).
        _prepend_args_from_env("${dh_helpername}_OPTIONS")
    }

    # Check if DH_ECHO_ARGS environment variable is set and if so,
    # print debhelper program name and options to stdout.
    if (exists $ENV{DH_ECHO_ARGS} && $ENV{DH_ECHO_ARGS}) {
        my $echoname = ($0 =~ m@^/@) ? basename($0) : $0;
        print $echoname, " ", escape_shell(@ARGV), "\n";
    }
    &$dh_lib_init(@_);
}

*Debian::Debhelper::Dh_Lib::init = *Debian::Debhelper::Dh_Lib::Ex::init_ex;

1;
