# code from http://www.chrisumbel.com/article/windows_services_in_python
import win32service
import win32serviceutil
import win32event

class PySvc(win32serviceutil.ServiceFramework):
    # you can NET START/STOP the service by the following name  
    _svc_name_ = "PySvc"  
    # this text shows up as the service name in the Service  
    # Control Manager (SCM)  
    _svc_display_name_ = "Python Test Service"  
    # this text shows up as the description in the SCM  
    _svc_description_ = "This service writes stuff to a file"  
      
    def __init__(self, args):  
        win32serviceutil.ServiceFramework.__init__(self, args)  
        # create an event to listen for stop requests on  
        self.hWaitStop = win32event.CreateEvent(None, 0, 0, None)
      
    def SvcDoRun(self):
        """ core logic of the service """
        self.begin()
        rc = None  

        # if the stop event hasn't been fired keep looping  
        while rc != win32event.WAIT_OBJECT_0:  
            # block for 5 seconds and listen for a stop event  
            rc = win32event.WaitForSingleObject(self.hWaitStop, 5000)  

        self.end()
    
    def SvcStop(self):  
        """ called when we're being shut down """
        # tell the SCM we're shutting down  
        self.ReportServiceStatus(win32service.SERVICE_STOP_PENDING)  
        # fire the stop event  
        win32event.SetEvent(self.hWaitStop)  
      
    def begin(self):
        pass
      
    def end(self):
        pass

def main(py):
    win32serviceutil.HandleCommandLine(py)

if __name__ == '__main__':  
    win32serviceutil.HandleCommandLine(PySvc)
