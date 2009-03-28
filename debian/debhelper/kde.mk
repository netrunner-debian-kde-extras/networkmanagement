# Using quilt patch system
include /usr/share/quilt/quilt.make

# Include default KDE 4 cmake configuration variables
include /usr/share/pkg-kde-tools/makefiles/1/variables.mk

# CMake module
include debian/debhelper/cmake.mk

# CMake configuration flags
DEB_CMAKE_KDE_DEFAULT_FLAGS = $(DEB_CMAKE_KDE4_FLAGS) $(DEB_CMAKE_CUSTOM_FLAGS)
CMAKE_ARGS = $(DEB_CMAKE_KDE_DEFAULT_FLAGS)

# Source package name
DEB_SOURCE_PACKAGE := $(shell grep '^Source:' debian/control | sed 's/^Source:[[:space:]]*\([^[:space:]]\+\).*$$/\1/')

# Handle DEB_BUILD_OPTIONS=noopt and C(XX)FLAGS
ifeq (,$(filter noopt,$(DEB_BUILD_OPTIONS)))
    CFLAGS = -g -O2
    CXXFLAGS = -g -O2
else
    CFLAGS = -g -O0
    CXXFLAGS = -g -O0
endif

export CFLAGS
export CXXFLAGS

# DEB_BUILD_OPTIONS parallel=n support (policy 3.8.0 compliance)
ifneq (,$(filter parallel=%,$(DEB_BUILD_OPTIONS)))
    NUMJOBS = $(patsubst parallel=%,%,$(filter parallel=%,$(DEB_BUILD_OPTIONS)))
    MAKEFLAGS += -j$(NUMJOBS)
endif

export MAKEFLAGS

# Pass -DCMAKE_USE_RELATIVE_PATHS=ON to cmake when cmake >= 2.6.2-1 is used.
CMAKE_DEB_VERSION := $(shell dpkg -l 'cmake' | grep 'ii' | awk '{print $$3}')
ifeq (yes,$(shell dpkg --compare-versions '$(CMAKE_DEB_VERSION)' ge '2.6.2-1' && echo 'yes'))
    DEB_CMAKE_CUSTOM_FLAGS += -DCMAKE_USE_RELATIVE_PATHS=ON
endif

# Default targets
DEB_ALL_DEFAULT_TARGETS := build install binary binary-arch binary-indep clean
KDE_ALL_DEFAULT_TARGETS :=  $(patsubst %,kde/%,$(DEB_ALL_DEFAULT_TARGETS))

# Default overrides for cmake configuring/building/installing
DEB_KDE_OVERRIDE_DH_AUTO_CONFIGURE ?= override_dh_auto_configure
$(DEB_KDE_OVERRIDE_DH_AUTO_CONFIGURE): cmake_configure
.PHONY: $(DEB_KDE_OVERRIDE_DH_AUTO_CONFIGURE)

DEB_KDE_OVERRIDE_DH_AUTO_BUILD ?= override_dh_auto_build
$(DEB_KDE_OVERRIDE_DH_AUTO_BUILD): cmake_build
.PHONY: $(DEB_KDE_OVERRIDE_DH_AUTO_BUILD)

DEB_KDE_OVERRIDE_DH_AUTO_INSTALL ?= override_dh_auto_install
$(DEB_KDE_OVERRIDE_DH_AUTO_INSTALL): cmake_install
.PHONY: $(DEB_KDE_OVERRIDE_DH_AUTO_INSTALL)

# dh_strip override - automatic -dbg package
DEB_DBG_PACKAGE_NAME ?= $(DEB_SOURCE_PACKAGE)-dbg
ifeq ($(DEB_DBG_PACKAGE_NAME),$(filter $(DEB_DBG_PACKAGE_NAME),$(shell dh_listpackages -s)))

DEB_KDE_OVERRIDE_DH_STRIP ?= override_dh_strip
$(DEB_KDE_OVERRIDE_DH_STRIP):
	dh_strip --dbg-package=$(DEB_DBG_PACKAGE_NAME)

endif

# Clean rule is more complex. Cleaning should be done
# before unpatching.
clean_before_unpatch: cmake_clean
	dh clean

unpatch: clean_before_unpatch

kde/clean: unpatch

# Required relationship between default targets
$(filter-out build clean,$(DEB_ALL_DEFAULT_TARGETS)): build

kde/build: patch

# Default implementation (DH) of default targets.
# Exclude clean as we have a specific target for it
$(filter-out kde/clean,$(KDE_ALL_DEFAULT_TARGETS)):
	dh $(subst kde/,,$@)

# An implicit rule which runs default kde/ targets
# It can be easily overriden.
%: kde/%
	

.PHONY: $(KDE_ALL_DEFAULT_TARGETS) clean_before_unpatch
