project('RWD', 'cpp')
add_global_arguments('-std=c++11', language : 'cpp')
qt = dependency('qt4', modules : ['Core', 'Gui', 'Xml'])
eigen = dependency('eigen3')
boost = dependency('boost', modules : 'utility')

executable(
  'RWD',
  [
    'src/RWDFramework/main.cpp',
    'src/RWDFramework/ModelConfiguration.cpp'
  ],
  dependencies : [
    boost,
    eigen,
    qt
  ],
  link_args : '-ldl'
)

subdir('plugins')
