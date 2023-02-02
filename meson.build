project('PanosUI', ['c', 'cpp'], default_options: ['cpp_std=c++17'])

deps = []

src = [
    'src/UIApplication.c',
    'src/UIView.c',
    'src/UIViewController.c',
    'src/UIWindow.c'
]

if host_machine.system() == 'linux'
    src += 'src/linux/platform.c'
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
endif

if host_machine.system() == 'darwin'
    src += 'src/macos/platform.m'

    cocoa = dependency('Cocoa')
    
    deps += cocoa
endif

if host_machine.system() == 'windows'
    src += 'src/win/platform.cpp'
endif

panosuilib = static_library('panosui',
                        src,
                        include_directories : ['src'],
                        dependencies : deps,
                        install : true)

executable('panos-client', 'examples/minimal.c', include_directories : ['include'], link_with : panosuilib)
executable('cpp-example', 'examples/cpp.cpp', include_directories : ['include', 'cpp'], link_with : panosuilib)

subdir('tests')