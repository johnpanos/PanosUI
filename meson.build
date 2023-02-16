project('PanosUI', ['c', 'cpp'], default_options: ['cpp_std=c++17'])

deps = []

src = [
    'src/UIApplication.c',
    'src/UIAnimation.c',
    'src/UIAnimation_timing.c',
    'src/UIView.c',
    'src/UILayer.c',
    'src/UIWindowController.c',
    'src/UIEventResponder.c',
    'src/UIWindow.c',
    'src/UIColor.c',
    'src/UIRect.c',
    'src/UIPoint.c',
    'src/shared/Array.c'
]

if host_machine.system() == 'linux'
    src += 'src/linux/platform.c'
    src += 'src/linux/globals.c'
    src += 'src/linux/pointer.c'
    src += 'src/linux/egl.c'
    src += 'src/linux/graphics.cpp'
    src += 'src/linux/deps/linux-dmabuf_unstable-v1.c'
    src += 'src/linux/deps/ext-blur-mask-unstable-v1.c'
    src += 'src/linux/deps/xdg-shell.c'

    src += 'src/linux/UIWindow_linux.c'

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


skia = declare_dependency(link_args : ['-L/home/john/Developer/skia/out/Debug', '-lskia'],
                               include_directories : ['/home/john/Developer/skia'])

deps += skia

panosuilib = shared_library('panosui',
                        src,
                        include_directories : ['src', '../', '/home/john/Developer/skia/'],
                        c_args: ['-O0'],
                        cpp_args: ['-O0'],
                        dependencies : deps,
                        install : true)
install_headers([
    'include/Array.h',
    'include/PanosUI.h',
    'include/UIAnimation.h',
    'include/UIApplication.h',
    'include/UIColor.h',
    'include/UIEvent.h',
    'include/UIEventResponder.h',
    'include/UIGeometry.h',
    'include/UILayer.h',
    'include/UIView.h',
    'include/UIWindow.h',
    'include/UIWindowController.h'
])

executable('panos-client', 'examples/minimal.c', include_directories : ['include'], link_with : panosuilib)
executable('layer', 'examples/layer.c', include_directories : ['include'], link_with : panosuilib)
executable('cpp-example', 'examples/cpp.cpp', include_directories : ['include', 'cpp'], link_with : panosuilib)

subdir('tests')

pkg = import('pkgconfig')
pkg.generate(panosuilib)