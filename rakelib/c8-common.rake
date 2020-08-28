def c8_common_errors_new key, c
  header = GeneratedFile.new(format: true) { |t|
    t.name = File.join('src/c8-common/errors', "#{key}.hpp")
    t.code = proc {
      d = []
      d << "#pragma once"
      d << ""
      d << "#include \"errors/Error.hpp\""
      d << ""
      d << "namespace C8::Common::Errors {"
      d << "  struct #{key} : public Error {"
      d << "    explicit #{key}();"
      d << "  };"
      d << "}"
    }
  }

  source = GeneratedFile.new(format: true) { |t|
    t.name = File.join('src/c8-common/errors', "#{key}.cpp")
    t.code = proc {
      d = []
      d << "#include \"#{key}.hpp\""
      d << "#include \"Format.hpp\""
      d << ""
      d << "namespace C8::Common::Errors {"
      d << "  #{key}::#{key}() : Error(#{c['string']}) {}"
      d << "}"
    }
  }

  test = GeneratedFile.new(format: true) { |t|
    t.name = File.join('test/c8-common/errors', "Test#{key}.cpp")
    t.code = proc {
      d = []
      d << "#include \"errors/#{key}.hpp\""
      d << "#include <gmock/gmock.h>"
      d << ""
      d << "namespace C8::Common::Errors {"
      d << "using namespace testing;"
      d << "using namespace std::string_literals;"
      d << ""
      d << "struct Test#{key} : public Test {"
      d << "  #{key} sut = #{key}();"
      d << "};"
      d << ""
      d << "TEST_F(Test#{key}, testWhat) {"
      d << "ASSERT_THAT(sut.what(), Eq(\"#{key}\"s));"
      d << "}"
      d << "}"
    }
  }

  [header, source, test]
end

namespace('c8-common') {
  flags = ['--std=c++17', '-Wall', '-Werror', '-O3', '-s', '-DNDEBUG']

  if ENV.has_key?('debug')
    flags -= ['-O3', '-s', '-DNDEBUG']
    flags += ['-g']
  end

  generated = ['src/c8-common/errors.hpp'].collect { |fn|
    if dir = fn.chomp(File.extname(fn)) and File.directory?(dir)
      Generate.includeDirectory(dir)
    end
  }

  library = Library.new { |t|
    t.name = 'lib/libc8-common.a'
    t.requirements << generated
    t.sources << FileList['src/c8-common/**/*.cpp']
    t.includes << ['src']
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-common-ut'
    t.requirements << generated
    t.sources << FileList['test/c8-common/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library]
    t.flags << flags
  }

  desc 'Builds c8-common'
  C8.multitask(default: Names['generated:default', library])

  desc 'Runs c8-common tests'
  C8.multitask(test: Names['generated:default', library, ut]) {
    sh ut.name
  }

  desc 'Generates new error'
  C8.task(:error, [:name]) { |t, args|
    name = args[:name]

    gen = c8_common_errors_new(name, {'string' => "\"#{name}\""})

    task('error_exec' => Names[gen])

    Rake::Task['error_exec'].invoke
  }
}
