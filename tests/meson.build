test_inc = ['../include']

test_UIApplication = executable(
    'test_UIApplication',
    'test_UIApplication.c',
    include_directories : test_inc,
    link_with: panosuilib
)
test('UIApplication', test_UIApplication)

test_UIApplication = executable(
    'test_UIView',
    'test_UIView.c',
    include_directories : test_inc,
    link_with: panosuilib
)
test('UIView', test_UIApplication)

test_UIApplication = executable(
    'test_UIViewController',
    'test_UIViewController.c',
    include_directories : test_inc,
    link_with: panosuilib
)
test('UIViewController', test_UIApplication)