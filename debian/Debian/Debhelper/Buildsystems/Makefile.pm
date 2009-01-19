# A buildsystem plugin for handling Makefile based projects
# (like autotools based ones). Configuration and
# out-of-source-tree builds are handled in the Makefile_Builddir
# plugin.
#
# Copyright: © 2008 Joey Hess
#            © 2008 Modestas Vainius
# License: GPL-2+

package Debian::Debhelper::Buildsystems::Makefile;

use strict;
use File::Spec;
use Debian::Debhelper::Dh_Lib;
use Debian::Debhelper::Buildsystem;
use base 'Debian::Debhelper::Buildsystem';

sub PLUGIN_PRIORITY { 90; }

sub _dpkg_architecture_value {
	my ($cls, $var) = @_;
	my $value=`dpkg-architecture -q$var 2>/dev/null` || error("dpkg-architecture failed");
	chomp $value;
	return $value;
}

sub _get_path_to_source {
	my ($self, $file) = @_;
	return ($file) ?
	    File::Spec->catfile($self->{path_to_source}, $file) :
	    $self->{path_to_source};
}

sub _sourcepackage {
    my $self = shift;

	open (CONTROL, $self->_get_path_to_source('debian/control')) ||
		error("cannot read debian/control: $!\n");
	while (<CONTROL>) {
		chomp;
		s/\s+$//;
		if (/^Source:\s*(.*)/) {
			close CONTROL;
			return $1;
		}
	}

	close CONTROL;
	error("could not find Source: line in control file.");
}

sub _exists_make_target {
	my ($cls, $target) = @_;
	# Use make -n to check to see if the target would do
	# anything. There's no good way to test if a target exists.
	my $ret=`$ENV{MAKE} -s -n $target 2>/dev/null`;
	chomp $ret;
	return length($ret);
}

sub _make_first_existing_target {
	my $cls = shift;
	my $targets = shift;

	$ENV{MAKE}="make" unless exists $ENV{MAKE};
	foreach my $target (@$targets) {
		if ($cls->_exists_make_target($target)) {
			doit($ENV{MAKE}, $target, @_);
			return $target;
		}
	}
	return undef;
}

#############################

sub is_plugin_applicable {
	my ($cls, $action) = @_;
	if (grep /^\Q$action\E$/, qw{build test install clean}) {
		return -e "Makefile" || -e "makefile" || -e "GNUmakefile";
	}
	# Do not handle configure stage here. It will be taken care by
	# Makefile_Builddir to support out-of-source-tree builds
	return 0;
}

sub new {
	my $cls = shift;
	return bless({
	    'path_to_source' => '.'}, $cls);
}

sub configure {
	my $self = shift;

	# Standard set of options for configure.
	my @opts;
	push @opts, "--build=" .
	    $self->_dpkg_architecture_value("DEB_BUILD_GNU_TYPE");
	push @opts, "--prefix=/usr";
	push @opts, "--includedir=\${prefix}/include";
	push @opts, "--mandir=\${prefix}/share/man";
	push @opts, "--infodir=\${prefix}/share/info";
	push @opts, "--sysconfdir=/etc";
	push @opts, "--localstatedir=/var";
	push @opts, "--libexecdir=\${prefix}/lib/" . $self->_sourcepackage();
	push @opts, "--disable-maintainer-mode";
	push @opts, "--disable-dependency-tracking";
	# Provide --host only if different from --build, as recommended in
	# autotools-dev README.Debian: When provided (even if equal) autotools
	# 2.52+ switches to cross-compiling mode.
	if ($self->_dpkg_architecture_value("DEB_BUILD_GNU_TYPE")
	    ne $self->_dpkg_architecture_value("DEB_HOST_GNU_TYPE")) {
		push @opts, "--host=" . $self->_dpkg_architecture_value("DEB_HOST_GNU_TYPE");
	}

	doit($self->_get_path_to_source("configure"), @opts, @{$dh{U_PARAMS}});
}

sub build {
	doit(exists $ENV{MAKE} ? $ENV{MAKE} : "make", @{$dh{U_PARAMS}});
}

sub test {
	my $self = shift;
	$self->_make_first_existing_target(['test', 'check'], @{$dh{U_PARAMS}});
}

sub install {
	my ($self, $destdir) = @_;

	$ENV{MAKE}="make" unless exists $ENV{MAKE};
	my @params="DESTDIR=$destdir";

	# Special case for MakeMaker generated Makefiles.
	if (-e "Makefile" &&
	    system('grep -q "generated automatically by MakeMaker" Makefile') == 0) {
		push @params, "PREFIX=/usr";
	}

	$self->_make_first_existing_target(['install'], @params, @{$dh{U_PARAMS}});
}

sub clean {
	my $self = shift;
	$self->_make_first_existing_target(
	    ['distclean', 'realclean', 'clean'], @{$dh{U_PARAMS}});
}

1;
