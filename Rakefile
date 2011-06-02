# encoding: utf-8

require 'rubygems'
require 'bundler'
begin
  Bundler.setup(:default, :development)
rescue Bundler::BundlerError => e
  $stderr.puts e.message
  $stderr.puts "Run `bundle install` to install missing gems"
  exit e.status_code
end
require 'rake'

require 'jeweler'
Jeweler::Tasks.new do |gem|
  # gem is a Gem::Specification... see http://docs.rubygems.org/read/chapter/20 for more options
  gem.name = "simpler-tiles"
  gem.homepage = "http://github.com/thejefflarson/simpler-tiles"
  gem.license = "MIT"
  gem.summary = %Q{TODO: one-line summary of your gem}
  gem.description = %Q{TODO: longer description of your gem}
  gem.email = "thejefflarson@gmail.com"
  gem.authors = ["Jeff Larson"]
  # dependencies defined in Gemfile
end
Jeweler::RubygemsDotOrgTasks.new

require 'rake/testtask'
Rake::TestTask.new(:test) do |test|
  test.libs << 'lib' << 'test'
  test.pattern = 'test/**/test_*.rb'
  test.verbose = true
end

require 'rcov/rcovtask'
Rcov::RcovTask.new do |test|
  test.libs << 'test'
  test.pattern = 'test/**/test_*.rb'
  test.verbose = true
  test.rcov_opts << '--exclude "gems/*"'
end

task :default => :test

require 'rake/extensiontask'
Rake::ExtensionTask.new('simpler_tiles', Rake.application.jeweler.gemspec) do |ext|
  ext.lib_dir = File.join('lib', 'simpler_tiles')
end

DEPEND = "ext/simpler_tiles/depend"
file DEPEND => Dir["ext/simpler_tiles/*.c"] do |t|
  `cd ext/simpler_tiles/; gcc -MM *.c > depend`
end
Rake::Task[:compile].prerequisites.unshift DEPEND

