project('RWD', 'cpp')
add_global_arguments('-std=c++11', language : 'cpp')
qt = dependency('qt4', modules : ['Core', 'Gui', 'Xml'])
eigen = dependency('eigen3')
boost = dependency('boost', modules : 'utility', version : '>=1.58', required : false)

if boost.found()
  odeint_inc = []
else
  odeint_sp = subproject('odeint')
  odeint_inc = odeint_sp.get_variable('odeint_inc')
endif

executable(
  'RWD',
  [
    'src/RWDFramework/main.cpp',
    'src/RWDFramework/ModelConfiguration.cpp'
  ],
  include_directories : odeint_inc,
  dependencies : [
    boost,
    eigen,
    qt
  ],
  link_args : '-ldl'
)

subdir('plugins')
