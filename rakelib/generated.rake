namespace(:generated) {
  directories = Dir['src/*'].select { |dir|
    File.directory?(dir)
  }.collect { |dir|
    Generate.includeDirectory(dir)
  }

  C8.multitask(default: Names[directories])
}
