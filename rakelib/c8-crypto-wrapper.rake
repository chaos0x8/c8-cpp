namespace('c8-crypto-wrapper') {
  flags = $flags

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
    t.requirements << ['c8-crypto-wrapper:pkgs', generated, C8::Config]
    t.sources << FileList['src/c8-crypto-wrapper/**/*.cpp']
    t.includes << ['src']
    t.pkgs << pkgs
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-crypto-wrapper-ut'
    t.requirements << ['c8-crypto-wrapper:pkgs', generated, C8::Config, 'c8-common:default']
    t.sources << FileList['test/c8-crypto-wrapper/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library, 'lib/libc8-common.a']
    t.libs << '-lgmock_main' unless t.sources.find { |x| File.basename(x.name) == 'main.cpp' }
    t.pkgs << pkgs
    t.flags << flags
  }

  desc 'Builds c8-crypto-wrapper'
  C8.multitask(default: Names::All['generated:default', library])

  desc 'Runs c8-crypto-wrapper tests'
  C8.multitask(test: Names::All['generated:default', library, ut]) {
    sh ut.name
  }
}
