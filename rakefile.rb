#!/usr/bin/ruby

gem 'rake-builder', '~> 3.1', '>= 3.1.0'

require 'rake-builder'

$argv = {}

RakeBuilder::OptionParser.new { |op|
  op.on('--help') {
    $stdout.puts op
    exit 0
  }

  op.on('--debug', 'adds debug flags') { |v|
    $argv[:debug] = v
  }
}.parse!(ARGV)

namespaces = Dir['rakelib/c8-*.rake'].collect { |x| File.basename(x).chomp('.rake') }

desc 'Builds all libs'
task(default: namespaces.collect { |x| "#{x}:default" })

desc 'Run all tests'
task(test: namespaces.collect { |x| "#{x}:test" })

desc 'Clean all build targets'
task(:clean) {
  Dir['.obj', 'lib', 'bin'].each { |fn|
    if File.directory? fn
      FileUtils.rm_rf fn, verbose: true
    else
      FileUtils.rm fn, verbose: true
    end
  }
}

desc 'Generates template for new library'
task(:new, [:name]) { |t, args|
  name = args[:name]

  unless File.exist?("rakelib/c8-#{name}.rake")
    IO.write("rakelib/c8-#{name}.rake", C8.erb(C8.data(__FILE__).rakefile, name: name))
  end

  FileUtils.mkdir_p "src/c8-#{name}"
  FileUtils.mkdir_p "test/c8-#{name}"

  unless File.exist?("test/c8-#{name}/main.cpp")
    IO.write("test/c8-#{name}/main.cpp", C8.erb(C8.data(__FILE__).ut_main))
  end

  unless File.exist?("src/c8-#{name}/#{name}.cpp")
    FileUtils.touch("src/c8-#{name}/#{name}.cpp")
  end
}

__END__
@@rakefile=
namespace('c8-<%= @name %>') {
  flags = ['--std=c++17', '-Wall', '-Werror']

  if $argv[:debug]
    flags += ['-g']
  else
    flags += ['-O3', '-s', '-DNDEBUG']
  end

  install = InstallPkg.new { |t|
    t.name = 'pkgs'
    t.pkgs << []
  }

  pkgs = []

  generated = [
    'src/c8-<%= @name %>/errors.hpp'
  ].collect { |fn|
    if dir = fn.chomp(File.extname(fn)) and File.directory?(dir)
      Generate.includeDirectory(dir)
    end
  }.compact

  library = Library.new { |t|
    t.name = 'lib/libc8-<%= @name %>.a'
    t.requirements << ['c8-<%= @name %>:pkgs', generated]
    t.sources << FileList['src/c8-<%= @name %>/**/*.cpp']
    t.includes << ['src']
    t.pkgs << pkgs
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-<%= @name %>-ut'
    t.requirements << ['c8-<%= @name %>:pkgs', generated]
    t.sources << FileList['test/c8-<%= @name %>/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library]
    t.pkgs << pkgs
    t.flags << flags
  }

  desc 'Builds c8-<%= @name %>'
  C8.multitask(default: Names['generated:default', library])

  desc 'Runs c8-<%= @name %> tests'
  C8.multitask(test: Names['generated:default', library, ut]) {
    sh ut.name
  }
}
@@ut_main=
#include <gtest/gtest.h>

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
