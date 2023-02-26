#!/bin/python3

import panosui_c

class UIWindow():
    __backing__ = None

    def __init__(self, frame):
        self.__backing__ = panosui_c.UIWindowCreate(frame)
    
    def show(self):
        panosui_c.UIWindowShow(self.__backing__)
    
    @property
    def title(self):
        return ""

    @title.setter
    def title(self, title):
        panosui_c.UIWindowSetTitle(self.__backing__, title)

class UIApplicationDelegate():
    __delegate__ = None

    def __init__(self):
        self.__delegate__ = panosui_c.UIApplicationDelegate(panosui_c.UIApplicationDelegate._fields_[0][1](self.__did_finish_launching__))

    def __did_finish_launching__(self, a):
        self.did_finish_launching()
    
    def did_finish_launching(self):
        pass

class UIApplication():
    @staticmethod
    def main(delegate):
        panosui_c.UIApplicationMain(delegate.__delegate__)