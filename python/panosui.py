from panosui_c import *

class UIWindow():
    __backing__ = None

    def __init__(self, frame):
        self.__backing__ = UIWindowCreate(frame)
    
    def show(self):
        UIWindowShow(self.__backing__)
    
    @property
    def title(self):
        return ""

    @title.setter
    def title(self, title):
        UIWindowSetTitle(self.__backing__, title)