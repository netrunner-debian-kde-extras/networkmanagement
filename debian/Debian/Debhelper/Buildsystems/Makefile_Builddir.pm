# A buildsystem plugin for handling Makefile based projects
# for building outside the source tree (in the subdirectory).
# It also handles configuration for both in-source-tree and
# out-of-source-tree Makefile builds.
#
# Copyright: © 2008 Joey Hess
#            © 2008 Modestas Vainius
# License: GPL-2+

package Debian::Debhelper::Buildsystems::Makefile_Builddir;

use strict;
use File::Spec;
use Debian::Debhelper::Dh_Lib;
use Debian::Debhelper::Buildsystems::Makefile;
use base 'Debian::Debhelper::Buildsystems::Makefile';

sub PLUGIN_PRIORITY { 90; }

sub FEATURES {
    # Perl emits a warning when there is one element in the anon hash
	return { 'out-of-source-tree' => 1, '' => '' };
}

sub _get_builddir_name {
	my $cls = shift;
	return "obj-" . $cls->_dpkg_architecture_value("DEB_BUILD_GNU_TYPE");
}

sub _cd {
	my ($cls, $dir) = @_;
	chdir $dir or error("Unable to chdir to $dir");
}

sub _get_builddir {
	my $self = shift;
	return $self->{builddir};
}

sub _cd_to_builddir {
	my $self = shift;
	if ($self->_get_builddir() && $self->_get_path_to_source() eq ".") {
		$self->_cd($self->_get_builddir());
		$self->{path_to_source} = "..";
		return 1;
	}
	return 0;
}

sub _cd_to_sourcedir {
	my $self = shift;
	if ($self->_get_builddir() && $self->_get_path_to_source() ne ".") {
		$self->_cd($self->_get_path_to_source());
		$self->{path_to_source} = ".";
		return 1;
	}
	return 0;
}

sub _mk_builddir {
	my $self = shift;

	my $builddir = $self->_get_builddir();
	if ($builddir && ! -d $builddir) {
		$self->_cd_to_sourcedir();
		doit("mkdir", $builddir);
	}
}

###################################

sub is_plugin_applicable {
	my ($cls, $action) = @_;
	my $builddir = $cls->_get_builddir_name();

	if (-d $builddir && grep /^\Q$action\E$/, qw{build test install clean}) {
		$cls->_cd($builddir);
		my $ret = 
		    Debian::Debhelper::Buildsystems::Makefile->is_plugin_applicable($action);
		$cls->_cd("..");
		return $ret;
	} elsif ($action eq "configure") {
		return -x "configure";
	}
	return 0;
}

sub new {
	my ($cls, $action) = @_;
	my $self =
	    Debian::Debhelper::Buildsystems::Makefile::new(@_);
	# Default to building out-of-source-tree unless we are
	# at configure stage (which we handle here for both
	# in-source-tree and out-of-source-tree cases)
	$self->build_out_of_source_tree($action ne "configure");
	return $self;
}

sub build_out_of_source_tree {
	my ($self, $val) = @_;
	$self->{builddir} = ($val) ? $self->_get_builddir_name() : undef;
}

sub configure {
	my $self = shift;

	# Support both in-source-tree and out-of-source-tree
	if ($self->_get_builddir()) {
		$self->_mk_builddir();
		$self->_cd_to_builddir();
		$self->SUPER::configure(@_);
		$self->_cd_to_sourcedir();
	} else {
		$self->SUPER::configure(@_);
	}
}

sub build {
	my $self = shift;
	$self->_cd_to_builddir();
	$self->SUPER::build(@_);
	$self->_cd_to_sourcedir();
}

sub test {
	my $self = shift;
	$self->_cd_to_builddir();
	$self->SUPER::test(@_);
	$self->_cd_to_sourcedir();
}

sub install {
    my $self = shift;
	$self->_cd_to_builddir();
	$self->SUPER::install(@_);
	$self->_cd_to_sourcedir();
}

sub clean {
	my $self = shift;

	if ($self->_get_builddir()) {
		doit("rm", "-rf", $self->_get_builddir(), "Makefile");
	} else {
		$self->_cd_to_builddir();
		$self->SUPER::clean(@_);
		$self->_cd_to_sourcedir();
	}
}

1;
