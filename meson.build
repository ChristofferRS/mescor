project('mcoral', 'c', subproject_dir: 'lib', default_options: [
	'picolibc:multilib=false',
])

#add_project_arguments('-Wno-discarded-qualifiers', language: 'c')

sources = files([
])

deps = []
deps += dependency('freertos', fallback: ['freertos', 'freertos_dep'])
deps += dependency('start', fallback: ['start', 'start_dep'])
deps += dependency('libc', fallback: ['picolibc', 'picolibc_dep'])


common_link_flags = []
common_link_flags += '--library-path=../'
common_link_flags += '-Xlinker'
common_link_flags += '--defsym=__use_shmem__=1'
common_link_flags += '-Wl,--gc-sections'
common_link_flags += '-Wl,-Map=map.map'
common_link_flags += '-uexception_table'
common_link_flags += '-nostdlib'
common_link_flags += '-lgcc'

#cm7_link_flags += '-Tcm7.ld'

cm4_c_flags = []
cm4_c_flags += '-mcpu=cortex-m4'
cm4_c_flags += '-mfloat-abi=hard'
cm4_c_flags += '-mfpu=fpv4-sp-d16'
cm4_c_flags += '-DNDEBUG'

cm4_link_flags = []
cm4_link_flags += '-mcpu=cortex-m4'
cm4_link_flags += '-mfloat-abi=hard'
cm4_link_flags += '-mfpu=fpv4-sp-d16'
#cm4_link_flags += '-Tcm4.ld'


link_args = common_link_flags
c_args = []

#exec_name = '@0@-@1@'.format(meson.project_name(), e70_prj.get_variable('slot'))
exec_name = 'tpu'
exec = executable(exec_name + '.elf', sources,
	dependencies: deps,
	sources: sources,
	link_args: link_args,
	c_args: c_args,
)

#custom_target('size', output: ['dummy.txt'], command: [find_program('arm-none-eabi-size'), exec.full_path()], depends: exec, build_by_default: true)
#
#bin_name = '@0@.bin'.format(exec_name)
#custom_target('bin', output: bin_name, command: [find_program('arm-none-eabi-objcopy'), '-Obinary', exec.full_path(), bin_name], depends: exec, build_by_default: true)
#
#
##ifdef DEBUG
##CFLAGS+=-g -D DEBUG -O0
##else
##CFLAGS+=-Os
##endif
#
