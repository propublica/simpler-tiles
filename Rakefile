# encoding: utf-8

require 'rubygems'
require 'bundler'

begin
  Bundler.setup(:default, :development, :test)
rescue Bundler::BundlerError => e
  $stderr.puts e.message
  $stderr.puts "Run `bundle install` to install missing gems"
  exit e.status_code
end
Bundler::GemHelper.install_tasks
require 'rake'
require 'yard'

YARD::Rake::YardocTask.new

require 'erb'
task :doc do |t|
  File.open("index.html", 'w').write ERB.new(File.open("index.erb").read).result(binding)
end

task :publish do |t|
  `git checkout gh-pages`
  `git merge master`
  `git push`
  `git checkout master`
end

require 'rake/testtask'
Rake::TestTask.new(:test) do |test|
  test.libs << 'lib' << 'test'
  test.pattern = 'test/**/test_*.rb'
  test.verbose = true
end

task :default => :test
# e.g. DEV_CONFIG='--with-simple-tiles-include=/tmp/simple-tiles/usr/local/include/ --with-simple-tiles-lib=/tmp/simple-tiles/usr/local/lib/' bundle exec rake test
require 'rake/extensiontask'
Rake::ExtensionTask.new('simpler_tiles') do |ext|
  if ENV['DEV_CONFIG']
    ext.config_options << ENV['DEV_CONFIG']
  end
  ext.lib_dir = File.join('lib', 'simpler_tiles')
end

Rake::Task[:test].prerequisites.unshift :compile
