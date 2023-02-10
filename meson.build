project('mcoral', 'c', subproject_dir: 'lib', default_options: [
	'picolibc:multilib=false',
])

#add_project_arguments('-Wno-discarded-qualifiers', language: 'c')

sources = files([
])

deps = []
deps += dependency('freertos', fallback: ['freertos', 'freertos_dep'])
deps += dependency('start', fallback: ['start', 'start_dep'])

link_args = []
#link_args += '-Wl,--library-path=../'
#link_args += '-Wl,-Ttiva123gxl.ld'
#link_args += '-Wl,-zmax-page-size=0x2000'
##link_args += '-Wl,--gc-sections'
#link_args += '-Wl,-Map=map.map'
#link_args += '-uexception_table'
#link_args += '-nostartfiles'
#link_args += '-nostdlib'
#link_args += '-lgcc'

#exec_name = '@0@-@1@'.format(meson.project_name(), e70_prj.get_variable('slot'))
exec_name = 'tpu'
exec = executable(exec_name + '.elf', sources,
	dependencies: deps,
	sources: sources,
	link_args: link_args,
)

custom_target('size', output: ['dummy.txt'], command: [find_program('arm-none-eabi-size'), exec.full_path()], depends: exec, build_by_default: true)

bin_name = '@0@.bin'.format(exec_name)
custom_target('bin', output: bin_name, command: [find_program('arm-none-eabi-objcopy'), '-Obinary', exec.full_path(), bin_name], depends: exec, build_by_default: true)


#ifdef DEBUG
#CFLAGS+=-g -D DEBUG -O0
#else
#CFLAGS+=-Os
#endif

