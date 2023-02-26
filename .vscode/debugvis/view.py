import io
import lldb
import debugger

def iterArray(arr):
    viewType = lldb.target.FindFirstType('UIView').GetPointerType()

    address = arr.GetChildMemberWithName('values').GetValueAsUnsigned()
    itemSize = arr.GetChildMemberWithName('valueSize').GetValueAsUnsigned()
    capacity = arr.GetChildMemberWithName('capacity').GetValueAsUnsigned()

    #print("Address: " + str(address))
    #print("Item size: " + str(itemSize))

    if (itemSize < 1):
        return ''

    # err = lldb.SBError()
    # membuf = lldb.process.ReadMemory(address, itemSize, err)

    markup = ''
    for i in range(0, capacity):
        child = lldb.target.CreateValueFromAddress("child", lldb.SBAddress(address + (i * itemSize), lldb.target), viewType)
        markup += drawView(child)
    

    return markup

def drawView(view):
    bg = view.GetChildMemberWithName('backgroundColor')
    frame = view.GetChildMemberWithName('frame')
    origin = frame.GetChildMemberWithName('origin')
    size = frame.GetChildMemberWithName('size')

    #print(bg)
    #print(origin)
    #print(size)
    
    style = """
    position: absolute;
    background-color: {bg};
    left: {x}px;
    top: {y}px;
    width: {w}px;
    height: {h}px;
    border-radius: {br}px;
    """.format(
        bg="rgba({}, {}, {}, {})".format(
            bg.GetChildMemberWithName('r').GetValueAsSigned(),
            bg.GetChildMemberWithName('g').GetValueAsSigned(),
            bg.GetChildMemberWithName('b').GetValueAsSigned(),
            bg.GetChildMemberWithName('a').GetValueAsSigned() / 255
        ),
        x=origin.GetChildMemberWithName('x').GetValueAsSigned(),
        y=origin.GetChildMemberWithName('y').GetValueAsSigned(),
        w=size.GetChildMemberWithName('width').GetValueAsSigned(),
        h=size.GetChildMemberWithName('height').GetValueAsSigned(),
        br=view.GetChildMemberWithName('cornerRadius').GetValueAsSigned(),
    ).replace('\n', '')

    style = ' '.join(style.split())

    #print(style)
    subviews = view.GetChildMemberWithName('subviews')
    return '<div style="{}">{}</div>'.format(style, iterArray(subviews))

def draw_views(v):
    view = debugger.unwrap(v)
    
    # iterArray(subviews)
    document = '<html><body style="position: relative; margin: 16px">' + drawView(view) + '</body></html>'
    #print(document)
    debugger.display_html(document, position=2, title='PanosUI Preview ({}{})'.format(view.GetDisplayTypeName(), view.GetName()))