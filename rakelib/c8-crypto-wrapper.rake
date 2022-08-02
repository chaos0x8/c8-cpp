namespace 'c8-crypto-wrapper' do
  p = project do |p|
    p.flags << $flags << %w[-Isrc]
    p.link 'lib/libc8-common.a'

    p.configure :configure_c8_crypto_wrapper do |t|
      t.apt_install 'libcrypto++-dev'
    end

    p.pkg_config 'libcrypto++'

    p.library 'lib/libc8-crypto-wrapper.a' do |t|
      t.sources << Dir['src/c8-crypto-wrapper/**/*.cpp']
    end

    p.executable 'bin/c8-crypto-wrapper-ut' do |t|
      t.flags << %w[-Itest]
      t.link_flags << %w[-pthread -lgtest -lgmock]
      t.sources << Dir['test/c8-crypto-wrapper/**/*.cpp']
    end
  end

  multitask 'all' => [*p.requirements]
  multitask 'main' => [*p.requirements('lib/libc8-crypto-wrapper.a')]

  multitask 'test' => [*p.requirements('bin/c8-crypto-wrapper-ut')] do
    sh 'bin/c8-crypto-wrapper-ut'
  end

  task 'clean' do
    p.clean
  end
end
