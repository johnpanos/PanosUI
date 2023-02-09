project('PanosUI', ['c', 'cpp'], default_options: ['cpp_std=c++17'])

deps = []

src = [
    'src/UIApplication.c',
    'src/UIView.c',
    'src/UIWindowController.c',
    'src/UIWindow.c',
    'src/UIColor.c',
    'src/UIRect.c',
    'src/shared/Array.c'
]

if host_machine.system() == 'linux'
    src += 'src/linux/platform.c'
    src += 'src/linux/pointer.c'
    src += 'src/linux/egl.c'
    src += 'src/linux/graphics.cpp'
    src += 'src/linux/deps/linux-dmabuf_unstable-v1.c'
    src += 'src/linux/deps/xdg-shell.c'

    egl = dependency('egl')
    glesv2 = dependency('glesv2')
    wayland_egl = dependency('wayland-egl')
    wayland_client = dependency('wayland-client')
    wayland_cursor = dependency('wayland-cursor')

    deps += egl
    deps += glesv2
    deps += wayland_egl
    deps += wayland_client
    deps += wayland_cursor
    deps += dependency('fontconfig')
    deps += dependency('libpng')
    deps += dependency('libjpeg')
    deps += dependency('glx')
endif

if host_machine.system() == 'darwin'
    src += 'src/macos/platform.m'

    cocoa = dependency('Cocoa')
    
    deps += cocoa
endif

if host_machine.system() == 'windows'
    src += 'src/win/platform.cpp'
endif


skia = declare_dependency(link_args : ['-L/home/john/Developer/skia/out/Release', '-lskia'],
                               include_directories : ['/home/john/Developer/skia'])

deps += skia

panosuilib = shared_library('panosui',
                        src,
                        include_directories : ['src', '../', '/home/john/Developer/skia/'],
                        c_args: ['-O4', '-flto'],
                        cpp_args: ['-O4'],
                        link_args: ['-fvtable-gc', '-fdata-sections', '-ffunction-sections', '-Wl,--gc-sections'],
                        dependencies : deps,
                        install : true)

executable('panos-client', 'examples/minimal.c', include_directories : ['include'], link_with : panosuilib)
executable('cpp-example', 'examples/cpp.cpp', include_directories : ['include', 'cpp'], link_with : panosuilib)

subdir('tests')