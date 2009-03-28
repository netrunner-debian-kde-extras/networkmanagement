CMAKE_DEFAULT_ARGS = -DCMAKE_INSTALL_PREFIX=/usr -D\"CMAKE_C_FLAGS\"="$(CFLAGS)" \
                       -D\"CMAKE_CXX_FLAGS\"="$(CXXFLAGS)" \
                       -DCMAKE_SKIP_RPATH=ON -DCMAKE_VERBOSE_MAKEFILE=ON
CMAKE_ARGS ?=
DEB_BUILDDIR ?= obj-$(shell dpkg-architecture -qDEB_BUILD_GNU_TYPE)
ifeq (1,$(shell dh_listpackages | wc -l))
DEB_DESTDIR ?= debian/$(shell dh_listpackages)
else
DEB_DESTDIR ?= debian/tmp
endif

$(DEB_BUILDDIR):
	mkdir "$@"

cmake_configure: $(DEB_BUILDDIR)
	cd $(DEB_BUILDDIR) && cmake .. $(CMAKE_DEFAULT_ARGS) $(CMAKE_ARGS)

cmake_build:
	cd $(DEB_BUILDDIR) && make

cmake_install:
	cd $(DEB_BUILDDIR) && make DESTDIR=$(CURDIR)/$(DEB_DESTDIR) install

cmake_clean:
	rm -rf $(DEB_BUILDDIR)
