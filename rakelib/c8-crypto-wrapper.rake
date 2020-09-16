namespace('c8-crypto-wrapper') {
  flags = ['--std=c++17', '-Wall', '-Werror', '-O3', '-s', '-DNDEBUG']

  if $argv[:debug]
    flags -= ['-O3', '-s', '-DNDEBUG']
    flags += ['-g']
  end

  install = InstallPkg.new { |t|
    t.name = 'pkgs'
    t.pkgs << ['libcrypto++-dev']
  }

  pkgs = ['libcrypto++']

  generated = [
    'src/c8-crypto-wrapper/errors.hpp'
  ].collect { |fn|
    if dir = fn.chomp(File.extname(fn)) and File.directory?(dir)
      Generate.includeDirectory(dir)
    end
  }.compact

  library = Library.new { |t|
    t.name = 'lib/libc8-crypto-wrapper.a'
    t.requirements << ['c8-crypto-wrapper:pkgs', generated]
    t.sources << FileList['src/c8-crypto-wrapper/**/*.cpp']
    t.includes << ['src']
    t.pkgs << pkgs
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-crypto-wrapper-ut'
    t.requirements << ['c8-crypto-wrapper:pkgs', generated, 'c8-common:default']
    t.sources << FileList['test/c8-crypto-wrapper/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library, 'lib/libc8-common.a']
    t.pkgs << pkgs
    t.flags << flags
  }

  desc 'Builds c8-crypto-wrapper'
  C8.multitask(default: Names['generated:default', library])

  desc 'Runs c8-crypto-wrapper tests'
  C8.multitask(test: Names['generated:default', library, ut]) {
    sh ut.name
  }
}
