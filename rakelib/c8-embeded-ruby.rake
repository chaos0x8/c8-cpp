namespace('c8-embeded-ruby') {
  flags = ['--std=c++17', '-Wall', '-Werror', '-Wno-register']

  if $argv[:debug]
    flags += ['-g']
  else
    flags += ['-O3', '-s', '-DNDEBUG']
  end

  install = InstallPkg.new { |t|
    t.name = 'pkgs'
    t.pkgs << ['ruby-dev']
  }

  generated = [
    'src/c8-embeded-ruby/errors.hpp'
  ].collect { |fn|
    if dir = fn.chomp(File.extname(fn)) and File.directory?(dir)
      Generate.includeDirectory(dir)
    end
  }

  library = Library.new { |t|
    t.name = 'lib/libc8-embeded-ruby.a'
    t.requirements << ['c8-embeded-ruby:pkgs', generated]
    t.sources << FileList['src/c8-embeded-ruby/**/*.cpp']
    t.includes << ['src']
    t.pkgs << ['ruby']
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-embeded-ruby-ut'
    t.requirements << ['c8-embeded-ruby:pkgs', generated]
    t.sources << FileList['test/c8-embeded-ruby/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library]
    t.pkgs << ['ruby']
    t.flags << flags
  }

  desc 'Builds c8-embeded-ruby'
  C8.multitask(default: Names['generated:default', library])

  desc 'Runs c8-embeded-ruby tests'
  C8.multitask(test: Names['generated:default', library, ut]) {
    sh ut.name
  }
}
