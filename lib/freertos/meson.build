project('freertos', 'c')

conf_data = configuration_data()
conf_data.set('configTOTAL_HEAP_SIZE', get_option('total_heap_size'))
conf_data.set('configTICK_RATE_HZ', get_option('tick_rate_hz'))
conf_data.set('configCPU_CLOCK_HZ', get_option('cpu_clock_hz'))

sdir = 'upstream/'

freertos_inc = ['upstream/include', '.']

freertos_src = files([
  'src/heap_useNewlib_NXP.c',
  'src/app_callbacks.c',
  'src/multicore.c',
  sdir + 'event_groups.c',
  sdir + 'list.c',
  sdir + 'portable/GCC/ARM_CM4F/port.c',
  sdir + 'queue.c',
  sdir + 'stream_buffer.c',
  sdir + 'tasks.c',
  sdir + 'timers.c',
  sdir + 'croutine.c',
  sdir + 'event_groups.c',
  sdir + 'list.c',
  sdir + 'queue.c',
  sdir + 'tasks.c',
  sdir + 'timers.c',
  ])

#conf_data.set('configSUPPORT_DYNAMIC_ALLOCATION', 1)
#conf_data.set('NUM_LOCKS', get_option('num_locks'))
#configure_file(output : 'freertos_config.h', configuration: conf_data)

freertos_deps = []
freertos_deps += dependency('start', fallback: ['start', 'start_dep'])

freertos_inc += sdir + 'portable/GCC/ARM_CM4F'
freertos_inc += 'src'

freertos_inc = include_directories(freertos_inc)

freertos_lib = static_library('freertos',
  include_directories : freertos_inc,
  sources : freertos_src,
  dependencies: freertos_deps,
  )

freertos_dep = declare_dependency(
  include_directories : freertos_inc,
  link_with : freertos_lib,
  )

freertos_dep_whole = declare_dependency(
  include_directories : freertos_inc,
  link_whole : freertos_lib,
  )
