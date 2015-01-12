# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'diff_set/version'

Gem::Specification.new do |spec|
  spec.name          = 'diff_set'
  spec.version       = DiffSet::VERSION
  spec.authors       = ['Michael Parrish']
  spec.email         = ['michael@zooniverse.org']
  spec.summary       = 'DiffSet contains a collection of data structures optimized to perform partial set subtractions'
  spec.description   = ''
  spec.homepage      = 'https://github.com/parrish/diff_set'
  spec.license       = 'MIT'
  
  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ['lib']
  spec.extensions    = ['ext/diff_set/extconf.rb']
  
  spec.add_development_dependency 'bundler', '~> 1.5'
  spec.add_development_dependency 'rake'
  spec.add_development_dependency 'rake-compiler', '~> 0.9.2'
  spec.add_development_dependency 'rspec'
  spec.add_development_dependency 'pry'
  spec.add_runtime_dependency 'rice', '~> 1.7'
end
