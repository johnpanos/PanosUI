test_inc = ['../include']

test_UIApplication = executable(
    'test_UIApplication',
    'test_UIApplication.c',
    include_directories : test_inc,
    link_with: panosuilib
)
test('UIApplication', test_UIApplication)

test_UIView = executable(
    'test_UIView',
    'test_UIView.c',
    include_directories : test_inc,
    link_with: panosuilib
)
test('UIView', test_UIView)

test_UILayer = executable(
    'test_UILayer',
    'test_UILayer.c',
    include_directories : test_inc,
    link_with: panosuilib
)
test('UILayer', test_UILayer)