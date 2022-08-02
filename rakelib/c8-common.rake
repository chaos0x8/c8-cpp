require_relative '_common'

def c8_common_errors_new(key, c, lib:)
  libNamespace = lib.gsub(/^c8-/, '').split('-').collect(&:capitalize).join
  namespace = ['C8', libNamespace, 'Errors'].join('::')

  header = GeneratedFile.new(format: true) do |t|
    t.name = File.join("src/#{lib}/errors", "#{key}.hpp")
    t.code = proc {
      C8.erb lib: lib, key: key, namespace: namespace do
        IO.read('templates/Error.hpp.erb')
      end
    }
  end

  source = GeneratedFile.new(format: true) do |t|
    t.name = File.join("src/#{lib}/errors", "#{key}.cpp")
    t.code = proc {
      C8.erb lib: lib, key: key, namespace: namespace, c: c do
        IO.read('templates/Error.cpp.erb')
      end
    }
  end

  test = GeneratedFile.new(format: true) do |t|
    t.name = File.join("test/#{lib}/errors", "Test#{key}.cpp")
    t.code = proc {
      C8.erb lib: lib, key: key, namespace: namespace do
        IO.read('templates/TestError.cpp.erb')
      end
    }
  end

  [header, source, test]
end

namespace 'c8-common' do
  p = project do |p|
    include_directory p, 'src/c8-common/errors.hpp', Dir['src/c8-common/errors/*.hpp']
    include_directory p, 'src/c8-common/type_traits.hpp', Dir['src/c8-common/type_traits/*.hpp']
    include_directory p, 'src/c8-common.hpp', Dir['src/c8-common/*.hpp'] + %w[src/c8-common/errors.hpp
                                                                              src/c8-common/type_traits.hpp]

    p.flags << $flags
    p.flags << %w[-Isrc]

    p.configure :install_c8_common do |t|
      t.apt_install 'libsqlite3-dev'
    end

    p.pkg_config 'sqlite3'

    p.library 'lib/libc8-common.a' do |t|
      t.sources << Dir['src/c8-common/**/*.cpp']
    end

    p.executable 'bin/c8-common-ut' do |t|
      t.flags << %w[-Itest]
      t.link_flags << %w[-pthread -lgtest -lgmock]
      t.sources << Dir['test/c8-common/**/*.cpp']
    end

    desc 'Generates new error in given library (default lib: c8-common)'
    task(:error, %i[name lib]) do |_t, args|
      name = args[:name]
      lib = args[:lib] || 'c8-common'

      gen = c8_common_errors_new(name, { 'string' => "\"#{name}\"" }, lib: lib)

      task('error_exec' => Names[gen])

      Rake::Task['error_exec'].invoke
    end
  end

  multitask 'all' => [*p.requirements]
  multitask 'main' => [*p.requirements('lib/libc8-common.a')]

  multitask 'test' => [*p.requirements('bin/c8-common-ut')] do
    sh 'bin/c8-common-ut'
  end

  task 'clean' do
    p.clean
  end
end
