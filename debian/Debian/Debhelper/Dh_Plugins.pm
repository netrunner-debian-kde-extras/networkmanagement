package Debian::Debhelper::Dh_Plugins;

use strict;
use File::Basename ();
use File::Spec ();
use Debian::Debhelper::Dh_Lib;

sub find_and_load_plugin {
	my $plugin_location = shift;
	my $plugin_data = shift;
	my @plugin_names = @_;

	$plugin_data = '' unless ($plugin_data);
	my $plugin_rel_dirname = File::Spec->catdir(split /::/, $plugin_location);
	for my $inc (@INC) {
		my $path = File::Spec->catfile($inc, $plugin_rel_dirname);
		if (-d $path) {
			my @modules;
			for my $module_path (glob "$path/*.pm") {
				my $plugin_name = File::Basename::basename($module_path);
				$plugin_name =~ s/\.pm$//;
				if (!@plugin_names || grep(/^\Q$plugin_name\E$/i, @plugin_names)) {
					my $module = "${plugin_location}::${plugin_name}";
					if (eval "require $module" && !$@) {
						# Module initialization was successful.
						push @modules, $module;
					} else {
						error("Unable to load plugin '$module' due to problems listed below:\n $@");
					}
				}
			}
			# Sort by priority and check which plugin is appriopriate
			for my $module (sort { $a->PLUGIN_PRIORITY() <=>
			                       $b->PLUGIN_PRIORITY() } @modules) {
				if ($module->is_plugin_applicable($plugin_data)) {
					return eval "new ${module}('$plugin_data')";
				}
			}
		}
	}
	return undef;
}

sub find_buildsystem_plugin {
	return find_and_load_plugin("Debian::Debhelper::Buildsystems", @_);
}

1;
