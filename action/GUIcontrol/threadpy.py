
import time
from PyQt4 import QtCore, QtGui

class WorkThread(QtCore.QThread):
    def __init__(self):
        QtCore.QThread.__init__(self)
 
    def run(self):
        while True:
            time.sleep(0.1) # artificial time delay
            self.emit( QtCore.SIGNAL('update(QString)'), "from work thread " )
#            print "thread"
        return

class WorkThread2(QtCore.QThread):
    def __init__(self):
        QtCore.QThread.__init__(self)
 
    def run(self):
        for i in range(100):
			time.sleep(0.1) # artificial time delay
#			print "Thread terminada"
        self.emit( QtCore.SIGNAL('update(QString)'), "work thread " )
        print "Thread terminada"
        return
