require 'bundler/gem_tasks'
require 'rake/extensiontask'
require 'rspec/core/rake_task'
require 'rubygems/package_task'

GEMSPEC = Gem::Specification.load 'diff_set.gemspec'

Gem::PackageTask.new(GEMSPEC) do |pkg|
  pkg.need_zip = true
  pkg.need_tar = true
end

Rake::ExtensionTask.new('diff_set_ext', GEMSPEC) do |ext|
  ext.ext_dir = 'ext/diff_set'
  ext.lib_dir = 'lib/diff_set'
  ext.source_pattern = '*.{h,cpp}'
end

RSpec::Core::RakeTask.new :spec
task default: [:compile, :spec]
