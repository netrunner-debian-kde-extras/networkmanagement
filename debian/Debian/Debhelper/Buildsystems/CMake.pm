# A buildsystem plugin for handling CMake based projects.
# It uses out-of-source-tree Makefile handler for everything but
# configuration.
#
# Copyright: © 2008 Modestas Vainius
# License: GPL-2+

package Debian::Debhelper::Buildsystems::CMake;

use strict;
use Debian::Debhelper::Dh_Lib;
use Debian::Debhelper::Buildsystems::Makefile_Builddir;
use base 'Debian::Debhelper::Buildsystems::Makefile_Builddir';

sub PLUGIN_PRIORITY { 10; }

# No custom features
sub FEATURES { {}; }

sub _add_cmake_flag {
	my ($self, $name, $val) = @_;
	push @{$self->{cmake_flags}}, "-D$name=$val";
}

##############################################

sub is_plugin_applicable {
	return -e "CMakeLists.txt";
}

sub new {
	my $cls = shift;
	my $self = Debian::Debhelper::Buildsystems::Makefile_Builddir::new($cls, @_);
	# Always default to out-of-source-tree builds. Otherwise
	# source directory would be hardly cleanable.
	$self->build_out_of_source_tree(1);
	$self->{cmake_flags} = [];
	return $self;
}

sub configure {
	my $self = shift;

	$self->_mk_builddir();

	# Standard set of cmake flags
	$self->_add_cmake_flag("CMAKE_INSTALL_PREFIX", "/usr");
	$self->_add_cmake_flag("CMAKE_C_FLAGS", $ENV{CFLAGS}) if (exists $ENV{CFLAGS});
	$self->_add_cmake_flag("CMAKE_CXX_FLAGS", $ENV{CXXFLAGS}) if (exists $ENV{CXXFLAGS});
	$self->_add_cmake_flag("CMAKE_SKIP_RPATH", "ON");
	$self->_add_cmake_flag("CMAKE_VERBOSE_MAKEFILE", "ON");

	$self->_cd_to_builddir();
	doit("cmake", $self->_get_path_to_source(),
	     @{$self->{cmake_flags}}, @{$dh{U_PARAMS}});
	$self->_cd_to_sourcedir();
}

1;
