# Defines debhelper buildsystem plugin interface.
# PLUGIN_PRIORITY() and is_plugin_applicable() methods
# are common for all plugins handled by Dh_Plugins,
# other methods are buildsystem specific.
#
# Copyright: © 2008 Modestas Vainius
# License: GPL-2+

package Debian::Debhelper::Buildsystem;

# Priority of the plugin. All plugins in the plugin directory
# are sorted ascendingly by this number and checked for applicability
# in the resulting sequence. Therefore, the smaller the number, the
# earlier the plugin may be picked (if it is applicable).
# Defaults to very low priority by default.
sub PLUGIN_PRIORITY { 99; }

# Custom plugin features. Currently supported 'out-of-source-tree'
# for configure.
sub FEATURES { {}; }

# Module (class) method. It is called to check if the plugin is
# applicable in the current situation, e.g. the package has the buildsystem
# which the plugin handles. Method is also given a 'data' parameter.
# Its value can be configure, build, test, install or clean representing
# which build stage the plugin will used to handle.
# This method must be reimplemented to return 1 appriopriate cases.
sub is_plugin_applicable { 0; }

# Module (class) method. Creates a new instance of the plugin.
# Default implementation creates an empty instance.
sub new {
	my $cls = shift;
	return bless({ }, $cls);
}

# Instance method called at configure stage.
# Default implementation does nothing.
sub configure { 1; }

# Instance method called at build stage.
# Default implementation does nothing.
sub build { 1; }

# Instance method called at test stage.
# Default implementation does nothing.
sub test { 1; }

# Instance method called at install stage. It needs 'destdir'
# argument specifying where to install all package files.
# Default implementation does nothing.
sub install { 1; }

# Instance method called at clean stage.
# Default implementation does nothing.
sub clean { 1; }

1;
