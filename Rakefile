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
require 'lib/simpler_tiles'
Jeweler::Tasks.new do |gem|
  # gem is a Gem::Specification... see http://docs.rubygems.org/read/chapter/20 for more options
  gem.name = "simpler-tiles"
  gem.homepage = "http://github.com/thejefflarson/simpler-tiles"
  gem.license = "MIT"
  gem.summary = %Q{maps!}
  gem.description = %Q{mappy maps!}
  gem.email = "thejefflarson@gmail.com"
  gem.authors = ["Jeff Larson"]
  gem.version = SimplerTiles::VERSION
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
file DEPEND => FileList["ext/simpler_tiles/*.c"] do |t|
  `cd ext/simpler_tiles/; gcc -MM *.c > depend`
end

DATA = "data/tl_2010_us_state10.shp"
file DATA do |t|
  if !File.exists? t.name
    require 'fileutils'
    FileUtils.mkdir_p "data"
    tasks = []
    tasks << 'cd data'
    tasks << 'curl -O ftp://ftp2.census.gov/geo/tiger/TIGER2010/STATE/2010/tl_2010_us_state10.zip'
    tasks << 'unzip tl_2010_us_state10.zip'
    `#{tasks.join ';'}`
  end
end

Rake::Task[:compile].prerequisites.unshift DEPEND
Rake::Task[:test].prerequisites.unshift DATA
Rake::Task[:test].prerequisites.unshift :compile
