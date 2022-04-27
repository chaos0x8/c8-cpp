#!/usr/bin/ruby

gem 'rake-builder', '~> 4.0'

require 'rake-builder'

C8::Config.register :debug, default: false

task('debug', [:value]) do |_t, args|
  value = args[:value] == 'true'
  C8::Config.debug = value
end

$flags = ['--std=c++17', '-Wall', '-Werror', '-Wsign-conversion']

$flags += if C8::Config.debug
            ['-g']
          else
            ['-O3', '-s', '-DNDEBUG']
          end

namespaces = Dir['rakelib/c8-*.rake'].collect { |x| File.basename(x).chomp('.rake') }

desc 'Builds all libs'
C8.multitask(default: namespaces.collect { |x| "#{x}:default" })

desc 'Run all tests'
C8.multitask(test: namespaces.collect { |x| "#{x}:#{x}" }) do
  namespaces.collect { |x| "#{x}:test" }.each do |task|
    Rake::Task[task].invoke
  end
end

desc 'Clean all build targets'
C8.target(:clean) do
  %w[lib bin].each do |path|
    rm path
  end

  (Dir['.obj/*'] - Dir['.obj/*.json']).each do |path|
    rm path
  end
end

desc 'Generates template for new library'
C8.task(:new, [:name]) do |_t, args|
  name = args[:name]

  unless File.exist?("rakelib/c8-#{name}.rake")
    code = C8.erb name: name do
      IO.read('templates/rakefile.rb.erb')
    end

    IO.write("rakelib/c8-#{name}.rake", code)
  end

  FileUtils.mkdir_p "src/c8-#{name}"
  FileUtils.mkdir_p "test/c8-#{name}"

  FileUtils.touch("src/c8-#{name}/#{name}.cpp") unless File.exist?("src/c8-#{name}/#{name}.cpp")
end
