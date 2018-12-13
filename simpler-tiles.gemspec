# -*- encoding: utf-8 -*-
require "#{File.expand_path(File.dirname(__FILE__))}/lib/simpler_tiles/version"

Gem::Specification.new do |s|
  s.name = %q{simpler-tiles}
  s.version = SimplerTiles::VERSION

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Jeff Larson"]
  s.date = %q{2011-06-23}
  s.description = %q{Ruby bindings for Simple Tiles}
  s.email = %q{thejefflarson@gmail.com}
  s.extensions = ["ext/simpler_tiles/extconf.rb"]
  s.extra_rdoc_files = [
    "LICENSE",
    "README"
  ]
  s.files = `git ls-files`.split("\n")
  s.test_files = `git ls-files -- {test}/*`.split("\n")
  s.homepage = %q{http://github.com/propublica/simpler-tiles}
  s.licenses = ["MIT"]
  s.require_paths = ["lib"]
  s.summary = %q{A set of ruby bindings for the Simple Tiles mapping library.}

  s.add_development_dependency(%q<bundler>, [">= 1.5.0"])
  s.add_development_dependency(%q<minitest>, ["~> 4.0.0"])
  s.add_development_dependency(%q<pry-byebug>, ["~> 3.6.0"])
  s.add_development_dependency(%q<pygmentize>, ["~> 0.0.3"])
  s.add_development_dependency(%q<rake-compiler>, [">= 0"])
  s.add_development_dependency(%q<yard>, ["~> 0.9.16"])
end
