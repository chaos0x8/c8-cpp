namespace(:generated) {
  directories = Dir['src/*'].select { |dir|
    File.directory?(dir)
  }.collect { |dir|
    Generate.includeDirectory(dir)
  }

  default = Invoke.new { |t|
    t.name = 'default'
    t.requirements << directories
  }
}
